#include <stdio.h>
#include<math.h>

void main(){
//Initialize the variable 
int a = 0;
//Asks user to enter a prime number
printf("Enter a prime number: ");
scanf("%d", &a);
//Sets up a counter
int p = 0;
//Sets up a iterator
int i;
//2 for loops are being set up to see which numbers are generators. We are looking at numbers from 0 - a-1. We then set them up in terms of
//powers. If it doesn't then the value of p goes up.  
for(i=0; i<a; i++){
	
	for (int j = 1 ; j <a-1; j++){
		if((int)pow(i,j)%a == 1){
			p++;
			
		}		
}

//If p is still equal to zero then it is a generator of Z prime. 	
if(p==0){
	printf("%d is a generator of Z_%d\n", i, a);

}
p=0;
}





}
