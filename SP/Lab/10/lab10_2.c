//Од стандарден влез да се прочита една низа од знаци со најмногу 100 карактери. Да се трансформира низата така што левата и десната половина од стрингот ќе си ги сменат местата.
//
//Напомена: Сите тест примери ќе имаат парен број на знаци.

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 100
            // 0 1 2 3 4 5
int main()  // S t e f a n \0
{
    char str[MAX];
    scanf("%s", str);
    int n = strlen(str);
    for (int i = 0; i<n/2; i++)
    {
        char tmp = str[i];
        str[i] = str[n/2 + i];
        str[n/2 + i] = tmp;
    }
    printf("%s", str);
    return 0;
}