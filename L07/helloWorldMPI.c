#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main(int argc, char** argv) {
	
	//every MPI program must start with an initialize 
	//always do this first
	MPI_Init(&argc, &argv);

	int rank;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD,//this tells MPI to get the rank of this process globally
		      &rank); 	     // stores the result in rank
	MPI_Comm_size(MPI_COMM_WORLD,//this tells MPI to get the total number of processes
		      &size);	     //stores the result in size
	printf("Hello World %d of %d!\n", rank, size);

	//all MPI must end with a finalize 
	MPI_Finalize(); 

}
