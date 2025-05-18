#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
 
enum class GydymoBusena {
    LaukiaRegistracijos,
    LaukiaGydytojo,
    Apziurimas,
    TyrimuLaukimas,
    LaukiaRezultatu,
    Gydomas,
    Baigta
};

string busenaToString(GydymoBusena b) {
    switch (b) {
        case GydymoBusena::LaukiaRegistracijos: return "Laukia registracijos";
        case GydymoBusena::LaukiaGydytojo: return "Laukia gydytojo";
        case GydymoBusena::Apziurimas: return "Apžiūrimas";
        case GydymoBusena::TyrimuLaukimas: return "Laukia tyrimų";
        case GydymoBusena::LaukiaRezultatu: return "Laukia rezultatų";
        case GydymoBusena::Gydomas: return "Gydomas";
        case GydymoBusena::Baigta: return "Gydymas baigtas";
        default: return "Nežinoma";
    }
}

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
private:
    static int nextID;              // ID generatorius
    int id;                        //darbuotojo ID
    std::string vardas;
    std::string pavarde;
    std::string pareigos;
    bool uzimtas;
    std::string telefonas;
    std::string elPastas;
    std::vector<int> darboValandos; // Darbo valandos (pvz. nuo 8 iki 17)
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

// Paveldima klasė Administratorius
class Administratorius : public Darbuotojas {
public:
    Administratorius(string v, string p) : Darbuotojas(v, p, "Administratorius") {}
};

// Pvaveldima klasė Laborantas
class Laborantas : public Darbuotojas {
public:
    Laborantas(string v, string p) : Darbuotojas(v, p, "Laborantas") {}
};

// Paveldima klasė Valytoja
class Valytoja : public Darbuotojas {
public:
    Valytoja(string v, string p) : Darbuotojas(v, p, "Valytoja") {}
};

// Pacientas klasė
class Pacientas {
    string vardas;
    string sveikatosBusena;
    int laukimoLaikas;
    GydymoBusena busena;
    int likoLaikoBusenoje; // kiek dar laiko liko paciento busenoje (minutemis)
public:
    Pacientas(string v, string sb) : vardas(v), sveikatosBusena(sb), laukimoLaikas(0), busena(GydymoBusena::LaukiaRegistracijos), likoLaikoBusenoje(1) {}

    void didintiLaukimoLaika() { laukimoLaikas++; }

    // Simuliuoja vienos minutės prabėgimą paciento būsenos procese
    void simuliuotiMinute() {
        if (likoLaikoBusenoje > 0)
            likoLaikoBusenoje--;
        if (likoLaikoBusenoje == 0)
            pereitiIKitaBusena();
    }

    // Pereina į kitą gydymo būseną ir nustato laiką naujoje būsenoje
    void pereitiIKitaBusena() {
        switch (busena) {
            case GydymoBusena::LaukiaRegistracijos:
                busena = GydymoBusena::LaukiaGydytojo;
                likoLaikoBusenoje = 2;
                break;
            case GydymoBusena::LaukiaGydytojo:
                busena = GydymoBusena::Apziurimas;
                likoLaikoBusenoje = 5;
                break;
            case GydymoBusena::Apziurimas:
                busena = GydymoBusena::TyrimuLaukimas;
                likoLaikoBusenoje = 4;
                break;
            case GydymoBusena::TyrimuLaukimas:
                busena = GydymoBusena::LaukiaRezultatu;
                likoLaikoBusenoje = 3;
                break;
            case GydymoBusena::LaukiaRezultatu:
                busena = GydymoBusena::Gydomas;
                likoLaikoBusenoje = 4;
                break;
            case GydymoBusena::Gydomas:
                busena = GydymoBusena::Baigta;
                likoLaikoBusenoje = 0;
                break;
            case GydymoBusena::Baigta:
                // jau baigta, nekeičiam
                break;
        }
    }

    string getVardas() { return vardas; }
    string getSveikatosBusena() { return sveikatosBusena; }
    int getLaukimoLaikas() { return laukimoLaikas; }
    GydymoBusena getBusena() const { return busena; } 

    void info() const {
        cout << "- Pacientas: " << vardas
             << ", sveikatos būklė: " << sveikatosBusena
             << ", laukimo laikas: " << laukimoLaikas << " min."
             << ", būklė: " << busenaToString(busena)
             << ", liko laiko būsenai: " << likoLaikoBusenoje << " min."
             << endl;
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

    void registruotiPacienta() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string vardas, bukle;
        cout << "Įveskite paciento vardą: ";
        getline(cin, vardas);
        cout << "Įveskite sveikatos būklę: ";
        getline(cin, bukle);
        pridetiPacienta(Pacientas(vardas, bukle));
        cout << "Pacientas užregistruotas sėkmingai!\n";
    }

    void simuliuotiMinute() {
    for (auto& p : pacientai) {
        p.simuliuotiMinute();
    }
}
    void rodytiPacientuBusena() {
    cout << "Pacientų gydymo būsenos:\n";
    for (auto& p : pacientai) {
        p.info();
    }
}

    // Paveldima klasė Finansai
    class Finansai {
    double balansas;
public:
    Finansai(double pradinis) : balansas(pradinis) {}

    void pridetiPajamu(double suma) {
        balansas += suma;
        cout << "Pridėta pajamų: " << suma << " EUR. Naujas balansas: " << balansas << " EUR.\n";
    }

    void sumazintiIslaidas(double suma) {
        balansas -= suma;
        cout << "Išlaidos: " << suma << " EUR. Naujas balansas: " << balansas << " EUR.\n";
    }

    double gautiBalansa() const {
        return balansas;
    }

    void info() const {
        cout << "Poliklinikos balansas: " << balansas << " EUR\n";
    }
};

// Klasė Inspekcija
class Inspekcija {
public:
    static void atliktiPatikra(Finansai& finansai, int neatitikimuSkaicius) {
        cout << "Vykdoma inspekcija...\n";
        if (neatitikimuSkaicius > 0) {
            double bauda = neatitikimuSkaicius * 50.0;
            cout << "Rasta neatitikimų: " << neatitikimuSkaicius 
                 << ". Skiriama bauda: " << bauda << " EUR.\n";
            finansai.sumazintiIslaidas(bauda);
        } else {
            cout << "Poliklinika atitiko visus reikalavimus. Baudų nėra.\n";
        }
    }
};

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

    // Administratoriai (3)
    poliklinika.pridetiDarbuotoja(new Administratorius("Ieva", "Naveraitė"));
    poliklinika.pridetiDarbuotoja(new Administratorius("Saulė", "Miknaitė"));
    poliklinika.pridetiDarbuotoja(new Administratorius("Emilija", "Grigonytė"));

    // Laborantai (5)
    poliklinika.pridetiDarbuotoja(new Laborantas("Tadas", "Urbšys"));
    poliklinika.pridetiDarbuotoja(new Laborantas("Inga", "Jankauskien4"));
    poliklinika.pridetiDarbuotoja(new Laborantas("Dainius", "Kalnietis"));
    poliklinika.pridetiDarbuotoja(new Laborantas("Tomas", "Petraitis"));
    poliklinika.pridetiDarbuotoja(new Laborantas("Rugilė", "Kazlauskaitė"));

    // Valytojos (3)
    poliklinika.pridetiDarbuotoja(new Valytoja("Rasa", "Petraitė"));
    poliklinika.pridetiDarbuotoja(new Valytoja("Neringa", "Balčiūnaitė"));
    poliklinika.pridetiDarbuotoja(new Valytoja("Laima", "Plieskytė"));
 

    // Pavyzdiniai pacientai
    poliklinika.pridetiPacienta(Pacientas("Petras", "Galvos skausmas"));
    poliklinika.pridetiPacienta(Pacientas("Ieva", "Kosulys"));
    poliklinika.pridetiPacienta(Pacientas("Lukas", "Pilvo skausmai"));
    poliklinika.pridetiPacienta(Pacientas("Greta", "Alergija"));
    poliklinika.pridetiPacienta(Pacientas("Martynas", "Akių paraudimas"));

    poliklinika.rodytiDarbuotojus();
    poliklinika.rodytiPacientus();
    poliklinika.priskirtiGydytojusPacientams();

    // Atspausdinti darbuotojus
    poliklinika.rodytiDarbuotojus();

// Sukuriame finansus ir įrangą:
Finansai finansai(1000.0);
vector<Iranga> irangos = {
    Iranga("Ultragarsas"),
    Iranga("EKG"),
    Iranga("Kraujospūdžio matuoklis")
};

// Naudojame įrangą:
irangos[0].naudoti(5); // tarkime, praėjo 5 minutės

// Įvyksta gedimas
irangos[1].sugenda();

// Patikriname balansą
finansai.pridetiPajamu(150.0);
finansai.sumazintiIslaidas(70.0);

// Atlikti inspekciją su 2 neatitikimais
Inspekcija::atliktiPatikra(finansai, 2);
