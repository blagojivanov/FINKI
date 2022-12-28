//Да се прочита број N од тастатура. Да се дефинира функција form(int n) што ќе испечати форма од ѕвезди како што е прикажано на сликата.
//За да се освојат сите поени од вежбата, потребно е функцијата form да биде рекурзивна.

#include <stdio.h>

void form(int n)
{
    int i = 0;
    for (; i<n; i++)
    {
        printf("*");
    }
    printf("\n");
    if (n == 0) return;
    else
        form(n-1);
}
int main()
{
    int n;
    scanf("%d", &n);
    form(n);
    return 0;
}