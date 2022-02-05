import socket
import logging
from random import randint
from time import sleep

logging.basicConfig(
    format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)

port = 42069
adresa = '198.10.0.2'
server_address = (adresa, port)
mesaje = ["Salut", "Imi plac gainile", "Piept de pui",
          "Lapte", "Michael Jordan", "Butelie?", "mooscles"]
lungime_mesaje = len(mesaje) - 1

while True:

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM,
                         proto=socket.IPPROTO_TCP)

    try:
        logging.info('Handshake cu %s', str(server_address))
        sock.connect(server_address)
        sock.send(mesaje[randint(0, lungime_mesaje)].encode('utf-8'))
        data = sock.recv(1024)
        logging.info('Content primit: "%s"', data)
        sock.close()
        sleep(2)
    except Exception as e:
        logging.error(e)
