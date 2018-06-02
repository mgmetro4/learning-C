/* Basic I/O Functions */

#include <stdio.h>

int main()
{
    /*---------GETCHAR AND PUTCHAR---------*/

    /* if INPUT = ab<ENTER to end input> , c3 will return ASCII value for newline */
    printf("Enter getchar() input!\n");
    int c1 = getchar(); /* returns an int. Type char works if compiler allows */
    int c2 = getchar();
    int c3 = getchar();
    printf("First char: %c\n", c1); /* use %c to display the ASCII symbol; %d for the integer value */
    printf("Second char: %c\n", c2);
    printf("Third char: %d\n", c3);

    printf("\nputchar():\n");

    putchar(c1); /* Does not add a newline character at the end */
    putchar(c2);
    putchar(c3);
    printf("\n Char number 97:  ");
    putchar(97);


    /*---------SCANF---------*/

    /* FIRST: clear stream buffer */
    char garbage[100];
    scanf("%s", garbage);

    printf("\n\n scanf()\n");
    char input[20]; /* strings are an array of chars */
    int input2;
    printf("Enter scanf() input1 with NO whitespace!\n");
    scanf("%s", input); /* string = array of chars */
    printf("\n Enter scanf() input2 (Integer) \n");
    scanf("%d", &input2); /* casts string to integer */

    printf("Input 1:%s\n", input);
    printf("Input 2:%d\n", input2); /* puts() does not like printing non-strings/char. Use placeholder to cast */



    /*---------FGETS---------*/

    printf("\n\n fgets() \n");
    /* FIRST: clear stream buffer */
    char garbage2[100];
    fgets(garbage2,100,stdin);

    char gets[20];
    printf("Enter fgets() input1\n");
    fgets(gets,20, stdin); /* stdin = standard input */
    /* Not really good for integers... */
    printf("fget input: %s\n", gets);

    return 0;
}