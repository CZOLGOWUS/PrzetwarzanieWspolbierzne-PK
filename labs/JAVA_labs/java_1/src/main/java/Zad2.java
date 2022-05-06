import java.util.Arrays;
import  java.util.Random;
import java.util.stream.*;
import java.util.Arrays.*;

public class Zad2
{
    public static void zad2(int numberOfThreads, int n, int m)
    {
        Random random = new Random();
        char[] charSet = {'~','`','!','@','#','$','%','^','&','*','(',')','_','-','=','+','[','{',']','}','\\','|',';','\'',',','<','.','>','?','/'};
        char[][] image = new char[n][m];

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
                image[i][j] = charSet[random.nextInt(0,charSet.length)];
        }


        int charsPerThread = charSet.length / numberOfThreads;
        int leftOverChars = charSet.length % numberOfThreads;
        Zad2Thr[] NewThr = new Zad2Thr[numberOfThreads];

        for (int i = 0, j = charsPerThread - 1, it = 0; it < numberOfThreads; i = j, j += charsPerThread, it++)
        {
            if(leftOverChars > 0)
            {
                j++;
                leftOverChars--;
            }

            (NewThr[it] = new Zad2Thr(it, Arrays.copyOfRange(charSet,i,j), image)).start();
        }

        for (int i = 0; i < numberOfThreads; i++)
        {
            try
            {
                NewThr[i].join();
            }
            catch (InterruptedException ignored) {}
        }
    }
}



class Zad2Thr extends Thread
{

    private static final Random random = new Random();

    private int number;
    private char[] charSet;
    private char[] image;

    public Zad2Thr(int number, char[] charSet, char[][] image)
    {
        this.number = number;
        this.charSet = charSet;
        this.image = new char[image.length * image[0].length];

        for (int i = 0; i < image.length; i++)
        {
            for (int j = 0; j < image[0].length; j++)
            {
                this.image[i+j] = image[i][j];
            }
        }

    }

    public void run()
    {
        for (char it : charSet)
        {
            Stream<Character> charStream = new String(image).chars().mapToObj(i -> (char) i);
            System.out.println("Watek " + number + ": " + it + " " + charStream.filter(c -> c == it).count() + "x");
        }

    }
}
