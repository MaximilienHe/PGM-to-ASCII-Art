#ifdef _WIN32
#include <windows.h>
#endif // Win 32

#include <iostream>

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // WIN 32

    //Ouverture du fichier "image1.pgm" en mode binaire :
    std::ifstream fichier("image1.pgm", std::ios_base::binary);
    //Ici vous devez décoder l'entête du fichier
    //...
    //Création d'une mémoire de 10 octets :
    std::vector<char> donnees(10);
    //Lecture de 10 octets depuis le fichier et stockage dans le tableau donnees :
    fichier.read(donnees.data(), 10);


    return 0;
}