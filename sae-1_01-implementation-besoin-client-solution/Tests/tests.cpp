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

    //Ouverture du fichier "imagetest.pgm" issu du dossier "ImagePGM" en mode binaire :
    std::ifstream fichier("../ImagePGM/image1.pgm", std::ios_base::binary);

    // Création du fichier image2.txt pour stocker l'image finale
    std::ofstream exportFichier("imagetest.txt");

    // Ouverture du fichier palette.txt issu du dossier "Platte-couleur" :
    std::ifstream palette("../Palette-couleur/paletteUTF8.txt");

    //Extraction des valeurs de la palette
    std::vector<std::string> tableauPalette;
    std::string valeurPalette;
    while (!palette.eof()) {
        std::getline(palette, valeurPalette);
        tableauPalette.push_back(valeurPalette);
    }

    //Décodage entête du fichier (4 lignes) dans un string "ligne"
    std::string ligne;
    std::string ligneTaille;
    std::vector <double> taille;
    taille.reserve(2);
    // On parcourt les 4 premières lignes, et lorsqu'on atteint la troisième (qui contient les tailles de pixels) on la stocke dans un string spécifique
    for (size_t i = 0; i < 4; i++) {
        std::getline(fichier, ligne);
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
    double tailleImage = 1, largeur = 0, hauteur = 0;
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
    double ecart = 255 / tableauPalette.size(); 

    for (auto parcourir : donnees) {
        for (size_t i = 1; i < tableauPalette.size(); i++) {
            if (parcourir <= ecart * i) {
                donneesEnAscii.push_back(tableauPalette[i]);
                double ecart = 255 / tableauPalette.size();
                break;
            }
        }
    }

    // On parcourt le tableau donneesEnAscii pour afficher les valeurs, et afficher un \n si on atteint la taille de la largeur
    size_t cptAffichage = 0;
    for (auto affichagefinal : donneesEnAscii) {
        exportFichier << affichagefinal;
        cptAffichage += 1;
        if (cptAffichage == largeur) {
            exportFichier << "\n";
            cptAffichage = 0;
        }
    }
}