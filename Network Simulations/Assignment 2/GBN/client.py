import socket
import select
from sender import Sender
from receiver import Receiver

# Function to handle client operations
def client():
    # define server ip address
    SERVER_IP='127.0.0.1'
    # define server port address
    SERVER_PORT=12345

    # start the client socket
    with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as client:

        client.connect((SERVER_IP, SERVER_PORT))

        # recieve connection acknowledgement from server
        msg =  client.recv(1024).decode()  
        print("From Server :" , msg, end='')

        # take the client name as input and send it to server
        name=input()

        client.sendall (bytes(name,'UTF-8'))

        # get client port number from server
        address = client.recv(1024).decode()
        
        senderAddress = int(address)

        # Loop until client wants to go offline
        while(True):
            print('\nClient Name - ' + name + ' | You can 1.Send data 2.Receive data 3.Leave\n')
            choice=int(input('Enter option : '))

            if(choice==1):
                client.send(str.encode("request for sending"))
            elif(choice!=2):
                client.send(str.encode("close"))
                break

            # initialize input and output event generators
            inputs=[client]
            output=[]

            # wait until any input/output event or timeout occurs
            readable,writable,exceptionals=select.select(inputs,output,inputs,3600)
            
            # if input event is generated(any data/signal came from server), handle it
            for s in readable:
                # Receive and decode the data
                data=s.recv(1024).decode()

                # If no other client is connected with server, cancel sending request
                if(data=="No client is available"):
                    print(data)
                    break

                # if this client got sending permission from server
                elif(choice == 1):

                    # data file name where data is stored
                    file_name="data.txt"

                    # receive available receiver list from server
                    receiver_list=data.split('$')

                    # print the list and choose one of them for data transfer
                    print("\nAvailable clients----->")
                    for index in range(0,len(receiver_list)):
                        print((index+1),'. ',receiver_list[index])
                    choice=int(input('\nEnter your choice : '))
                    choice-=1

                    # ensure that the choice is valid
                    while(choice not in range(0,(len(receiver_list)))):
                        choice=int(input('Correctly input your choice : '))
                        choice-=1

                    #notify server about the choice
                    s.send(str.encode(str(choice)))

                    # get receiver port from server
                    receiverAddress = int(s.recv(1024).decode())

                    # initialize sender object
                    my_sender=Sender(client,name,senderAddress,receiver_list[index],receiverAddress,file_name)
                    
                    # start transmission (using sender object)
                    my_sender.transmit()

                    # set and print notification from server about data transfer complition
                    data=s.recv(1024)
                    data=data.decode()
                    print(data)

                # if this client got receiving request
                else:
                    # print the receiver starting status
                    print('Receiving data ...')

                    # file name where received data will be stored
                    file_name = "test.txt"
                    
                    # initialize receiver object
                    receiverAddress = int(data)
                    
                    s.send (bytes("start", 'utf-8'))
                    my_receiver=Receiver(client,name,senderAddress,receiverAddress,file_name)
                    
                    # start data receiving through receiver object
                    my_receiver.startReceiving()
            
            # if no data sent/received for an hour, again ask for user options(loop again)
            if not (readable or writable or exceptionals):
                continue


if __name__=='__main__':
    client()    