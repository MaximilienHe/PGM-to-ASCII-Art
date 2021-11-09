#ifdef _WIN32
#include <windows.h>
#endif // Win 32

#include <iostream>
#include "../project-sae-1_01/pgm2ascii.h"
#include "../project-sae-1_01/pgm2ascii_export.h"

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // WIN 32

    //Ouverture du fichier "image2.pgm" issu du dossier "ImagePGM" en mode binaire :
    std::ifstream fichier("../ImagePGM/image2.pgm", std::ios_base::binary);

    // Decodage de l'entete dans un tableau taille
    std::vector<double> taille = decodageEntete(fichier);

    // Création du fichier image-exporter.txt pour stocker l'image finale
    std::ofstream exportFichier("image-exporter.txt");

    // Ouverture du fichier palette2.txt issu du dossier "Platte-couleur" :
    std::ifstream palette("../Palette-couleur/palette2.txt");

    //Extraction des valeurs de la palette
    std::vector<std::string> tableauPalette = extractPalette(palette);
  
    std::vector<double> metaDonnes = recuperationMetadonnes(taille);
    double tailleImage = metaDonnes[0], largeur = metaDonnes[1], hauteur = metaDonnes[2];

    // Recuperation des données du fichier
    std::vector<std::vector<int>> donnees = recuperationDonneesDuFichier(fichier, tailleImage, hauteur, largeur);
  
    // On parcourt les valeurs du vecteur donnees, et on les compare pour savoir si elles correspondent � W, w, l ...
    std::vector<std::vector<std::string>> donneesEnAscii = convertirAvecPalette(donnees, tableauPalette, tailleImage, hauteur, largeur);

    // On parcourt le tableau donneesEnAscii pour créer un fichier texte qui contient l'image
    exportImageAsciiEnTxt(donneesEnAscii, exportFichier);

    return 0;
}
