#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "mpi.h"
#include "functions.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  //seed value for the randomizer 
  double seed = clock()+rank; //this will make your program run differently everytime
  //double seed = rank; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  //begin with rank 0 getting user's input
  unsigned int n;

  /* Q3.1 Make rank 0 setup the ELGamal system and
    broadcast the public key information */
   // printf("Enter a number of bits: "); fflush(stdout);
   // char status = scanf("%u",&n);
    n = 10;
  //make sure the input makes sense
  if ((n<3)||(n>31)) {//Updated bounds. 2 is no good, 31 is actually ok
    printf("Unsupported bit size.\n");
    return 0;   
  }
  printf("\n");

  //declare storage for an ElGamal cryptosytem
  unsigned int p, g, h, x;

  //setup an ElGamal cryptosystem
  if(rank == 0){
  setupElGamal(n,&p,&g,&h,&x);
  MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD); 
  MPI_Bcast(&g, 1, MPI_INT, 0, MPI_COMM_WORLD); 
  MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD); 
  MPI_Bcast(&h, 1, MPI_INT, 0, MPI_COMM_WORLD); 
}



  //Suppose we don't know the secret key. Use all the ranks to try and find it in parallel
  if (rank==0)
    printf("Using %d processes to find the secret key...\n", size);

  /*Q3.2 We want to loop through values i=0 .. p-2
     determine start and end values so this loop is 
     distributed amounst the MPI ranks  */
  unsigned int N = p-1; //total loop size
  unsigned int start, end;

   //This divides the number of start and end   
  // start = (N)/(size) * (rank);
  // end = (N)/(size) + start;
   
   if(rank < N%size){
      start =((N)/(size) * (rank)) + rank; 
      end = ((N)/(size) + (rank + 1)) + rank;
   }
   else{ 
      start = (N)/(size) * (rank);
      end = (N)/(size) + start;
  }
   
  
  MPI_Barrier(MPI_COMM_WORLD);
  double startTime = MPI_Wtime();
  //loop through the values from 'start' to 'end'
  for (unsigned int i=start;i<end;i++) {
    if (modExp(g,i+1,p)==h)
      printf("Secret key found! x = %u \n", i+1);
  }
  double endTime = MPI_Wtime();
  double runTime = MPI_Wtime() - startTime;
  double throughPut = N/(runTime); 
  printf("This is the runTime for the rank: %f \n ", runTime);
  printf("This is the Throughput for the program:%f \n", throughPut); 
  MPI_Finalize();
//Explained in document on how problems in new river could not be fixed in time. 
  return 0;
}
