//Од тастатура се вчитуваат броевите A и B. На екран да се испечатат сите броеви од интервалот [A,B]
//кои се палиндроми и се составени само од цифрите 0,1,2,3 и 4.
//Предлог за работа:
//Да се имплементира функција reverseNumber (int number) која ќе го пресмета обратниот број на определен број number.
//Да се имплементира функција isPalindrome (int number) која ќе врати 1 доколку бројот number е палиндром, а 0 во спротивно
//Да се имплементира функција containsDigits (int number) која ќе врати 1 доколку сите цифри во бројот се 0,1,2,3 или 4, а 0 во спротивно.
//Да се искористат функциите isPalindrome и containsDigits во main функцијата
//Дополнително: Направете ја функцијата containsDigits рекурзивна.

#include <stdio.h>

int reverseNumber(int number)
{
    int sum=0;
    while(number>0)
    {
        sum*=10;
        sum+=number%10;
        number/=10;
    }
    return sum;
}

int isPalindrome(int number)
{
    return (reverseNumber(number) == number);
}

int containsDigits(int number)
{
    if (number%10 == 0 || number%10 == 1 || number%10 == 2 || number%10 == 3 || number%10 == 4)
    {
        if (number == 0)
            return 0;
        else
            return containsDigits(number/10);
    } else
        return number;
}

int main()
{
    int a,b,i;
    scanf("%d%d", &a,&b);
    for (i = a; i<=b; i++)
    {
        if (isPalindrome(i))
        {
            if (containsDigits(i) == 0)
            {
                printf("%d\n", i);
            }
        }
    }
    return 0;
}