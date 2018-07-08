/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package coe628.lab9;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Meet Patel
 */
public class Phil extends Thread{
   private int hungry=0;
   private int thinking=1;
   private int eating=2;
   private int states;
   private Semaphore semaphor=new Semaphore(2);
   private Semaphore sem_0=new Semaphore(1);
   private Phil phil[];
   private int lefts;
   private int rights;
   private int num;
   private int size;
   
   public Phil(int num){
       this.num=num;
   }
   
  public void init(Phil phil[]){
      states=hungry;
      size=phil.length;
       this.phil=phil;
       rights=(num)%phil.length;
       lefts=(num==phil.length ? 0:num);
        try {
            sem_0.down();
            

        } catch (InterruptedException ex) {
            Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
        }
       
       
  }
  public void eat(){
      System.out.println("Phil #"+num+"Eating..");
     states=eating;
  }
   
   public void getForks(){
       System.out.println("--Phil #"+num+"Hungry..");
       states=hungry;
       while(states==hungry){
           try {
               semaphor.down();
           } catch (InterruptedException ex) {
               Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
           }
           if(states==hungry&&phil[lefts].State()!=eating&&phil[rights].State()!=eating){
               eat();
               try {
                   sem_0.up();
               } catch (InterruptedException ex) {
                   Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
               }
               
           }
           try {
               semaphor.up();
               sem_0.down();
           } catch (InterruptedException ex) {
               Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
           }
           
       }
       
   }
   
   public void putForks(){
        try {
            System.out.println("Phil #"+num+"Done Eating..");
            semaphor.down();
        } catch (InterruptedException ex) {
            Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
        }
       states=thinking;
       if(phil[lefts].State()==hungry){
           phil[lefts].unlock();
       }
       if(phil[rights].State()==hungry){
           phil[rights].unlock();
       }
        try {
            semaphor.up();
        } catch (InterruptedException ex) {
            Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
        }
 
   }
   
   public int State(){
       return states;
   }
   public void think(){
       System.out.println("Phil #"+num+"Thinking..");
       states=thinking;
   }
   
   public void unlock(){
        try {
            sem_0.up();
        } catch (InterruptedException ex) {
            Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
        }
   }
  
   @Override
   public void run(){
        try {
        //think();
       getForks();
       
       
       putForks();
   
            Thread.sleep((int) (Math.random() * 10));
        } catch (InterruptedException ex) {
            Logger.getLogger(Phil.class.getName()).log(Level.SEVERE, null, ex);
        }
       
  
   }
    
}
