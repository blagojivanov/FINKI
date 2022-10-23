/*
 * Од стандарден влез се чита еден природен број n.
 * Меѓу природните броеви помали од n, да се најде оној чиј што збир на делителите е најголем.
 * Во пресметувањето на збирот на делителите на даден број, да не се зема предвид самиот број.
 * */
#include <stdio.h>

int main() {
    int n, zbirmax = 0, imax;
    scanf("%d", &n);
    for (int i = n-1; i>0; i--)
    {
        int zbirdel = 1;
        for (int del = 2; del < i/2 +1 ; del++)
            if (i%del == 0)
                zbirdel+=del;
        if (zbirdel > zbirmax)
        {
            zbirmax = zbirdel;
            imax = i;
        }
    }
    printf("%d",imax);
    return 0;
}

/*
 * TEST SLUCAI (Input - Output)
 * 10 - 8
 * 50 - 48
 * 1000 - 960
 * 11 - 10
 * 30 - 24
 * 40 - 36
 * 20 - 18
 * */
