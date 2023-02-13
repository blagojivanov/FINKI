//Во датотеката podatoci.txt се запишани редови со низи од знаци (секој не подолг од 80 знаци).
//
//Од стандарден влез се читаат два знака z1 и z2. Да се напише програма со која на стандарден излез ќе се испечатат поднизите од секој ред од датотеката составени од знаците што се наоѓаат меѓу z1 и z2 (без нив). Секоја подниза се печати во нов ред.
//
//Се смета дека секој ред од датотеката точно еднаш ги содржи знаците z1 и z2, знакот z1 секогаш се наоѓа пред знакот z2, а меѓу z1 и z2 секогаш има барем еден знак.
//nfjskdz0nvjkfdmnlks9bvfkjmcdz,
//bfhjdskvfdkl0fvkdzddjmje k dmkldz kdfds!%mlacsd9
//0fbnrjkdn9
//fjkd0jdfkfmjndksfjd;sj sad;jm 9nfcjka
//#
//09

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void wtf()
{FILE *f = fopen("podatoci.txt", "w");
    char c;
    while ((c = getchar()) != '#') {
        fputc(c, f);
    }
    //fputc(EOF,f);
    fclose(f);
}

int main()
{
    wtf();
    char z1,z2,e;
    scanf("%c%c%c",&e,&z1,&z2);
    FILE *f = fopen("podatoci.txt", "r");

    while(1) {
        char str[81];
        fgets(str,81,f);
        if (feof(f))
        {
            break;
        }
        int pos1=0, pos2=0;
        for (int i = 0; i<strlen(str); i++)
        {
            if (str[i] == z1 && pos1 == 0)
            {
                pos1 = i+1;
            }
            if (str[i] == z2 && pos1 > 0)
            {
                pos2 = i-1;
                break;
            }
        }

        for (int i = pos1; i<=pos2; i++)
        {
            printf("%c", str[i]);
        }

        printf("\n");
    }
    fclose(f);
    return 0;
}