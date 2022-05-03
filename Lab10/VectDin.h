#pragma once
#include <string>
#include "Medicament.h"

using namespace std;
template <typename T>
struct Nod {
	T med;
	Nod* urm;
	Nod(T v) :med{ v }, urm{ nullptr }{};
	Nod(T v, Nod* urm) :med{ v }, urm{ urm }{};
};
template <typename T>
class MyListIterator;
template <typename T>
class MyList {
	Nod<T>* cap;

	//deameda toate nodurile
	void elibereazaNoduri() noexcept;

	//face o copie a listei,parcurgand lista si creand noduri in care copiaza medatarii
	Nod<T>* copiaza(Nod<T>* curent);

public:
	MyList()noexcept :cap{ nullptr } {};

	//constructor de copiere
	MyList(const MyList& ot);

	//operator de assignment
	void operator=(const MyList& ot);

	//destructor
	~MyList();

	//returneaza nr de elem
	size_t size()const noexcept;

	//adauga la inceput
	void addInceput(T v);

	//adauga la sfarsit
	void push_back(T v);

	//Returneaza primul element
	T& first()const noexcept;

	//returneaza iterator pozitionat pe primul element
	MyListIterator<T> begin()const noexcept;

	//returneaza iterator cu nodul nullptr(dupa ultimul element)
	MyListIterator<T> end()const noexcept;

	//obtine elementul de pe pozitia poz
	T& operator[](int poz) noexcept;


	//sterge un element de dupa un nod dat
	void stergeNod(Nod<T>* predecesor)noexcept;

	//sterge medatarul dat
	void stergeValoare(T med);
};
template <typename T>
//iteratorul pt lista
class MyListIterator {
	//pozitia curenta-nullptr daca am ajuns la sf listei
	Nod<T>* curent;

public:
	MyListIterator(Nod<T>* curent) noexcept :curent{ curent } {}

	//operator !=
	bool operator!=(const MyListIterator& ot) noexcept;

	//operator ++ pt a trece la urmatorul element din lista
	void operator++() noexcept;

	//operator * pentru a returna elementul curent(medoarea)
	T& operator*() noexcept;


};

template <typename T>
//lista inlantuita
MyList<T>::MyList(const MyList& ot) {
	//copiez din ot in obiectul curent
	cap = copiaza(ot.cap);
}
template <typename T>
void MyList<T>::operator=(const MyList& ot) {
	elibereazaNoduri();
	cap = copiaza(ot.cap);
}
template <typename T>
MyList<T>::~MyList() {
	elibereazaNoduri();
}
template <typename T>
Nod<T>* MyList<T>::copiaza(Nod<T>* curent) {
	if (curent == nullptr)
		return nullptr;

	auto nod = new Nod<T>{ curent->med };
	nod->urm = copiaza(curent->urm);
	return nod;
}
template <typename T>
void MyList<T>::addInceput(T v) {
	Nod<T>* n = new Nod<T>{ v,cap };
	cap = n;
}
template <typename T>
void MyList<T>::push_back(T v) {
	auto nodCurent = cap;
	while (nodCurent != nullptr && nodCurent->urm != nullptr) {
		nodCurent = nodCurent->urm;
	}
	if (nodCurent == nullptr) {
		cap = new Nod<T>{ v,nullptr };
	}
	else {
		nodCurent->urm = new Nod<T>{ v,nullptr };
	}

}
template <typename T>
size_t MyList<T>::size()const noexcept {
	auto nodCurent = cap;
	size_t lg = 0;
	while (nodCurent != nullptr) {
		lg++;
		nodCurent = nodCurent->urm;
	}
	return lg;
}
template <typename T>
T& MyList<T>::operator[](int poz) noexcept {
	auto nodCurent = cap;
	int lg = 0;
	while (lg < poz) {
		lg++;
		nodCurent = nodCurent->urm;
	}
	return nodCurent->med;
}
template <typename T>
T& MyList<T>::first()const noexcept {
	return cap->med;
}
template <typename T>
void MyList<T>::elibereazaNoduri() noexcept {
	auto nodCurent = cap;
	while (nodCurent != nullptr) {
		auto aux = nodCurent->urm;
		delete nodCurent;
		nodCurent = aux;
	}
	cap = nullptr;
}


template <typename T>
void MyList<T>::stergeNod(Nod<T>* predecesor) noexcept {
	auto* deSters = predecesor->urm;
	predecesor->urm = predecesor->urm->urm;
	delete deSters;
}

template <typename T>
void MyList<T>::stergeValoare(T c) {
	//if (cap == nullptr)
		//return;
	//sterg de pe prima pozitie
	if (cap->med == c) {
		auto* deSters = cap;
		cap = cap->urm;
		delete deSters;
		return;
	}
	//parcurg pana ajung la predecesorul nodului cautat
	auto* elem = cap;
	while (elem->urm != nullptr && elem->urm->med != c) {
		elem = elem->urm;
	}
	if (elem->urm != nullptr)
		stergeNod(elem);
}

template <typename T>
MyListIterator<T> MyList<T>::begin() const noexcept {
	return MyListIterator<T>{ cap };
}
template <typename T>
MyListIterator<T> MyList<T>::end()const noexcept {
	return MyListIterator<T>{ nullptr };

}


//iterator
template <typename T>
bool MyListIterator<T>::operator!=(const MyListIterator& ot) noexcept {
	return curent != ot.curent;
}
template <typename T>
void MyListIterator<T>::operator++() noexcept {
	curent = curent->urm;
}
template <typename T>
T& MyListIterator<T>::operator*() noexcept {
	return curent->med;
}