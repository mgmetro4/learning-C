#include <stdio.h>

int main() {
    int a;
    printf("Enter an integer greater than 100: \n");
    scanf("%d", &a);

    if (a > 0) printf("A > 0\n");
    if (a > 10) { printf("A > 10\n"); }
    if (a > 100) {
        printf("A > 100\n");
    }

    /*
     * works because they are only one line. For multiple lines, use brackets!
     * if (a < 0) printf("A is negative\n");
     * else printf("A is positive\n");
     */

    /*
     * can also use:
     * printf(a < 0 ? "A is negative\n" : "A is positive\n");
     */

    if (a < 0) {
        printf("A is negative\n");
    } else if (a == 0) {
        printf("A is 0\n");
    } else {
        printf("A is positive\n");
    }

    /* CASE STATEMENTS */
    char c;
    printf("\nEnter A, B, or C\n");

    scanf(" %c", &c); /* leave a space to get rid of saved whitespace in buffer */

    switch (c)
    {
        case 'A':
        case 'a':
            puts("You entered A");
            break;
        case 'B':
        case 'b':
            puts("You entered B");
            break;
        default:
            puts("You entered C");
    }


    return 0;
}
