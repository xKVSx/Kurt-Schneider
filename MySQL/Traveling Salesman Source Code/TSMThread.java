
package tsm;


public class TSMThread implements Runnable
{
     boolean changeLeft = true;
     boolean changeRight = true;
     int bestTourFound = Integer.MAX_VALUE;
     int pruned = 0;                         //number of pruned nodes
     float rootLowerBound = 0;
     TSM tsm;
     int counter = 0;
   
     TSMThread(TSM tsm, float rootLowerBound)
     {
         this.tsm = tsm;
         this.rootLowerBound = rootLowerBound;
     }
             
     public synchronized void grabNode(Node left, Node right)
     {
         left.initializeConstraint(tsm.tree.element());
         right.initializeConstraint(tsm.tree.element());
         tsm.tree.remove();  //remove the head after the children are created
         //increment counter
     }
     @Override
     public void run()
     {  
        //data structure to increment when a thread grabs something to the tree.
        while (tsm.tree.isEmpty() == false && counter == 0)
        {
            Node left = new Node(tsm.getNumCities(), tsm.getNumCities());
            Node right = new Node(tsm.getNumCities(), tsm.getNumCities());
            grabNode(left, right);
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
            //decrement counter (protected)
       }
     }
}
