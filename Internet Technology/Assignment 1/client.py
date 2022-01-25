import socket
import sys
from user import User


def generateQuery():
    """generate tokens to be sent to server"""

    # number of queries
    n = len(sys.argv)
    if (n < 4):
        raise Exception("Invalid input string")

    # get the server hostname and port
    serverHost = sys.argv[1]
    serverPort = int(sys.argv[2])
    username = sys.argv[3]
    yield (serverHost, serverPort, username)

    i = 4
    while (i < n):
        # get query or manager query
        func = sys.argv[i]
        if func == "get" or func == "viewall":
            str = " ".join((func, sys.argv[i + 1]))
            i += 2
        # put query
        elif func == "put":
            str = " ".join((func, sys.argv[i + 1], sys.argv[i + 2]))
            i += 3

        else:
            raise Exception("Invalid input string")
        yield str


# create a new socket object
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:
        # connection status with server
        connected = False

        for msg in generateQuery():
            if not connected:
                (server, port, username) = msg
                client.connect((server, port))
                # send it to server
                client.sendall(bytes(username, 'UTF-8'))
                in_data = client.recv(1024).decode()

                if in_data == "ok":
                    connected = True
                else:
                    break

            else:
                # send it to server
                client.sendall(bytes(msg, 'UTF-8'))
                in_data = client.recv(1024).decode()

                if in_data == "$":
                    pass
                elif in_data == "undefined":
                    print("")
                elif not in_data:
                    break
                else:
                    print(in_data)

    except Exception as ex:
        print(ex)
