#include "morfo.h"
#include "gauss.h"
#include "logic.h"
#include "entro.h"

Bitmap^ histogram_gauss(Bitmap^ obr, int szer, int wys, const int N);
Bitmap^ filtracja_entropii(Bitmap^ obr, int szer, int wys, const int N);
Bitmap^ morfologie(Bitmap^ obr, int szer, int wys);
Bitmap^ przeciecie_brzegiem(Bitmap^ obr, int szer, int wys);

int main()
{
	Bitmap ^ obraz, ^obraz2;
	obraz = gcnew Bitmap("../fruits.png");
	//obraz = gcnew Bitmap("..\\cameraman.tif");
	//obraz = gcnew Bitmap("..\\zelda.png");
	//obraz = gcnew Bitmap("..\\kropken.png");
	//obraz = gcnew Bitmap("..\\polar.bmp");
	int wys = obraz->Height;
	int szer = obraz->Width;
	const int N = 256;
	//cout << "Wysokosc " << wys << "  Szerokosc  " << szer << endl;

	obraz2 = gcnew Bitmap(szer, wys);
	int button=0;
	cout << "Wybierz przekszalcenie:" << endl << "1.Normalizacja histogramu" << endl << "2.Filtracja entropii" << endl << "3.Gradient morfologiczny" << endl<<"4.Usuniecie elementow przecietych brzegiem" << endl;
	cin>>button;
	switch (button) {
		case 1:
			obraz2 = histogram_gauss(obraz, szer, wys,  N);
			break;
		case 2:
			obraz2 = filtracja_entropii(obraz, szer, wys, N);
			break;
		case 3:
			obraz2 = morfologie(obraz, szer, wys);
			break;
		case 4:
			obraz2 = przeciecie_brzegiem(obraz, szer, wys);
			break;
		default:
			cout << "Nieprawidlowa wartosc" << endl;
			return 0;
	}
	
	obraz2->Save("newImage.bmp");

	return 0;
}

Bitmap^ histogram_gauss(Bitmap^ obr, int szer, int wys, const int N) {

	double srednia = 127.5;
	int N_klas = 10;
	double odchy;
	cout << "Podaj wartoœc odchylenia" << endl;
	cin >> odchy; // zadane odchylenie

	return histogram(obr, szer, wys, srednia, odchy, N, N_klas);
}

Bitmap^ filtracja_entropii(Bitmap^ obr, int szer, int wys, const int N) {
	int szer_okno, wys_okno;
	cout << "Podaj szer okna: " << endl;
	cin >> szer_okno;
	cout << "Podaj wys okna: " << endl;
	cin >> wys_okno;
	if (!(szer_okno % 2) || !(wys_okno % 2)) {
		cout << "Wymagana liczba parzysta parametrów" << endl;
		exit(0);
	}
	return filter(obr, szer, wys, szer_okno, wys_okno, N);
}

Bitmap^ morfologie(Bitmap^ obr, int szer, int wys) {
	int met = 0;
	cout << "Wybierz metode:"<<endl<<"1.dylatacja-obraz" << endl << "2.obraz-erozja" << endl << "3.dylatacja-erozja" << endl;
	cin >> met;
	switch (met) {
	case 1:
		return morf_dyl_obr(obr, wys, szer);
	case 2:
		return morf_obr_ero(obr, wys, szer);
	case 3:
		return morf_dyl_ero(obr, wys, szer);
	}
}

Bitmap^ przeciecie_brzegiem(Bitmap^ obr, int szer, int wys) {
	Bitmap^ black = gcnew Bitmap(szer, wys);
	Bitmap^ log2 = gcnew Bitmap(szer, wys);
	int pz, px;
	for (pz = 1; pz < wys - 1; pz++)
		for (px = 1; px < szer - 1; px++)
			black->SetPixel(px, pz, Color::FromArgb(0, 0, 0));

	for (pz = 0; pz < wys; pz++)  black->SetPixel(0, pz, obr->GetPixel(0, pz));
	for (px = 0; px < szer; px++) black->SetPixel(px, 0, obr->GetPixel(px, 0));
	for (pz = 0; pz < wys; pz++)  black->SetPixel(szer - 1, pz, obr->GetPixel(szer - 1, pz));
	for (px = 0; px < szer; px++) black->SetPixel(px, wys - 1, obr->GetPixel(px, wys - 1));

	int i = 1, j = 1;
	while (i < szer - 1 && j < wys - 1) {
		log2 = dylatacja(black, szer, wys, i, j);
		black = iloczyn(obr, log2, szer, wys, i, j);
		i++;
		j++;
	}
	return roznica(obr, black, szer, wys);
}
