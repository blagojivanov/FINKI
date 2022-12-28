// sortiranje na 3 broja

#include <stdio.h>

void sort (int *a, int *b, int *c)
{
    if (*a<*b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
    if (*a<*c)
    {
        int tmp = *a;
        *a = *c;
        *c = tmp;
    }
    if (*b<*c)
    {
        int tmp = *b;
        *b = *c;
        *c = tmp;
    }
}

int main()
{
    int a, b,c;
    scanf("%d", &a,&b,&c);
    sort(&a,&b,&c);
    printf("%d %d %d", a,b,c);
    return 0;
}
