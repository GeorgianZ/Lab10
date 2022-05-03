#pragma once
#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::ostream;
using std::istream;

class Medicament {
private:
	string denumire;
	string producator;
	string substanta_activa;
	double pret;
public:
	/*
	* Stergem constructorul default pentru a nu permite sa se creeze un medicament fara argumente
	*/
	Medicament() = default;
	Medicament(string denumire, string producator, string substanta_activa, double pret) : denumire{ denumire }, producator{ producator }, substanta_activa{ substanta_activa }, pret{ pret }{};

	Medicament(const Medicament& ot) :denumire{ ot.denumire }, producator{ ot.producator }, substanta_activa{ ot.substanta_activa }, pret{ ot.pret }{
		//std::cout << "Copy constructor\n";
	}

	string get_denumire() const;
	string get_producator() const;
	string get_substanta_activa() const;
	double get_pret() const;

	void set_denumire(string denumire);
	void set_producator(string producator);
	void set_substanta_activa(string sub_act);
	void set_pret(double pretNou);

	//bool cmpDenumire(const Medicament& m1, const Medicament& m2);
	//bool cmpProducator(const Medicament& m1, const Medicament& m2);
	//bool cmpSubAndPrice(const Medicament& m1, const Medicament& m2);

	bool operator==(const Medicament& ot) noexcept {
		return denumire == ot.get_denumire();
	}

	bool operator!=(const Medicament& ot) noexcept {
		return denumire != ot.get_denumire();
	}

	/**
	* Functie generica pentru afisarea unui medicament
	*
	* @params: out - o referinta la un string de tip ostream
	*		   medicament - o referinta constanta la un medicament
	*
	* @return: o referinta la un string de tip ostream
	*/
	friend ostream& operator<<(ostream& out, const Medicament& m);

	/**
	* Functie generica pentru citirea unui medicament
	*
	* @params: in - o referinta la un string de tip istream
	*		   masina - o referinta la un medicament
	*
	* @return: o referinta la un string de tip istream
	*/
	friend istream& operator>>(istream& in, Medicament& m);
};

void test_domain();