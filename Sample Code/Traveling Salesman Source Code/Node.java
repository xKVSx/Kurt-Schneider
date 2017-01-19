/*Kurt Schneider
  CECS 590
  Homework 2*/

package tsm;

import java.util.BitSet;

public class Node 
{
    private float lowerBound;       //holds the lower bound of the node
    private int tourCost;           //holds the cost of the tour
    private int [] tour;
    private int rows, columns;      //holds the number of rows and columns
    private int [][] constraint;    /*adjacency matrix for the node.  A 0
                                      will represent an edge that can be used,
                                      a 1 will represent an edge that is required,
                                      and a -1 will represent an edge that is not
                                      allowed.*/
    private boolean isCycle = false;//set true if premature cycle is found.
    private BitSet bit;             //used to detect premature cycles.
    private int [] edgeCost;          /*This holds the values of the edges for
                                      calculating the lower bound. */
    private int usedEdges;

    Node (int rows, int columns)
    {
        this.rows = rows;
        this.columns = columns;
        constraint = new int[rows][columns];    //generate the matrix
        edgeCost = new int[columns];
        usedEdges = 0;
        tour = new int[rows];
    }
    
    public void initializeConstraint()
    {
        for(int row = 0;row <= rows - 1; row++)
        {
            for(int column = 0; column <= columns - 1; column++)
            {
                constraint[row][column] = 0;
                constraint[column][row] = 0;
            }
        }
    }
    
    public void initializeConstraint(Node node)
    {
        for(int row = 0; row <= rows - 1; row++)
        {
            for(int column = 0; column <= columns - 1; column++)
            {
                constraint[row][column] = node.constraint[row][column];
                constraint[column][row] = node.constraint[column][row];
            }
        }
    }
    
    public void addConstraint(int value)
    {
         for (int r = 0; r <= rows - 1; r++)
         {
            for (int c = 0; c <= columns - 1; c++)
            {
                if (r != c && constraint[r][c] == 0)
                {
                    constraint[r][c] = value;
                    constraint[c][r] = value;
                    return;
                }
            }
         }
        /* The value of the constraint is either 0, 1, or -1.  Since this is an
        undirected graph, if the constraint exist on edge x between node a and 
        node b, then it must also exist on edge x between node b and node a.*/
    }
    
    public boolean addEdgesNotAllowed()
    {
        boolean changed = false;
        
        for (int row = 0; row <= rows - 1; row++)
        {
            int edgesUsed = 0;
            for (int column = 0; column <= columns - 1; column++)
            {
                if (row != column && constraint[row][column] == 1)
                    edgesUsed = edgesUsed + 1;
                    //a node cannot have an edge to itself
            }
            if (edgesUsed >= 2)
            {
                for (int column = 0; column <= columns - 1; column++)
                {
                    if (row != column && constraint[row][column] == 0)
                    {
                        constraint[row][column] = -1;
                        constraint[column][row] = -1;
                        changed = true;
                    }
                    /*A node cannot have more than two edges incident to it.
                      If two edges are used, set the other edges as not allowed*/
                }
            }
        }
        
        /*This checks to see that if any edge currently allowed will cause a
          premature cycle.  The isCycle method determines if adding a currently
          allowed edge will create a cycle.  The usedNodes method counts how 
          many nodes have been used.  If a cycle is created before all the nodes
          have been used, then the cycle is premature.*/
        for (int row = 0; row <= rows - 1; row++)
            for (int column = 0; column <= columns - 1; column++)
            {
                if (row != column && isCycle(row, column) && usedNodes(bit) < rows)
                {
                    if (constraint[row][column] == 0)
                    {
                        constraint[row][column] = -1;
                        constraint[column][row] = -1;
                        changed = true;
                    }
                }
            }
         return changed;
    }
    
    public boolean addNecessaryEdges()
    {
        boolean changed = false;
        
        for (int row = 0; row <= rows - 1; row++)
        {
            int cantUse = 0;
            for (int column = 0; column <= columns - 1; column++)
            {
                if (row != column && constraint[row][column] == -1)
                    cantUse = cantUse + 1;
                    /*Before any edges are added, we must find the edges that
                      cannot be used.*/
            }
            if (cantUse >= rows - 3)
            {
                /*If the number of edges that cannot be used equals rows - 3,
                  then there are only two remaining possible edges left, and 
                  thus the remaining edges must be included.*/
                for(int column = 0; column <= columns -1; column++)
                {
                    if(row != column && constraint[row][column] == 0)
                    {
                        constraint[row][column] = 1;
                        constraint[column][row] = 1;
                        changed = true;
                        //This will set the remaining two possible edges
                    }
                }
            }
        }
        return changed;
    }
    
    public boolean isCycle(int row, int column)
    {
        bit = new BitSet(rows); //create a vector of bits to track nodes used
        bit.set(row);           //set node as used
        bit.set(column);        //set node as used
        int from = row;         //represents the starting node
        int to = column;        //represents the ending node
        int edges = 1;
        boolean stop = false;
        
        while (to != row && edges <= columns - 1 && stop == false)
        {
            stop = true;
            
            for (int col = 0; col <= columns -1; col++)
            {
                /*Check to see if the current ending node has an edge with
                another node.  If it does, update the current ending node and
                check if that node does*/
                if (col != from && constraint[to][col] == 1)
                {
                    edges++;
                    from = to;      //update the coming from node
                    to = col;       //update the to node
                    bit.set(to);    //update to include the new node
                    stop = false;
                    break;
                }
            }
        }
        
        /*If the starting node equals the ending node, then there is a cycle.
          If the number of edges is greater than or equal to the number of nodes,
          then there must also be a cycle.  In either case, return true. */
        return to == row || edges >= columns;
    }
    private int usedNodes(BitSet bit)
    {
        int counter = 0;
        for (int i = 0; i <= rows - 1; i++)
        {
            if (bit.get(i) == true)
                counter++;
        }
        
        return counter;
    }
    
    public boolean isTour()
    {
        /*Initialize path by checking to see if the start node is connected to
          another node and break if it is.*/
        int walkTo = 0;
        boolean cycle;
        
        for (int column = 1; column <= columns - 1; column++)
        {
            if (constraint[0][column] == 1)
            {
                walkTo = column;
                break;
            }
        }
        
        if (walkTo > 0)
        {
            cycle = isCycle(0, walkTo);
            return cycle == true && usedNodes(bit) == columns;
        }
        else
            return false;
    }
    
     public void calcTourCost (TSM tsm) 
    {
        int path = 0, row = 0;
        int from, pos;
        for (int column = 1; column <= columns - 1; column++) 
        {
            if (constraint[0][column] == 1) 
            {
                path = column;
                break;
            }
        }
        tourCost = tsm.getCostMatrixValue(0, path);
        tour[0] = path;
        from = row; 
        pos = path;
     
        while (pos != row) 
        {
            for (int column = 0; column <= columns - 1; column++) 
            {
                if (column != from && constraint[pos][column] == 1) 
                {
                    from = pos;
                    pos = column;
                    tourCost += tsm.getCostMatrixValue(from, pos);
                    tour[from] = pos;
                    break;
                }
            }
        }
    }
    public void computeLowerBound (TSM tsm) 
    {
        float lowBound = 0; 
        for (int row = 0; row <= rows - 1; row++) 
        {
            for (int col = 0; col <= columns - 1; col++)
            {
               edgeCost[col] = tsm.getCostMatrixValue(row, col);
               if (edgeCost[col] == 0)
                   edgeCost[col] = Integer.MAX_VALUE;
            }
            
            // Eliminate edges that are not allowed
            for (int col = 0; col <= columns - 1; col++) 
            {
                if (constraint[row][col] == -1) 
                    edgeCost[col] = Integer.MAX_VALUE;
            }
            
            int [] required = new int[columns];
            int numRequired = 0;

            // Determine whether an edge is required
            for (int col = 0; col <= columns - 1; col++) 
            {
                if (constraint[row][col] == 1) 
                {
                    numRequired++;
                    required[numRequired] = edgeCost[col];
                    edgeCost[col] = Integer.MAX_VALUE;
                }
            }
            int smallest = 0, nextSmallest = 0;
            if (numRequired == 0) 
            {
                smallest = smallest();
                nextSmallest = nextSmallest();
            } 
            else if (numRequired == 1) 
            {
                smallest = required[1];
                nextSmallest = smallest();
            } 
            else if (numRequired == 2) 
            {
                smallest = required[1];
                nextSmallest = required[2];
            }
            if (smallest == Integer.MAX_VALUE)
            {
                smallest = 0;
            }
            if (nextSmallest == Integer.MAX_VALUE) 
            {
                nextSmallest = 0;
            }
            lowBound += smallest + nextSmallest;
        } 
        lowerBound = lowBound/2;
    }
    
    private int smallest () 
    {
        int smallest = edgeCost[0];
        int index = 0;
        for (int i = 1; i <= columns - 1; i++) 
        { 
            if (edgeCost[i] < smallest) 
            {
                smallest = edgeCost[i];
                index = i; 
            }
        }
        
        int temp = edgeCost[0];
        edgeCost[0] = edgeCost[index];
        edgeCost[index] = temp;
        
        return edgeCost[0];
    }

    private int nextSmallest () 
    {
        int nextSmallest = edgeCost[1];
        int index = 1;
        for (int i = 1; i <= columns - 1; i++) 
        {
            if (edgeCost[i] < nextSmallest) {
                nextSmallest = edgeCost[i];
                index = i;
            }
        }
        int temp = edgeCost[1];
        edgeCost[1] = edgeCost[index];
        edgeCost[index] = temp;
        return edgeCost[1];
    }

    public float getLowerBound()
    {
        return lowerBound;
    }
    
    public int getTourCost () 
    {
        return tourCost;
    }

    public int [] getTour()
    {
        return tour;
    }
}
