// Ibrahim Awada 595489
// Das Programm multipliziert 2 Matrizen, die als erste beide Argumente
// eingegeben werden und schreibt das Ergebnis in eine Datei, die wie der
// 3. Parameter eingegeben wurde, heißt.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include <time.h>

int main(int argc, char *argv[]) 
{
  int dimA;
  int dimB;
  int z;
  int i;
  int j;
  
  time_t startZeit,endZeit;
  
  FILE *DateiA;
  FILE *DateiB;
  FILE *DateiC;
	
printf("jiba\");

  // Überprüfen ob Eingabe richtig ist.
  if(argc != 4) {
    printf("Die Anzahl der Parameter muss 4 sein.");
    return 0;
  }

  
  DateiA = fopen(argv[1],"r");
  
  DateiB = fopen(argv[2],"r");
  
  DateiC = fopen(argv[3],"w");

  
   
  
  // allocating the memory for 3 matrices
  fscanf(DateiA, "%d", &dimA);
  int **matrixA;
  int **matrixB;
  int **matrixC;
  matrixA = (int**)malloc(sizeof(int*) * (dimA + 1));
  matrixB = (int**)malloc(sizeof(int*) * (dimA + 1));
  matrixC = (int**)malloc(sizeof(int*) * (dimA + 1));
  for(i =0;i<dimA;++i){
	  matrixA[i] = (int*)malloc(sizeof(int) * (dimA + 1));
	  matrixB[i] = (int*)malloc(sizeof(int) * (dimA + 1));
	  matrixC[i] = (int*)malloc(sizeof(int) * (dimA + 1));
  }
  
  // reading matrixA and matrixB
  printf("reading matrixA\n");
  for(i=0; i<dimA; i++) {
    for(j=0; j<dimA; j++) {
      fscanf(DateiA, "%d", &z);
	 matrixA[i][j]=z; 
    }
  }
  

  printf("reading matrixB\n");
  fscanf(DateiB, "%d", &dimB);
  for(i=0; i<dimB; i++) {
    for(j=0; j<dimB; j++) {
      fscanf(DateiB, "%d", &z);
	 matrixB[i][j]=z; 
    }
  }
  
  
 

  // Error detection if the dimensions aren't equal
  if(dimA != dimB) {
    printf("Matrizen haben unterschiedliche Dimensionen");
    fclose(DateiA);
    fclose(DateiB);
    fclose(DateiC);
    return 0;
  } 

  // Multiplication of  matrixA*matrixB

  time(&startZeit);  
  int numProcs = omp_get_num_procs();  
  printf("Multiplying with number of procs:%d\n",numProcs);
  
  #pragma omp parallel for  
  for(i=0; i<dimA; i++) {
    for(j=0; j<dimA; j++) {
      int c=0;
      int k;
      for(k=0; k<dimA; k++) {
        c = c + matrixA[i][k]*matrixB[k][j];
      }
      matrixC[i][j] = c;
    }
  }
  
  // calculating and printing the elapsed time
  time(&endZeit); 
  
  printf("%ld Sekunden zum Multiplizieren der Matrizen\n",endZeit-startZeit);
  //End of the Multiplication

  
  
  // Writing the Results in matrixC
  printf("writing results in matrixC\n");
  fprintf(DateiC,"%d\n",dimA);
  for(i=0; i<dimA; i++) {
    for(j=0; j<dimA; j++) {
      fprintf(DateiC,"%d ",matrixC[i][j]); 
    }
    fprintf(DateiC,"\n");
  }
  

  printf("finished\n");
  free(matrixA);
  free(matrixB);
  free(matrixC);
  

  // Datein schließen
  fclose(DateiA);
  fclose(DateiB);
  fclose(DateiC);
}

