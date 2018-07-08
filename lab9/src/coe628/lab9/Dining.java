/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package coe628.lab9;

import java.util.Scanner;

/**
 *
 * @author Meet Patel
 */
public class Dining {
    
    public static void main(String[] args) {
        String ans="y";
        Scanner s= new Scanner(System.in);
        
        int numOfPhils=5;
        Phil phil[]=new Phil[5];
        for(int i=0;i<5;++i){
            phil[i]=new Phil(i);
        }
        for(int i=0;i<5;i++){
            phil[i].init(phil);
        }
        
        while(ans.contentEquals("y")){
            System.out.println("----------Loop Iteration");
            for(int i=0;i<5;i++){
           phil[i].run();
            }
            System.out.println("Continue Run?");
            ans=s.nextLine();
            
        }
        
        
    }
    
}
