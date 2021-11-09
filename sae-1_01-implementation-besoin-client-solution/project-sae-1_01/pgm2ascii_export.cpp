#include "pgm2ascii_export.h"

void affichageImageAscii(std::vector<std::string> donneesEnAscii, double largeur)
{
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