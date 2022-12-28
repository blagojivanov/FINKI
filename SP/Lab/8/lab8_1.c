//Да се дефинираат функциите:
//divisibleByK (int number, int k) - која ќе враќа 1 доколку бројот k е делител на бројот number, a 0 во спротивно
//nextDivisibleByK (int number, int k) - која ќе го врати првиот број поголем од number кој е делив со k. Да се употреби повик до divisibleByK во ова функција.
//Да не се менува main функцијата!
//Објаснување на примерот: Во секоја линија лево од стрелката се печати секој број од интервалот од [10,20],
//а десно од стрелката се печати наредниот број поголем од бројот лево којшто е делив со бројот k.
//Бонус: Направете ја функцијата nextDivisibleByK рекурзивна.

#include <stdio.h>

int divisibleByK(int number, int k)
{
    return (number%k) ? 0 : 1;
}

int nextDivisibleByK(int number, int k)
{
    return (divisibleByK(number+1,k)) ? number+1 : nextDivisibleByK(number+1, k);
}

int main() {

    int a, b, k;
    scanf("%d %d %d", &a, &b, &k);

    for (int i = a; i <= b; i++) {
        printf("%d -> %d\n", i, nextDivisibleByK(i, k));
    }

    return 0;
}
