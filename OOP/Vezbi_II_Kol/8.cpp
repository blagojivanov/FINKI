#include <iostream>
#include <cstring>

using namespace std;

class Koncert {
private:
    char naziv[20];
    char lokacija[20];
    float popust;
    float bilet;

public:
    Koncert(const char *naziv = "", const char *lokacija = "", float bilet = 0) {
        strcpy(this->naziv, naziv);
        strcpy(this->lokacija, lokacija);
        this->bilet = bilet;
        popust = 20;
    }

    virtual float cena() {
        float c = bilet;
        c*=(1-(popust/100));
        return c;
    }

    const char *getNaziv() const {
        return naziv;
    }

    void setNaziv(const char *naziv) {
        strcpy(this->naziv, naziv);
    }

    const char *getLokacija() const {
        return lokacija;
    }

    void setLokacija(const char *lokacija) {
        strcpy(this->lokacija, lokacija);
    }

    float getBilet() const {
        return bilet;
    }

    void setBilet(int c) {
        bilet = c;
    }

    float getSezonskiPopust()
    {
        return popust/100;
    }

    float setSezonskiPopust(int p)
    {
        popust= p*100;
    }
};

class ElektronskiKoncert : public Koncert {
private:
    char *name;
    float hrs;
    bool daynnite;

public:
    ElektronskiKoncert(const char *naziv = "", const char *lokacija = "", float bilet = 0, const char *name = "",
                       float hrs = 0, bool daynnite = false)
            : Koncert(naziv, lokacija, bilet) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->hrs = hrs;
        this->daynnite = daynnite;
    }

    ElektronskiKoncert(const ElektronskiKoncert &ek)
            : Koncert(ek) {
        this->name = new char[strlen(ek.name) + 1];
        strcpy(this->name, ek.name);
        this->hrs = ek.hrs;
        this->daynnite = ek.daynnite;
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &ek) {
        if (this == &ek) return *this;
        delete[] name;
        this->setNaziv(ek.getNaziv());
        this->setLokacija(ek.getLokacija());
        this->setBilet(ek.getBilet());
        this->name = new char[strlen(ek.name) + 1];
        strcpy(this->name, ek.name);
        this->hrs = ek.hrs;
        this->daynnite = ek.daynnite;
    }

    float cena() override {
        float c = Koncert::cena();
        if (hrs > 7) {
            c += 360;
        } else if (hrs > 5) {
            c += 150;
        }
        if (daynnite) {
            c -= 50;
        } else {
            c += 100;
        }
        return c;
    }

    ~ElektronskiKoncert() {
        delete[] name;
    }
};

void najskapKoncert(Koncert **koncerti, int n) {
    int id = 0;
    int max = koncerti[0]->cena();
    for (int i = 1; i < n; i++) {
        if (max < koncerti[i]->cena())
        {
            max = koncerti[i]->cena();
            id = i;
        }
    }
    int c = 0;
    for (int i = 0; i<n; i++)
    {
        ElektronskiKoncert  *ek = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if (ek != 0) c++;
    }

    cout<<"Najskap koncert: "<<koncerti[id]->getNaziv()<<" "<<koncerti[id]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<c<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski)
{
    bool found = false;
    int id = 0;
    for (int i = 0; i<n; i++)
    {
        if (strcmp(koncerti[i]->getNaziv(), naziv) == 0)
        {
            if (elektronski)
            {
                ElektronskiKoncert *ek = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
                if (ek != 0)
                {
                    id = i;
                    found = true;
                }
            } else
            {
                id = i;
                found = true;
            }
        }

    }
    if (found)
    {
        cout<<koncerti[id]->getNaziv()<<" "<<koncerti[id]->cena()<<endl;
        return true;
    }
    return false;
}

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else cout << "Ne e pronajden" << endl;

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 1000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 1100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
