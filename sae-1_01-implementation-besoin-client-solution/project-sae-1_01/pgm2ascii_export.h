#pragma once
#include <iostream>
#include "pgm2ascii.h"

void affichageImageAscii(std::vector<std::vector<std::string>> donneesEnAscii);
void exportImageAsciiEnTxt(std::vector<std::vector<std::string>> donneesEnAscii, std::ofstream& exportFichier);