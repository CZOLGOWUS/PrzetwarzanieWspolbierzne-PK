#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int arg, char *args[])
{
	printf("Jarosław Kołodziej | PID = %d | zmienna_globalna = %s\n", getpid(), args[1]);

	return 0;
}