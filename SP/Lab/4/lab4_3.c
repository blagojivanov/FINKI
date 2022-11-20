//Од тастатура се внесуваат цели броеви се додека не се внесе нешто што не е цел број.
//Да се испечати на екран сумата на броевите во кои цифрите се подредени во опаѓачки редослед. Доколку нема такви броеви, да се испечати порака NEMA.
#include <stdio.h>

int main() {
    int n, sum = 0, brojac = 0;
    while (scanf("%d", &n)) {
        int ncpy = n;
        while (ncpy > 9) {
            if (ncpy % 10 < ncpy / 10 % 10) {
                ncpy /= 10;
            } else {
                break;
            }
        }
        if (ncpy < 10) {
            sum += n;
            brojac++;
        }
    }
    if (brojac == 0) {
        printf("NEMA");
    } else {
        printf("%d", sum);
    }
    return 0;
}