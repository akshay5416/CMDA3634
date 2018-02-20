#include <stdio.h>


void main(){
//Initialize the variable to be used 
int a=0; 
//Asks the user to enter a number
printf("Enter a number: ");
scanf("%d", &a);
//Sets up the counter
int p = 0;
	//Sets up a for loop that sets up a counter that increases if the mod is zero
	for(int i = 2; i<a/2; i++){
		if(a%i==0){
		  p++;		
		}
	}
	//If p does not increase then it is prime. 
	if(p == 0){
		printf("%d is prime\n", a);
	}
	else{
		printf("%d is not prime\n", a); 
	}

}
