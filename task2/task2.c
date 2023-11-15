#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int exitPrgm(int a, int b);


int main (){
	/* IMPLEMENT ME: Insert your algorithm here */
	char input;
	int (*operations[])(int, int) = {add, subtract, multiply, divide, exitPrgm};
	do{
	printf("Operand 'a' : 6 | Operand 'b' : 3\nSpecify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit): ");
	scanf(" %c", &input);
	int index = input - '0';
	(index <= 4) ? printf("%d\n", operations[index](6, 3)) : printf("Invalid input, try again!\n");
	} while(1);
	return 0;
}

/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { printf ("Adding 'a' and 'b': "); return a + b; }
int subtract (int a, int b) { printf ("Subtracting 'b' from 'a': "); return a - b; }
int multiply (int a, int b) { printf ("Multiplying 'a' and 'b': "); return a * b; }
int divide (int a, int b) { printf ("Diving 'a' by 'b': "); return a / b; }
int exitPrgm (int a, int b) { printf ("Exiting program\n"); exit(0); return 0;}
