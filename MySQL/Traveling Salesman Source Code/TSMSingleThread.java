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
       
    public static void main (String args[])
    {
        TSM tsm = new TSM();
        boolean changeLeft = true;
        boolean changeRight = true;
        int bestTourFound = Integer.MAX_VALUE;
        int pruned = 0;                         //number of pruned nodes
        float rootLowerBound = 0;
        Node root = new Node(tsm.getNumCities(), tsm.getNumCities());
        root.initializeConstraint();
        root.computeLowerBound(tsm);
        rootLowerBound = root.getLowerBound();
        System.out.println("Lower bound of root node is " + root.getLowerBound());
        tsm.tree.add(root);
        
        while (tsm.tree.isEmpty() == false)
        {
            Node left = new Node(tsm.getNumCities(), tsm.getNumCities());
            Node right = new Node(tsm.getNumCities(), tsm.getNumCities());
            left.initializeConstraint(tsm.tree.element());
            right.initializeConstraint(tsm.tree.element());
            tsm.tree.remove();  //remove the head after the children are created
            left.addConstraint(1);
            right.addConstraint(-1);
            
            while (changeLeft == true)
            {
                changeLeft = left.addEdgesNotAllowed();
                changeLeft = left.addNecessaryEdges();
            }
            left.computeLowerBound(tsm);
            
            while (changeRight == true)
            {
                changeRight = left.addEdgesNotAllowed();
                changeRight = left.addNecessaryEdges();
            }
            
            right.computeLowerBound(tsm);
            
            if (left.isTour() == true)
            {
                left.calcTourCost(tsm);
                if (left.getTourCost() < bestTourFound)
                {
                    bestTourFound = left.getTourCost();
                    System.out.println("Best tour found is " + bestTourFound);
                    for (int i = 0; i <= left.getTour().length - 1; i++)
                        System.out.print(left.getTour()[i]);
                    System.out.println();
                }
            }
            else
            {
                /*if the lowerbound is less than the best tour found so far,
                  this node still needs to be expanded.  The reason the
                  lower bound is checked against the lower bound of the root,
                  is because no node can have a lower bound smaller than the
                  root.  If the lower bound of the child is less than the lower
                  bound of the root, the lower bound did was not calcuated
                  taking two edges incident to each node*/
                if (left.getLowerBound() < bestTourFound && left.getLowerBound() >= rootLowerBound)
                {
                    tsm.tree.add(left);
                    System.out.println("Lower bound of left node is " + left.getLowerBound());
                }
                else
                    System.out.println("Pruned nodes is " + ++pruned);
            }
          
            if (right.isTour() == true)
            {
                right.calcTourCost(tsm);
                if (right.getTourCost() < bestTourFound)
                {
                    bestTourFound = right.getTourCost();
                    System.out.println("Best tour found is " + bestTourFound);
                    for (int i = 0; i <= right.getTour().length - 1; i++)
                        System.out.print(right.getTour()[i]);
                    System.out.println();
                }
            }
            else
            {
                if (right.getLowerBound() < bestTourFound && right.getLowerBound() >= rootLowerBound)
                {
                    System.out.println("Lower bound of right node is " + right.getLowerBound());
                    tsm.tree.add(right);
                }
                else
                    System.out.println("Pruned nodes is " + ++pruned);
            }
            
            changeLeft = true;
            changeRight = true;
        }
    }
}
