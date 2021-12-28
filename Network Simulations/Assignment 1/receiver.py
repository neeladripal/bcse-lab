# import socket module
import socket
import errorMechanisms as em			

SERVER = "127.0.0.1"        # host interface of the server
PORT = 12345                # port on which the server listens

# create a new socket object
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client :
    client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    try:
        # connect to server
        client.connect((SERVER, PORT))
        # recieve connection acknowledgement from server
        msg =  client.recv(1024).decode()  
        print("From Server :" , msg, end='')

        # confirm to begin
        confirmation = input()

        client.sendall (bytes(confirmation,'UTF-8'))

        if confirmation == "start":
            errMechanisms = ["VRC", "LRC", "CHECKSUM", "CRC"]
            crc8key = "111010101"
            crc4key = "10101"
            errObj = [em.VRC(), em.LRC(8), em.CheckSum(8), em.CRC(crc8key)]
            # a forever loop until we interrupt it or an error occurs
            while True:
                # recieve data from server
                codeword = client.recv(1024)

                # if connection is interrupted accidentally
                if not codeword:
                    break

                # receive the codeword from server
                codeword = codeword.decode()

                # if message is 'end', terminate the connection
                if codeword == 'end':
                    break
                
                ackword = ""

                codeword = codeword.split(" ")

                # check validity of codeword
                for i in range(4):
                    # print("From Server :" , codeword[i], errMechanisms[i])
                    if (errObj[i].checkCodeword(codeword[i])):
                        ackword += '0'
                        # print ("STATUS- PASS")
                    else:
                        ackword += '1'
                        # print ("STATUS- FAIL")
                    
                # print(ackword)

                # send validity ackword to server
                client.sendall (bytes(ackword,'UTF-8'))

            print ("Checking finished")

        else:
            print("Invalid confirmation message")

    except:
        print("Connection refused")
