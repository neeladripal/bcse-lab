import socket
import time

serverAddress = ("127.0.0.1", 20001)
bufferSize = 1024

# create a UDP socket at client side
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as client:

    # request IP from DHCP server
    msgFromClient = "Give me IP"
    client.sendto(str.encode(msgFromClient), serverAddress)

    # get the IP back from server
    bytesAddressPair = client.recvfrom(bufferSize)

    if bytesAddressPair:
        msgFromServer = bytesAddressPair[0].decode()

        # if an IP is available
        if msgFromServer != "No IPs found":
            ip = msgFromServer.split(":")[1]
            print("STATUS: Online [ IP:", ip, "]")
            while True:
                time.sleep(2)
                chr = input("Enter q to terminate: ")
                if chr == 'q' or chr == 'Q':
                    # while terminating, send back the IP to the server
                    client.sendto(str.encode(ip), serverAddress)
                    break

print("STATUS: Offline")
