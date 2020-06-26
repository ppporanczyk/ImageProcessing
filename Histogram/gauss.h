#pragma once

#include "main.h"

double* func_gauss(double srednia, double odchy, int N);
double* dystrybuanta(int* histo, int szer, int wys, int N);
Bitmap^ histogram(Bitmap^ obraz, int szer, int wys, double srednia, double odchy, int N, int N_klas);