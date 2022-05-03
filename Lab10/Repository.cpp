#include "Repository.h"
#include <assert.h>
#include <algorithm>

const vector<Medicament>& Repo::get_all() {
	return this->MedicineList;
}

void Repo::add(const Medicament& m) {
	if (exist(m))
		throw RepoException("Medicamentul exista deja in lista!\n");
	else
		MedicineList.push_back(m);
}

const Medicament& Repo::find_medicine(string denumire, string producator) {
	for (const Medicament& m : MedicineList)
		if (m.get_denumire() == denumire && m.get_producator() == producator)
			return m;
	throw RepoException("Medicamentul cu denumirea " + denumire + " si producatorul " + producator + " nu exista in lista");
}

bool Repo::exist(const Medicament& m) {
	try {
		find_medicine(m.get_denumire(), m.get_producator());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

const Medicament Repo::delete_medicine(const Medicament& m) {
	Medicament med{ "", "", "", 1 };
	if (exist(m)) {
		for (int i = 0; i < MedicineList.size(); i++)
			if (MedicineList[i].get_denumire() == m.get_denumire() && MedicineList[i].get_producator() == m.get_producator()) {
				med = MedicineList[i];
				MedicineList.erase(MedicineList.begin() + i);
				break;
			}
	}
	else
		throw(RepoException("Medicamentul cu denumirea " + m.get_denumire() + " si producatorul " + m.get_producator() + " nu exista in lista\n"));
	return med;
	/*int found = 0;
	for (auto const& med : MedicineList) {
		if (med.get_denumire() == m.get_denumire() && med.get_producator() == m.get_producator()) {
			found = 1;
			MedicineList.stergeValoare(med);
			break;
		}
	}
	if(found == 0)
		throw(RepoException("Medicamentul cu denumirea " + m.get_denumire() + " si producatorul " + m.get_producator() + " nu exista in lista\n"));*/
}

const Medicament Repo::modify(const Medicament& m)
{
	Medicament med{ "","","",1 };
	bool flag = 0;
	if (exist(m))
		throw RepoException("Medicamentul exista deja in lista!\n");
	else {
		for (int i = 0; i < MedicineList.size(); i++)
			if (MedicineList[i].get_denumire() == m.get_denumire()) {
				med = MedicineList[i];
				MedicineList[i].set_producator(m.get_producator());
				MedicineList[i].set_substanta_activa(m.get_substanta_activa());
				MedicineList[i].set_pret(m.get_pret());
				flag = 1;
				break;
			}
	}
	if (flag == 0)
		throw RepoException("Medicamentul cu denumirea data nu exista in lista!\n");
	return med;

}

void test_repoExp()
{
	RepoException exp1{ "Exceptia1" };
	assert(exp1.get_errorMsg() == "Exceptia1");
	RepoException exp2{ "Exceptia2" };
	assert(exp2.get_errorMsg() == "Exceptia2");
}

void test_repo()
{
	Repo repo;
	Medicament m1{ "Paracetamol","Farmacisti","nuj",25 };
	Medicament m2{ "Ceva","Baieti","subs",456 };
	repo.add(m1);
	vector<Medicament> v = repo.get_all();
	assert(v.size() == 1);
	assert(v[0].get_denumire() == "Paracetamol");
	assert(v[0].get_producator() == "Farmacisti");
	assert(v[0].get_substanta_activa() == "nuj");
	assert(v[0].get_pret() == 25);
	repo.add(m2);
	v = repo.get_all();
	assert(v.size() == 2);
	Medicament m3{ "Paracetamol","Farmacisti","nuj",25 };
	try {
		repo.add(m1);
	}
	catch (RepoException) {

	}
	repo.delete_medicine(m3);
	v = repo.get_all();
	assert(v.size() == 1);
	assert(v[0].get_denumire() == "Ceva");
	assert(v[0].get_producator() == "Baieti");
	assert(v[0].get_substanta_activa() == "subs");
	assert(v[0].get_pret() == 456);
	Medicament m4{ "Ceva","Fete","subs2",45 };
	try {
		repo.delete_medicine(m4);
	}
	catch (RepoException) {

	}
	repo.modify(m4);
	v = repo.get_all();
	assert(v.size() == 1);
	assert(v[0].get_denumire() == "Ceva");
	assert(v[0].get_producator() == "Fete");
	assert(v[0].get_substanta_activa() == "subs2");
	assert(v[0].get_pret() == 45);
	try {
		repo.modify(m4);
	}
	catch (RepoException) {

	}
	try {
		repo.modify(m1);
	}
	catch (RepoException) {

	}
}