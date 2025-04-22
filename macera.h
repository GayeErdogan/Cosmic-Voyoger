#ifndef YAZILIM_KAPLANI_MACERA_H
#define YAZILIM_KAPLANI_MACERA_H

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <random>
#include <string>

class Gemi
{
protected:
    int yakit;
    int saglik;
    int para;

public:
    Gemi()
            : yakit(100)
            , saglik(100)
            , para(0)
    {
    }

    virtual double kacma_Olasiligi() const = 0;
    virtual double hasar_Katsayisi() const = 0;

    bool hasar_Al(int miktar)
    {
        int hasar = static_cast<int>(miktar * hasar_Katsayisi());
        saglik -= hasar;
        return saglik > 0;
    }

    void para_Ekle(int miktar) { para += miktar; }

    void yakit_Tuket(int miktar) { yakit = std::max(yakit - miktar, 0); }

    int get_Yakit() const { return yakit; }
    int get_Saglik() const { return saglik; }
    int get_para() const { return para; }

    virtual ~Gemi() {}
};

class Hizli_Gemi : public Gemi
{
public:
    double kacma_Olasiligi() const override { return 1.5; }
    double hasar_Katsayisi() const override { return 1.5; }
};

class Guclu_Gemi : public Gemi
{
public:
    double kacma_Olasiligi() const override { return 0.5; }
    double hasar_Katsayisi() const override { return 0.5; }
};

class Normal_Gemi : public Gemi
{
public:
    double kacma_Olasiligi() const override { return 1.0; }
    double hasar_Katsayisi() const override { return 1.0; }
};

std::random_device rd;
std::mt19937 mt(rd());

int random_Sayi(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
int secPazarlikMiktari()
{
    int pazarlikMiktarlari[3] = { 10, 20, 30 };
    int index = random_Sayi(0, 2);
    return pazarlikMiktarlari[index];
}
void uzay_korsanlari(Gemi* gemi)
{
    std::cout << "UZAY KORSANLARI!!! Kasif komuta sendeydi napmamiz gerektigini soyle.\nKacmak icin (1), Savasmak icin "
                 "(2), Pazarlik icin (3)\nUmarim dogru karari verirsin: ";
    bool tekrarSecenekSun;
    do {
        tekrarSecenekSun = false;
        int pazarlik_Miktari;
        int secim;
        std::cin >> secim;
        switch(secim) {
            case 1:
                if(gemi->get_Yakit() < 33) { // Yeterli yakıt kontrolü
                    std::cout << "Yeterli yakitin yok KASIF, kacamazsin! \nNeyse hala vaktimiz var.\nSavasmak icin (2), "
                                 "Pazarlik icin (3)\nSana guveniyorum kasif:  ";
                    tekrarSecenekSun = true;
                } else if(random_Sayi(1, 100) <= static_cast<int>(gemi->kacma_Olasiligi() * 50)) {
                    std::cout
                            << "Korsanlari kaybettik! Boyle kivrak manevralar alabildigini bilsem cok onceden ise alirdim seni."
                            << std::endl;
                    gemi->yakit_Tuket(23);
                } else {
                    std::cout << "HALA PESIMIZDELER! Yakalayamadiler hala.\nKacmak icin (1), Savasmak icin (2), Pazarlik "
                                 "icin (3)\nSana guveniyorum kasif:  ";
                    gemi->yakit_Tuket(33);
                    tekrarSecenekSun = true;
                }
                break;
            case 2: // Savaşma
                if(random_Sayi(1, 100) <= 50) {
                    std::cout << "Perisan ettik korsanlari. Bir dahakine namimizi duyup saldirmazlar az zekilerse.\nBu da "
                                 "ne. Para!!! Ustune bir de para kazandik kasif!"
                              << std::endl;
                    gemi->para_Ekle(50);
                } else {
                    std::cout << "Hayat bitti! Tam bir rezillik! Savasi kaybettik!\nMakine dairesinden gelen verilere gore "
                              << gemi->hasar_Katsayisi() * 40 << " hasar almisiz." << std::endl;
                    gemi->hasar_Al(40);
                }
                break;
            case 3: // Pazarlık
                pazarlik_Miktari = secPazarlikMiktari();
                if(gemi->get_para() >= pazarlik_Miktari) {
                    gemi->para_Ekle(-pazarlik_Miktari);
                    std::cout << "Cana gelecegine mala gelsin." << pazarlik_Miktari
                              << " rusvet vererek korsanlardan kurtulduk." << std::endl;
                } else {
                    std::cout << "Madem paramm paramiz yok niye pazarlik seciyorsun sayin kasif! Gafil avlandik ciddi "
                                 "zarar aldik.\nMakine dairesinden gelen verilere gore "
                              << gemi->hasar_Katsayisi() * 40 << " hasar almisiz." << std::endl;
                    gemi->hasar_Al(40);
                }
                break;
            default:
                std::cout << "Sayin kasif yeterli zeka seviyesine sahip oldugunuzu dusunmek istiyorum.\nGecersiz emriniz "
                             "sonucu korsanlar sinirlendi.\nCiddi zarar aldik.\nMakine dairesinden gelen verilere gore "
                          << gemi->hasar_Katsayisi() * 30 << " hasar almisiz." << std::endl;
                gemi->hasar_Al(30);
                break;
        }
    } while(tekrarSecenekSun);
}
void handle_Events(Gemi* gemi)
{
    int event = random_Sayi(1, 3);
    std::cout << "Uzaktan bir sey yaklasiyor!!!";

    if(event == 1) {
        std::cout << "EYVAH! Bu bir astroid kusagi!" << std::endl;
        if(random_Sayi(1, 2) == 1) {
            int hasar = 10;
            gemi->hasar_Al(hasar);
            std::cout << "Agh!!! Daha taksidi bitmemisti geminin. Makine dairesinden gelen verilere gore "
                      << gemi->hasar_Katsayisi() * hasar << " hasar almisiz." << std::endl;
        } else {
            std::cout << "Ucuz atlattik bir caylaga gore bayagi iyisin." << std::endl;
        }

    } else if(event == 2) {
        std::cout << "Terkedilmis bir gezegen! Inip bakalim belki degerli bir seyler vardir." << std::endl;
        if(random_Sayi(1, 2) == 1) {
            int bulunan_para = 10;
            gemi->para_Ekle(bulunan_para);
            std::cout << "Su madenlere bak! HAHAHAHAHAHAHAHA!!! Koseyi donduk kasif! " << bulunan_para
                      << " para degerinde maden bulduk." << std::endl;
        } else {
            uzay_korsanlari(gemi);
        }
    } else {
        uzay_korsanlari(gemi);
    }
    gemi->yakit_Tuket(10);
    std::cout << "\n\nYasanan olaylar sonucu durum raporu.\n" << std::endl;
    std::cout << "Geminizin kalan yakiti: " << gemi->get_Yakit() << std::endl;
    std::cout << "Geminizin saglik durumu: " << gemi->get_Saglik() << std::endl;
    std::cout << "Topladiginiz para miktari: " << gemi->get_para() << "\n\n";
    std::cout << "Robot olmadiginizi kontrol etmek icin herhengi bir sey yazip entera basin: ";
    int w;
    std::cin >> w;
}

int hesapla_Puan(const Gemi& gemi)
{
    return (gemi.get_Yakit() * 5) + (gemi.get_Saglik() * 10) + (gemi.get_para() * 10);
}

void oyun_Akisi(Gemi* gemi)
{
    int puan;
    const int max_Olay_Sayisi = 5;
    for(int i = 0; i < max_Olay_Sayisi; ++i) {
        handle_Events(gemi);

        if(gemi->get_Yakit() == 0) {
            puan = hesapla_Puan(*gemi);
            std::cout << "Yakitiniz bitti ve uzayin derin boslugunda suzulup sonsuzluk icinde yok oldunuz.\nOyun "
                         "Bitti!\nOyun sonu puaniniz: "
                      << puan << std::endl;
            return;
        }

        if(gemi->get_Saglik() <= 0) {
            puan = hesapla_Puan(*gemi);
            std::cout << "Geminiz hasar gordu ve hava sizdiriyorsunuz. Nefessiz kaldiniz ve oldunuz.\nOyun "
                         "bitti!\nOyun sonu puaniniz: "
                      << puan << std::endl;
            return;
        }
    }
    puan = hesapla_Puan(*gemi);
    std::cout << "Guzel bir yolculuktu kasif. Umarim ileride baska maceralarda da karsilasiriz.\nOyun sonu puaniniz: "
              << puan << std::endl;
}

#endif //YAZILIM_KAPLANI_MACERA_H
