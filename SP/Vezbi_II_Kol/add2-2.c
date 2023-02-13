//Од тастатура се чита природен број N (N < 400).
//Да се напише програма којашто формира квадратна матрица што ги содржи броевите од 1 до N по
//растечки редослед на следниот начин: во првата колона во правец од горе надолу,
//па продолжува во втората колона од долу нагоре, па продолжува во третата колона од горе надолу итн.
//Да се избере најмалата димензија на матрицата во која ќе ги собере сите броеви до N.
//Доколку има преостанати празни места, тие да се пополнат со нули.
//Формираната матрица да се запише во датотека "shema.txt".

#include <stdio.h>
#include <math.h>
void printFile() {
    FILE *f=fopen("shema.txt","r");
    char line[1000];
    while(!feof(f)){
        fgets(line,1000,f);
        if (feof(f))
            break;
        printf("%s",line);
    }
    fclose(f);
}

int main()
{
    int a[20][20];
    int n;
    scanf("%d", &n);
    int c = 1;
    for (int j = 0; j<ceil(sqrt(n)); j++) {
        if (c <= n) {
            if (j % 2 == 0) {
                for (int i = 0; i < ceil(sqrt(n)); i++) {
                    a[i][j] = c;
                    if (c!=0 && ++c>n)
                    {
                        c = 0;
                    }
                }
            } else {
                for (int i = ceil(sqrt(n)) - 1; i >= 0; i--) {
                    a[i][j] = c;
                    if (c != 0 && ++c>n)
                    {
                        c = 0;
                    }
                }
            }
        }
    }
    FILE *f = fopen("C:\\Users\\Blagoj\\CLionProjects\\FINKI\\SP\\Vezbi_II_Kol\\shema.txt", "w");
    for (int i = 0; i<ceil(sqrt(n)); i++)
    {
        for (int j = 0; j<ceil(sqrt(n)); j++)
        {
            fprintf(f,"%d ", a[i][j]);
        }
        fprintf(f,"\n");
    }
//    for (int i = 0; i<ceil(sqrt(n)); i++)
//    {
//        for (int j = 0; j<ceil(sqrt(n)); j++)
//        {
//            printf("%d ", a[i][j]);
//        }
//        printf("\n");
//    }

    //printFile();
    fclose(f);
    return 0;
}