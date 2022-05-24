#pragma once
#include "Medicament.h"
#include "Observer.h"
#include <vector>
using std::vector;

class Reteta: public Observable {
private:
	std::vector<Medicament> reteta;
public:
	Reteta() = default;

	/*
	* Stergem constructorul de copiere
	*/
	Reteta(const Reteta& ot) = delete;

	/*
	* Adauga un medicament in lista de retete
	* param m: Medicament
	*/
	void adaugaMedicament(const Medicament& m);

	/*
	* Adauga random in lista un numar de medicamente
	* param lista: vector<Medicament>
	* param number: int
	* Adauga in lista un numar de medicamente egal cu number
	*/
	void adaugaRandom(std::vector<Medicament> lista, int number);

	/*
	* Sterge toate medicamentele de pe reteta
	*/
	void deleteReteta();

	/*
	* Returneaza reteta
	*/
	vector<Medicament> getReteta();
};

