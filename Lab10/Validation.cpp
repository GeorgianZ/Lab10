#include "Validation.h"

string Validate::valideaza(const Medicament& m) {
	string err = "";
	if (m.get_denumire() == "")
		err += "Medicamentul are o denumire invalida!\n";
	if (m.get_producator() == "")
		err += "Medicamentul are un producator invalid!\n";
	if (m.get_substanta_activa() == "")
		err += "Medicamentul are o substanta activa invalida!\n";
	if (m.get_pret() <= 0)
		err += "Medicamnetul are un pret invalid!\n";
	return err;
}