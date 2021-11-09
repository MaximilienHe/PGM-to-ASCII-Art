#include "pgm2ascii.h"

// Fonction qui permet de décoder l'entete
std::vector<double> decodageEntete(std::ifstream& fichier)
{
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
    return taille;
}

// Fonction qui permet de récuperer les données de l'entete : taille de l'image, hauteur, largeur
std::vector<double> recuperationMetadonnes(std::vector<double> taille)
{
    std::vector<double> result;
    result.reserve(3);
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
    result.push_back(tailleImage);
    result.push_back(largeur);
    result.push_back(hauteur);

    return result;
}

// Fonction qui permet de récuperer les données du fichier sous forme d'un vecteur de int
std::vector<int> recuperationDonneesDuFichier(std::ifstream& fichier, double tailleImage)
{
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

    return donnees;
}

// Fonction qui permet de convertir le tableau de int en tableau de code ascii
std::vector<std::string> convertirAvecPalette(std::vector<int> donnees, double tailleImage)
{
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

    return donneesEnAscii;
}