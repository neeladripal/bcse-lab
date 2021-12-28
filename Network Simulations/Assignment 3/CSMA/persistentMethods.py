import random
import time

from channel import VULNERABLE_TIME

def onePersistent (monitor):
    ready=False
    while not ready:
        monitor.send(str.encode("status?"))
        received = monitor.recv(384).decode()
        if (received == "idle"):
            ready = True

def nonPersistent (monitor):
    ready=False
    while not ready:
        monitor.send(str.encode("status?"))
        received = monitor.recv(384).decode()
        if (received == "idle"):
            ready = True
        else:
            randomTime=random.randint(0,200)/100
            time.sleep(randomTime)

def pPersistent (monitor, p=0.1):
    ready=False
    while not ready:
        monitor.send(str.encode("status?"))
        received = monitor.recv(384).decode()
        if (received == "idle"):
            x = random.randint(0,100) / 100
            if x <= p:
                ready = True
            else:
                time.sleep(0.17)