#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
    printf("---------------------CALLER----------------------\n");

    // name of fifo, to identify the fifo
    char *myfifo = "myfifo";
    remove (myfifo);

    // create the fifo
    if (mkfifo(myfifo, 0777) == -1) {
        perror("Fifo file could not be created\n");
        return 1;
    }

    // open it
    int fn = open(myfifo, O_WRONLY);
    char str[10];
    int len;
    while (1) {
        // take input of message
        printf("Enter message: ");
        scanf("%s", str);
        
        len = strlen(str) + 1;
        str[len - 1] = '\0';      
        
        // store the length of message
        if (write(fn, &len, sizeof(int)) == -1) {
            printf("Error while writing length of string\n");
            return 0;
        }
        
        // store the message
        if (write(fn, str, sizeof(char) * len) == -1) {
            printf("Error while writing string\n");
            return 0;
        }

        // terminate if message is end
        if (strcmp(str, "end") == 0) {
            break;
        }
        printf("Message has been sent\n");
    }
    printf("CONVERSATION ENDED\n");
    close(fn);
    return 0;
};
