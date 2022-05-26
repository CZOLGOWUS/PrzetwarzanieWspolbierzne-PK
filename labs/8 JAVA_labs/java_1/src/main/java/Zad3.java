import java.util.Arrays;
import  java.util.Random;


class Zad3Thr extends Thread {

    private static final Random random = new Random();
    private final int number;
    private final int from;
    private final int to;
    private final int[] res;


    public Zad3Thr(int number,int from, int to, int[] res)
    {
        this.number = number;
        this.from = from;
        this.to = to;
        this.res= res;

    }

    public void run()
    {
        for (int i = from; i < to; i++)
        {
            int num = res[i];
            if(num == -1 || num == 1)
                continue;

            for (int j = num; j < res.length; j++)
            {
                int numberBeingChecked = res[j];

                if(numberBeingChecked == -1)
                    continue;

                if ( numberBeingChecked % num == 0 && numberBeingChecked != num)
                {
                    res[j] = -1;
                }

            }
        }
    }
}

public class Zad3
{

    public static void zad3(int sizeOfSourceArray, int numbersPerThread)
    {
        int[] result = new int[sizeOfSourceArray];
        int numberOfThreads = sizeOfSourceArray/numbersPerThread;
        int leftNumbers = sizeOfSourceArray % numbersPerThread;

        Zad3Thr[] NewThr = new Zad3Thr[numberOfThreads];

        for (int i = 1; i <= sizeOfSourceArray; i++)
        {
            result[i-1] = i;
        }

        for (int it = 0, from = 0, to = numbersPerThread - 1;
             it < numberOfThreads;
             it++, from = to + 1, to += numbersPerThread)
        {
            if(leftNumbers > 0)
            {
                to++;
                leftNumbers--;
            }

            (NewThr[it] = new Zad3Thr(it, from, to, result)).start();
        }

        for (int i = 0; i < numberOfThreads; i++)
        {
            try
            {
                NewThr[i].join();
            }
            catch (InterruptedException ignore) {}
        }

        int[] endArray = Arrays.stream(result).filter(i -> i != -1).toArray();
        System.out.println(Arrays.toString(endArray));
    }
}
