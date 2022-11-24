//Од тастатура се внесува цел број m, а потоа непознат број цели броеви. Да се
//испечатат должините на секвенците составени од најмалку два
//последователни броја за кои истовремено важи:
//• следниот број е строго поголем од претходниот и
//• секој од нив има точно m цифри.
//Задачата да се реши без користење на низи.

#include <stdio.h>

int main()
{
    int m,k, seq = 1, prev, tf = 0, prevnd = 0;
    scanf("%d",&m);
    while(scanf("%d", &k)) {
        int kcpy = k, temp = 0;
        while (kcpy)
        {
            temp++;
            kcpy/=10;
        }

        if (tf == 0)
        {
            tf = 1;
        } else
        {
            if (prev < k && prevnd == m && temp ==m)
            {
                seq++;
            } else
            {
                if (seq>=2)
                {
                    printf("%d ", seq);
                    seq = 1;
                }
            }
        }
        prevnd = temp;
        prev = k;
    }
    if (seq >=2)
    {
        printf("%d", seq);
    }
    return 0;
}