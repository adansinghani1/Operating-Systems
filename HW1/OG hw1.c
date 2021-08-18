#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 10
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{

int n;

	if (argc == 1) {
		fprintf(stderr,"Usage: ./hw1 <starting value>\n");
		
		return -1;
	}

	n = atoi(argv[1]); //  n is the input starting value



	return 0;
}
