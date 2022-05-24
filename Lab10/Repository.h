#pragma once
#include "Medicament.h"
#include "VectDin.h"
#include "Observer.h"
#include <vector>
using std::vector;



class RepoException {
private:
	string errorMsg;
public:
	RepoException(string error) : errorMsg{ error } {};
	string get_errorMsg() const {
		return this->errorMsg;
	}
};

class Repo {
private:
	vector<Medicament> MedicineList;
	//MyList<Medicament> MedicineList;
public:
	Repo() = default;

	/*
	* Stergem constructorul de copiere, deoarece dorim sa existe un singur repository
	*/
	Repo(const Repo& ot) = delete;

	/*
	* Adauga un medicament in lista de medicamente
	* @param m: medicament
	* return: -
	*
	* throws: RepoException daca medicamentul exista deja in lista
	*/
	virtual void add(const Medicament& m);

	/*
	* Returneaza o lista cu toate medicamentele
	* return: lista de medicamente
	*/
	const vector<Medicament>& get_all();

	/*
	* Cauta un medicament in lista de medicamente dupa denumire si producator
	* @param denumire: string
	* @param producator: string
	* return: Medicament cu denumirea si producatorul dat
	*
	* throws: RepoException daca medicamentul nu exista in lista
	*/
	const Medicament& find_medicine(string denumire, string producator);

	/*
	* Returneaza true daca un obiect exista in lista si false daca obiectul nu exista
	* return: true/false
	*/
	bool exist(const Medicament& m);

	/*
	* Sterge un medicament din lista daca acesta exista
	* @param m: Medicament
	* return: -
	*
	* throws: RepoException daca medicamentul nu exista in lista
	*/
	virtual const Medicament delete_medicine(const Medicament& m);

	/*
	* Modifica un medicament din lista
	* @param m: Medicament
	* return -
	*
	* throws: RepoException daca medicamentul exista deja in lista
	*/
	virtual const Medicament modify(const Medicament& m);
};


void test_repoExp();
void test_repo();

