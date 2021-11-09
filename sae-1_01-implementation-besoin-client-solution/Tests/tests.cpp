#ifdef _WIN32
#include <windows.h>
#endif // Win 32

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
  
    // Recuperation des données de l'entete et stockage dans des variables
    std::vector<double> metaDonnes = recuperationMetadonnes(taille);
    double tailleImage = metaDonnes[0], largeur = metaDonnes[1], hauteur = metaDonnes[2];

    // Recuperation des données du fichier
    std::vector<int> donnees = recuperationDonneesDuFichier(fichier, tailleImage);

    // On parcourt les valeurs du vecteur donnees, et on les compare pour savoir si elles correspondent à W, w, l ...
    std::vector<std::string> donneesEnAscii = convertirAvecPalette(donnees, tailleImage);

    // On parcourt le tableau donneesEnAscii pour afficher les valeurs, et afficher un \n si on atteint la taille de la largeur
    affichageImageAscii(donneesEnAscii, largeur);
}