#pragma once
#include <fstream>
#include <vector>
#include <sstream>

std::vector<double> decodageEntete(std::ifstream& fichier);
std::vector<double> recuperationMetadonnes(std::vector<double> taille);
std::vector<std::vector<int>> recuperationDonneesDuFichier(std::ifstream& fichier, double tailleImage, double hauteur, double largeur);
std::vector<std::vector<std::string>> convertirAvecPalette(std::vector<std::vector<int>> donnees, std::vector<std::string> tableauPalette, double tailleImage, double hauteur, double largeur);
std::vector<std::string> extractPalette(std::ifstream& palette);