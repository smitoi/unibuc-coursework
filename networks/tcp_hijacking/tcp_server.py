import socket
import logging
from random import randint

logging.basicConfig(
    format=u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level=logging.NOTSET)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM,
                     proto=socket.IPPROTO_TCP)

port = 42069
adresa = '0.0.0.0'
server_address = (adresa, port)
sock.bind(server_address)
logging.info("Serverul a pornit pe %s si portul portul %d", adresa, port)
sock.listen(5)

mesaje = ["Server zice HELLO!!1", "Jackson Michael",
          "Cocobranza", "Reksio", "Kretes", "Bolt", "Michael Jackson"]
lungime_mesaje = len(mesaje) - 1

try:
    while True:
        logging.info('Asteptam conexiui...')
        conexiune, address = sock.accept()
        logging.info("Handshake cu %s", address)
        data = conexiune.recv(1024)
        logging.info('Content primit: "%s"', data)
        conexiune.send(mesaje[randint(0, lungime_mesaje)].encode("utf-8"))
        conexiune.close()
except KeyboardInterrupt:
    sock.close()
