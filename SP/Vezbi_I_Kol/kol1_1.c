//Од тастатура се вчитува природен број N, а потоа се вчитуваат последователно N тројки цели броеви (a, b, c).
//Нека за секоја тројка цели броеви a, b и c се дефинира вредност rez што се пресметува според следната формула:
//rez = 2*min – max/2 + |min - a|
//кадешто min е најмалиот број од тројката, а max - најголемиот број од тројката броеви a, b, c.
//На излез да се испечати вредноста rez за секоја од тројките броеви, во посебни редови, според форматот во примерот.
//Пр. Влез: 2 5 1 5 2 -10 6
//Излез: 3.50 -11.00

#include <stdlib.h>
#include <stdio.h>
int main()
{
    int n,i;
    scanf("%d", &n);
    for (i = 0; i<n; i++)
    {
        int a,b,c,locmin, locmax;
        scanf("%d%d%d", &a,&b,&c);
        locmin = locmax = a;
        if (locmin > b)
        {
            locmin = b;
        }
        if (locmin > c)
        {
            locmin = c;
        }
        if (locmax < b)
        {
            locmax = b;
        }
        if (locmax < c)
        {
            locmax = c;
        }

        float rez = 2*locmin - locmax/2.0 + abs(locmin-a);
        printf("%f", rez);
    }
    return 0;
}