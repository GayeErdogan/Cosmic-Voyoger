#include "cmake-build-debug/.cmake/macera.h"

int main()
{
    std::cout << "COSMIC VOYAGER'a Hos Geldiniz!\n";
    std::cout << "Gemi tipi secin: Hizli (1), Guclu (2), Normal (3): ";

    int gemi_Tipi;
    while(!(std::cin >> gemi_Tipi) || gemi_Tipi < 1 || gemi_Tipi > 3) {
        std::cout << "Dusundurucu daha 3 secenek arasindan duzgun bir tercih bile yapamiyorsun. Tekrar sec: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Gemi* gemi = nullptr;

    switch(gemi_Tipi) {
        case 1:
            gemi = new Hizli_Gemi();
            break;
        case 2:
            gemi = new Guclu_Gemi();
            break;
        case 3:
            gemi = new Normal_Gemi();
            break;
    }

    oyun_Akisi(gemi);

    delete gemi;
    return 0;
}
