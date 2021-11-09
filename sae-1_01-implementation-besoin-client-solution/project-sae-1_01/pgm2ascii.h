#pragma once
#include <fstream>
#include <vector>
#include <sstream>

std::vector<double> decodageEntete(std::ifstream& fichier);
std::vector<double> recuperationMetadonnes(std::vector<double> taille);
std::vector<int> recuperationDonneesDuFichier(std::ifstream& fichier, double tailleImage);
std::vector<std::string> convertirAvecPalette(std::vector<int> donnees, double tailleImage);