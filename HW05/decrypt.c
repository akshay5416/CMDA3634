#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

//trying to fix git stuff
int main (int argc, char **argv) {

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
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
    unsigned int *Zmessage = (unsigned int *) malloc(count*sizeof(unsigned int));
      unsigned int *a = (unsigned int *) malloc(count*sizeof(unsigned int));
    for(unsigned int i = 0; i<count; i++){
	fscanf(file2, "%u %u", &Zmessage[i], &a[i]);
        printf("Zmessage[%u] : %u \n", i, Zmessage[i]);
        
        printf("a[%u] : %u \n", i, a[i]);
        
    }
    fclose(file2);
  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      }         
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }


  /* Q3 After finding the secret key, decrypt the message */
 // ElGamalDecrypt(Zmessage, a, count, p, x);
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  printf("Error 1\n");
  unsigned int charsPerInt = (n-1)/8*count;
  printf("Error 1.2\n");
  ElGamalDecrypt(Zmessage, a, count, p, x);
  printf("Error 1.3\n");
  convertZToString(Zmessage, count, message, charsPerInt);
  printf("Decrypted Message = \"%s\"\n", message);
  printf("\n");
  return 0;
}
