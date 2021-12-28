# import socket module
import socket			

SERVER = "127.0.0.1"        # host interface of the server
PORT = 12345                # port on which the server listens

# create a new socket object
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client :
    client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # connect to server
    client.connect((SERVER, PORT))

    # a forever loop until we interrupt it or an error occurs
    while True:
        # recieve data from server
        in_data =  client.recv(1024)
        print("From Server :" ,in_data.decode())

        # take message from user
        msg = input('Say something: ')

        # send it to server
        client.sendall (bytes(msg,'UTF-8'))

        # if message is 'bye', terminate the connection
        if msg=='bye':
            break