#pragma once

#include "main.h"

int** normalize(double** img, int nor_szer, int nor_wys, double min_in, double max_in, int min_out, int max_out);
Bitmap^ filter(Bitmap^ img, int szer, int wys, int szer_ok, int wys_ok, int N);