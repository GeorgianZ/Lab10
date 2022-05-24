#pragma once
#include "Repository.h"
#include "Validation.h"
#include "Reteta.h"
#include <unordered_map>
#include "Undo.h"
#include <string>
#include "FileRepository.h"
using std::unique_ptr;
using std::string;


class Service {
private:
	Repo& repo;
	Validate& val;
	std::vector<unique_ptr<Undo>> undoActions;
	Reteta reteta;
	unordered_map<string, int> map;
public:
	Service(Repo& repo, Validate& val) : repo{ repo }, val{ val } {};

	/*
	* Stergem constructorul de copiere pentru ca vrem sa fie doar un singur Service
	*/
	Service(const Service& ot) = delete;

	/*
	* Adauga un medicament in lista
	* Primeste datele necesare unui medicament
	* Medicamentul este creat, validat si adaugat in repository
	* @param denumire: string
	* @param producator: string
	* @param substanta_activa: string
	* @param pret: double
	* return: -
	*/
	void adauga(string denumire, string producator, string substanta_activa, double pret);

	/*
	* Returneaza o lista de medicamente
	* return lista de medicamente
	*/
	const vector<Medicament>& get_all();

	/*
	* Sterge un medicament din lista
	* Primeste denumirea si producatorul medicamentului
	* @param denumire: string
	* @param producator: string
	* return: -
	*/
	void sterge(string denumire, string producator);

	/*
	* Modifica un medicament din lista
	* Primeste denumirea, producatorul, substanta activa si pretul
	* Modifica medicamentul cu aceeasi denumire
	* @param denumire: string
	* @param producator: string
	* @param substanta_activa: string
	* @param pret: double
	* return: -
	*/
	void modifica(string denumire, string producator, string substanta_activa, double pret);

	/*
	* Cauta un medicament in lista de medicamente
	* Primeste ca parametrii denumirea si producatorul
	* @param denumire: string
	* @param producator: string
	* return: Medicament cu denumirea si producatorul dat
	*/
	const Medicament& find(string denumire, string producator);

	/*
	* Returneaza o lista filtrata dupa pret
	* Elementele din lista au pretul mai mare decat cel trimis ca parametru
	* @param pret: double
	* return lista de medicamente
	*/
	const vector<Medicament> filter_pret(double pret);

	/*
	* Returneaza o lista filtrata dupa substanta activa
	* Elementele din lista au substanta activa cea trimisa ca parametru
	* @param subs_act: string
	* return lista de medicamente
	*/
	const vector<Medicament> filter_sub(string subs_act);

	/*
	* Returneaza o lista sortata dupa denumirea medicamentelor
	* return: lista sortata dupa denumire
	*/
	const vector<Medicament> sort_by_denumire();

	/*
	* Returneaza o lista sortata dupa producator
	* return: lista sortata dupa producator
	*/
	const vector<Medicament> sort_by_producator();

	/*
	* Returneaza o lista sortata dupa substanta activa si pret
	* return: lista sortata dupa substanta activa si pret
	*/
	const vector<Medicament> sort_by_subAndPrice();

	/*
	* Adauga un medicament cu denumirea si producatorul dat
	*
	* @param denumirea: denumirea medicamentului care se adauga (string)
	* @param producator: producatorul medicamentului care se adauga (string)
	*
	* @throws: RepoException daca nu exista medicament cu denumirea si producatorul dat
	*/
	void addToReteta(string denumire, string producator);

	/*
	* Adauga random un numar de medicamente dat de utilizator
	*
	* @param number: numarul de medicamente care trebuie adaugat
	*
	* @throws: RepoException daca vrem sa adaugam mai multe medicamente decat exista in repository
	*/
	void addRandom(int number);

	/*
	* Returneaza lista de medicamente din reteta
	*/
	vector<Medicament> getReteta();

	/*
	* Sterge medicamentele de pe reteta
	*/
	void deleteReteta();

	void createMap();
	unordered_map<string, int> getMap();

	/*
	* Executa functia de undo pentru elementele din repository
	* throws Exception: daca nu exista elemente in lista
	* return: -
	*/
	void undo();

	Reteta& getList() {
		return this->reteta;
	}

};

void test_add_service();
void test_sterge_service();
void test_modifica_service();
void test_find();
void test_filter_pret();
void test_filter_sub();
void test_sort();
void test_reteta();
void test_map();
void test_undo();

