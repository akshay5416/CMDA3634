#include <stdio.h>

int GCD(int c, int d);

void main(){
//initialize variables to use in program 
int a = 0;
int b = 0;
//Asks the user to enter first number
printf("Enter the first number: ");
scanf("%d", &a);
//Asks the user to enter the second number
printf("Enter the second number: ");
scanf("%d", &b);
//stores value from GCD of two numbers in an int variable
int cp = GCD(a,b);
//Helps decide if the two numbers are coprimes
if(cp == 1){
	printf("%d and %d are coprime\n", a, b);
}
else{
	printf("%d and %d are not coprime.\n", a, b);
}

}
//Used GCD code from 4.1 to help with deciding if two numbers are coprimes
int GCD(int c, int d){
if(d == 0){
	return c;
}
else{
	GCD(d, c%d);
}
}
