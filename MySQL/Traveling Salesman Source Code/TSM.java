/*Kurt Schneider
  CECS 590
  Homework 2*/

package tsm;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class TSM 
{
       private int numCities;
       private int costMatrix[][];
       Queue <Node> tree = new PriorityQueue <>(1, costCompare);
              
       File graph = new File ("C:\\Users\\xxx\\Desktop\\cities.txt"); 
       
       TSM()
       {
           try {
               Scanner sc = new Scanner(graph);
               if(sc.hasNextInt() == true)
               {
                   numCities = sc.nextInt();
                   costMatrix = new int [numCities][numCities];
               }
               for (int i = 0; i < numCities; i++)
               {
                   for (int j = 0; j < numCities; j++)
                   {
                      if (sc.hasNextInt() == true)
                      {
                           costMatrix[i][j] = sc.nextInt();
                           costMatrix[j][i] = costMatrix[i][j];
                      }
                   }
               }
           } catch (FileNotFoundException ex) {
               Logger.getLogger(TSM.class.getName()).log(Level.SEVERE, null, ex);
           }
       }
       
       int getNumCities()
       {
           return numCities;
       }
       
       int getCostMatrixValue(int row, int column)
       {
           return costMatrix[row][column];
       }
       
       static Comparator<Node> costCompare = new Comparator<Node>()
       {
            @Override
            public int compare(Node n1, Node n2) 
            {
                return (int) (n1.getLowerBound() - n2.getLowerBound());
            }
        };
       
    public static void main (String args[]) throws InterruptedException
    {
        long startTime = System.currentTimeMillis();    //returns the start time
        TSM tsm = new TSM();
        Thread[] t = new Thread[20];                     //number of threads
        float rootLowerBound = 0;
        Node root = new Node(tsm.getNumCities(), tsm.getNumCities());
        root.initializeConstraint();
        root.computeLowerBound(tsm);
        rootLowerBound = root.getLowerBound();
        System.out.println("Lower bound of root node is " + root.getLowerBound());
        tsm.tree.add(root);
       
        for(int i = 0; i < t.length; i++)
        {
            t[i] = new Thread(new TSMThread(tsm, rootLowerBound));
            t[i].start();
        }
        
        for (Thread t1 : t)    //main thread waits for worker threads to finish
               t1.join();
       
        long endTime = System.currentTimeMillis();      //returns end time
        
        System.out.println("Excecution time: " + (endTime - startTime));
    }
}
