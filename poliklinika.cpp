#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

//REIK PRIDET FUNKCIJAS KIEKVIENAM ISVEDIME KUR PRADETI ZAIDIMA
//NES PARASIUS SKAICIU TIK MENIU RODO
using namespace std;

//ok cia pasirodo paprastesnis rasymas nei keliu klasiu, tai paliekam.
    //jei klaus kas cia, tai enum: leidzia turet aisku sarasa busenu
enum GydymoBusena {
    LaukiaRegistracijos,
    LaukiaGydytojo,
    Apziurimas,
    TyrimuLaukimas,
    LaukiaRezultatu,
    Gydomas,
    Baigta
};
//cia konvertuojamas enum i teksta
string busenaToString(GydymoBusena b) {
    switch (b) { //tikriname busena
        //case leidzia vykdyti skirtingus veiksmus pagal reiksme
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
//isvedame meniu i ekrana
void rodytiMeniu() {
    cout << "\n _________________________________\n";
    cout << "  --- POLIKLINIKOS VALDYMO MENIU ---\n";
    cout << "  _________________________________\n";
    cout << "1. Naujas pacientas\n";
    cout << "2. Paslaugų kainos\n";
    cout << "3. Paskirti gydytoją pacientui\n";
    cout << "4. Darbuotojų ištekliai\n";
    cout << "5. Įvykių sąrašas\n";
    cout << "6. Priimti sprendimą dėl įvykio\n";
    cout << "7. Pacientų rezultatai\n";
    cout << "8. Darbuotojų sąrašas\n";
    cout << "9. Prižiūrėti paciento gydymą\n";
    cout << "10. Peržiūrėti pacientų pasitenkinimą\n";
    cout << "11. Perkelti pacientą\n";
    cout << "12. Valdyti finansus ir įrangą\n";
    cout << "13. Reaguoti į inspekciją\n";
    cout << "0. Išeiti iš žaidimo\n";
    cout << "-----------------------------------\n";
    cout << "Pasirinkite veiksmą (įveskite skaičių): ";

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


// Bazinė klasė Darbuotojas
class Darbuotojas {
private:
    static int nextID;              // ID generatorius
    int id;                        //darbuotojo ID
    string vardas;
    string pavarde;
    string pareigos;
    bool uzimtas;
    string elPastas;
    vector<int> darboValandos; // Darbo valandos (pvz. nuo 8 iki 17)
public:
// Konstruktorius su numatytais kontaktais ir darbo grafiku
    Darbuotojas(string v, string p, string par,
                string email = "",
                vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : id(nextID++), vardas(move(v)), pavarde(move(p)), pareigos(move(par)),
          uzimtas(false), elPastas(move(email)), darboValandos(move(grafikas)) {} //reikia iki cia pakeisti nuo pirmu skliaustu

    // Virtualus destruktorius, jei paveldima klasė
    virtual ~Darbuotojas() = default;

    // Getteriai
    int getID() const { return id; }
    const string& getVardas() const { return vardas; } 
    const string& getPavarde() const { return pavarde; } 
    const string& getPareigos() const { return pareigos; } 
    bool arUzimtas() const { return uzimtas; } 
    const string& getElPastas() const { return elPastas; } 
    const vector<int>& getDarboValandos() const { return darboValandos; }
    
    // Statuso keitimas
    void uzimti() { uzimtas = true; }
    void atlaisvinti() { uzimtas = false; }

    bool dirbaValanda(int valanda) const {
    for (int v : darboValandos) {
        if (v == valanda) {
            return true;
        }
    }
    return false;
}

    // Išvedame info apie darbuotoją
    virtual void info() const {
        cout << left << setw(4) << id
             << setw(20) << (vardas + " " + pavarde)
             << setw(25) << pareigos
             << (uzimtas ? "Užimtas" : "Laisvas")
             << " | El. paštas: " << (elPastas.empty() ? "Nėra" : elPastas)
             << "\nDarbo valandos: ";
        for (int val : darboValandos) cout << val << ":00 ";
        cout << endl;
    }
};

// Statinio lauko inicializacija (būtina kažkur .cpp faile, arba šalia klasės)
int Darbuotojas::nextID = 1;

// Paveldima klasė Gydytojas
class Gydytojas : public Darbuotojas {
    string specializacija;
    vector<string> pacientuSarasas; 

public:
   Gydytojas(const string& v, const string& p, const string& spec,
              const string& email = "",
              const vector<int>& grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(v, p, "Gydytojas", email, grafikas), specializacija(spec) {}

    void pridetiPacienta(const std::string& pacientoVardas) {
        pacientuSarasas.push_back(pacientoVardas);
    }

    void info() const override { 
        Darbuotojas::info();
        cout << "  Specializacija: " << specializacija << "\n";
        cout << "  Pacientų skaičius: " << pacientuSarasas.size() << "\n";
    }
};

// Paveldima klasė Slaugytoja
class Slaugytoja : public Darbuotojas {
public:
int priziurimuPacientuSkaicius = 0;
    Slaugytoja(const string& v, const string& p,
               const string& email = "",
               const vector<int>& grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(v, p, "Slaugytoja", email, grafikas) {}

    void pridetiPacienta() { priziurimuPacientuSkaicius++; }
    void info() const override {
        Darbuotojas::info();
        cout << "  Prižiūrimų pacientų skaičius: " << priziurimuPacientuSkaicius << "\n";
    }
};

// Paveldima klasė Administratorius
class Administratorius : public Darbuotojas {
public:
    Administratorius(const string& v, const string& p,
                     const string& email = "",
                     const vector<int>& grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(v, p, "Administratorius", email, grafikas) {}

    void registruotiPacienta() {
    cout << getVardas() << " " << getPavarde() << " registruoja pacientą.\n";
}

    void info() const override {
        Darbuotojas::info();
        std::cout << "  Administruoja poliklinikos dokumentaciją ir registraciją\n";
    }
};

// Paveldima klasė Laborantas
class Laborantas : public Darbuotojas {
public:
    Laborantas(const string& v, const string& p,
               const string& email = "",
               const vector<int>& grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(v, p, "Laborantas", email, grafikas) {}

    void atliktiTyrima() {
        cout << getVardas() << " " << getPavarde() << " atlieka laboratorinius tyrimus.\n";
    }

    void info() const override {
        Darbuotojas::info();
        cout << "  Atlieka laboratorinius tyrimus\n";
    }
};

// Paveldima klasė Valytoja
class Valytoja : public Darbuotojas {
public:
    Valytoja(const string& v, const string& p,
             const string& email = "",
             const vector<int>& grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(v, p, "Valytoja", email, grafikas) {}

    void valyti() {
        cout << getVardas() << " " << getPavarde() << " valo polikliniką.\n";
    }

    void info() const override {
        Darbuotojas::info();
        cout << "  Atsakinga už poliklinikos švarą\n";
    }
};

// Pacientas klasė
class Pacientas {
    string vardas;
    string sveikatosBusena;
    int laukimoLaikas;
    GydymoBusena busena;
    int likoLaikoBusenoje; // kiek dar laiko liko paciento busenoje (minutemis)
public:
    Pacientas(const string& v, const string& sb)
        : vardas(v), sveikatosBusena(sb), laukimoLaikas(0),
          busena(GydymoBusena::LaukiaRegistracijos), likoLaikoBusenoje(1) {}

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

    string getVardas() const { return vardas; }
    string getSveikatosBusena() const { return sveikatosBusena; }
    int getLaukimoLaikas() const { return laukimoLaikas; }
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
        cout << "            === Sveiki atvykę į Antakalnio polikliniką ===                       \n";
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        ⠀⠀" << endl;
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        " << endl;
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⠀ ⢠⣴⣶⣶⣶⣶⣶⣶⣶⣶⣶⠶⠖⠲⠶⣶⣶⣶⣶⣶⣶⣶⣶⣦⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ⢸⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁ ⣶⣶⠀⠈⢻⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣀⣀⣀⣀⣀⣀⣀⡀⠀ ⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀ ⠀ ⢀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠿⠿⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀   ⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣿⣇⣀⣿⣀⣸⣸⡇⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀  ⣿⣀⣸⣇⣀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣿⡏⠉⣿⠉⢹⡏⠁⠀⠀⢸⣿ Antakalnio Poliklinika⣿⡇    ⣿⠉⢹⡏⠉⣿⡇⠀⠀⠀       ⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣿⡟⠛⣿⠛⢻⡇⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠿⠿⠿⠿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀ ⢸⣿⠛⢻⡟⠛⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣿⣧⣴⣿⣤⣾⡇⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀  ⢸⣿⣤⣾⣧⣴⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀ ⢸⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⣤⣤ ⣿⣿⣿⣿⣿⣿⣧⣤⣤⣼⣿⣿⠿⠿⠿⠿⠿⠿⠿⠿⣿⣧⣤⣤⣤⣤⣼⣿⣿⠿⠿⠿⠿⠿⠿⣿⣿⣧⣤⣤⣼⣿⣿⣿⣿⣿⣿⣧⣤⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
        cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀" << endl;
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
        cin.ignore(1000, '\n');
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
    poliklinika.pridetiDarbuotoja(new Gydytojas("Jonas", "Kazlauskas", "Šeimos gydytojas", "jonas.kazlauskas@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Rasa", "Petrauskienė", "Šeimos gydytojas", "rasa.petrauskiene@clinic.lt", {9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Agnė", "Vaitkutė", "Vaikų ligų gydytoja", "agne.vaitkute@clinic.lt", {8,9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Mindaugas", "Urbonas", "Akušeris ginekologas", "mindaugas.urbonas@clinic.lt", {10,11,12,13,14,15}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Jurgita", "Stanevičiūtė", "Psichologė", "jurgita.staneviciute@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Tomas", "Šalkauskis", "Kineziterapeutas", "tomas.salkauskis@clinic.lt", {8,9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Simona", "Mažeikytė", "Oftalmologė", "simona.mazeikyte@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Vytautas", "Paškevičius", "Kardiologas", "vytautas.paskevicius@clinic.lt", {8,9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Rūta", "Marcinkevičienė", "Neurologė", "ruta.marcinkeviciene@clinic.lt", {9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Edita", "Jurkevičiūtė", "Dermatologė", "edita.jurkeviciute@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Dainius", "Giedraitis", "Otorinolaringologas", "dainius.giedraitis@clinic.lt", {10,11,12,13,14,15}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Loreta", "Žukauskaitė", "Psichiatrė", "loreta.zukauskaite@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Justė", "Kuprevičiūtė", "Pediatrė", "juste.kupreviciute@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Algis", "Tamkevičius", "Anesteziologas reanimatologas", "algis.tamkevicius@clinic.lt", {9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Tautvydas", "Kairys", "Urologas", "tautvydas.kairys@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Monika", "Grigaitė", "Gastroenterologė", "monika.grigaite@clinic.lt", {9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Indrė", "Sabaliauskaitė", "Ergoterapeutė", "indre.sabaliauskaite@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Andrius", "Dirgėla", "Pulmonologas", "andrius.dirgela@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Gydytojas("Ramunė", "Milinienė", "Radiologė", "ramune.miliniene@clinic.lt", {8,9,10,11,12}));

    // Slaugytojos (5)
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Neringa", "Balčiūnaitė", "neringa.balciunaite@clinic.lt", {8,9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Eglė", "Drungilaitė", "egle.drungilaite@clinic.lt", {9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Asta", "Kalvaitienė", "asta.kalvaitiene@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Renata", "Kundrotienė", "renata.kundrotiene@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Slaugytoja("Laima", "Navickaitė", "laima.navickaite@clinic.lt", {8,9,10,11}));

    // Administratoriai (3)
    poliklinika.pridetiDarbuotoja(new Administratorius("Ieva", "Naveraitė", "ieva.naveraite@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Administratorius("Saulė", "Miknaitė", "saule.mikaite@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Administratorius("Emilija", "Grigonytė", "emilija.grigonyte@clinic.lt", {8,9,10,11}));
    // Laborantai (5)
    poliklinika.pridetiDarbuotoja(new Laborantas("Tadas", "Urbšys", "tadas.urbsys@clinic.lt", {8,9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Laborantas("Inga", "Jankauskienė", "inga.jankauskiene@clinic.lt", {9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Laborantas("Dainius", "Kalnietis", "dainius.kalnietis@clinic.lt", {8,9,10,11,12,13}));
    poliklinika.pridetiDarbuotoja(new Laborantas("Tomas", "Petraitis", "tomas.petraitis@clinic.lt", {9,10,11,12,13,14}));
    poliklinika.pridetiDarbuotoja(new Laborantas("Rugilė", "Kazlauskaitė", "rugile.kazlauskaite@clinic.lt", {8,9,10,11}));
    // Valytojos (3)
    poliklinika.pridetiDarbuotoja(new Valytoja("Rasa", "Petraitė", "rasa.petraite@clinic.lt", {8,9,10,11}));
    poliklinika.pridetiDarbuotoja(new Valytoja("Neringa", "Balčiūnaitė", "neringa.balciunaite@clinic.lt", {9,10,11,12}));
    poliklinika.pridetiDarbuotoja(new Valytoja("Laima", "Plieskytė", "laima.plieskyte@clinic.lt", {8,9,10}));
 

    // Pavyzdiniai pacientai
    poliklinika.pridetiPacienta(Pacientas("Petras", "Galvos skausmas"));
    poliklinika.pridetiPacienta(Pacientas("Ieva", "Kosulys"));
    poliklinika.pridetiPacienta(Pacientas("Lukas", "Pilvo skausmai"));
    poliklinika.pridetiPacienta(Pacientas("Greta", "Alergija"));
    poliklinika.pridetiPacienta(Pacientas("Martynas", "Akių paraudimas"));

    poliklinika.rodytiDarbuotojus();
    poliklinika.rodytiPacientus();
    poliklinika.priskirtiGydytojusPacientams();

    // Atspausdinti darbuotojus ir pacientus
    poliklinika.rodytiDarbuotojus();
    poliklinika.rodytiPacientus();

    // Priskirti gydytojus pacientams
    poliklinika.priskirtiGydytojusPacientams();

    // Finansai
    Poliklinika::Finansai finansai(1000.0);
    finansai.info();
    finansai.pridetiPajamu(500.0);
    finansai.sumazintiIslaidas(200.0);

 // Inspekcija
    Poliklinika::Inspekcija::atliktiPatikra(finansai, 2);

// Paleisti meniu
    pradetiZaidima();

    return 0;
}

