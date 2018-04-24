#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
  FILE *file; 
  file = fopen("public_key.txt", "r");
  fscanf("%d\n", &n);
  fscanf("%d\n", &p);
  fscanf("%d\n", &g);
  fscanf("%d\n", &h);
  unsigned int *m = malloc(sizeof(unsigned int));
  unsigned int *a = malloc(sizeof(unsigned int));
  unsigned int charsPerInt = (n-1)/8;
  unsigned int Nints = strlen(message)/charsPerInt;
  ElGamalEncrypt(m, a, Nints, p, g, h);
  fclose(file);

 FILE *filem; 
 filem = fopen("messages.txt", "w");
 fprintf(filem, n); 
 for(int i = 0; i<n; i++){
 	fprintf(filem, "%d %d\n", m[i], a[i]);
} 
  
  return 0;
}
