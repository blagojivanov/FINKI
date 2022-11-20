//Од стандарден влез се вчитува број N, а потоа и N цели броеви.
//Да се испечати на екран најголемата разлика помеѓу два последователно внесени броја.
//Да се реши без користење на низи!
//Објаснување на примерот:
//N=5, па се внесуваат 5 броја: 1,3,0,5,2. Разликите се соодветно:
//3-1 = 2
//0-3 = -3
//5-0 = 5
//2-5 = -3
//
//Најголема разлика е 5.

#include <stdio.h>

int main() {
    int n, prevnum, i = 1, maxraz;
    scanf("%d", &n);
    scanf("%d", &prevnum);
    while (i < n) {

        int currn, raz;
        scanf("%d", &currn);
        raz = currn - prevnum;
        prevnum = currn;
        if (i == 1) {
            maxraz = raz;
        }
        if (raz > maxraz) {
            maxraz = raz;
        }
        i++;

    }
    printf("%d", maxraz);
    return 0;
}
