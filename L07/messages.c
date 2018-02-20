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

	if (rank == 0){
	int N = 10;
	int destRank = 1;
	int tag = 1;
	
	MPI_Send(&N,//pointer to the location of the data we're sending
		1,//number of entries to send 
		MPI_INT,//type of each entry(data type)
		destRank,//rank of destination
		tag,	//tags the message with some number
		MPI_COMM_WORLD);//flag to full MPI network 
} else if (rank ==1){
int N;
int sourceRank = 0; 
int tag = 1;
MPI_Status status;


MPI_Recv(&N, //pointer to where to put data
	1,	//number of entries
	MPI_INT,//data type
	sourceRank,//rank of sender
	tag,//message tag
	MPI_COMM_WORLD,
	&status);

printf("Rank %d received a message from rank %d: value = %d: value= %d\n", rank, sourceRank, N);

}
	//all MPI must end with a finalize 
	MPI_Finalize(); 
	return 0;
}
