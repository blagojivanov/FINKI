//Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер.
//Структурата треба да содржи: (5 поени)
//Фирма која го произведува ( низа од 100 знаци)
//Големина на монитор во инчи (реален број)
//Дали е со touch или не (булова променлива)
//Цена (цел број)
//Да се креира структура ITStore, што содржи: (5 поени)
//
//Име на продавницата (низа од 100 знаци)
//Локација (низа од 100 знаци)
//Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
//Број на елементи во низата (цел број)
//Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)
//
//[Ime na prodavnicata] [Lokacija]
//[Marka1] [dim_monitor1] [Cena1]
//[Marka2] [dim_monitor2] [Cena2]
//[Marka3] [dim_monitor3] [Cena3]
//...
//Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*
//
//Да се дополни функцијата main (10 поени).
//
//Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.
#include <stdio.h>

typedef struct laptop {
    char firma[100];
    float size;
    int touch;
    int price;

} Laptop;

typedef struct ITStore {
    char name[100];
    char location[100];
    Laptop lapotopovi[100];
    int n;
} ITStore;

void print(ITStore store, int size) {
    printf("%s %s\n", store.name, store.location);
    for (int i = 0; i < size; i++) {
        printf("%s %g %d\n", store.lapotopovi[i].firma, store.lapotopovi[i].size, store.lapotopovi[i].price);
    }
}

void najeftina_ponuda(ITStore *itStores, int num) {
    ITStore ch = itStores[0];
    Laptop overallcheapest = itStores[0].lapotopovi[0];
    int first = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < itStores[i].n; j++) {
            if (itStores[i].lapotopovi[j].touch == 1) {
                if (!first)
                {
                    overallcheapest = itStores[i].lapotopovi[j];
                    first = 1;
                }
                if (overallcheapest.price > itStores[i].lapotopovi[j].price)
                {
                    ch = itStores[i];
                    overallcheapest = itStores[i].lapotopovi[j];
                }

            }
        }
//        if (overallcheapest.price > cheapest.price)
//        {
//            overallcheapest=cheapest;
//        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n");
    printf("%s %s\n", ch.name, ch.location);
    printf("Najniskata cena iznesuva: %d", overallcheapest.price);
}

int main() {
    ITStore s[100];
    int n;
    scanf("%d", &n); //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for (int i = 0; i < n; i++) {
        scanf("%s\n%s\n", s[i].name, s[i].location);
        scanf("%d", &s[i].n);
        for (int j = 0; j < s[i].n; j++) {
            scanf("%s\n%f%d%d", s[i].lapotopovi[j].firma, &s[i].lapotopovi[j].size, &s[i].lapotopovi[j].touch,
                  &s[i].lapotopovi[j].price);
        }
    }
    //pecatenje na site prodavnici

    for (int i = 0; i<n; i++)
    {
        print(s[i], s[i].n);
    }

    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}