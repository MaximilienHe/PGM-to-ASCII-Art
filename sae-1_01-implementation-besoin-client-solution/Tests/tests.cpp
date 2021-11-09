#ifdef _WIN32
#include <windows.h>
#endif // Win 32

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // WIN 32

    //Ouverture du fichier "ImageTest1.pgm" en mode binaire :
    std::ifstream fichier("../ImagePGM/image1.pgm", std::ios_base::binary);
    //Ici vous devez décoder l'entête du fichier
    std::string line;
    for (size_t i = 0; i < 4; i++)
    {
        std::getline(fichier, line);
        /*std::cout << line << "\n";*/
    }

    //Création d'une mémoire de 10 octets :
    double tailleImage = 50325;
    std::vector<char> donneesChar(tailleImage);
    //Lecture de 10 octets depuis le fichier et stockage dans le tableau donnees :
    fichier.read(donneesChar.data(), tailleImage);
    std::vector<unsigned char> donneesUnsignedChar;
    donneesUnsignedChar.reserve(tailleImage);
    for (const auto charSigned : donneesChar) {
        donneesUnsignedChar.push_back(static_cast<unsigned char>(charSigned));
    }
    std::vector<int> donnees;
    donnees.reserve(tailleImage);
    for (const auto intValeur : donneesUnsignedChar) {
        donnees.push_back(static_cast<int>(intValeur));
    }


    return 0;
}