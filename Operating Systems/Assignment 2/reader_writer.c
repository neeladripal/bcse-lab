#include <stdio.h>
#include <pthread.h>
// for sleep()
#include <unistd.h>
#include <stdlib.h>
// exit()
#include <time.h>

void *reader(void *);
void *writer(void *);

pthread_mutex_t wrtMutex;
pthread_mutex_t wrtWaitMutex;
pthread_mutex_t readMutex;

// shared buffer
int buffer = 0;

// number of writers currently writing
int wrt_count = 0;
// number of writers currently waiting
int wrt_wait_count = 0;
// number of readers currently reading
int read_count = 0;

int main(void)
{
    // initialize the mutex and variables
    pthread_mutex_init(&wrtMutex, NULL);
    pthread_mutex_init(&wrtWaitMutex, NULL);
    pthread_mutex_init(&readMutex, NULL);

    int ret1, ret2;

    // reader and writer id indices
    int wrtIndex = 0;
    int readIndex = 0;
    
    // take input of the number of reader and writers
    int r, w;
    printf ("Enter no of writers: ");
    scanf ("%d", &w);
    printf ("Enter no of readers: ");
    scanf ("%d", &r);
    
    // dynamically allocate the array of threads
    pthread_t *wrt_thread = (pthread_t*) malloc (w * sizeof (pthread_t*));
    pthread_t *read_thread = (pthread_t*) malloc (r * sizeof (pthread_t*));
    
    // dynamically allocate the array of thread ids
    int *idw = (int*) malloc (w * sizeof (int*));
    int *idr = (int*) malloc (r * sizeof (int*));
    
    // start the writer threads
    for (int wrtIndex = 0; wrtIndex < w; wrtIndex++) {
        idw[wrtIndex] = wrtIndex;
        ret1 = pthread_create(wrt_thread + wrtIndex, NULL, writer, (void *)&idw[wrtIndex]);
    }
    
    // start the reader threads
    for (int readIndex = 0; readIndex < r; readIndex++) {
        idr[readIndex] = readIndex;
        ret2 = pthread_create(read_thread + readIndex, NULL, reader, (void *)&idr[readIndex]);
    }
    
    // wait for the writers to complete
    for (int wrtIndex = 0; wrtIndex < w; wrtIndex++) {
        pthread_join(wrt_thread[wrtIndex], NULL);
    }
    
    // wait for the readers to complete
    for (int readIndex = 0; wrtIndex < w; wrtIndex++) {
        pthread_join(read_thread[readIndex], NULL);
    }
    
    // free space occupied by the dynamic arrays
    free (wrt_thread);
    free (read_thread);
    free (idw);
    free (idr);

    // destroy the mutex variables
    pthread_mutex_destroy(&wrtMutex);
    pthread_mutex_destroy(&wrtWaitMutex);
    pthread_mutex_destroy(&readMutex);

    return 0;
}

// writer thread
void *writer(void *index)
{
    // maximum number of trials attempted by a writer
    int trials = 5;

    // seed the random generator
    srand (time(NULL));

    while(trials--) {
        // acquire write wait lock
        pthread_mutex_lock(&wrtWaitMutex);
        wrt_wait_count += 1;
        // release write lock
        pthread_mutex_unlock(&wrtWaitMutex);
        
        // acquire write lock
        pthread_mutex_lock(&wrtMutex);
        // enter critical section

        pthread_mutex_lock(&wrtWaitMutex);
        wrt_wait_count -= 1;
        pthread_mutex_unlock(&wrtWaitMutex);
        
        wrt_count += 1;

        // write into buffer
        buffer = rand() % 100 + 1;
        printf ("Writer %d is writing %d to buffer {%d writer(s) writing, %d writer(s) waiting}\n", *(int*)index, buffer, wrt_count, wrt_wait_count);

        wrt_count -= 1;
        // exit critical section

        // release write lock
        pthread_mutex_unlock(&wrtMutex);

        // sleep for a random time interval
        sleep (2 + (rand() % 100) / 50.0);
    }

    return NULL;
}


// reader thread
void *reader(void *index)
{
    // maximum number of trials attempted by a reader
    int trials = 20;
    while(trials--) {
        // wait for the writers to finish
        while(wrt_count > 0 || wrt_wait_count > 0);
        pthread_mutex_lock(&readMutex);
        read_count++;
        pthread_mutex_unlock(&readMutex);

        sleep (1);
        // finish off with the reading process
        printf ("Reader %d is reading %d from buffer {%d reader(s) reading}\n", *(int*)index, buffer, read_count);

        pthread_mutex_lock(&readMutex);
        read_count--;
        pthread_mutex_unlock(&readMutex);
    }

    return NULL;
}