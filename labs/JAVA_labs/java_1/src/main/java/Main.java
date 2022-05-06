import  java.util.Random;
import java.util.stream.Stream;


public class Main
{

    public static void main(String[] args) throws Exception
    {
        if(args.length != 7)
        {
            throw new IllegalArgumentException("prog <VECTOR_SIZE> <THREAD_FRAME> <NUMBER_OF_THREADS> <IMAGE_N_SIZE> <IMAGE_M_SIZE> <TEMP>");
        }

        final int vecSize = Integer.parseInt(args[0]);
        final int threadFrame = Integer.parseInt(args[1]);
        final int numOfThreads_zad2 = Integer.parseInt(args[2]);
        final int n = Integer.parseInt(args[3]);
        final int m = Integer.parseInt(args[4]);
        final int sizeOfSourceArray = Integer.parseInt(args[5]);
        final int numbersPerThread = Integer.parseInt(args[6]);

        System.out.printf("Zad1 ---------------------------- vector size: %d, operations per one thread: %d\n",vecSize,threadFrame);
        Zad1.zad1(vecSize, threadFrame);
        System.out.printf("Zad2 ---------------------------- number of threads: %d, n = %d, m = %d\n",numOfThreads_zad2,n,m);
        Zad2.zad2(numOfThreads_zad2,n,m);
        System.out.printf("Zad3 ---------------------------- size of Source int array: %d, numbers per thread: %d\n",sizeOfSourceArray,numbersPerThread);
        Zad3.zad3(sizeOfSourceArray, numbersPerThread);
    }



}