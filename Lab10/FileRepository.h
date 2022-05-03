#pragma once
#include "Repository.h"
#include <string>
#include <fstream>

class FileRepo : public Repo {
	std::string filename;

	/**
	* Functie care populeazare repo-ul cu informatii din fisierul cu numele filename
	*
	* @params: -
	*
	* @return -
	*/
	void loadFromFile();

	/**
	* Functie care scrie repo-ul in fisierul cu numele filename
	*
	* @params: -
	*
	* @return -
	*/
	void writeToFile();

public:
	FileRepo(const string& filename) : Repo(), filename{ filename }{
		this->loadFromFile();
	};

	/*
	* Adauga un medicament in lista de medicamente
	* @param m: medicament
	* return: -
	*
	* throws: RepoException daca medicamentul exista deja in lista
	*/
	void add(const Medicament& med) override;

	/**
	* Functie care sterge o masina din repo
	*
	* @params: masina - o referinta constanta la o masina
	*
	* @return: -
*/
	const Medicament delete_medicine(const Medicament& med) override;

	/*
	* Modifica un medicament din lista
	* @param m: Medicament
	* return -
	*
	* throws: RepoException daca medicamentul exista deja in lista
	*/
	const Medicament modify(const Medicament& med) override;
};


