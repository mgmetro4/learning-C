#include <stdio.h>

void myFunction(void); /* Prototype Statement */

int main()
{
    int x = 100;
    myFunction();
    printf("\nmain function x = %d \n", x);

    return(0);
}

void myFunction(void){
    int x = 2;
    printf("\nThis is myFunction!\n");
    printf("x = %d\n", x);

    return; /* don't need */
}