#include "morfo.h"

Bitmap^ morf_obr_ero(Bitmap^ obraz, int wys, int szer) {
	Bitmap^ obraz2 = gcnew Bitmap(szer, wys);
	int px, pz;
	for (pz = 0; pz < wys; pz++)
		for (px = 0; px < szer; px++) {
			int org = obraz->GetPixel(px, pz).R;
			int min = org;
			if (min == 0)
				obraz2->SetPixel(px, pz, Color::FromArgb(0, 0, 0));
			else {
				if (px != 0) min = (obraz->GetPixel(px - 1, pz).R < min) ? obraz->GetPixel(px - 1, pz).R : min;
				if (px != szer - 1) min = (obraz->GetPixel(px + 1, pz).R < min) ? obraz->GetPixel(px + 1, pz).R : min;
				if (pz != 0) min = (obraz->GetPixel(px, pz - 1).R < min) ? obraz->GetPixel(px, pz - 1).R : min;
				if (pz != wys - 1) min = (obraz->GetPixel(px, pz + 1).R < min) ? obraz->GetPixel(px, pz + 1).R : min;
				obraz2->SetPixel(px, pz, Color::FromArgb(org - min, org - min, org - min));
			}
		}
	return obraz2;
}

Bitmap^ morf_dyl_obr(Bitmap^ obraz, int wys, int szer) {
	Bitmap^ obraz2 = gcnew Bitmap(szer, wys);
	int px, pz;
	for (pz = 0; pz < wys; pz++)
		for (px = 0; px < szer; px++) {
			int org = obraz->GetPixel(px, pz).R;
			int max = org;
			if (max == 255)
				obraz2->SetPixel(px, pz, Color::FromArgb(0, 0, 0));
			else {
				if (px != 0) max = (obraz->GetPixel(px - 1, pz).R > max) ? obraz->GetPixel(px - 1, pz).R : max;
				if (px != szer - 1) max = (obraz->GetPixel(px + 1, pz).R > max) ? obraz->GetPixel(px + 1, pz).R : max;
				if (pz != 0) max = (obraz->GetPixel(px, pz - 1).R > max) ? obraz->GetPixel(px, pz - 1).R : max;
				if (pz != wys - 1) max = (obraz->GetPixel(px, pz + 1).R > max) ? obraz->GetPixel(px, pz + 1).R : max;
				obraz2->SetPixel(px, pz, Color::FromArgb(max - org, max - org, max - org));
			}
		}
	return obraz2;
}

Bitmap^ morf_dyl_ero(Bitmap^ obr, int wys, int szer) {
	Bitmap^ dylat = morf_dyl_obr(obr, wys, szer);
	Bitmap^ eroz = morf_obr_ero(obr, wys, szer);
	Bitmap^ obraz = gcnew Bitmap(szer, wys);
	int px, pz;
	for (pz = 0; pz < wys; pz++)
		for (px = 0; px < szer; px++) {
			int tem = dylat->GetPixel(px, pz).R + eroz->GetPixel(px, pz).R;
			obraz->SetPixel(px, pz, Color::FromArgb(tem, tem, tem));
		}
	return obraz;
}