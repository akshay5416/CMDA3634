#include <stdio.h>

int GCD(int c, int d); 

void main(){
//Initializing my two integers I will be using
int a=0;
int b=0; 
//Asks the user to enter the first number 
printf("Enter the first number: ");
scanf("%d",&a);
//Asks the user to enter the second number
printf("Enter the second number: ");
scanf("%d",&b);
//Computes the numerator and denominator for the problem
int n = a*b;
int d = GCD(a,b);
int lcm =n/d ;

printf("The least common multiple of %d and %d is %d\n", a, b, lcm);
}
//Created a method to help use the GCD in helping me solve for my LCM(used code from my GCD function)
int GCD(int c, int d){
  if(d == 0){
	return c;

} 
else{
	GCD(d, c%d);

}

}
