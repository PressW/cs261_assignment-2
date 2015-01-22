#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add(struct DynArr *stack)
{
    double first, second;
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(2);
    }
    second = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(3);
    }
    first = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    pushDynArr(stack, (first + second));
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
    double first, second;
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(4);
    }
    second = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(5);
    }
    first = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    pushDynArr(stack, (first - second));
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
    double first, second;
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(6);
    }
    second = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(7);
    }
    first = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    pushDynArr(stack, (first / second));
}

/*	param:  stack the stack being manipulated, opCode, integer code to specify operation
            opCodes:
                     1       x * y
                     2       x^y
	pre:    the stack contains at least two elements
	post:   the top two element are popped and replaced w/the result of performing
            the specified operation on them
 */
void opForDoubleOperand(struct DynArr *stack, int opCode) {

    double first, second;
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(9);
    }
    second = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(10);
    }
    first = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    switch (opCode) {
        case(1):
            pushDynArr(stack, (first * second));
            break;
            
        case(2):
            pushDynArr(stack, pow(first, second));
            break;
        
        default:
            printf("Error. Invalid argument opCode passed to opForDoubleOperand. Goodbye.");
            exit(11);
    }
}

/*	param:  stack the stack being manipulated, opCode, integer code to specify operation
            opCodes:
                    1       ^2
                    2       ^3
                    3       abs
                    4       sqrt
                    5       exp
                    6       ln
                    7       log base 10
                    other:  error - kill program
	pre:    the stack contains at least one element
	post:   the top element is popped and replaced w/the result of performing
            the specified operation on the top element
*/
void opForSingleOperand(struct DynArr *stack, int opCode) {
    
    double first;
    
    if (isEmptyDynArr(stack)) {
        printf("Error! You have provided too few operands. Goodbye.\n");
        exit(12);
    }
    first = topDynArr(stack);
    //remove top element
    popDynArr(stack);
    
    switch (opCode) {
        case(1):
            pushDynArr(stack, pow(first, 2));
            break;
        
        case(2):
            pushDynArr(stack, pow(first, 3));
            break;
            
        case(3):
            pushDynArr(stack, fabs(first));
            break;
            
        case(4):
            pushDynArr(stack, sqrt(first));
            break;
            
        case(5):
            pushDynArr(stack, pow(M_E, first));
            break;
            
        case(6):
            pushDynArr(stack, log(first));
            break;
            
        case(7):
            pushDynArr(stack, log10(first));
            break;

        default:
            printf("Error. Invalid argument opCode passed to opForSingleOperand. Goodbye.");
            exit(13);
    }
}

void numError(int errorCode) {
    printf("Error! You have entered too few operators. Goodbye.\n");
    exit(errorCode);
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0, *number = (double*)malloc(sizeof(double));
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		if(strcmp(s, "+") == 0)
			add(stack);
		
        else if(strcmp(s,"-") == 0)
			subtract(stack);
		
        else if(strcmp(s, "/") == 0)
			divide(stack);
		
        else if(strcmp(s, "x") == 0)
            opForDoubleOperand(stack, 1);
            
        else if(strcmp(s, "^") == 0)
            opForDoubleOperand(stack, 2);
        
        else if(strcmp(s, "^2") == 0)
            opForSingleOperand(stack, 1);
        
        else if(strcmp(s, "^3") == 0)
			opForSingleOperand(stack, 2);
        
        else if(strcmp(s, "abs") == 0)
			opForSingleOperand(stack, 3);
		
        else if(strcmp(s, "sqrt") == 0)
			opForSingleOperand(stack, 4);
		
        else if(strcmp(s, "exp") == 0)
			opForSingleOperand(stack, 5);
		
        else if(strcmp(s, "ln") == 0)
			opForSingleOperand(stack, 6);
		
        else if(strcmp(s, "log") == 0)
			opForSingleOperand(stack, 7);
		
        else
		{
            
            if (strcmp(s, "pi") == 0) {
                pushDynArr(stack, M_PI);
                
                if (i == (numInputTokens - 1)) {
                    numError(14);
                }

            }
            else if (strcmp(s, "e") == 0) {
                pushDynArr(stack, M_E);
                
                if (i == (numInputTokens - 1)) {
                    numError(15);
                }

            }
            else if (isNumber(s, number)) {
                pushDynArr(stack, *number);

                if (i == (numInputTokens - 1)) {
                    numError(8);
                }
            }
            else {
                printf("Error! You have entered an invalid argument: %s. Goodbye.\n", s);
                exit(1);
            }
            
			
		}
	}	//end for
    
    //there should only be one element in stack at this point
    if (isEmptyDynArr(stack) || sizeDynArr(stack) > 1) {
        printf("Error! There is more than 1 element in your stack after performing all operations. Goodbye.\n");
        exit(16);
    }
    
    result = topDynArr(stack);
    printf("The result of your operation is: %.02f\n", result);
    
    deleteDynArr(stack);
	
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}
