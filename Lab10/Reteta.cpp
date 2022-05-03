#include "Reteta.h"
#include <algorithm>
#include <random>
using std::shuffle;

void Reteta::adaugaMedicament(const Medicament& m) {
	reteta.push_back(m);
}

void Reteta::adaugaRandom(vector<Medicament> lista, int number) {
	shuffle(lista.begin(), lista.end(), std::default_random_engine(std::random_device{}()));
	while (reteta.size() < number && lista.size() > 0) {
		reteta.push_back(lista.back());
		lista.pop_back();
	}
}

void Reteta::deleteReteta() {
	if (reteta.size() > 0)
		reteta.clear();
}

vector<Medicament> Reteta::getReteta() {
	return this->reteta;
}