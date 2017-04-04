/*Input for the lawn begins with an integer L, indicating the number of corners 
(vertices) on the lot. This is followed (on the same input line) by L pairs of 
integers, each pair specifying the X and Y coordinates of the position of each 
corner of the lot. The next input line for a data set will contain an integer H, 
indicating the number of corners (vertices) on the house. This is followed 
(on the same input line) by H pairs of integers, each pair specifying the X and Y 
coordinates of the position of each corner of the house. Following this will be 
an integer N on a  line by itself, indicating the number of landscaping beds. 
Each of the next N lines will contain an integer B indicating the number of 
corners (vertices) on that bed, followed by B pairs of integers, specifying the X
and Y coordinates of the position of each corner. All corners (vertices) will be 
specified consecutively in counter-clockwise order. Calculate the size of the lawn.
(Fertilizer is sold in terms of 1000-square­feet of coverage).*/

package lawnmaintenance;

import java.awt.Point;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

    
public class LawnMaintenance 
{
    public static final int COVERAGE = 1000;
    int l;                  //number of corners in the lot
    int h;                  //number of corners of the house
    int n;                  //number of landscape beds
    int[] b;                //number of corners for the beds
    int tempX;              //temporary x coordinate
    int count = 1;          //used to index the array
    Point[] lp;             //x,y coordinates for the lot corners
    Point[] hp;             //x,y coordinates for the house corners
    Point[] bp;             //x,y coordinates for the beds
    double[] area;          //area of the beds
    File input = new File("C:\\Users\\xxx\\Desktop\\maintenance.txt");  //the input file
    
    LawnMaintenance()
    {
        try {
               Scanner sc = new Scanner(input);
               if(sc.hasNextInt() == true)
               {
                   l = sc.nextInt();
                   lp = new Point[l];
                   createPoint(lp);
               }
               for (int i = 0; i < l*2; i++) //multiply by 2 since it's pairs
               {
                    if (sc.hasNextInt() == true)
                    {
                        if (i % 2 == 0) //x coordinate
                            tempX = sc.nextInt();
                        else //y coordinate
                            lp[i-count++].setLocation(tempX, sc.nextInt());
                    }
               }
               if(sc.hasNextInt() == true)
               {
                   h = sc.nextInt();
                   hp = new Point[h];
                   createPoint(hp);
                   count = 1;           //reset count for the house
               }
               for (int i = 0; i < h*2; i++)
               {
                   if (sc.hasNextInt() == true)
                    {
                        if (i % 2 == 0) //x coordinate
                            tempX = sc.nextInt();
                        else //y coordinate
                            hp[i-count++].setLocation(tempX, sc.nextInt());
                    }
               }
               if(sc.hasNextInt() == true)
               {
                   n = sc.nextInt();
                   b = new int[n];
                   area = new double[n];
               }
                for (int i = 0; i < n; i++)     //loop for number of beds
               {
                   count = 1;                   //reset count for the beds
                   b[i] = sc.nextInt();
                   bp = new Point[b[i]];
                   createPoint(bp);
                   
                   for (int j = 0; j < b[i]*2; j++)
                   {
                        if (sc.hasNextInt() == true)
                        {
                            if (j % 2 == 0) //x coordinate
                                tempX = sc.nextInt();
                            else //y coordinate
                                bp[j-count++].setLocation(tempX, sc.nextInt());
                        }
                   }
                   
                   area[i] = polygonArea(bp);
               }
           } catch (FileNotFoundException ex) {
               Logger.getLogger(LawnMaintenance.class.getName()).log(Level.SEVERE, null, ex);
           }
    }
    
    void createPoint(Point[] p)
    {
        for (int i = 0; i < p.length; i++)
            p[i] = new Point();
    }
    
    double polygonArea(Point[] p)
    {
        double area = 0;        //accumulates the area
        int j = p.length-1;     //last vertex to first vertex
        
        for (int i = 0; i < p.length; i++)
        {
            area = area + ((p[j].getX() + p[i].getX()) * (p[j].getY() - p[i].getY()));
            j = i;
        }
        
        return Math.abs(area/2);
    }
 
    public static void main(String[] args) 
    {
        LawnMaintenance lawnMaintenance = new LawnMaintenance();
        double lotArea, houseArea, bedArea = 0, maintenanceArea;
      
        lotArea = lawnMaintenance.polygonArea(lawnMaintenance.lp);
        houseArea = lawnMaintenance.polygonArea(lawnMaintenance.hp);
        
        for (int j = 0; j < lawnMaintenance.n; j++)
            bedArea = bedArea + lawnMaintenance.area[j];
        
        maintenanceArea = lotArea - houseArea - bedArea;
        System.out.println((int)Math.ceil(maintenanceArea/COVERAGE));
    }
}
