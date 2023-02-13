//Од стандарден влез се чита природен број N (N <= 100), како и низа од позитивни цели броеви a[ ] со N елементи.
//Да се напише функција int par(a, n)
//која ќе го врати најмалиот елемент во низата кој се појавува парен број пати во низата. Доколку нема таков елемент, функцијата враќа вредност 0.
//Напишете програма што ќе ја повика функцијата par за внесената низа a[ ] и ќе го испечати најмалиот број којшто се појавува парен број пати во низата a[ ].

#include <stdio.h>

void sort(int *a, int n)
{
    for (int i = 0; i<n; i++)
    {
        int min = a[i], min_pos = i;
        for (int j = i+1; j<n; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                min_pos = j;
            }
        }
        int temp = a[i];
        a[i] = a[min_pos];
        a[min_pos] = temp;
    }
}

int par(int *a, int n)
{
    sort(a,n);
    for (int j = 0; j<n; j++)
    {
        int min = a[j];
        int tempct = 0;
        for (int i = j; i < n; i++)
        {
            if (a[i] == min)
            {
                tempct++;
                j++;
            }
        }
        if (tempct%2 == 0)
        {
            return min;
        } else
        {
            j--;
        }
    }
    return 0;
}

int main()
{
    int n,a[100];
    scanf("%d", &n);
    for (int i = 0; i<n; i++)
    {
        scanf("%d", &a[i]);
    }
    int num = par(a,n);
    if (num > 0)
    {
        printf("Najmaliot element koj se pojavuva paren broj pati e %d", num);
    } else
    {
        printf("Nitu eden element ne se pojavuva paren broj pati!");
    }
    return 0;
}