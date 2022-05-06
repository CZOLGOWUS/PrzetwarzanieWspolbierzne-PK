import java.util.Random;

class zad1Thr extends Thread {

    private static final Random random = new Random();
    private int number;
    private int vecSize;
    private int[] vec1;
    private int[] vec2;
    private int[] resVec;
    int firstIndex;
    int lastIndex;

    public zad1Thr(int number, int[] vec1, int[] vec2, int[] result, int vecSize, int firstIndex, int lastIndex)
    {
        this.number = number;
        this.vecSize = vecSize;
        this.vec1 = vec1;
        this.vec2 = vec2;
        this.resVec = result;
        this.firstIndex = firstIndex;
        this.lastIndex = lastIndex;
    }

    public void run()
    {
        for(int i = firstIndex; i <= lastIndex; i++)
        {
            resVec[i] = vec1[i] + vec2[i];
        }
    }
}


class Zad1
{
    public static void zad1(int vecSize, int thFrame)
    {
        int[] vec1 = new int[vecSize];
        int[] vec2 = new int[vecSize];
        int[] resVec = new int[vecSize];

        final Random random = new Random();
        for (int i = 0; i < vecSize; i++)
        {
            vec1[i] = random.nextInt(100) + 1;
            vec2[i] = random.nextInt(100) + 1;
            resVec[i] = 0;
        }

        int num_threads = vecSize / thFrame;
        int restOfThreads = vecSize % thFrame;
        zad1Thr[] NewThr = new zad1Thr[num_threads];


        for (int i = 0, j = thFrame - 1, k = 0;
             i != vecSize;
             i = j + 1, j += thFrame, k++)
        {
            if(j > vecSize - 1 )
            {
                j = i + (j - (vecSize - 1));
                (NewThr[k] = new zad1Thr(k,vec1,vec2,resVec, vecSize,i,j)).start();
                break;
            }

            if(restOfThreads > 0)
                ++j;

            (NewThr[k] = new zad1Thr(k,vec1,vec2,resVec, vecSize,i,j)).start();

            --restOfThreads;
        }

        for (int i = 0; i < num_threads; i++)
        {
            try
            {
                NewThr[i].join();
            } catch (InterruptedException e) {}
        }

        //test
        System.out.print(
                "last element of vec1: "  + vec1[vecSize -1] +
                        "\nlast element of vec2: " +  vec2[vecSize -1] +
                        "\nlast element of vec result: " +  resVec[vecSize -1] + "\n");
    }
}