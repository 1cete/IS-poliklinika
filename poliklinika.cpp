#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
 
enum class GydymoBusena { //kas cia? nes tokio nesimokem su enum:DD //Nezinau kaip kitaip pakeisti:D
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
    std::string elPastas;
    std::vector<int> darboValandos; // Darbo valandos (pvz. nuo 8 iki 17)
public:
// Konstruktorius su numatytais kontaktais ir darbo grafiku
    Darbuotojas(std::string v, std::string p, std::string par,
                std::string email = "",
                std::vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : id(nextID++), vardas(std::move(v)), pavarde(std::move(p)), pareigos(std::move(par)),
          uzimtas(false), elPastas(std::move(email)), darboValandos(std::move(grafikas)) {}

    // Virtualus destruktorius, jei paveldima klasė
    virtual ~Darbuotojas() = default;

    // Getters
    int getID() const { return id; }
    const std::string& getVardas() const { return vardas; }
    const std::string& getPavarde() const { return pavarde; }
    const std::string& getPareigos() const { return pareigos; }
    bool arUzimtas() const { return uzimtas; }
    const std::string& getElPastas() const { return elPastas; }
    const std::vector<int>& getDarboValandos() const { return darboValandos; }

    // Statuso keitimas
    void uzimti() { uzimtas = true; }
    void atlaisvinti() { uzimtas = false; }

    // Tikriname ar darbuotojas dirba nurodytą valandą
    bool dirbaValanda(int valanda) const {
        return std::find(darboValandos.begin(), darboValandos.end(), valanda) != darboValandos.end();
    }

    // Išvedame info apie darbuotoją
    virtual void info() const {
        std::cout << std::left << std::setw(4) << id
                  << std::setw(20) << (vardas + " " + pavarde)
                  << std::setw(25) << pareigos
                  << (uzimtas ? "Užimtas" : "Laisvas")
                  << " | El. paštas: " << (elPastas.empty() ? "Nėra" : elPastas)
                  << "\nDarbo valandos: ";
        for (int val : darboValandos) {
            std::cout << val << ":00 ";
        }
        std::cout << std::endl;
    }
};

// Statinio lauko inicializacija (būtina kažkur .cpp faile, arba šalia klasės)
int Darbuotojas::nextID = 1;

// Paveldima klasė Gydytojas
class Gydytojas : public Darbuotojas {
    std::string specializacija;
    std::vector<std::string> pacientuSarasas; 

public:
    Gydytojas(std::string v, std::string p, std::string spec,
              std::string email = "",
              std::vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(std::move(v), std::move(p), "Gydytojas", std::move(email), std::move(grafikas)),
          specializacija(std::move(spec)) {}

    void pridetiPacienta(const std::string& pacientoVardas) {
        pacientuSarasas.push_back(pacientoVardas);
    }

    void info() const override {
        Darbuotojas::info();
        std::cout << "  Specializacija: " << specializacija << "\n";
        std::cout << "  Pacientų skaičius: " << pacientuSarasas.size() << "\n";
    }
};

// Paveldima klasė Slaugytoja
class Slaugytoja : public Darbuotojas {
   int prižiūrimųPacientųSkaičius = 0;

public:
    Slaugytoja(std::string v, std::string p,
               std::string email = "",
               std::vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(std::move(v), std::move(p), "Slaugytoja", std::move(email), std::move(grafikas)) {}

    void pridetiPacienta() { prižiūrimųPacientųSkaičius++; }
    void info() const override {
        Darbuotojas::info();
        std::cout << "  Prižiūrimų pacientų skaičius: " << prižiūrimųPacientųSkaičius << "\n";
    }
};

// Paveldima klasė Administratorius
class Administratorius : public Darbuotojas {
public:
    Administratorius(std::string v, std::string p,
                     std::string email = "",
                     std::vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(std::move(v), std::move(p), "Administratorius", std::move(email), std::move(grafikas)) {}

    void registruotiPacienta() {
        std::cout << vardas << " " << pavarde << " registruoja pacientą.\n";
    }

    void info() const override {
        Darbuotojas::info();
        std::cout << "  Administruoja poliklinikos dokumentaciją ir registraciją\n";
    }
};

// Pvaveldima klasė Laborantas
class Laborantas : public Darbuotojas {
public:
    Laborantas(std::string v, std::string p,
               std::string email = "",
               std::vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(std::move(v), std::move(p), "Laborantas", std::move(email), std::move(grafikas)) {}

    void atliktiTyrima() {
        std::cout << vardas << " " << pavarde << " atlieka laboratorinius tyrimus.\n";
    }

    void info() const override {
        Darbuotojas::info();
        std::cout << "  Atlieka laboratorinius tyrimus\n";
    }
};

// Paveldima klasė Valytoja
class Valytoja : public Darbuotojas {
public:
    Valytoja(std::string v, std::string p,
             std::string email = "",
             std::vector<int> grafikas = {8,9,10,11,12,13,14,15,16,17})
        : Darbuotojas(std::move(v), std::move(p), "Valytoja", std::move(email), std::move(grafikas)) {}

    void valyti() {
        std::cout << vardas << " " << pavarde << " valo polikliniką.\n";
    }

    void info() const override {
        Darbuotojas::info();
        std::cout << "  Atsakinga už poliklinikos švarą\n";
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
