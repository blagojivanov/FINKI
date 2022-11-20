//Од тастатура се внесуваат 5 позитивни цели броеви едно по друго. Да се испечати бројот на непарни броеви кој што се внесени.
#include <stdio.h>

int main() {
    int a, b, c, d, e, counter = 0;
    scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
    counter += a % 2;
    counter += b % 2;
    counter += c % 2;
    counter += d % 2;
    counter += e % 2;
    printf("%d", counter);
    return 0;
}