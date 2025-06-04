#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>  

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
GydymoBusena stringToBusena(const string& s) {
    if (s == "Laukia registracijos") return GydymoBusena::LaukiaRegistracijos;
    if (s == "Laukia gydytojo") return GydymoBusena::LaukiaGydytojo;
    if (s == "Apžiūrimas") return GydymoBusena::Apziurimas;
    if (s == "Laukia tyrimų") return GydymoBusena::TyrimuLaukimas;
    if (s == "Laukia rezultatų") return GydymoBusena::LaukiaRezultatu;
    if (s == "Gydomas") return GydymoBusena::Gydomas;
    if (s == "Gydymas baigtas") return GydymoBusena::Baigta;
    return GydymoBusena::LaukiaRegistracijos;
}

}
//skyrius nustatom
string gautiSkyriuPagalBusena(GydymoBusena busena) {
    switch (busena) {
        case GydymoBusena::LaukiaRegistracijos:
            return "Registratūra";
        case GydymoBusena::LaukiaGydytojo:
            return "Laukiamojo skyrius";
        case GydymoBusena::Apziurimas:
            return "Gydytojo kabinetas";
        case GydymoBusena::TyrimuLaukimas:
            return "Laboratorija";
        case GydymoBusena::LaukiaRezultatu:
            return "Rezultatų skyrius";
        case GydymoBusena::Gydomas:
            return "Gydymo skyrius";
        case GydymoBusena::Baigta:
            return "Išrašymas";
        default:
            return "Nežinomas skyrius";
    }
}
//isvedame meniu i ekrana
void rodytiMeniu() {
    cout << "\n --------------------------------\n";
    cout << " --- POLIKLINIKOS VALDYMO MENIU ---";
    cout << "\n --------------------------------\n";
    cout << "1. Naujas pacientas\n";
    cout << "2. Paslaugų kainos\n";
    cout << "3. Paskirti gydytoją pacientui\n";
    cout << "4. Darbuotojų ištekliai\n";
    cout << "5. Įvykių sąrašas\n";
    cout << "6. Priimti sprendimą dėl įvykio\n";
    cout << "7. Pacientų rezultatai\n";
    cout << "8. Darbuotojų sąrašas\n";
    cout << "9. Peržiūrėti pacientų pasitenkinimą\n";
    cout << "10. Perkelti pacientą\n";
    cout << "11. Valdyti finansus ir įrangą\n";
    cout << "12. Reaguoti į inspekciją\n";
    cout << "0. Išeiti iš žaidimo\n";
    cout << "-----------------------------------\n";
    cout << "Pasirinkite veiksmą (įveskite skaičių): ";

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

    virtual string toString() const {
    stringstream ss;
    ss << getVardas() << ";" << getPavarde() << ";" << getPareigos()
       << ";" << getElPastas();
    return ss.str();
}

Pacientas(const string& v, const string& sb, GydymoBusena b, int laukLaikas, const string& skyr)
: vardas(v), sveikatosBusena(sb), laukimoLaikas(laukLaikas),
  busena(b), likoLaikoBusenoje(1), skyrius(skyr) {}


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
    string skyrius;

public:
    Pacientas(const string& v, const string& sb)
        : vardas(v), sveikatosBusena(sb), laukimoLaikas(0),
          busena(GydymoBusena::LaukiaRegistracijos), likoLaikoBusenoje(1),
          skyrius("Registratūra") {}

    void setSkyrius(const string& naujasSkyrius) {
        skyrius = naujasSkyrius;
    }
    string getSkyrius() const {
        return skyrius;
    }

    void atnaujintiSkyriuPagalBusena() {
        skyrius = gautiSkyriuPagalBusena(busena);
    }

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
                break;
        }
        atnaujintiSkyriuPagalBusena();
    }

    void didintiLaukimoLaika() { 
        laukimoLaikas++; 
    }

    void simuliuotiMinute() {
        if (likoLaikoBusenoje > 0)
            likoLaikoBusenoje--;
        if (likoLaikoBusenoje == 0)
            pereitiIKitaBusena();
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
             << ", skyrius: " << skyrius << endl;
    }
};

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

// Poliklinika klasė
class Poliklinika {
    vector<Darbuotojas*> darbuotojai;
    vector<Pacientas> pacientai;
public:
    ~Poliklinika() {
        for (auto d : darbuotojai) delete d;
    }

    void sveikinimas() {
        cout << " \n                                                                              \n";
        cout << "     === Sveiki atvykę į Antakalnio polikliniką ===                          \n";
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


    void perkeltiPacientaISkyriu() {
        if (pacientai.empty()) {
            cout << "Nėra pacientų poliklinikoje.\n";
            return;
        }

        cout << "Pacientų sąrašas:\n";
        for (size_t i = 0; i < pacientai.size(); i++) {
            cout << i+1 << ". " << pacientai[i].getVardas()
                 << " (dabar skyrius: " << pacientai[i].getSkyrius() << ")\n";
        }

        cout << "Įveskite paciento numerį, kurį norite perkelti: ";
        int pacIndex;
        if (!(cin >> pacIndex) || pacIndex < 1 || pacIndex > (int)pacientai.size()) {
            cout << "Neteisingas pasirinkimas.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Įveskite naują skyrių paciento perkėlimui: ";
        string naujasSkyrius;
        getline(cin, naujasSkyrius);

        pacientai[pacIndex - 1].setSkyrius(naujasSkyrius);

        cout << "Pacientas " << pacientai[pacIndex - 1].getVardas()
             << " perkeltas į skyrių: " << naujasSkyrius << "\n";
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

    void irasytiDarbuotojaIFaila(const Darbuotojas& d) {
    std::ofstream failas("darbuotojai.txt", std::ios::app);
    if (failas.is_open()) {
        failas << d.toString() << std::endl;
        failas.close();
    } else {
        std::cout << "Nepavyko atidaryti failo įrašymui.\n";
    }
}

void nuskaitytiDarbuotojusIsFailo() {
    ifstream failas("darbuotojai.txt");
    if (!failas.is_open()) {
        cerr << "Nepavyko atidaryti darbuotojai.txt\n";
        return;
    }

    string eilute;
    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        string idStr, vardas, pavarde, pareigos, uzimtasStr, elpastas;

        getline(ss, idStr, ';');
        getline(ss, vardas, ';');
        getline(ss, pavarde, ';');
        getline(ss, pareigos, ';');
        getline(ss, uzimtasStr, ';');
        getline(ss, elpastas, ';');

        Darbuotojas* d = nullptr;
        if (pareigos == "Gydytojas") {
            d = new Gydytojas(vardas, pavarde, "Bendra", elpastas);
        } else if (pareigos == "Slaugytoja") {
            d = new Slaugytoja(vardas, pavarde, elpastas);
        } else if (pareigos == "Administratorius") {
            d = new Administratorius(vardas, pavarde, elpastas);
        } else if (pareigos == "Laborantas") {
            d = new Laborantas(vardas, pavarde, elpastas);
        }

        if (d) {
            if (uzimtasStr == "1") d->uzimti();
            pridetiDarbuotoja(d);
        }
    }

    failas.close();
}



    void rodytiPacientus() {
        cout << "Pacientai:\n";
        for (auto& p : pacientai) {
            p.info();
        }
        cout << endl;
    }

    void irasytiPacientusIFaila() {
    ofstream failas("pacientai.txt");
    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo įrašymui.\n";
        return;
    }

    for (const auto& p : pacientai) {
        failas << p.getVardas() << ";"
               << p.getSveikatosBusena() << ";"
               << p.getLaukimoLaikas() << ";"
               << busenaToString(p.getBusena()) << ";"
               << p.getSkyrius() << "\n";
    }

    failas.close();
    cout << "Pacientų duomenys įrašyti į pacientai.txt\n";
}



    void priskirtiGydytojusPacientams() {
    for (auto& pacientas : pacientai) {
        Gydytojas* laisvasGydytojas = nullptr;

        for (auto darbuotojas : darbuotojai) {
            Gydytojas* g = dynamic_cast<Gydytojas*>(darbuotojas);
            if (g && !g->arUzimtas()) {
                laisvasGydytojas = g;
                break;
            }
        }

        if (laisvasGydytojas) {
            laisvasGydytojas->pridetiPacienta(pacientas.getVardas());
            laisvasGydytojas->uzimti();
            cout << "Pacientas " << pacientas.getVardas()
                 << " priskirtas gydytojui "
                 << laisvasGydytojas->getVardas() << " "
                 << laisvasGydytojas->getPavarde() << ".\n";
        } else {
            cout << "Nėra laisvų gydytojų pacientui "
                 << pacientas.getVardas() << ".\n";
        }
    }
}


    void registruotiPacienta() {
        cin.ignore(1000, '\n');
    string vardas, bukle;
    cout << "Įveskite paciento vardą: ";
    getline(cin, vardas);
    cout << "Įveskite sveikatos būklę: ";
    getline(cin, bukle);

    Pacientas naujas(vardas, bukle);
    pridetiPacienta(naujas);

    // Įrašymas į failą
    ofstream failas("pacientai.txt", ios::app); // atidarom papildymui
    if (failas.is_open()) {
        failas << "Pacientas: " << vardas 
               << ", Būklė: " << bukle 
               << ", Skyrius: " << naujas.getSkyrius()
               << ", Busena: " << busenaToString(naujas.getBusena())
               << endl;
        failas.close();
        cout << "Pacientas įrašytas į failą.\n";
    } else {
        cout << "Nepavyko atidaryti failo įrašymui.\n";
    }
}

    void nuskaitytiPacientusIsFailo() {
    ifstream failas("pacientai.txt");
    if (!failas.is_open()) {
        cerr << "Nepavyko atidaryti pacientai.txt\n";
        return;
    }

    string eilute;
    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        string vardas, sveikata, aptarnautasStr, busena, lokacija;
        getline(ss, vardas, ';');
        getline(ss, sveikata, ';');
        getline(ss, aptarnautasStr, ';');
        getline(ss, busena, ';');
        getline(ss, lokacija, '\n');
        bool aptarnautas = (aptarnautasStr == "1");

        Pacientas p(vardas, sveikata, aptarnautas, busena, lokacija);
        pacientai.push_back(p);
    }

    failas.close();
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

};

// Saugus pasirinkimo nuskaitymas iš meniu
int gautiPasirinkima() {
    int pasirinkimas;

    while (true) {
        rodytiMeniu();

        if (!(cin >> pasirinkimas)) {
            cout << "Klaidinga įvestis, įveskite skaičių.\n";
            cin.clear(); // išvalome klaidos būseną
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // išvalome buferį
            continue; // bandome dar kartą
        }

        // Išvalome buferį po įvesto skaičiaus
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return pasirinkimas;
    }
}

public void parodytiGydymoBusena() {
    for (Pacientas p : pacientai) {
        System.out.println(p.getVardas() + ": " + p.gydymoBusena());
    }
}


void pradetiZaidima(Poliklinika& poliklinika) {
    int pasirinkimas;
    string pasirinktasIvykis;
    Finansai finansai(1000.0); // pradinis balansas

    vector<string> ivykiai = {
                    "Sutriko elektros tiekimas - pacientas negali pažiūrėti 'Labas rytas, Lietuva' ",
                    "Trūksta reagentų laboratorijoje - laborantas pyksta",
                    "Atėjo netikėta inspekcija, o poliklinikoje bėgioja pelė",
                    "Sugedo rentgeno aparatas",
                    "Gydytojas nori naujo kompiuterio, nes 'Senasis negražus' ",
                    "Vandentiekio avarija laboratorijoje - užlieta patalpa",
                    "Gydytojas išrašė netinkamų vaistų",
                    "Buvo gandas, kad artėja inspekcija, bet ji neatvyksta",
                    "Signalizacija suveikė be priežasties",
                    "Gydytojas pareikalavo didesnio atlyginimo",
                    "Valytoja miega darbo vietoje",
                    "Vieno paciento dokumentas neteisingai susegtas",
                    "Administratorė nori rožių registratūroje"
                };

    do {
        pasirinkimas = gautiPasirinkima();

        switch (pasirinkimas) {
            case 1:
                poliklinika.registruotiPacienta();
                cout << "\n--- Pacientų sąrašas po registracijos ---\n";
                poliklinika.rodytiPacientus(); // <-- tai parodys naujai pridėtą pacientą
                poliklinika.irasytiPacientusIFaila();
                break;
            case 2:
                cout << "\nPaslaugų kainos:\n"
                     << "- Konsultacija: 20 EUR\n"
                     << "- Tyrimai: 30 EUR\n"
                     << "- Gydymas: 50 EUR\n\n";
                break;
            case 3:
                poliklinika.priskirtiGydytojusPacientams();
                break;
            case 4:
                poliklinika.rodytiDarbuotojus();
                break;
            case 5: {
                int index = rand() % ivykiai.size();
                pasirinktasIvykis = ivykiai[index];
                cout << "\nĮvykis: " << pasirinktasIvykis << "\n\n";
                break;
            }

            case 6: {
                int sprendimas;
                cout << "Sprendimo simuliacija: pasirinkite 1 (spręsti) arba 2 (ignoruoti): ";
                if (!(cin >> sprendimas)) {
                    cout << "Klaidinga įvestis. Grįžtama į meniu.\n";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (sprendimas == 1) {
                    cout << "Sprendimas priimtas – problema išspręsta!\n";
                    finansai.sumazintiIslaidas(100.0);
                } else {
                    cout << "Ignoruota – gali būti pasėkmių!\n";
                }
                break;
            }
            case 7:
                poliklinika.simuliuotiMinute();
                poliklinika.rodytiPacientuBusena();
                break;
            case 8:
                poliklinika.rodytiDarbuotojus();
                break;
            case 9:
                cout << "\nPacientų pasitenkinimo apklausa:\n";
                cout << "- 80% pacientų patenkinti\n";
                cout << "- 15% vidutiniškai\n";
                cout << "- 5% nepatenkinti\n\n";
                break;
            case 10:
                poliklinika.perkeltiPacientaISkyriu();
                break;
            case 11:
                finansai.info();
                finansai.pridetiPajamu(300);
                finansai.sumazintiIslaidas(150);
                break;
            case 12:
                Inspekcija::atliktiPatikra(finansai, rand() % 4); // random 0–3 neatitikimų
                break;
            case 0:
                cout << "Išeinama iš žaidimo. Ačiū, kad žaidėte!\n";
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar kartą.\n";
                break;
        }
    } while (pasirinkimas != 0);
}

int main() {

 srand(time(0)); // dėl atsitiktinių skaičių inspekcijai

    Poliklinika poliklinika;
    poliklinika.sveikinimas();

     // ASCII menas
    cout << R"(
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
     `=._`=./
    )" << std::endl;

    // 🔽 Čia nuskaito iš failų
    poliklinika.nuskaitytiDarbuotojusIsFailo();
    poliklinika.nuskaitytiPacientusIsFailo();

    rodytiMeniu(poliklinika);

    // Paleisti meniu
    pradetiZaidima(poliklinika);

    return 0;
}
