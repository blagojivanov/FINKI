//Од стандарден влез се чита еден број кој претставува датум во формат DDMMYYYY
//(DD-ден, MM-месец, YYYY-година) кој го означува денешниот датум. Потоа се
//вчитува цел број N, по кој се вчитуваат N датуми на раѓање во дадениот
//формат. За секој од прочитаните N датуми на раѓање треба да се отпечати "DA"
//ако на денешниот ден (вчитан на почетокот) има повеќе или точно 18 години,
//а во спортивно "NE".

#include <stdio.h>

int main()
{
    int date, n, i;
    scanf("%d", &date);
    scanf("%d", &n);

    for (i = 0; i<n; i++) {
        int newdate, y,m,d;
        scanf("%d", &newdate);
        y = date%1000 - newdate%1000;
        m = date/1000%100 - newdate/1000%100;
        d = date/1000000 - newdate/1000000;
        if (y<18)
        {
            printf("NE");
        } else if (y == 18)
        {
            if (m < 0)
            {
                printf("NE");
            } else
            {
                if (d<=0)
                {
                    printf("DA");
                } else
                {
                    printf("NE");
                }
            }
        } else
        {
            printf("DA");
        }
    }
    return 0;
}