//Дадена е текстуална датотека (livce.txt) која претставува ливче во спортска обложувалница.
//На почетокот во датотеката, во посебен ред е запишана сумата на уплата (цел број).
//Потоа во секој ред од датотеката е запишан по еден тип во следниот формат:
//ab12 1 1.25
//Првиот број е шифрата на типот (низа од знаци која не е подолга од 9 знаци),
//вториот број е типот (може да биде 1, 0 или 2) додека третиот број е коефициентот (реален број).
//Ваша задача е да се испечати типот со најголем коефициент како и можната добивка на ливчето.
//Доколку има повеќе типови со ист максимален коефициент, да се испечати првиот.
//Можната добивка се пресметува како производ на сите коефициенти со сумата на уплата.
#include <stdio.h>

// ne menuvaj ovde
void wf() {
    FILE *f = fopen("livce.txt", "w");
    char c;
    while ((c = getchar()) != '#') {
        fputc(c, f);
    }
    fclose(f);
}

int main() {
    wf();

    FILE *f = fopen("livce.txt", "r");
    int n;
    fscanf(f, "%d", &n);
    double coeff = 1, max_coeff = 1, coefficients[100];
    char mat[100][9];
    int i = 0, maxpos = 0, tips[100];
    while (!(feof(f))) {
        fscanf(f, "%s %d %lf\n", mat[i], &tips[i], &coefficients[i]);
//        if (mat[i][0] == '\0') {
//            coeff*=1.0;
//            break;
        coeff *= coefficients[i];
        //printf("%.2f %d\n", coeff, i);
        if (coefficients[i] > max_coeff) {
            max_coeff = coefficients[i];
            maxpos = i;
        }
        i++;
    }

    printf("%s %d %.2lf\n", mat[maxpos], tips[maxpos], coefficients[maxpos]);
    printf("%.2lf", coeff*n);
    fclose(f);
    return 0;
}