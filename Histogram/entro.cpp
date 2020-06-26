#include "entro.h"

int** normalize(double** img, int nor_szer, int nor_wys, double min_in, double max_in, int min_out, int max_out) {
	int px, pz, k, col_in, col_out;
	int** ent = new int* [nor_wys];
	for (k = 0; k < nor_wys; k++) ent[k] = new int[nor_szer];
	for (pz = 0; pz < nor_wys; pz++) 
		for (px = 0; px < nor_szer; px++)
			ent[px][pz] = ((min_out - max_out) / (min_in - max_in) * (img[px][pz]- min_in)) + min_out;

	return ent;
}

Bitmap^ filter(Bitmap^ img, int szer, int wys, int szer_ok, int wys_ok, int N) {
	Bitmap^ img_out = gcnew Bitmap(szer, wys);
	Color PQ;
	int px, pz, px_loc, pz_loc, k;
	double entro = 0, min = 255, max = 0;
	double* praw = new double[N];
	for (k = 0; k < N; k++) praw[k] = 0;
	double** ent = new double* [wys];
	for (k = 0; k < wys; k++) ent[k] = new double[szer]; 
	int** ent_int = new int* [wys];
	for (k = 0; k < wys; k++) ent_int[k] = new int[szer];

	int odstep_x = (szer_ok - 1) / 2;
	int odstep_y = (wys_ok - 1) / 2;

	for (pz = 0; pz < wys; pz++) {
		for (px = 0; px < szer; px++) {
			if (px >= odstep_x && px < (szer - odstep_x) && pz >= odstep_y && pz < (wys - odstep_y)) {
				for (pz_loc = pz - odstep_y; pz_loc <= pz + odstep_y; pz_loc++)
					for (px_loc = px - odstep_x; px_loc <= px + odstep_x; px_loc++) {
						PQ = img->GetPixel(px_loc, pz_loc);
						praw[PQ.R]++;
						praw[PQ.G]++;
						praw[PQ.B]++;
					}

				for (k = 0; k < N; k++) if (praw[k] > 0) praw[k] = praw[k] / ((double)(szer_ok * wys_ok * 3));

				entro = 0;
				for (k = 0; k < N; k++)
					if (praw[k] > 0) {
						entro += praw[k] * (log10(praw[k]));
						praw[k] = 0;
					}
				
				ent[px][pz] = -1*entro;

				min = (ent[px][pz] < min) ? ent[px][pz] : min;
				max = (ent[px][pz] > max) ? ent[px][pz] : max;
				
			}

		}
	}
	
	for (pz = 0; pz < odstep_y; pz++) for (px = 0; px < szer; px++) ent[px][pz]=ent[px][pz+odstep_y];
	for (pz = wys - odstep_y; pz < wys; pz++) for (px = 0; px < szer; px++) ent[px][pz]= ent[px][pz - odstep_y];
	for (pz = 0; pz < wys; pz++) for (px = 0; px < odstep_x; px++) ent[px][pz] = ent[px + odstep_x][pz];
	for (pz = 0; pz < wys; pz++) for (px = szer - odstep_x; px < szer; px++) ent[px][pz] = ent[px - odstep_x][pz];
	
	for (pz = 0; pz < wys; pz++) 
		for (px = 0; px < szer; px++) 
			ent[px][pz] /= max;
	ent_int = normalize(ent, szer, wys, 0, 1, 0, 255);
	for (pz = 0; pz < wys; pz++)
		for (px = 0; px < szer; px++)
			img_out->SetPixel(px, pz, Color::FromArgb(ent_int[px][pz], ent_int[px][pz], ent_int[px][pz]));
	delete[] praw;
	for (k = 0; k < wys; k++) delete[] ent[k];
	delete[] ent;
	for (k = 0; k < wys; k++) delete[] ent_int[k];
	delete[] ent_int;
	return img_out;
}
