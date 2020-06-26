#include "gauss.h"

double* func_gauss(double srednia, double odchy, int N) {
	int k, kz;
	double* gauss = new double[N];
	for (k = 0; k < N; k++)	gauss[k] = 0;
	for (kz = 0; kz < N; kz++) gauss[kz] = exp(-1 * pow((double)kz - srednia, 2) / (2. * pow(odchy, 2))) / (odchy * sqrt(2. * 3.1415));
	for (k = 1; k < N; k++) gauss[k] += (gauss[k - 1] >= 1) ? 1 : gauss[k - 1];
	return gauss;
}

double* dystrybuanta(int* histo, int szer, int wys, int N) {
	double* dyst = new double[N];
	int k;
	for (k = 1; k < N; k++) histo[k] += histo[k - 1];
	for (k = 0; k < N; k++) dyst[k] = (double)histo[k] / ((double)szer * (double)wys);
	return dyst;
}

Bitmap^ histogram(Bitmap^ obraz, int szer, int wys, double srednia, double odchy, int N, int N_klas) {
	Bitmap^ obraz2 = gcnew Bitmap(szer, wys);
	int kz, kx, k;
	int* hist = new int[N];
	//double* dyst = new double[N];
	double* dyst_gauss = new double[N];
	int** mono = new int* [szer];
	for (kz = 0; kz < szer; kz++) mono[kz] = new int[wys];
	double* LUT = new double[N];

	Color Px;
	for (kz = 0; kz < wys; kz++)
		for (kx = 0; kx < szer; kx++) {
			Px = obraz->GetPixel(kx, kz);
			mono[kx][kz] = (int)(0.299 * (double)Px.R +
				0.587 * (double)Px.G + 0.114 * (double)Px.B);
			if (mono[kx][kz] < 0) mono[kx][kz] = 0;
			if (mono[kx][kz] >= N) mono[kx][kz] = N - 1;
			hist[mono[kx][kz]]++;
		}
	//dyst = dystrybuanta(hist, szer, wys, N);
	dyst_gauss = func_gauss(srednia, odchy, N);

	double n = 0;
	for (k = 0; k < N; k++) {
		if (dyst_gauss[k] >= ((n + 1.) / (double)N_klas)) {
			n++;
			if (n >= N_klas) n = N_klas - 1;
		}
		LUT[k] = ((double)((N - 1) * n) / (double)(N_klas));
	}


	for (kz = 0; kz < wys; kz++)
		for (kx = 0; kx < szer; kx++) {
			mono[kx][kz] = LUT[mono[kx][kz]];
			obraz2->SetPixel(kx, kz, Color::FromArgb(mono[kx][kz], mono[kx][kz], mono[kx][kz]));
		}

	delete[] hist;
	delete[] LUT;
	for (k = 0; k < wys; k++) delete[] mono[k];
	delete[] mono;
	//delete[] dyst;
	delete[] dyst_gauss;

	return obraz2;
}