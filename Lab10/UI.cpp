#include "UI.h"
#include <iostream>
#include <fstream>

ofstream f("file.cvs");
using namespace std;

void Console::printRetetaMenu() {
	cout << "1 - adauga un medicament\n";
	cout << "2 - adauga random un numar de medicamente\n";
	cout << "3 - sterge reteta\n";
	cout << "4 - exporta reteta\n";
	cout << "5 - parasire meniu reteta\n";
}

void Console::printMenu() {
	cout << "1 - adauga\n";
	cout << "2 - sterge\n";
	cout << "3 - modifica\n";
	cout << "4 - filtreaza\n";
	cout << "5 - sorteaza\n";
	cout << "6 - printeaza\n";
	cout << "7 - interfata reteta\n";
	cout << "8 - Undo\n";
	cout << "9 - exit\n";
}

void Console::print() {
	if (serv.get_all().size() == 0)
		cout << "Lista este goala!\n";
	else
		for (auto x : serv.get_all())
			cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";

}

void Console::ui_add() {
	string denumire, producator, subs_activa;
	double pret;
	cout << "Introduceti denumirea: ";
	getline(cin >> ws, denumire);
	cout << "Introduceti producatorul: ";
	getline(cin >> ws, producator);
	cout << "Introduceti substanta activa: ";
	getline(cin >> ws, subs_activa);
	cout << "Introduceti pretul: ";
	cin >> pret;
	try {
		serv.adauga(denumire, producator, subs_activa, pret);
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}
	catch (ValidationException& ve) {
		cout << ve.get_error();
	}
}

void Console::ui_delete() {
	string denumire, producator;
	cout << "Introduceti denumirea: ";
	getline(cin >> ws, denumire);
	cout << "Introduceti producatorul: ";
	getline(cin >> ws, producator);
	try {
		serv.sterge(denumire, producator);
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}

}

void Console::ui_modify() {
	string denumire, producator, subs_activa;
	double pret;
	cout << "Introduceti denumirea: ";
	getline(cin >> ws, denumire);
	cout << "Introduceti producatorul: ";
	getline(cin >> ws, producator);
	cout << "Introduceti substanta activa: ";
	getline(cin >> ws, subs_activa);
	cout << "Introduceti pretul: ";
	cin >> pret;
	try {
		serv.modifica(denumire, producator, subs_activa, pret);
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}
	catch (ValidationException& ve) {
		cout << ve.get_error();
	}
}

void Console::ui_find() {
	string denumire, producator;
	cout << "Introduceti denumirea: ";
	getline(cin >> ws, denumire);
	cout << "Introduceti producatorul: ";
	getline(cin >> ws, producator);
	try {
		auto x = serv.find(denumire, producator);
		cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}
}

void Console::ui_filter() {
	cout << "Introduceti tipul dupa care doriti sa filtrati(pret, substanta activa): ";
	string tip;
	getline(cin >> ws, tip);
	if (tip == "pret") {
		cout << "Introduceti pretul cu care doriti sa filtrati: ";
		double pret;
		cin >> pret;
		try {
			auto list = serv.filter_pret(pret);
			for (auto x : list)
				cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
		}
		catch (RepoException& re) {
			cout << re.get_errorMsg();
		}
	}
	else if (tip == "substanta activa") {
		cout << "Introduceti substanta activa a medicamentelor: ";
		string sub;
		getline(cin >> ws, sub);
		try {
			auto list = serv.filter_sub(sub);
			for (auto x : list)
				cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
		}
		catch (RepoException& re) {
			cout << re.get_errorMsg();
		}
	}
	else
		cout << "Tipul introdus este invalid!\n";
}

void Console::ui_sort() {
	if (serv.get_all().size() > 0) {
		cout << "1 - denumire\n2 - producator\n3 - substata activa + pret\nIntroduceti tipul de sortare pe care doriti sa-l realizati: ";
		int tip;
		cin >> tip;
		if (tip == 1) {
			auto list = serv.sort_by_denumire();
			for (auto x : list)
				cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
		}
		else if (tip == 2) {
			auto list = serv.sort_by_producator();
			for (auto x : list)
				cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
		}
		else if (tip == 3) {
			auto list = serv.sort_by_subAndPrice();
			for (auto x : list)
				cout << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
		}
		else
			cout << "Tip invalid!\n";
	}
	else
		cout << "Lista nu contine medicamente!\n";
}

void Console::reteta_add() {
	string denumire, producator;
	cout << "Introduceti denumirea: ";
	getline(cin >> ws, denumire);
	cout << "Introduceti producatorul: ";
	getline(cin >> ws, producator);
	try {
		serv.addToReteta(denumire, producator);
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}
}

void Console::reteta_sterge() {
	serv.deleteReteta();
	cout << "Reteta a fost stearsa!\n";
}



void Console::reteta_add_rand() {
	int numar;
	cout << "Introduceti numarul de retete care doriti sa fie adaugate: ";
	cin >> numar;
	try {
		serv.addRandom(numar);
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}
}

void Console::reteta_export() {
	if (serv.getReteta().size() == 0)
		f << "Reteta este goala!\n";
	else
		for (auto x : serv.getReteta())
			f << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";

}

void Console::ui_undo() {
	try {
		serv.undo();
	}
	catch (RepoException& re) {
		cout << re.get_errorMsg();
	}
}

void Console::ui_reteta() {
	bool run = 1;
	int cmd2;
	while (run) {
		printRetetaMenu();
		cout << "Introduceti o comanda: ";
		cin >> cmd2;
		switch (cmd2) {
		case 1:reteta_add(); break;

		case 2:reteta_add_rand(); break;

		case 3:reteta_sterge(); break;

		case 4:reteta_export(); break;

		case 5:
			cout << "Ati parasit interfata retetei!\n";
			run = 0;
			break;
		}
	}
}

void Console::run() {
	bool running = 1;
	f << " ";
	int cmd;
	while (running) {
		printMenu();
		cout << "Introduceti o comanda: ";
		cin >> cmd;
		switch (cmd) {
		case 1:ui_add(); break;

		case 2:ui_delete(); break;

		case 3:ui_modify(); break;

		case 4:ui_filter(); break;

		case 5:ui_sort(); break;

		case 6:print(); break;

		case 7:ui_reteta(); break;

		case 8:ui_undo(); break;

		case 9:
			cout << "Ati parasit aplicatia!\n";
			running = 0;
			break;
		default:
			cout << "Comanda invalida!\n";
		}
	}
}