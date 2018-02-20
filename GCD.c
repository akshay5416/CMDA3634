#include <stdio.h>

int gcd(int c, int d);
int main(){
//Initialize the variables I will be using
int a=0;
int b=0;
int g=0;
//Asks the user to the enter the first number
printf("Enter the first number: ");
scanf("%d",&a);
//Asks the user to enter the second number
printf("Enter the second number: ");
scanf("%d", &b);

//using recursion to find the gcd of the two numbers
g = gcd(b, a%b);


printf("The greatest common divisior of %d and %d is %d\n", a, b, g);

}
//gcd method that uses recursion
int gcd(int c, int d){

if(d == 0){
	return c;	

}
else{
	 gcd(d, c%d);
}
}
