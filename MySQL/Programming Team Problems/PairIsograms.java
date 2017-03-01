
package pairisograms;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class PairIsograms 
{
    private int total;                //the number of words to be processed
    private String[] words;           //the words to be processed
    File input = new File("C:\\Users\\xxx\\Desktop\\pairisogram.txt");  //the input file
    
    PairIsograms()
    {
        try {
               Scanner sc = new Scanner(input);
               if(sc.hasNextInt() == true)
               {
                   total = sc.nextInt();
                   words = new String[total];
               }
               
               for (int i = 0; i < total; i++)
               {
                    if (sc.hasNext() == true)
                        words[i] = sc.next();
               }
           } catch (FileNotFoundException ex) {
               Logger.getLogger(PairIsograms.class.getName()).log(Level.SEVERE, null, ex);
           }
    }
    public static void main(String[] args) 
    {
        PairIsograms pairIsograms = new PairIsograms();
        char currentChar, compareChar;  //the current and next character to check
        int counter = 0;                //counts the occurance of each character
        boolean pairIsogram = true;
        String currentWord;
        
       
        for (int i = 0; i < pairIsograms.total; i++)
        {
            currentWord = pairIsograms.words[i];
            
            for (int j = 0; j < currentWord.length(); j++)
            {
                currentChar = currentWord.charAt(j);
           
                for (int k = 0; k < currentWord.length(); k++)
                {
                    compareChar = currentWord.charAt(k);
               
                    if (currentChar == compareChar && j != k)
                        counter++;
               
                    if (counter > 1)
                    {
                        pairIsogram = false;
                        break;
                    }
                }
           
                if (counter == 0)
                {
                    pairIsogram = false;
                    break;
                }
                else
                    counter = 0;    //reset for next character
            }
            
            if (pairIsogram == true)
                System.out.println(currentWord + " --- Pair isogram");
            else
                System.out.println(currentWord + " --- Not pair isogram");
            
            pairIsogram = true;     //reset for next word
        }
    }
}
