
package texting;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Texting 
{
    private int totalAbbrvtns;      //the number of abbreviations
    private int totalExpntns;       //the number of lines to be expanded
    private String[] abreviations;  //array of abbreviations
    private String[] expansions;    //array of expanded terms
    private String[] toExpand;      //array of phrases to expand
    private String[] output;        //array of the expanded phrases
    File input = new File("C:\\Texting.txt");  //the input file
    
    Texting()
    {
        try {
               Scanner sc = new Scanner(input);
               if(sc.hasNextInt() == true)
               {
                   totalAbbrvtns = sc.nextInt();
                   abreviations = new String[totalAbbrvtns];
                   expansions = new String[totalAbbrvtns];
               }
        
               for (int i = 0; i < totalAbbrvtns; i++)
               {
                    if (sc.hasNext() == true)
                    {
                        abreviations[i] = sc.next();
                        expansions[i] = sc.nextLine();
                    }
               }
               
               if(sc.hasNextInt() == true)
               {
                    totalExpntns = sc.nextInt();
                    toExpand = new String[totalExpntns];
                    output = new String[totalExpntns];
                    sc.nextLine();  //discard the remainder of the line
               }
               
                for (int i = 0; i < totalExpntns; i++)
               {
                    if (sc.hasNext() == true)
                        toExpand[i] = sc.nextLine();
               }
               
               
           } catch (FileNotFoundException ex) {
               Logger.getLogger(Texting.class.getName()).log(Level.SEVERE, null, ex);
           }
    }
    public static void main(String[] args)
    {
        Texting texting = new Texting();
        String temp = new String();
           
        for(int i = 0; i < texting.toExpand.length; i++)
        {
            temp = " " + texting.toExpand[i] + " "; //pad beginning and end
            
            for(int j = 0; j < texting.abreviations.length; j++)
            {
                temp = temp.replaceAll(" " + texting.abreviations[j] + " ", texting.expansions[j]);
            }
            
            texting.output[i] = temp;
        }
        
        for(int i = 0; i < texting.toExpand.length; i++)
        {
            System.out.println(texting.toExpand[i]);
        }
        
        for(int i = 0; i < texting.output.length; i++)
        {
            System.out.println(texting.output[i]);
        }
        
    }
    
}
