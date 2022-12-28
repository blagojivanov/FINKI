// da se najdat najgolemio i najmalio element vo niza i da se smenat mestata a site drugi
// elementi da se zgolemat za razlikata na najgolemio i najmalio

#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int fMax(int *arr, int n)
{
    int max = 0, i = 0;
    for (; i<n; i++)
    {
        if (*(arr+max) < *(arr+i))
        {
            max = i;
        }
    }
    return max;
}
int fMin(int *arr, int n)
{
    int min = 0, i = 0;
    for (; i<n; i++)
    {
        if (*(arr+min) > *(arr+i))
        {
            min = i;
        }
    }
    return min;
}

void transform(int *arr, int n)
{
    int max = fMax(arr, n);
    int min = fMin(arr, n);
    int razlika = *(arr+max) - *(arr+min);
    swap(arr+max, arr+min);
    int i = 0;
    for (; i<n; i++)
    {
        if (i == max || i == min)
        {
            continue;
        } else
        {
            *(arr+i) += razlika;
        }
    }
    //swap(arr+max, arr+min);
}

int main()
{
    int n, i;
    scanf("%d", &n);
    int array[100];
    for (i = 0; i<n; i++)
        scanf("%d", &array[i]);

    transform(array, n);

    for (i = 0; i<n; i++)
        printf("%d ", array[i]);
    return 0;
}