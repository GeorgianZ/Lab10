#include "GUI.h"

void GUI::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu melodii

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente

	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	edit_denumire = new QLineEdit;
	edit_producator = new QLineEdit;
	edit_subs = new QLineEdit;
	edit_pret = new QLineEdit;

	lyForm->addRow(denumire, edit_denumire);
	lyForm->addRow(producator, edit_producator);
	lyForm->addRow(subs_act, edit_subs);
	lyForm->addRow(pret, edit_pret);
	addMed = new QPushButton("Adauga medicament");
	lyForm->addWidget(addMed);

	//adaugam toate componentele legate de adaugare melodie
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);


	QWidget* formMod = new QWidget;
	QFormLayout* lyFormMod = new QFormLayout;
	formMod->setLayout(lyFormMod);
	edit_mod_den = new QLineEdit;
	edit_mod_prod = new QLineEdit;
	edit_mod_subs = new QLineEdit;
	edit_mod_pret = new QLineEdit;

	lyFormMod->addRow(mod_denumire, edit_mod_den);
	lyFormMod->addRow(mod_prod, edit_mod_prod);
	lyFormMod->addRow(mod_subs, edit_mod_subs);
	lyFormMod->addRow(mod_pret, edit_mod_pret);
	modMed = new QPushButton("Modifica medicament");
	lyFormMod->addWidget(modMed);

	lyLeft->addWidget(formMod);



	QWidget* formDel = new QWidget;
	QFormLayout* lyFormDel = new QFormLayout;
	formDel->setLayout(lyFormDel);
	edit_del_den = new QLineEdit;
	edit_del_prod = new QLineEdit;

	lyFormDel->addRow(del_denumire, edit_del_den);
	lyFormDel->addRow(del_prod, edit_del_prod);
	delMed = new QPushButton("Sterge medicament");
	lyFormDel->addWidget(delMed);

	lyLeft->addWidget(formDel);

	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)

	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupa artist+titlu 
	//si durata) + butonul de sortare

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->sortBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(sort_denumire);
	lyRadioBox->addWidget(sort_producator);
	lyRadioBox->addWidget(sort_subAndPrice);

	sort = new QPushButton("Sorteaza medicamente");
	lyRadioBox->addWidget(sort);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(sortBox);

	QVBoxLayout* lyRadioBox2 = new QVBoxLayout;
	this->filterBox->setLayout(lyRadioBox2);
	lyRadioBox2->addWidget(filter_pret);
	lyRadioBox2->addWidget(filter_subs); 
	edit_filt_pret = new QLineEdit;
	edit_filt_pret = new QLineEdit;

	//lyRadioBox2->addRow(filtru_pret, edit_filt_pret);
	//lyRadioBox2->addRow(filtru_subs, edit_filt_subs);

	filter = new QPushButton("FIltreaza medicamente");
	lyRadioBox2->addWidget(filter);

	lyLeft->addWidget(filterBox);

	// Buton folosit pentru a reincarca datele
		//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
		reload_data = new QPushButton("Reload data");
	lyLeft->addWidget(reload_data);

	undo = new QPushButton("Undo");
	lyLeft->addWidget(undo);


	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->medicamente = new QTableWidget{ noLines, noColumns };

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Denumire" << "Producator" << "Substanta activa" << "Pret";
	this->medicamente->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->medicamente->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


	lyRight->addWidget(medicamente);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}

void GUI::reloadMedicamente(vector<Medicament> medicamente) {
	this->medicamente->clearContents();
	this->medicamente->setRowCount(medicamente.size());

	int lineNumber = 0;
	for (auto& m : medicamente) {
		this->medicamente->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(m.get_denumire())));
		this->medicamente->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(m.get_producator())));
		this->medicamente->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(m.get_substanta_activa())));
		this->medicamente->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(m.get_pret())));
		lineNumber++;
	}
}

void GUI::connectSignalsSlots() {
	QObject::connect(addMed, &QPushButton::clicked, this, &GUI::guiAddMedicament);

	QObject::connect(modMed, &QPushButton::clicked, this, &GUI::guiModMedicament);

	QObject::connect(delMed, &QPushButton::clicked, this, &GUI::guiDelMedicament);

	QObject::connect(sort, &QPushButton::clicked, [&]() {
		if (this->sort_denumire->isChecked())
			this->reloadMedicamente(serv.sort_by_denumire());
		else if (this->sort_producator->isChecked())
			this->reloadMedicamente(serv.sort_by_producator());
		else if (this->sort_subAndPrice->isChecked())
			this->reloadMedicamente(serv.sort_by_subAndPrice());
		});

	QObject::connect(filter, &QPushButton::clicked, [&]() {
		//string filtru_subs = this->editFilterCriteria->text().toStdString();
		if (this->filter_pret->isChecked()) {
			try {
				this->reloadMedicamente(serv.filter_pret(50));
			}
			catch (RepoException& re) {
				QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
			}
		}
		else if (this->filter_subs->isChecked()) {
			
			try {
				this->reloadMedicamente(serv.filter_sub("ceva"));
			}
			catch (RepoException& re) {
				QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
			}
		}
		});

	QObject::connect(reload_data, &QPushButton::clicked, [&]() {
		this->reloadMedicamente(serv.get_all());
		});

	QObject::connect(undo, &QPushButton::clicked, [&]() {
		try {
			serv.undo();
		}
		catch (RepoException& re) {
			QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
		}
		this->reloadMedicamente(serv.get_all());
		});
		

}

void GUI::guiAddMedicament() {
	try {
		//preluare detalii din QLineEdit-uri
		string denumire = edit_denumire->text().toStdString();
		string producator = edit_producator->text().toStdString();
		string subs = edit_subs->text().toStdString();
		double pret = edit_pret->text().toDouble();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		edit_denumire->clear();
		edit_producator->clear();
		edit_subs->clear();
		edit_pret->clear();

		this->serv.adauga(denumire, producator, subs, pret);
		this->reloadMedicamente(this->serv.get_all());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_error()));
	}


}

void GUI::guiModMedicament() {
	try {
		//preluare detalii din QLineEdit-uri
		string mod_denumire = edit_mod_den->text().toStdString();
		string mod_prod = edit_mod_prod->text().toStdString();
		string mod_subs = edit_mod_subs->text().toStdString();
		double mod_pret = edit_mod_pret->text().toDouble();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		edit_mod_den->clear();
		edit_mod_prod->clear();
		edit_mod_subs->clear();
		edit_mod_pret->clear();

		this->serv.modifica(mod_denumire, mod_prod, mod_subs, mod_pret);
		this->reloadMedicamente(this->serv.get_all());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament modificat cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_error()));
	}


}

void GUI::guiDelMedicament() {
	try {
		//preluare detalii din QLineEdit-uri
		string del_denumire = edit_del_den->text().toStdString();
		string del_prod = edit_del_prod->text().toStdString();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		edit_del_den->clear();
		edit_del_prod->clear();

		this->serv.sterge(del_denumire, del_prod);
		this->reloadMedicamente(this->serv.get_all());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament sters cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_error()));
	}


}