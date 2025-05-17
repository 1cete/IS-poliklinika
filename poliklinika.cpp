#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Bazinė klasė Darbuotojas
class Darbuotojas {
protected:
    string vardas;
    string pavarde;
    string pareigos;
    bool uzimtas;
public:
    Darbuotojas(string v, string p, string par)
        : vardas(v), pavarde(p), pareigos(par), uzimtas(false) {}

    string getVardas() { return vardas; }
    string getPavarde() { return pavarde; }
    string getPareigos() { return pareigos; }
    bool arUzimtas() { return uzimtas; }

    void uzimti() { uzimtas = true; }
    void atlaisvinti() { uzimtas = false; }

    virtual void info() {
        cout << left << setw(25) << pareigos
             << setw(20) << (vardas + " " + pavarde)
             << (uzimtas ? "- uzimtas" : "- laisvas") << endl;
    }
};

// Paveldima klasė Gydytojas
class Gydytojas : public Darbuotojas {
public:
    Gydytojas(string v, string p, string specializacija)
        : Darbuotojas(v, p, specializacija) {}
};

// Paveldima klasė Slaugytoja
class Slaugytoja : public Darbuotojas {
public:
    Slaugytoja(string v, string p) : Darbuotojas(v, p, "Slaugytoja") {}
};

// Pacientas klasė
class Pacientas {
    string vardas;
    string sveikatosBusena;
    int laukimoLaikas;
public:
    Pacientas(string v, string sb) : vardas(v), sveikatosBusena(sb), laukimoLaikas(0) {}

    void didintiLaukimoLaika() { laukimoLaikas++; }
    string getVardas() { return vardas; }
    string getSveikatosBusena() { return sveikatosBusena; }
    int getLaukimoLaikas() { return laukimoLaikas; }

    void info() {
        cout << "- Pacientas: " << vardas << ", sveikatos būklė: " << sveikatosBusena
             << ", laukimo laikas: " << laukimoLaikas << " min." << endl;
    }
};

// Poliklinika klasė
class Poliklinika {
    vector<Darbuotojas*> darbuotojai;
    vector<Pacientas> pacientai;
public:
    ~Poliklinika() {
        for (auto d : darbuotojai) delete d;
    }

    void sveikinimas() {
        cout << "=== Sveiki atvykę į Antakalnio polikliniką ===\n\n";
    }

    void pridetiDarbuotoja(Darbuotojas* d) {
        darbuotojai.push_back(d);
    }

    void pridetiPacienta(const Pacientas& p) {
        pacientai.push_back(p);
    }

    void rodytiDarbuotojus() {
        cout << "Darbuotojai:\n";
        cout << left << setw(25) << "Pareigos"
             << setw(20) << "Vardas Pavardė"
             << "Būsena" << endl;
        cout << string(60, '-') << endl;
        for (auto d : darbuotojai) {
            d->info();
        }
        cout << endl;
    }

    void rodytiPacientus() {
        cout << "Pacientai:\n";
        for (auto& p : pacientai) {
            p.info();
        }
        cout << endl;
    }

    void priskirtiGydytojusPacientams() {
        cout << "Priskyrimai:\n";
        int dIndex = 0;
        for (auto& pacientas : pacientai) {
            while (dIndex < darbuotojai.size() && darbuotojai[dIndex]->arUzimtas()) {
                dIndex++;
            }
            if (dIndex < darbuotojai.size()) {
                darbuotojai[dIndex]->uzimti();
                cout << "- " << darbuotojai[dIndex]->getPareigos() << " "
                     << darbuotojai[dIndex]->getVardas() << " " << darbuotojai[dIndex]->getPavarde()
                     << " priskirtas pacientui " << pacientas.getVardas() << endl;
                dIndex++;
            } else {
                cout << "- Nėra laisvų gydytojų pacientui " << pacientas.getVardas() << endl;
            }
        }
        cout << endl;
    }
};

int main() {
    Poliklinika poliklinika;
    poliklinika.sveikinimas();

    // Gydytojai su specializacijomis
    poliklinika.pridetiDarbuotoja(new Gydytojas("Jonas", "Kazlauskas", "Šeimos gydytojas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Rasa", "Petrauskienė", "Šeimos gydytojas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Agnė", "Vaitkutė", "Vaikų ligų gydytojas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Mindaugas", "Urbonas", "Akušeris ginekologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Jurgita", "Stanevičiūtė", "Psichologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Tomas", "Šalkauskis", "Kineziterapeutas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Simona", "Mažeikytė", "Oftalmologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Vytautas", "Paškevičius", "Kardiologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Rūta", "Marcinkevičienė", "Neurologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Edita", "Jurkevičiūtė", "Dermatologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Dainius", "Giedraitis", "Otorinolaringologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Loreta", "Žukauskaitė", "Psichiatras"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Justė", "Kuprevičiūtė", "Pediatras"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Algis", "Tamkevičius", "Anesteziologas reanimatologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Tautvydas", "Kairys", "Urologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Monika", "Grigaitė", "Gastroenterologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Indrė", "Sabaliauskaitė", "Ergoterapeutas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Andrius", "Dirgėla", "Pulmonologas"));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Ramunė", "Milinienė", "Radiologas"));

    // Slaugytojos (5)
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Neringa", "Balčiūnaitė"));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Eglė", "Drungilaitė"));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Asta", "Kalvaitienė"));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Renata", "Kundrotienė"));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Laima", "Navickaitė"));

    // Pavyzdiniai pacientai
    poliklinika.pridetiPacienta(Pacientas("Petras", "Galvos skausmas"));
    poliklinika.pridetiPacienta(Pacientas("Ieva", "Kosulys"));
    poliklinika.pridetiPacienta(Pacientas("Lukas", "Pilvo skausmai"));
    poliklinika.pridetiPacienta(Pacientas("Greta", "Alergija"));
    poliklinika.pridetiPacienta(Pacientas("Martynas", "Akių paraudimas"));

    poliklinika.rodytiDarbuotojus();
    poliklinika.rodytiPacientus();
    poliklinika.priskirtiGydytojusPacientams();

    return 0;
}