#include <stdio.h>

void main(){

int a,b;//allocates an integer called a
int *pt_a; // allocates a pointer, called pt_a, to an integer
a=3;
b=4;
pt_a = &a;//stores not the value of a but its location

printf("The size of an int is %ld\n" , sizeof(int));
printf(" a = %d \n", a);
printf("a is located at %p\n", pt_a);

printf(" b = %d \n", b);
printf(" a+b = %d \n", a+b);
printf(" a-b = %d \n", a-b);
printf(" a*b = %d \n", a*b);
printf(" a/b = %d \n", a/b);






}
