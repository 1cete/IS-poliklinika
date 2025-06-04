#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string zaidejoVardas;
    cout << "Įveskite žaidėjo vardą: ";
    getline(cin, zaidejoVardas);

    ofstream failas("pacientai.txt", ios::app);
    if (failas.is_open()) {
        failas << zaidejoVardas << "\n";
        failas.close();
        cout << "Žaidėjas užregistruotas. Palaukite paciento generavimo serveryje.\n";
    } else {
        cout << "Nepavyko atidaryti failo pacientai.txt\n";
    }

    return 0;
}
