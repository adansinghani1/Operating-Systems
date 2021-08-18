#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_THREADS 12

//#..

/*
Declare necessary global variables including 2D-array to store input and output matrices
int mat1[dim1][dim2] ...
Created variables mat1, mat2, mulMatrix with arrays that store the NUM_THREAD
 ...
 ...
*/
int mat1[NUM_THREADS][NUM_THREADS];
int mat2[NUM_THREADS][NUM_THREADS];
int mulMatrix[NUM_THREADS][NUM_THREADS];


/*
 Create data structure to store thread input info
 */
struct input {
  int i;
  int *mat1;
  int (*mat2) [NUM_THREADS];
  int *mulMatrix;
};

/*
 Function Declaration:
void *mulMatrixMulter(void *params);
void ...
*/
void printRes(int a[NUM_THREADS][NUM_THREADS]);
void *mat (void *param);
void readFile (char *s, int mat [NUM_THREADS][NUM_THREADS]);

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

    // variables declarations
    int i, j, k, sum;

    pthread_t tid[NUM_THREADS]; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    pthread_attr_init(&attr); /* get the default attributes */

    printf("Read mulMatrix_1:\nRow: 12, col: 12\n");
    readFile("mat1.txt", mat1);
    printf("Read mulMatrix_2:\nRow: 12, col: 12\n");
    readFile("mat2.txt", mat2);

  // create structs for threads arguments
  struct input args[NUM_THREADS];
  for (i = 0; i < NUM_THREADS; i++) {
    args[i].i = i + 1;
    args[i].mat1 = mat1[i];
    args[i].mat2 = mat2;
    args[i].mulMatrix = mulMatrix[i];
  }

  /* create the thread */
  for (i = 0; i < NUM_THREADS; i++) {
    printf("Creating thread no.%d\n", i);
    pthread_create(&(tid[i]),&attr, mat, &args[i]);
  }
  /* wait for the thread to exit */
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }
  printf("Matric multiplication completed!\n");

  printf("\nmulMatrix_1 = \n");
  printRes(mat1);
  printf("\nmulMatrix_2 = \n");
  printRes(mat2);
  printf("\nmulMatrix_1*mulMatrix_2 =\n");
  printRes(mulMatrix);


  return 0;
}

/*
 Create your functions here..
*/

// function that takes in the matricies and multiplies the rows
void * mat (void *param) {
  struct input * input = (struct input*) param;
  int *mat1 = input->mat1;
  int *mulMatrix = input->mulMatrix;
  int (*mat2)[NUM_THREADS] = input->mat2;
  int i, j, k, sum;
      //calculate one row in mulMatrix
      for (j = 0; j < NUM_THREADS; j++) {
        //calculate one element in mulMatrix
        sum = 0;
        for (i = 0; i < NUM_THREADS; i++) {
          sum += mat1[i] * mat2[i][j];
        }
        mulMatrix[j] = sum;
      }
  printf("Row %d calculation succeed!\n", input->i);
  pthread_exit(0);
}

// create the file as an input
void readFile (char *s, int mat [NUM_THREADS][NUM_THREADS]) {
    FILE* f;
    int index1, index2;
    //mat1
    if((f = fopen(s, "r")) == NULL)
        exit(1);

    for(index2=0; index2<NUM_THREADS; index2++)
        for(index1=0; index1<NUM_THREADS; index1++)
            if(fscanf(f, "%d", &mat[index2][index1]) != 1)
                exit(1);
    fclose(f);
}


// print mulMatrix
void printRes(int a[NUM_THREADS][NUM_THREADS]){
    int index1, index2;
    for(index2=0; index2<NUM_THREADS; index2++){
        for(index1=0; index1<NUM_THREADS; index1++)
            printf ("%d ", a[index2][index1]);
        printf("\n");
    }
}


