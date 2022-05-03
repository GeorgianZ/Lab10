#include "FileRepository.h"

void FileRepo::loadFromFile() {
	std::ifstream in(this->filename, std::ios::in);

	if (!in.is_open()) {

		throw RepoException("Open error: " + this->filename + "\n");
	}

	if (in.peek() == std::ifstream::traits_type::eof()) {
		return;
	}

	while (!in.eof()) {
		if (in.peek() == std::ifstream::traits_type::eof()) {
			return;
		}
		Medicament med;
		in >> med;
		Repo::add(med);
	}
}

void FileRepo::writeToFile() {
	std::ofstream out(this->filename, std::ios::trunc);

	if (!out.is_open()) {
		throw RepoException("Open error: " + this->filename + "\n");
	}

	for (const auto& masina : get_all()) {
		out << masina;
	}
}

void FileRepo::add(const Medicament& m) {
	Repo::add(m);
	this->writeToFile();
}

const Medicament FileRepo::delete_medicine(const Medicament& m) {
	const Medicament med = Repo::delete_medicine(m);
	this->writeToFile();
	return med;
}

const Medicament FileRepo::modify(const Medicament& m) {
	const Medicament med = Repo::modify(m);
	this->writeToFile();
	return med;
}