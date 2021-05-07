package problem_7;

// import the necessary packages
import java.util.*;

class Store {
    private int item;
    private boolean empty;      // attribute to check if items are available to consume

    // default constructor
    Store () {
        item = 0;
        empty = true;
    }

    // parameterized constructor
    Store (int i) {
        item = i;
    }

    // synchronized getter method to be used by consumer
    synchronized int get () throws InterruptedException {
        // while there are no items to consume, consumer must wait
        while (empty) {
            wait();
        }
        empty = true;       // consumer has consumed the items
        notifyAll();
        Thread.sleep(1000);
        return item;
    }

    // synchronized setter method to be used by producer
    synchronized void set (int k) throws InterruptedException {
        // while there are items still left to consume, producer must wait
        while (!empty) {
            wait();
        }
        item = k;
        empty = false;      // items produced
        notifyAll();
        Thread.sleep(1000);
    }
}

class Producer implements Runnable {
    private Store s;

    // default constructor
    Producer () {
        s = null;
    }

    // parameterized constructor
    Producer (Store st) {
        s = st;
    }

    @Override
    public void run () {
        int i = 1;
        while (true) {
            try {
                s.set(i);
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("Producer produced - " + i);
            i++;
        }
    }
}

class Consumer implements Runnable {
    Store s;

    // default constructor
    public Consumer() {
        s = null;
    }

    // parameterized constructor
    public Consumer(Store st) {
        s = st;
    }

    @Override
    public void run() {
        while (true) {
            try {
                System.out.println("Consumer consumed - " + s.get());
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class ProducerConsumer {
    public static void main(String args[]) {
        Store s = new Store();
        Producer p = new Producer(s);       // creating Runnable instances on same Store object
        Consumer c = new Consumer(s);
        
        Thread pt = new Thread (p);         // creating producer thread
        Thread ct = new Thread (c);         // creating consumer thread

        System.out.println ("Start -->");
        
        pt.start();         // start the threads simultaneously
        ct.start();

        try {
            if (pt.isAlive())
                pt.join();
            if (ct.isAlive())
                pt.join();
        }

        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }   
}