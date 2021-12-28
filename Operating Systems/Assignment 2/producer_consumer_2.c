#include <stdio.h>
/* for shm_* and mmap() */
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
/* for getpid() */
#include <unistd.h>
/* exit() */
#include <stdlib.h>
/* for sem_* functions */
#include <sys/stat.h>
#include <semaphore.h>
/* for seeding time() */
#include <time.h>
/* for wait function */
#include <sys/wait.h>

/* name of the semaphore */
#define SEMOBJ_NAME "/mutex"

/* maximum number of seconds to sleep between each loop operation */
#define MAX_SLEEP_SECS 3

/* maximum buffer size */
#define BUFFER_SIZE 50

/* defining the structure for buffer */
typedef struct {
   int in, out;
   int items[BUFFER_SIZE];       // shared circular queue
   int TOTAL;
   int produce_complete, consume_complete;
} BUFFER;

/* initialize the buffer */
void init_buffer (BUFFER *buf) {
   buf->in = 0;
   buf->out = 0;
   buf->TOTAL = 0;
   buf->produce_complete = 0;
   buf->consume_complete = 0;
   for (int i = 0; i < BUFFER_SIZE; i++)
      buf->items[i] = 0;
}

int main () {
   int p, c;
   int pitem, citem;
   int flag1, flag2;
   printf ("Enter no of producers: ");
   scanf ("%d", &p);
   pitem = (BUFFER_SIZE/p);
   printf ("Enter no of consumers: ");
   scanf ("%d", &c);
   citem = (BUFFER_SIZE/c);
   if (p & c == 0) {
      perror("No of consumers or producers cannot be zero");
      exit(1);
   }

   /* getting a new semaphore for the shared segment */
   sem_t *bufmutex = sem_open(SEMOBJ_NAME, O_CREAT | O_EXCL, S_IRWXU | S_IRWXG, 1);
   if (bufmutex == SEM_FAILED) {
      perror("In sem_open()");
      exit(1);
   }
   /* requesting the semaphore not to be held when completely unreferenced */
   sem_unlink(SEMOBJ_NAME);

   /* requesting the shared segment */    
   BUFFER* buf = (BUFFER *)mmap(NULL, sizeof(BUFFER), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
   if (buf == MAP_FAILED) {
      perror("In mmap()");
      exit(1);
   }
   fprintf(stderr, "Shared memory segment allocated correctly (%d bytes) at %p.\n", (int)sizeof(BUFFER), buf);
   
   /* initialize the buffer */
   init_buffer(buf);
   
   /* seeding the random number generator */
   // srand (time(NULL));

   /* create the producer manager process */
   int producer_manager = fork();

   if (producer_manager < 0) {
      perror("In producer manager process");
      exit(1);
   }

   else if (producer_manager == 0) {
      for (int i = 0; i < p; i++) {
         //sleep(1);
         //srand(time(NULL));

         // create a new producer
         int producer = fork();
         if (producer < 0) {
            perror("In producer process");
            exit(1);
         }
         else if (producer == 0) {
            int item_produced = 0;

            // loop until all item produced
            while (item_produced < pitem) {
               
               sem_wait (bufmutex);
               // produce item
               int produce = random() % 100 + 1;
               buf->items[buf->in] = produce;
               printf ("Producer %d produced %d at %d\n", getpid(), produce, buf->in);
               buf->in = ((buf->in + 1) % BUFFER_SIZE);
               sem_post (bufmutex);
               item_produced++;
               
            }
            exit (0);
         }
         
      }
      wait(NULL);
      buf->produce_complete = 1;
      exit(0);
   }

   /* create the consumer manager process */
   int consumer_manager = fork();

   if (consumer_manager < 0) {
      perror("In consumer manager process");
      exit(1);
   }
   else if (consumer_manager == 0) {
      for (int i = 0; i < c; i++) {
         // create a new consumer
         int consumer = fork();

         // wait for the semaphore for mutual exclusive access to the buffer
         if (consumer < 0) {
            perror("In consumer process");
            exit(1);
         }

         // wait if the buffer is empty
         else if (consumer == 0) {
            
            int item_consumed = 0;
            
            while (item_consumed < citem) {
               // consume item
                sem_wait (bufmutex);
                if(buf->in == buf->out)
                {
                    sem_post (bufmutex);
                    continue;
                }
                
                int consume = buf->items[buf->out];
                printf ("Consumer %d consumed %d at %d\n", getpid(), consume, buf->out);
                buf->out = (buf->out + 1) % BUFFER_SIZE;
                buf -> TOTAL += consume;
                
                // release the semaphore
                sem_post (bufmutex);
                item_consumed++;
            }
            exit (0);
    
         }
      }
      wait(NULL);
      buf->consume_complete = 1;
      exit (0);
   }
   wait (NULL);

   while(buf->produce_complete == 0 || buf->consume_complete == 0) {
       sleep(1);
   }

   /* freeing the reference to the semaphore */
   sem_close(bufmutex);
   printf ("TOTAL -> %d", buf->TOTAL);

   /* release the shared memory space */
   munmap(buf, sizeof(BUFFER));
}
