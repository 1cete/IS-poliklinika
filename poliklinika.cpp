#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void rodytiMeniu() {
    std::cout << "\n _________________________________\n";
    std::cout << "\n--- POLIKLINIKOS VALDYMO MENIU ---\n";
    std::cout << "\n _________________________________\n";
    std::cout << "1. Naujas pacientas\n";
    std::cout << "2. Paslaugų kainos\n";
    std::cout << "3. Paskirti gydytoją pacientui\n";
    std::cout << "4. Darbuotojų ištekliai\n";
    std::cout << "5. Įvykių sąrašas\n";
    std::cout << "6. Priimti sprendimą dėl įvykio\n";
    std::cout << "7. Pacientų rezultatai\n";
    std::cout << "8. Darbuotojų sąrašas\n";
    std::cout << "9. Prižiūrėti paciento gydymą\n";
    std::cout << "10. Peržiūrėti pacientų pasitenkinimą\n";
    std::cout << "11. Perkelti pacientą\n";
    std::cout << "12. Valdyti finansus ir įrangą\n";
    std::cout << "13. Reaguoti į inspekciją\n";
    std::cout << "0. Išeiti iš žaidimo\n";
    std::cout << "-----------------------------------\n";
    std::cout << "Pasirinkite veiksmą (įveskite skaičių): ";

}

void pradetiZaidima() {
    int pasirinkimas;
    do {
        rodytiMeniu();
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                // registruotiPacienta();
                break;
            case 2:
                // nustatytiPaslauguKainas();
                break;
            case 3:
                // skubiaiPaskirtiGydytoja();
                break;
            case 4:
                // valdytiDarbuotojus();
                break;
            case 5:
                // matytiIvykius();
                break;
            case 6:
                // sprendimasDelIvykio();
                break;
            case 7:
                // perziuretiRezultatus();
                break;
            case 8:
                // tvarkytiDarbuotojuSarasa();
                break;
            case 9:
                // priziuretiGydymoProcesa();
                break;
            case 10:
                // perziuretiPasitenkinima();
                break;
            case 11:
                // perkeltiPacienta();
                break;
            case 12:
                // valdytiFinansus();
                break;
            case 13:
                // reaguotiIInspekcija();
                break;
            case 0:
                std::cout << "Išeinama iš žaidimo. Ačiū, kad žaidėte!\n";
                break;
            default:
                std::cout << "Neteisingas pasirinkimas. Bandykite dar kartą.\n";
                break;
        }
    } while (pasirinkimas != 0);
}

//DABAR CIA VISUR REIKIA JAU APRASYTI KIEKVIENA PASIRINKIMA KLASE IDET IR SITAS KLASES APACIOJ IDET I KAZKURIAS/


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


    pradetiZaidima();


     // ASCII menas
    std::cout << R"(
      .----. 
       ===(_)==   LABA DIENA
      // 6  6 \\  /
      (    7   )
       \ '--' /
        \_ ._/
       __)  (__
    /"`/`\`V/`\`\
   /   \  `Y _/_ \
  / [DR]\_ |/ / /\
  |     ( \/ / / /
   \  \  \      /
    \  `-/`  _.`
jgs  `=._`=./
    )" << std::endl;

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