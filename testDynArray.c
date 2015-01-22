/* testDynArray.c
 * This file is used for testing the dynamicArray.c file. 
 * This test suite is by no means complete or thorough.
 * More testing is needed on your own.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicArray.h"


void assertTrue(int predicate, char *message) 
{
	printf("%s: ", message);
	if (predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}

void dynArrTestScript(DynArr *dyn) {
    
    printf("Creating DynArr with cap 1...\n");
    dyn = createDynArr(1);
    
    printf("Adding numbers 0 - 999 to dyn @ index 0 - 999...\n");
    for (int i = 0; i < 1000; i++) {
        addDynArr(dyn, i);
    }
    printf("dyn == [0, 1, 2, ... , 997, 998, 999]\n");
    assertTrue(sizeDynArr(dyn) == 1000, "Test size = 1000");
    assertTrue(EQ(getDynArr(dyn, 499), 499), "Test 499th element == 499");
    assertTrue(EQ(getDynArr(dyn, 782), 782), "Test 782nd element == 782");
    
    printf("Removing all values from dyn...\n");
    for (int i = 999; i >= 0; i--) {
        removeAtDynArr(dyn, i);
    }
    assertTrue(sizeDynArr(dyn) == 0, "Test size == 0");
    
    printf("Now dyn has size 0 and capacity 1024. Adding values to dyn 1999 - 0 @ index 0 - 1999...\n");
    for (int i = 1999; i >= 0; i--) {
        addDynArr(dyn, i);
    }
    printf("dyn == [1999, 1998, ... , 3, 2, 1]\n");
    assertTrue(sizeDynArr(dyn) == 2000, "Test size == 2000");
    assertTrue(EQ(getDynArr(dyn, 0), 1999), "Test 0th element == 1999");
    assertTrue(EQ(getDynArr(dyn, 1999), 0), "Test 1999th element == 0");
    
    printf("Swapping, calling swapDynArr(dyn, 0, 1999)...\n");
    swapDynArr(dyn, 0, 1999);
    assertTrue(EQ(getDynArr(dyn, 0), 0), "Test 0th element == 0");
    assertTrue(EQ(getDynArr(dyn, 1999), 1999), "Test 1999th element == 1999");
}

void testPutHigh() {
    
    DynArr *dyn;
    dyn = createDynArr(2);
    addDynArr(dyn, 1);
    addDynArr(dyn, 2);
    
    printf("dyn = [1,2], trying to insert element at index 2. This should kill the program.\n");
    putDynArr(dyn, 2, 5);
}

void testPutLow() {

    DynArr *dyn;
    dyn = createDynArr(2);
    addDynArr(dyn, 1);
    addDynArr(dyn, 2);
    
    printf("dyn = [1,2], trying to insert element at index -1. This should kill the program.\n");
    putDynArr(dyn, -1, 6);
}

void testRemoveHigh() {
  
    DynArr *dyn;
    dyn = createDynArr(2);
    addDynArr(dyn, 1);
    addDynArr(dyn, 2);
    
    printf("dyn = [1,2], trying to remove element at index 5. This should kill the program.\n");
    removeAtDynArr(dyn, 5);
}

void testRemoveLow() {
    
    DynArr *dyn;
    dyn = createDynArr(2);
    addDynArr(dyn, 1);
    addDynArr(dyn, 2);

    printf("dyn = [1,2], trying to remove element at index -1. This should kill the program.\n");
    removeAtDynArr(dyn, -1);
}

// this main function contains some
int main(int argc, char* argv[]){

    if (argc > 1) {

        if (strcmp(argv[1], "putHigh") == 0)
            testPutHigh();
        
        else if (strcmp(argv[1], "putLow") == 0)
            testPutLow();
        
        else if (strcmp(argv[1], "remHigh") == 0)
            testRemoveHigh();

        else if (strcmp(argv[1], "remLow") == 0)
            testRemoveLow();
        
        else
            printf("Error. Unknown argument passed to main.\n");
    }
    
    else {
        
        DynArr *dyn;
        dyn = createDynArr(2);
        
        printf("\n\nTesting addDynArr...\n");
        addDynArr(dyn, 3);
        addDynArr(dyn, 4);
        addDynArr(dyn, 10);
        addDynArr(dyn, 5);
        addDynArr(dyn, 6);
        
        printf("The array's content: [3,4,10,5,6]\n");
        assertTrue(EQ(getDynArr(dyn, 0), 3), "Test 1st element == 3");
        assertTrue(EQ(getDynArr(dyn, 1), 4), "Test 2nd element == 4");
        assertTrue(EQ(getDynArr(dyn, 2), 10), "Test 3rd element == 10");
        assertTrue(EQ(getDynArr(dyn, 3), 5), "Test 4th element == 5");
        assertTrue(EQ(getDynArr(dyn, 4), 6), "Test 5th element == 6");
        assertTrue(sizeDynArr(dyn) == 5, "Test size = 5");
        
        printf("\n\nTesting putDynArr...\nCalling putDynArr(dyn, 2, 7)\n");
        putDynArr(dyn, 2, 7); 
        printf("The array's content: [3,4,7,5,6]\n");
        assertTrue(EQ(getDynArr(dyn, 2), 7), "Test 3rd element == 7");
        assertTrue(sizeDynArr(dyn) == 5, "Test size = 5");
        
        printf("\n\nTesting swapDynArr...\nCalling swapDynArr(dyn, 2, 4)\n");
        swapDynArr(dyn, 2, 4);
        printf("The array's content: [3,4,6,5,7]\n");
        assertTrue(EQ(getDynArr(dyn, 2), 6), "Test 3rd element == 6");
        assertTrue(EQ(getDynArr(dyn, 4), 7), "Test 5th element == 7");
        
        printf("\n\nTesting removeAtDynArr...\nCalling removeAtDynArr(dyn, 1)\n");
        removeAtDynArr(dyn, 1);
        printf("The array's content: [3,6,5,7]\n");
        assertTrue(EQ(getDynArr(dyn, 0), 3), "Test 1st element == 3");
        assertTrue(EQ(getDynArr(dyn, 3), 7), "Test 4th element == 7");
        assertTrue(sizeDynArr(dyn) == 4, "Test size = 4");
        
        printf("\n\nTesting stack interface...\n");
        printf("The stack's content: [3,6,5,7] <- top\n");
        assertTrue(!isEmptyDynArr(dyn), "Testing isEmptyDynArr");
        assertTrue(EQ(topDynArr(dyn), 7), "Test topDynArr == 7");
        
        popDynArr(dyn);
        printf("Poping...\nThe stack's content: [3,6,5] <- top\n");
        assertTrue(EQ(topDynArr(dyn), 5), "Test topDynArr == 5");
        
        pushDynArr(dyn, 9);
        printf("Pushing 9...\nThe stack's content: [3,6,5,9] <- top\n");
        assertTrue(EQ(topDynArr(dyn), 9), "Test topDynArr == 9");
        
        printf("\n\nTesting bag interface...\n");
        printf("The bag's content: [3,6,5,9]\n");
        assertTrue(containsDynArr(dyn, 3), "Test containing 3");
        assertTrue(containsDynArr(dyn, 6), "Test containing 6");
        assertTrue(containsDynArr(dyn, 5), "Test containing 5");
        assertTrue(containsDynArr(dyn, 9), "Test containing 9");
        assertTrue(!containsDynArr(dyn, 7), "Test not containing 7");
        
        removeDynArr(dyn, 3);
        printf("Removing 3...\nThe stack's content: [6,5,9]\n");
        assertTrue(!containsDynArr(dyn, 3), "Test not containing 3");
        
        printf("\n\nFreeing dyn and calling dynArrTestScript(dyn)...\n");

        deleteDynArr(dyn);
        dynArrTestScript(dyn);
    }
    
	return 0;
}