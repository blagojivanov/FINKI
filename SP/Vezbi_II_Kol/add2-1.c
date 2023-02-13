//Од стандарден влез се чита цел број N (N<=100) и потоа N низи од знаци.
//Низите знаци содржат букви, цифри и специјални знаци (без знаци за празно место), а секоја од нив не е подолга од 80 знаци.
//Да се напише програма со која што на стандарден излез ќе се отпечати најдолгата низа, којашто е палиндром
//(се чита исто од од лево на десно и од десно на лево) и што содржи барем еден специјален знак. Ако нема такви низи, се печати "Nema!".
//Ако има две или повеќе низи што го задоволуваат овој услов, се печати првата низа којашто го задоволува условот.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isPalindrome(char *st)
{
    for (int i = 0; i< strlen(st)/2; i++)
    {
        if (*(st+i) != *(st+strlen(st)-i-1))
        {
            return 0;
        }
    }
    return 1;
}

int containsSpec(char *c)
{
    for (int i = 0; i< strlen(c); i++)
    {
        if (!isalnum(c[i]))
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n, maxlen=0,maxpos = 0, ct=0;
    scanf("%d", &n);
    char st[100][80];

    for (int i = 0; i<n; i++)
    {
        scanf("%s", st[i]);
    }
    for (int i = 0; i<n; i++)
    {
        if (isPalindrome(st[i]) && containsSpec(st[i]))
        {
            ct++;
            if (strlen(st[i]) > maxlen)
            {
                maxlen = strlen(st[i]);
                maxpos = i;
            }
        }
    }
    if (!ct)
    {
        printf("Nema!");
    } else
    {
        printf("%s", st[maxpos]);
    }

    return 0;
}