#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pomiar_czasu.h"
int zmienna_globalna = 0;

int main()
{

  int pid, wynik, i;
  inicjuj_czas();
  for (i = 0; i < 1000; i++)
  {
    zmienna_globalna = 0;

    pid = fork();

    if (pid == 0)
    {

      zmienna_globalna++;

      char glob[16];
      sprintf(glob, "%d", zmienna_globalna);

      char *charArray[3] = {
          "./prog",
          glob,
          0};

      wynik = execv("./prog", charArray);
      if (wynik == -1)
        printf("Proces potomny nie wykonal programu\n");

      exit(0);
    }
    else
    {

      wait(NULL);
    }
  }
  drukuj_czas();

  return 0;
}
