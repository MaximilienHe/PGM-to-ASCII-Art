#ifdef _WIN32
#include <windows.h>
#endif // Win 32

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // WIN 32

    //Ouverture du fichier "image1.pgm" issu du dossier "ImagePGM" en mode binaire :
    std::ifstream fichier("../ImagePGM/image1.pgm", std::ios_base::binary);

    //Décodage entête du fichier (4 lignes) dans un string "ligne"
    std::string ligne;
    std::string ligneTaille;
    std::vector <double> taille;
    taille.reserve(2);
    // On parcourt les 4 premières lignes, et lorsqu'on atteint la troisième (qui contient les tailles de pixels) on la stocke dans un string spécifique
    for (size_t i = 0; i < 4; i++) {
        std::getline(fichier, ligne);
        std::cout << ligne << "\n";
        // 3e ligne atteinte, on récupère les 2 valeurs de taille (largeur / hauteur) dans un vector
        if (i == 2) {
            std::stringstream ligneTailleInter(ligne);
            while (!ligneTailleInter.eof()) {
                std::getline(ligneTailleInter, ligneTaille, ' ');
                taille.push_back(std::stod(ligneTaille));
            }
        }
    }
  
    // A partir du vecteur, on calcule la largeur * hauteur dans la variable tailleImage, et on stocke la largeur et la hauteur
    double tailleImage = 1, largeur, hauteur;
    size_t cptTaille = 0;
    for (auto valeurs : taille) {
        tailleImage *= valeurs;
        if (cptTaille == 0) {
            largeur = valeurs;
        }
        else {
            hauteur = valeurs;
        }
        cptTaille += 1;
    }
    std::cout << tailleImage;
  
    //Ouverture du fichier "ImageTest1.pgm" en mode binaire :
    std::ifstream fichier("../ImagePGM/image1.pgm", std::ios_base::binary);

    //Création d'une mémoire de tailleImage octets :
    std::vector<char> donneesChar(tailleImage);
  
    //Lecture de tailleImage octets depuis le fichier et stockage dans le tableau donnees :
    fichier.read(donneesChar.data(), tailleImage);
  
    //Convertion en un tableau de unsigned char
    std::vector<unsigned char> donneesUnsignedChar;
    donneesUnsignedChar.reserve(tailleImage);
    for (const auto charSigned : donneesChar) {
        donneesUnsignedChar.push_back(static_cast<unsigned char>(charSigned));
    }
  
    //Convertion en un tableau de int
    std::vector<int> donnees;
    donnees.reserve(tailleImage);
    for (const auto intValeur : donneesUnsignedChar) {
        donnees.push_back(static_cast<int>(intValeur));
    }

    // On parcourt les valeurs du vecteur donnees, et on les compare pour savoir si elles correspondent à W, w, l ...
    std::vector<std::string> donneesEnAscii;
    donneesEnAscii.reserve(tailleImage);
    for (auto parcourir : donnees) {
        if (parcourir <= 31) {
            donneesEnAscii.push_back("W");
        }
        else if (parcourir <= 63) {
            donneesEnAscii.push_back("w");
        }
        else if (parcourir <= 95) {
            donneesEnAscii.push_back("l");
        }
        else if (parcourir <= 127) {
            donneesEnAscii.push_back("i");
        }
        else if (parcourir <= 159) {
            donneesEnAscii.push_back(":");
        }
        else if (parcourir <= 191) {
            donneesEnAscii.push_back(",");
        }
        else if (parcourir <= 223) {
            donneesEnAscii.push_back(".");
        }
        else if (parcourir <= 255) {
            donneesEnAscii.push_back(" ");
        }
    }

    // On parcourt le tableau donneesEnAscii pour afficher les valeurs, et afficher un \n si on atteint la taille de la largeur
    size_t cptAffichage = 0;
    for (auto affichagefinal : donneesEnAscii) {
        std::cout << affichagefinal;
        cptAffichage += 1;
        if (cptAffichage == largeur) {
            std::cout << "\n";
            cptAffichage = 0;
        }
    }
}