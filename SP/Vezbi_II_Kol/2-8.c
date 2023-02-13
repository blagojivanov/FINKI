// Во дадена датотека dat.txt да се најде најдолгиот ред во кој има барем 2 цифри.
// На стандарден излез да се испечатат знаците од најдолгиот ред кои се наоѓаат помеѓу
// првата и последната цифра (заедно со тие 2 цифри) во истиот редослед.
// Доколку има повеќе такви редови се печати последниот.
// Се претпоставува дека ниту еден ред на датотеката не е подолг од 100 знаци.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// ne menuvaj ovde
void wtf() {
    FILE *f = fopen("dat.txt", "w");
    char c;
    while((c = getchar()) != '~') {
        fputc(c, f);
    }
    fclose(f);
}

int main() {
    wtf();
    // vasiot kod ovde
    FILE *f = fopen("dat.txt", "r");
    int max_len = 0,maxstrsize;
    char maxstr[100];
    while(!feof(f))
    {
        int gate1 = 0, gate2 = 0, pos1=0, pos2=0;
        char str[100];
        fgets(str, 100, f);
        int size = (int) strlen(str);
        for (int i = 0; i<size/2; i++)
        {
            if (isdigit(str[i]) && gate1 == 0)
            {
                gate1 = 1;
                pos1=i;
            }
            if (isdigit(str[size-1-i]) && gate2 == 0)
            {
                gate2 = 1;
                pos2=size-i;
            }
            if (gate1 && gate2)
            {
                if (max_len <= size)
                {
                    max_len = size;
                    strncpy(maxstr, str+pos1, pos2-pos1);
                    maxstrsize = pos2-pos1;
                    break;
                }
            }
        }
    }
    maxstr[maxstrsize] = '\0';
    printf("%s", maxstr);
    fclose(f);
    return 0;
}
