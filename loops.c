#include <stdio.h>
#include <stdbool.h> /* BOOLEAN VALUES */

int main() {
    printf("Infinite While Loop with a break statement..."\n);

    while(true){
        printf("LOOPING\n");
        printf("BREAK\n");
        break;
    }

    printf("\nDo While Loop\n");
    int x = 0;
    do{
        printf("%d \n", x);
        x++;
    } while(x <= 10);

    printf("\n For Loop\n");
    for(int i = 0; i < 5; i++)
        printf("%c\n", 'a'+i);
}