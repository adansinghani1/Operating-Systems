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
int mat1[NUM_THREADS][NUM_THREADS];
int mat2[NUM_THREADS][NUM_THREADS];
int matrix[NUM_THREADS][NUM_THREADS];


/*
 Create structure to store thread input info
 */
struct input {
  int i;
  int *mat1;
  int (*mat2) [NUM_THREADS];
  int *matrix;
};

/*
 Function Declaration:
void *matrixMulter(void *params);
void ...
*/
void printall(int a[NUM_THREADS][NUM_THREADS]);
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

	/***************
    1.Keep your code MODULARIZED and STRUCTURED!
        i.e. KEEP YOUR MAIN FUNCTION AS LIGHT AS NECESSARY!
     
    2. Pay attention to the data integrity when passing large collection data, e.g. array, list, queue, etc.
     
        Data coping of a large portion of matrix (e.g. entire row or column) or whole matrix
        should be avoided in your algorithm for multi-threading program.
     
     ***************/
    int i, j, k, sum;

    pthread_t tids[NUM_THREADS]; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    pthread_attr_init(&attr); /* get the default attributes */

    printf("Read matrix_1:\nRow: 12, col: 12\n");
    readFile("mat1.txt", mat1);
    printf("Read matrix_2:\nRow: 12, col: 12\n");
    readFile("mat2.txt", mat2);

  // create structs for threads arguments
  struct input args[NUM_THREADS];
  for (i = 0; i < NUM_THREADS; i++) {
    args[i].i = i + 1;
    args[i].mat1 = mat1[i];
    args[i].mat2 = mat2;
    args[i].matrix = matrix[i];
  }

  /* create the thread */
  for (i = 0; i < NUM_THREADS; i++) {
    printf("Creating thread no.%d\n", i);
    pthread_create(&(tids[i]),&attr, mat, &args[i]);
  }
  /* wait for the thread to exit */
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(tids[i], NULL);
  }
  printf("Matrix multiplication completed!\n");

  printf("\nMatrix_1 = \n");
  printall(mat1);
  printf("\nMatrix_2 = \n");
  printall(mat2);
  printf("\nMatrix_1*Matrix_2 =\n");
  printall(matrix);


  return 0;
}

/*
 Create your functions here..
*/

// function for threads
void * mat (void *param) {
  struct input * input = (struct input*) param;
  int *mat1 = input->mat1;
  int *matrix = input->matrix;
  int (*mat2)[NUM_THREADS] = input->mat2;
  int i, j, k, sum;
      //calculate one row in matrix
      for (j = 0; j < NUM_THREADS; j++) {
        //calculate one element in matrix
        sum = 0;
        for (i = 0; i < NUM_THREADS; i++) {
          sum += mat1[i] * mat2[i][j];
        }
        matrix[j] = sum;
      }
  printf("Row %d calculation succeed!\n", input->i);
  pthread_exit(0);
}

// inserting mat1 file file
void readFile (char *s, int mat [NUM_THREADS][NUM_THREADS]) {
    FILE* f;
    int i, j;
    //mat1
    if((f = fopen(s, "r")) == NULL)
        exit(1);

    for(j=0; j<NUM_THREADS; j++)
        for(i=0; i<NUM_THREADS; i++)
            if(fscanf(f, "%d", &mat[j][i]) != 1)
                exit(1);
    fclose(f);
}


// print multiplied matrix
void printRes(int a[NUM_THREADS][NUM_THREADS]){
    int i, j;
    for(j=0; j<NUM_THREADS; j++){
        for(i=0; i<NUM_THREADS; i++)
            printf ("%d ", a[j][i]);
        printf("\n");
    }
}
