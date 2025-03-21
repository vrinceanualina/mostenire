#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Vehicul {
protected:
    string nr_inmatriculare;
    int ora_intrare, minut_intrare;
    int ora_iesire, minut_iesire;

public:
    Vehicul (string nr_inmatriculare, int ora_intrare, int minut_intrare, int ora_iesire, int minut_iesire)
        : nr_inmatriculare(nr_inmatriculare), ora_intrare(ora_intrare), minut_intrare(minut_intrare),
          ora_iesire(ora_iesire), minut_iesire(minut_iesire) {}
    
    virtual ~Vehicul() = default;

    int calculeaza_timp_petrecut() const {
        int timp_total_intrare = ora_intrare * 60 + minut_intrare;
        int timp_total_iesire = ora_iesire * 60 + minut_iesire;
        return timp_total_iesire - timp_total_intrare;
    }

    virtual double calculeaza_tarif() const = 0;

    void afiseaza_informatii() const {
        cout << "Tip: " << tip_vehicul() << ", Nr Inmatriculare: " << nr_inmatriculare
             << ", Timp Petrecut: " << calculeaza_timp_petrecut() / 60.0 << " h"
             << ", Tarif: " << calculeaza_tarif() << " lei\n";
    }

protected:
    virtual string tip_vehicul() const = 0;
};

class Masina : public Vehicul {
public:
    Masina(string nr_inmatriculare, int ora_intrare, int minut_intrare, int ora_iesire, int minut_iesire)
        : Vehicul(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire) {}

    double calculeaza_tarif() const override {
        return calculeaza_timp_petrecut() / 60.0 * 5.0;
    }

protected:
    string tip_vehicul() const override {
        return "Masina";
    }
};

class Motocicleta : public Vehicul {
public:
    Motocicleta(string nr_inmatriculare, int ora_intrare, int minut_intrare, int ora_iesire, int minut_iesire)
        : Vehicul(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire) {}

    double calculeaza_tarif() const override {
        return calculeaza_timp_petrecut() / 60.0 * 3.0;
    }

protected:
    string tip_vehicul() const override {
        return "Motocicleta";
    }
};

class Camion : public Vehicul {
public:
    Camion(string nr_inmatriculare, int ora_intrare, int minut_intrare, int ora_iesire, int minut_iesire)
        : Vehicul(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire) {}

    double calculeaza_tarif() const override {
        return calculeaza_timp_petrecut() / 60.0 * 10.0;
    }

protected:
    string tip_vehicul() const override {
        return "Camion";
    }
};

class Bicicleta : public Vehicul {
public:
    Bicicleta(string nr_inmatriculare, int ora_intrare, int minut_intrare, int ora_iesire, int minut_iesire)
        : Vehicul(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire) {}

    double calculeaza_tarif() const override {
        int timp_petrecut = calculeaza_timp_petrecut();
        if (timp_petrecut < 120) {
            return 0.0;
        } else {
            return (timp_petrecut - 120) / 60.0 * 2.0;
        }
    }

protected:
    string tip_vehicul() const override {
        return "Bicicleta";
    }
};

void citeste_date_din_fisier(const string& fisier_nume, vector<Vehicul*>& vehicule) {
    ifstream fisier(fisier_nume);
    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fisierului.\n";
        return;
    }

    string linie;
    while (getline(fisier, linie)) {
        istringstream iss(linie);
        string tip_vehicul, nr_inmatriculare;
        int ora_intrare, minut_intrare, ora_iesire, minut_iesire;
        char separator;

        iss >> tip_vehicul >> nr_inmatriculare >> ora_intrare >> separator >> minut_intrare >> ora_iesire >> separator >> minut_iesire;

        if (tip_vehicul == "Masina") {
            vehicule.push_back(new Masina(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire));
        } else if (tip_vehicul == "Motocicleta") {
            vehicule.push_back(new Motocicleta(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire));
        } else if (tip_vehicul == "Camion") {
            vehicule.push_back(new Camion(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire));
        } else if (tip_vehicul == "Bicicleta") {
            vehicule.push_back(new Bicicleta(nr_inmatriculare, ora_intrare, minut_intrare, ora_iesire, minut_iesire));
        }
    }

    fisier.close();
}

int main() {
    vector<Vehicul*> vehicule;
    citeste_date_din_fisier("parcari.txt", vehicule);

    for (const auto& vehicul : vehicule) {
        vehicul->afiseaza_informatii();
        delete vehicul;
    }
    
    vehicule.clear();
    return 0;
}
