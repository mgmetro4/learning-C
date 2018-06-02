/* Variable Keywords and their sizes using GNU Compiler Collection (GCC) */
/* Exact sizes depend on the compiler */

#include <stdio.h>

int main()
{
    char c = 1;
    short int si = 2;
    int i = 2;
    long  int li = 2;
    long long int lli = 2;
    float f = 2.0;
    double d = 2.0;
    long double ld = 2.0;
    long l = 2;
    long long ll = 2;

    printf("Size of Char: %d\n", sizeof(c));
    printf("Size of Short Int: %d\n", sizeof(si));
    printf("Size of int: %d\n", sizeof(i));
    printf("Size of Long Int: %d\n", sizeof(li));
    printf("Size of Long Long Int: %d\n", sizeof(lli));
    printf("Size of Float: %d\n", sizeof(f));
    printf("Size of Double: %d\n", sizeof(d));
    printf("Size of Long Double: %d\n", sizeof(ld));
    printf("Size of Long: %d\n", sizeof(l));
    printf("Size of Long Long: %d\n", sizeof(ll));

    return 0;
}