#include "pgm2ascii.h"

// Fonction qui permet de d�coder l'entete
std::vector<double> decodageEntete(std::ifstream& fichier)
{
    //D�codage ent�te du fichier (4 lignes) dans un string "ligne"
    std::string ligne;
    std::string ligneTaille;
    std::vector <double> taille;
    taille.reserve(2);
    // On parcourt les 4 premi�res lignes, et lorsqu'on atteint la troisi�me (qui contient les tailles de pixels) on la stocke dans un string sp�cifique
    for (size_t i = 0; i < 4; i++) {
        std::getline(fichier, ligne);
        // 3e ligne atteinte, on r�cup�re les 2 valeurs de taille (largeur / hauteur) dans un vector
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

// Fonction qui permet de r�cuperer les donn�es de l'entete : taille de l'image, hauteur, largeur
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

// Fonction qui permet de r�cuperer les donn�es du fichier sous forme d'un vecteur de int
std::vector<std::vector<int>> recuperationDonneesDuFichier(std::ifstream& fichier, double tailleImage, double hauteur, double largeur)
{
    //Cr�ation d'une m�moire de tailleImage octets :
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
    std::vector<std::vector<int>> donnees;
    donnees.reserve(hauteur);
    std::vector<int> donneesLigne;
    donneesLigne.reserve(largeur);
    size_t cptValeur = 0;
    for (const auto intValeur : donneesUnsignedChar) {
        donneesLigne.push_back(static_cast<int>(intValeur));
        cptValeur++;
        if (cptValeur == largeur) {
            donnees.push_back(donneesLigne);
            donneesLigne = {};
            cptValeur = 0;
        }
    }

    return donnees;
}

// Fonction qui permet de convertir le tableau de int en tableau de code ascii
std::vector<std::vector<std::string>> convertirAvecPalette(std::vector<std::vector<int>> donnees, std::vector<std::string> tableauPalette, double tailleImage, double hauteur, double largeur)
{
    // On parcourt les valeurs du vecteur donnees, et on les compare pour savoir si elles correspondent � W, w, l ...
    std::vector<std::vector<std::string>> donneesEnAscii;
    donneesEnAscii.reserve(hauteur);
    std::vector<std::string> donneesEnAsciiLigne;
    donneesEnAsciiLigne.reserve(largeur);

    double ecart = 255 / tableauPalette.size();

    for (auto ligne : donnees) {
        for (auto valeur : ligne) {
            for (size_t i = 1; i < tableauPalette.size() + 1; i++) {
                if (valeur <= ecart * i) {
                    donneesEnAsciiLigne.push_back(tableauPalette[i - 1]);
                    double ecart = 255 / tableauPalette.size();
                    break;
                }
            }
        }
        donneesEnAscii.push_back(donneesEnAsciiLigne);
        donneesEnAsciiLigne = {};
    }

    return donneesEnAscii;
}

// Fonction qui permet d'extraire dans un tableau la palette de couleur
std::vector<std::string> extractPalette(std::ifstream& palette)
{
    std::vector<std::string> tableauPalette;
    std::string valeurPalette;
    while (!palette.eof()) {
        std::getline(palette, valeurPalette);
        tableauPalette.push_back(valeurPalette);
    }

    return tableauPalette;
}