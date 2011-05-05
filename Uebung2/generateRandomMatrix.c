// This program generates a square matrix of random integer values. 
// The parameter is a file name.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIMENSION 999

int matrix[DIMENSION][DIMENSION];

void writeMatrix(int matrix[DIMENSION][DIMENSION], FILE *fp) {
  int i,j;
  fprintf(fp,"%d\n",DIMENSION);
  for(i=0; i<DIMENSION; i++) {
    for(j=0; j<DIMENSION; j++) {
      fprintf(fp,"%d ",matrix[i][j]); 
    }
    fprintf(fp,"\n");
  }
}

int main(int argc, char *argv[]) 
{
  int i, j;
  FILE *filePointer;
  time_t startTime,endTime, seed;
  
  if(argc != 2) {
    printf("Inproper number of arguments.");
    return 0;
  }

  // stop start time
  time(&startTime);

  // open file
  filePointer = fopen(argv[1],"w");

  // set seed for function rand()
  time(&seed); 
  srand(seed);

  for(i=0; i<DIMENSION; i++) {
    for(j=0; j<DIMENSION; j++) {
      // generate a random matrix entry
      matrix[i][j] = rand()/1000;
    }
  }

  // write matrix to file
  writeMatrix(matrix,filePointer);

  // close file
  fclose(filePointer);

  // stop end time
  time(&endTime);
  printf("The programm uses %ld seconds to generate the file %s.\n",endTime-startTime,argv[1]);
}

