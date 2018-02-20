#include <stdio.h>

void main(){

//Initialize the variables I will be using
int a=0;
int b=0;
int g=0;
//Asks user to enter the first number
printf("Enter the first number: ");
scanf("%d",&a);
//Asks user to enter second number
printf("Enter the second number: ");
scanf("%d",&b); 
//for loop helps make sure we go through each number through the highest whether it is a or b.
//If the remainder of a and b is equal to 0 then that number i is equal to gcd for the two 
//numbers. If either number is equal to zero the other number automatically is the gcd for the
//two numbers. 
for(int i = 1; i<a+1 && i<b+1; i++){
	if(a==0){
	  g = b; 		
	}
	else if(b==0){
	  g = a;
	}	
	else if(a%i==0 && b%i==0){
	  g = i;
	}
}
printf("The greatest common divisor of %d and %d is %d\n",a, b, g);
}
