#include "logic.h"

Bitmap^ roznica(Bitmap^ obr1, Bitmap^ obr2, int szer, int wys) {
	Bitmap^ obr_wyj = gcnew Bitmap(szer, wys);
	int pz, px;
	for (pz = 0; pz < wys; pz++)
		for (px = 0; px < szer; px++)
			if ((obr1->GetPixel(px, pz).R == obr2->GetPixel(px, pz).R) && (obr1->GetPixel(px, pz) == Color::FromArgb(255, 255, 255)))
				obr_wyj->SetPixel(px, pz, Color::FromArgb(0, 0, 0));
			else
				obr_wyj->SetPixel(px, pz, obr1->GetPixel(px, pz));
	return obr_wyj;
}

Bitmap^ iloczyn(Bitmap^ obr1, Bitmap^ obr2, int szer, int wys, int i, int j) {
	Bitmap^ obr_wyj = gcnew Bitmap(obr2);
	int pz, px;
	for (pz = 0; pz < wys; pz++) {
		if ((obr1->GetPixel(i, pz) == obr2->GetPixel(i, pz)) && (obr1->GetPixel(i, pz) == Color::FromArgb(255, 255, 255)))
			obr_wyj->SetPixel(i, pz, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(i, pz, Color::FromArgb(0, 0, 0));
		if ((obr1->GetPixel(szer - i - 1, pz) == obr2->GetPixel(szer - i - 1, pz)) && (obr1->GetPixel(szer - i - 1, pz) == Color::FromArgb(255, 255, 255)))
			obr_wyj->SetPixel(szer - i - 1, pz, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(szer - i - 1, pz, Color::FromArgb(0, 0, 0));
	}
	for (px = 0; px < szer; px++) {
		if ((obr1->GetPixel(px, j) == obr2->GetPixel(px, j)) && (obr1->GetPixel(px, j) == Color::FromArgb(255, 255, 255)))
			obr_wyj->SetPixel(px, j, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(px, j, Color::FromArgb(0, 0, 0));
		if ((obr1->GetPixel(px, wys - 1 - j) == obr2->GetPixel(px, wys - 1 - j)) && (obr1->GetPixel(px, wys - 1 - j) == Color::FromArgb(255, 255, 255)))
			obr_wyj->SetPixel(px, wys - 1 - j, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(px, wys - 1 - j, Color::FromArgb(0, 0, 0));
	}
	return obr_wyj;
}

Bitmap^ dylatacja(Bitmap^ obraz, int szer, int wys, int i, int j) {
	Bitmap^ obr_wyj = gcnew Bitmap(obraz);
	int px, pz;

	for (pz = 1; pz < wys - 1; pz++) {
		if (obraz->GetPixel(i, pz).R || obraz->GetPixel(i - 1, pz).R || obraz->GetPixel(i, pz - 1).R || obraz->GetPixel(i + 1, pz).R || obraz->GetPixel(i, pz + 1).R)
			obr_wyj->SetPixel(i, pz, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(i, pz, Color::FromArgb(0, 0, 0));
		if (obraz->GetPixel(szer - i - 1, pz).R || obraz->GetPixel(szer - i - 1 - 1, pz).R || obraz->GetPixel(szer - i - 1, pz - 1).R || obraz->GetPixel(szer - i + 1 - 1, pz).R || obraz->GetPixel(szer - i - 1, pz + 1).R)
			obr_wyj->SetPixel(szer - i - 1, pz, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(szer - i - 1, pz, Color::FromArgb(0, 0, 0));
	}
	for (px = 1; px < szer - 1; px++) {
		if (obraz->GetPixel(px, j).R || obraz->GetPixel(px - 1, j).R || obraz->GetPixel(px, j - 1).R || obraz->GetPixel(px + 1, j).R || obraz->GetPixel(px, j + 1).R)
			obr_wyj->SetPixel(px, j, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(px, j, Color::FromArgb(0, 0, 0));
		if (obraz->GetPixel(px, wys - 1 - j).R || obraz->GetPixel(px - 1, wys - 1 - j).R || obraz->GetPixel(px, wys - 1 - j - 1).R || obraz->GetPixel(px + 1, wys - 1 - j).R || obraz->GetPixel(px, wys - 1 - j + 1).R)
			obr_wyj->SetPixel(px, wys - 1 - j, Color::FromArgb(255, 255, 255));
		else
			obr_wyj->SetPixel(px, wys - 1 - j, Color::FromArgb(0, 0, 0));
	}
	return obr_wyj;
}
