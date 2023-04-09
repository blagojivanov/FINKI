#include <iostream>
#include <cstring>

struct Laptop {
    char firma[100];
    float size;
    int touch;
    int price;

};

struct ITStore {
    char name[100];
    char location[100];
    Laptop lapotopovi[100];
    int n;
};

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