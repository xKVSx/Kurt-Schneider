/*Professor Boolando can only think in binary, or more specifically, in powers of 2.  
He converts any number you give him to the smallest power of 2 that is equal to 
or greater than your number. For example, if you give him 5, he converts it to 8; 
if you give him 100, he converts it to 128; if you give him 512, he converts it to 512.*/ 

package binarize;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Binarize 
{
    private int total;                  //the amount of numbers to binarize
    private int[] numbers;              //the numbers to be binarized
    private double[] bNumbers;          //the binarized numbers
    private double[] exponents;         //the exponents used to binarize
    File input = new File("C:\\binarize.txt");  //the input file
    
    Binarize()
    {
        try {
               Scanner sc = new Scanner(input);
               if(sc.hasNextInt() == true)
               {
                   total = sc.nextInt();
                   numbers = new int[total];
                   bNumbers = new double[total];
                   exponents = new double[total];
               }
               for (int i = 0; i < total; i++)
               {
                    if (sc.hasNextInt() == true)
                    {
                        numbers[i] = sc.nextInt();
                    }
               }
           } catch (FileNotFoundException ex) {
               Logger.getLogger(Binarize.class.getName()).log(Level.SEVERE, null, ex);
           }
    }
    
    int getTotal()
    {
        return total;
    }
    
    int[] getNumbers()
    {
        return numbers;
    }
    
    double[] getBNumbers()
    {
        return bNumbers;
    }
    
     double[] getExponents()
    {
        return exponents;
    }
        
    public static void main(String[] args) 
    {
        Binarize binarize = new Binarize();
        double logResult;
        
        for(int i = 0; i <binarize.exponents.length; i++)
        {
            logResult = Math.log(binarize.getNumbers()[i]) / Math.log(2);
            binarize.exponents[i] = Math.ceil(logResult);
            binarize.bNumbers[i] = Math.pow(2, binarize.exponents[i]);
        }
            
        for(int i = 0; i < binarize.bNumbers.length; i++)
        {
            System.out.println("Input value: " + binarize.numbers[i]);
            System.out.println((int)binarize.bNumbers[i]);
            System.out.println();
        }
    }  
}
