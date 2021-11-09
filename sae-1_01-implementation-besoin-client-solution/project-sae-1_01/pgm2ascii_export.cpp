#include "pgm2ascii_export.h"

// Fonction qui affiche l'image en ascii dans la console
void affichageImageAscii(std::vector<std::vector<std::string>> donneesEnAscii)
{
    for (auto ligne : donneesEnAscii) {
        for (auto valeur : ligne) {
            std::cout << valeur;
        }
        std::cout << "\n";
    }
}