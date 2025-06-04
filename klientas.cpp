#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>

#define SOKETO_FAILAS "./zaidimas.sock"
#define BUFERIO_DYDIS 1024

void klaida(const char* pranesimas) {
    perror(pranesimas);
    exit(EXIT_FAILURE);
}

int main() {
    int soketas;
    struct sockaddr_un serverioAdresas;
    char buferis[BUFERIO_DYDIS];

    // 1. Sukuriame UNIX soketą
    if ((soketas = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        klaida("Nepavyko sukurti soketo");
    }

    // 2. Nustatome serverio adresą
    memset(&serverioAdresas, 0, sizeof(serverioAdresas));
    serverioAdresas.sun_family = AF_UNIX;
    strncpy(serverioAdresas.sun_path, SOKETO_FAILAS, sizeof(serverioAdresas.sun_path) - 1);

    // 3. Prisijungiame prie serverio
    if (connect(soketas, (struct sockaddr*)&serverioAdresas, sizeof(serverioAdresas)) < 0) {
        klaida("Nepavyko prisijungti prie serverio");
    }

    std::cout << "✅ Prisijungta prie serverio.\n";

    while (true) {
    // 1. Įvestis iš vartotojo
    std::string ivestis;
    std::cout << ">>> ";
    std::getline(std::cin, ivestis);

    // 2. Siunčiame serveriui
    send(soketas, ivestis.c_str(), ivestis.size(), 0);

    if (ivestis == "0" || ivestis == "exit")
        break;

    // 3. Gauname atsakymą iš serverio
    memset(buferis, 0, BUFERIO_DYDIS);
    int gauta = recv(soketas, buferis, BUFERIO_DYDIS, 0);
    if (gauta > 0) {
        std::cout << "🔁 Atsakymas: " << buferis << std::endl;
    } else {
        std::cerr << "❌ Serveris atsijungė arba įvyko klaida.\n";
        break;
    }
}


    close(soketas);
    std::cout << "🔚 Atsijungta nuo serverio.\n";
    return 0;
}
