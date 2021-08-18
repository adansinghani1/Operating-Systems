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
    int fd[2];
    pipe(fd); 
    int childId = 0;  
    int n; 

    if (argc == 1) {
		fprintf(stderr,"Usage: ./hw1 <starting value>\n");
		
		return -1;
	}

    n = atoi(argv[1]); 
    int Vals = n; 
    int finalValue;  
    int count = 1; 
    int tripleDigit  = 495; 
    int valsinArr = 3;
    pid_t pid = fork();
    // initialize childId process  
    if( pid==0 ) { 
	
	// check if the value given is < 99 or value is repeating two follwing values
	// if given such, return 0 or NULL

	if ( Vals==111 || Vals ==222 || Vals ==333 || Vals ==444 || Vals ==555 || Vals ==666 || Vals ==777 || Vals == 888 ||Vals == 999 || Vals < 99 || Vals > 999 ) 
            return 0;
 do {
     int up[valsinArr];
     int down[valsinArr];
        

        int i;
	int ten = 10; 
	for ( i = 0; i < valsinArr; i++ ) { 
	up[i] = Vals%ten; 
	down[i] = Vals%ten;
	Vals = Vals/ten; 
            } 
            
           
	// sort numbers in upending order
	int j, tmp; 
	int k = valsinArr;
	for(i = 0; i < k; i++) {
	for(j = i+1; j < k ; j++) {
	if(up[j] < up[i]){
	tmp = up[i];
	up[i] = up[j];
	up[j] = tmp;
                    }
                }
            }
            
         // sort numbers in downending order
	 int x;
	 int y = valsinArr;
	 for (i = 0; i < y; ++i) {
	 for (j = i + 1; j < y; ++j) {
	 if (down[i] < down[j]) {
         tmp = down[i];
         down[i] = down[j];
         down[j] = tmp;
                    }
                }
            }
          
	  // converting values into real numbers      
          int z = valsinArr;
          int inc= 0;
          int dec= 0;
          for (i = 0; i < z; i++)
          inc= ten * inc+ up[i];
          for (i = 0; i < z; i++)
          dec= ten * dec+ down[i];
            
	  int subtract = abs(dec - inc); 
          printf("Child process %d %d %d - %d = %d \n",getpid(),count, dec, inc, subtract);
          count++;
          finalValue = subtract;
          Vals = finalValue;
        }

        while( finalValue != tripleDigit );
        childId = finalValue;
    	write(fd[1], &childId, sizeof(childId));

   }       else { 
	read(fd[0], &childId, sizeof(childId));
	printf("Result from child process: (%d) is: %d\n", getpid(), childId);
	close(fd[2]);
    }    
	return 0;
}



