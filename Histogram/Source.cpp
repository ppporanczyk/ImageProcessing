#include <iostream>

using namespace std;
using namespace System;
using namespace System::Drawing;

int main()
{
	Bitmap^ obraz, ^ obraz2; // obraz wejs. i wyjsciowy
	obraz = gcnew Bitmap("..\\dots.bmp", true);
	int wys, szer;
	wys = obraz->Height;
	szer = obraz->Width;
	double wys2, szer2, cc, ss, kat;
	wys2 = (double)wys / 2.0; // wsp. srodka obrazu
	szer2 = (double)szer / 2.0;
	int kx, kz, nx, nz; // k - wspolrzedne starego obrazu, n - nowego
	obraz2 = gcnew Bitmap(szer, wys);
	Color Black, Border, White;
	Black = Color::FromArgb(0, 0, 0); //kolor czarny
	Border = Color::FromArgb(0.5, 0.5, 0.5); //kolor czarny
	White = Color::FromArgb(1, 1, 1); //kolor czarny


	for (nx = 0; nx < szer; nx++) {
		if (obraz->GetPixel(nx, 0) == White) {
			obraz2->SetPixel(nx, 0, Border);
		}
		else
			obraz2->SetPixel(nx, 0, Black);
	}

	for (nz = 1; nz < wys; nz++) {
		for (nx = 0; nx < szer; nx++) {
			if (obraz->GetPixel(nx, nz) == White && obraz->GetPixel(nx, nz - 1) == Border) {
				obraz2->SetPixel(nx, nz, Border);
			}
			else
				obraz2->SetPixel(nx, nz, Black);
		}
	}
	
	for (nz = 0; nz < szer; nz++) {
		if (obraz->GetPixel(0, nz) == White) {
			obraz2->SetPixel(0, nz, Border);
		}
		else if(obraz->GetPixel(0, nz) == Black)
			obraz2->SetPixel(nx, 0, Black);
	}
		
	for (nx = 1; nx < szer; nx++) {
		for (nz = 0; nz < wys; nz++) {
			if (obraz->GetPixel(nx, nz) == White && obraz->GetPixel(nx - 1, nz) == Border) {
				obraz2->SetPixel(nx, nz, Border);
			}
			else if (obraz->GetPixel(nx, nz) == Black)
				obraz2->SetPixel(nx, nz, Black);
		}
	}

	for (nx = 0; nx < szer; nx++) {
		if (obraz->GetPixel(nx, wys-1) == White) {
			obraz2->SetPixel(nx, wys-1, Border);
		}
		else if (obraz->GetPixel(nx, wys-1) == Black)
			obraz2->SetPixel(nx, wys-1, Black);
	}

	for (nz = wys-2; nz > 0; nz--) {
		for (nx = 0; nx < szer; nx++) {
			if (obraz->GetPixel(nx, nz) == White && obraz->GetPixel(nx, nz + 1) == Border) {
				obraz2->SetPixel(nx, nz, Border);
			}
			else if (obraz->GetPixel(nx, nz) == Black)
				obraz2->SetPixel(nx, nz, Black);
		}
	}
	
	for (nz = 0; nz < wys; nz--) {
		if (obraz->GetPixel(szer-1, nz) == White) {
			obraz2->SetPixel(szer-1, nz, Border);
		}
		else if(obraz->GetPixel(szer-1, nz) == Black)
			obraz2->SetPixel(szer-1, nz, Black);
	}
		
	for (nx = szer - 2; nx > 0; nx--) {
		for (nz = 0; nz < wys; nz++) {
			if (obraz->GetPixel(nx, nz) == White && obraz->GetPixel(nx, nz + 1) == Border) {
				obraz2->SetPixel(nx, nz, Border);
			}
			else if (obraz->GetPixel(nx, nz) == Black)
				obraz2->SetPixel(nx, nz, Black);
		}
	}
	obraz2->Save("dots_new.png");
	return 0;
}