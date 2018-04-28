#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"


   
__device__ unsigned int modProd(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int za = a;
  unsigned int ab = 0;

  while (b > 0) {
    if (b%2 == 1) ab = (ab +  za) % p;
    za = (2 * za) % p;
    b /= 2;
  }
  return ab;
}

//compute a^b mod p safely
__device__ unsigned int modExponential(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int z = a;
  unsigned int aExpb = 1;

  while (b > 0) {
    if (b%2 == 1) aExpb = modProd(aExpb, z, p);
    z = modProd(z, z, p);
    b /= 2;
  }
  return aExpb;
}

// find the secret key
__global__ void findSecretKey(unsigned int g, unsigned int p, unsigned int h, unsigned int *d_a){
  int thread = threadIdx.x;
  int block  = blockIdx.x;
  int blockSize = blockDim.x;

  //unique global thread ID
  int id = thread + block*blockSize;

 if (id < p-1) {  
   // for (unsigned int i=0;i<p-1;i++) {
      if (modExponential(g, id,p)==h) {
       //iintf("Secret key found! x = %u \n", i+1);
        *d_a=id-1;
      }
    }
   // double endTime = clock();

   // double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
   // double work = (double) p;
   // double throughput = work/totalTime;

   // printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }



int main (int argc, char **argv) {


  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */
    //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
     // int bufferSize = 1024;
    // unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
     // unsigned int charsPerInt = (n-1)/8 ;
     // unsigned int Nchars = mystrlen(message);
     // Nints = mystrlen(message)/charsPerInt;

    FILE* file;
    file = fopen("public_key.txt", "r");
    fscanf(file,"%u\n", &n);
    fscanf(file,"%u\n", &p);
    fscanf(file,"%u\n", &g);
    fscanf(file,"%u\n", &h);
    fclose(file);

     FILE *file2;
    file2 = fopen("messages.txt", "r");
    unsigned int count;
    fscanf(file2,"%u\n", &count);

    unsigned int *Zmessage = (unsigned int *) malloc(Nints*sizeof(unsigned int));
    unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));

    for(int i = 0; i<count; i++){
        fscanf(file2, "%u %u\n", &Zmessage[i], &a[i]);
    }
    fclose(file2);
//find the secret key
  int Nthreads = 32;
  dim3 B = (32, 1,1);
  dim3 G = ((p-1)+Nthreads)/(32,1,1);

  double deviceStart = clock();

  unsigned int *h_a = (unsigned int *) malloc(sizeof(unsigned int));
  unsigned int *d_a;
  cudaMalloc(&d_a, Nthreads*sizeof(unsigned int));


  findSecretKey<<<G,B>>> (g, p, h,d_a);
  cudaDeviceSynchronize();

  double deviceEnd = clock();
  double deviceTime = (deviceEnd-deviceStart)/(double) CLOCKS_PER_SEC;

  cudaMemcpy(h_a,d_a, Nthreads*sizeof(unsigned int), cudaMemcpyDeviceToHost);

  printf("The secret key is %u\n ", h_a);
  printf("The device took %d seconds to find the secret key \n", deviceTime);
    
    /* Q3 After finding the secret key, decrypt the message */
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  unsigned int charsPerInt = (n-1)/8 ;
  unsigned int Nchars = mystrlen(message);
               Nints = mystrlen(message)/charsPerInt;
  ElGamalDecrypt(Zmessage,a,Nints,p,x);

  convertZToString(Zmessage, Nints, message, Nchars);
  printf("Decrypted Message = %s\n", message);

/* Q4 Make the search for the secret key parallel on the GPU using CUDA. */
  cudaFree(d_a);
  free(h_a);

  return 0;
}
