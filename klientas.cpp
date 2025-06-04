// klientas.cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string vardas, sveikata;
    cout << "Įveskite paciento vardą: ";
    getline(cin, vardas);
    cout << "Įveskite sveikatos būklę: ";
    getline(cin, sveikata);

    ofstream failas("pacientai.txt", ios::app);
    if (failas.is_open()) {
        failas << vardas << ";" << sveikata << ";0;Laukia registracijos;Registratūra\n";
        failas.close();
        cout << "Pacientas sėkmingai užregistruotas.\n";
    } else {
        cout << "Nepavyko atidaryti failo.\n";
    }

    return 0;
}
