//Да се напише програма која за петцифрен број внесен од стандарден влез ќе ја пресмета сумата на цифрите на парните и непарните позиции соодветно.
//Напомена: Последната цифра во бројот се наоѓа на 0-та позиција.
//Појаснување: За бројот 54321 цифрата на 0-та позиција е 1, додека цифрата на 4-та позиција е 5.

#include <stdio.h>

int main() {
    int a, sump = 0, sumnp = 0;
    scanf("%d", &a);
    sump = a % 10 + a / 100 % 10 + a / 10000;
    sumnp = a / 10 % 10 + a / 1000 % 10;
    printf("Sumata na cifrite na parnite pozicii e %d\nSumata na cifrite na neparnite pozicii e %d", sump, sumnp);
    return 0;
}