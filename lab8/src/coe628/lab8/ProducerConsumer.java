package coe628.lab8;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Meet Patel
 */
public class ProducerConsumer {

    static final int BUFFER_SIZE = 1;
    private static Producer Producer;
    static Semaphore full = new Semaphore(0);
    static Semaphore empty = new Semaphore(BUFFER_SIZE);

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Queue q = new Queue(BUFFER_SIZE);
        Producer p = new Producer(q);
        Consumer c = new Consumer(q);
        p.start();
        c.start();

    }

    public static class Queue {

        private final int[] nums;
        private int rears;
        private int frnt;
        private final int size;

        public Queue(int size) {
            nums = new int[size + 1];
            frnt = 0;
            rears = 0;
            this.size = size;
        }

        public int get() {
            int value = nums[frnt];
            frnt = (frnt + 1) % size;
            return value;
        }

        public void put(int value) {
            nums[rears] = value;
            rears = (rears + 1) % size;
        }
    }

    private static class Producer extends Thread {

        private final Queue q;

        public Producer(Queue q) {
            this.q = q;
        }

        @Override
        public void run() {
            for (int i = 0; i < BUFFER_SIZE * 10; i++) {
                empty.down();
                System.out.println("Producing: " + i);
                q.put(i);
                try {
                    Thread.sleep((int) (Math.random() * 10));
                } catch (InterruptedException ex) {
                    Logger.getLogger(ProducerConsumer.class.getName()).log(Level.SEVERE, null, ex);
                }
                full.up();
            }
        }
    }

    private static class Consumer extends Thread {

        private final Queue q;

        public Consumer(Queue q) {
            this.q = q;
        }

        @Override
        public void run() {
            for (int i = 0; i < BUFFER_SIZE * 10; i++) {
                full.down();
                System.out.println("\t\tConsuming: " + q.get());
                q.get();
                try {
                    Thread.sleep((int) (Math.random() * 10));
                } catch (InterruptedException ex) {
                    Logger.getLogger(ProducerConsumer.class.getName()).log(Level.SEVERE, null, ex);
                }
                empty.up();
            }
        }
    }

}
