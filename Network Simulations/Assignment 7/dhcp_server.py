import socket
import random


class IPManager:
    """class to manage the IP address table"""
    IPdatabase = {}

    def __init__(self):
        """Fill the address table with some random IPs"""
        for i in range(20):
            ip = ""
            for j in range(3):
                ip += str(random.randint(0, 255))
                ip += "."
            ip += str(random.randint(0, 255))
            self.IPdatabase[ip] = False

    def getNewIP(self):
        """Get next free IP"""
        for ip in self.IPdatabase:
            if not self.IPdatabase[ip]:
                self.IPdatabase[ip] = True
                return ip
        return ""

    def releaseIP(self, ip):
        """Release a previous alloted IP"""
        if ip in self.IPdatabase:
            self.IPdatabase[ip] = False
            return True
        else:
            return False


serverIP = "127.0.0.1"
serverPort = 20001
bufferSize = 1024

ipMaster = IPManager()

# Create a datagram socket
with socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) as server:
    print("DHCP Server started")

    # set socket options, SO_REUSEADDR specifies that the local
    # address to which the socket binds can be reused
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # Bind to address and ip
    server.bind((serverIP, serverPort))
    print("Server socket binded to", serverPort)
    print("Server is waiting for client request...")

    # Listen for incoming datagrams
    while(True):
        try:
            # get a datagram from client
            bytesAddressPair = server.recvfrom(bufferSize)

            msgFromClient = bytesAddressPair[0]
            clientAddress = bytesAddressPair[1]

            clientIP, clientPort = clientAddress

            if msgFromClient:
                msgFromClient = msgFromClient.decode()

                # if the client requests a new IP
                if msgFromClient == "Give me IP":
                    # get the next available ip
                    newIP = ipMaster.getNewIP()
                    if newIP == "":
                        msgFromServer = "No IPs left"
                    else:
                        msgFromServer = "IP:" + newIP
                    # send it to client
                    server.sendto(str.encode(msgFromServer), clientAddress)
                    print(msgFromServer, "sent to client at", clientAddress)

                # if the client wants to release the ip
                else:
                    # receive the ip to be released
                    ipToRelease = msgFromClient
                    if (ipMaster.releaseIP(ipToRelease)):
                        print("IP:"+ipToRelease+" released")
                    else:
                        print("IP:"+ipToRelease+" not found")

        except:
            break

print("Server ended")
