#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_THREADS 12
//#..

/*
Declare necessary global variables including 2D-array to store input and output matrices
int mat1[dim1][dim2] ...
 ...
 ...
*/


/*
 Create structure to store thread input info
 */

/*
 Function Declaration:
void *matrixMulter(void *params);
void ...
 
*/


int main(int argc, char *argv[]){
    /*
     Command prompt:
     ./hw2 mat1.txt mat2.txt
    */
	if(argc!=3){
		fprintf(stderr,"Usage: ./filename <mat1> <mat2>\n");
		return -1;
	}

	/***************
    1.Keep your code MODULARIZED and STRUCTURED!
        i.e. KEEP YOUR MAIN FUNCTION AS LIGHT AS NECESSARY!
     
    2. Pay attention to the data integrity when passing large collection data, e.g. array, list, queue, etc.
     
        Data coping of a large portion of matrix (e.g. entire row or column) or whole matrix
        should be avoided in your algorithm for multi-threading program.
     
     ***************/
    
    
    return 0;
}



/*
 Create your functions here..
*/





