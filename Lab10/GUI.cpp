#include "GUI.h"

void GUI::initializeGUIComponents() {

	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unui medicament
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

	//adaugam toate componentele legate de adaugare medicamentului
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);


	QWidget* formMod = new QWidget;
	QFormLayout* lyFormMod = new QFormLayout;
	formMod->setLayout(lyFormMod);
	modMed = new QPushButton("Modifica medicament");
	lyFormMod->addWidget(modMed);

	lyLeft->addWidget(formMod);



	QWidget* formDel = new QWidget;
	QFormLayout* lyFormDel = new QFormLayout;
	formDel->setLayout(lyFormDel);
	
	delMed = new QPushButton("Sterge medicament");
	lyFormDel->addWidget(delMed);

	lyLeft->addWidget(formDel);

	

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

	filter = new QPushButton("FIltreaza medicamente");
	lyRadioBox2->addWidget(filter);

	lyLeft->addWidget(filterBox);

	QWidget* formReteta = new QWidget;
	QFormLayout* lyFormReteta = new QFormLayout;
	formReteta->setLayout(lyFormReteta);
	reteta = new QPushButton("Reteta");
	lyFormReteta->addWidget(reteta);

	//lyLeft->addWidget(formReteta);

	// Buton folosit pentru a reincarca datele
		//i.e. afisam toate medicamentele in tabel, in ordinea initiala din fisier
		reload_data = new QPushButton("Reload data");
	lyLeft->addWidget(reload_data);

	undo = new QPushButton("Undo");
	lyLeft->addWidget(undo);


	
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
				guifilter_pret();
			}
			catch (RepoException& re) {
				QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
			}
		}
		else if (this->filter_subs->isChecked()) {
			
			try {
				guifilter_subs();
			}
			catch (RepoException& re) {
				QMessageBox::information(this, "Info", QString::fromStdString(re.get_errorMsg()));
			}
		}
		});

	QObject::connect(reteta, &QPushButton::clicked, this, &GUI::guiReteta);
		
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
	QWidget* modificaWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* denLabel = new QLabel("Denumire: ");
	QLineEdit* denLine = new QLineEdit;
	formLayout->addRow(denLabel, denLine);

	QLabel* producatorLabel = new QLabel("Producator: ");
	QLineEdit* producatorLine = new QLineEdit;
	formLayout->addRow(producatorLabel, producatorLine);

	QLabel* subsLabel = new QLabel("Substanta activa: ");
	QLineEdit* subsLine = new QLineEdit;
	formLayout->addRow(subsLabel, subsLine);

	QLabel* pretLabel = new QLabel("Pret: ");
	QLineEdit* pretLine = new QLineEdit;
	formLayout->addRow(pretLabel, pretLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* modifica = new QPushButton("&Modifica");
	QObject::connect(modifica, &QPushButton::clicked, [=]() {
		try {
			this->serv.modifica(denLine->text().toStdString(), producatorLine->text().toStdString(), subsLine->text().toStdString(), pretLine->text().toDouble());
			this->reloadMedicamente(this->serv.get_all());
			modificaWindow->close();
		}
		catch (const ValidationException& ve) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare validare");
			msgBox.setText(QString::fromUtf8(ve.get_error()));
			msgBox.exec();
			modificaWindow->close();
		}
		catch (const RepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
			msgBox.exec();
			modificaWindow->close();
		}
		});
	vLayout->addWidget(modifica);

	modificaWindow->setLayout(vLayout);
	modificaWindow->show();


}

void GUI::guiDelMedicament() {
	QWidget* modificaWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* denLabel = new QLabel("Denumire: ");
	QLineEdit* denLine = new QLineEdit;
	formLayout->addRow(denLabel, denLine);

	QLabel* producatorLabel = new QLabel("Producator: ");
	QLineEdit* producatorLine = new QLineEdit;
	formLayout->addRow(producatorLabel, producatorLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* sterge = new QPushButton("&Modifica");
	QObject::connect(sterge, &QPushButton::clicked, [=]() {
		try {
			this->serv.sterge(denLine->text().toStdString(), producatorLine->text().toStdString());
			this->reloadMedicamente(this->serv.get_all());
			modificaWindow->close();
		}
		catch (const ValidationException& ve) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare validare");
			msgBox.setText(QString::fromUtf8(ve.get_error()));
			msgBox.exec();
			modificaWindow->close();
		}
		catch (const RepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
			msgBox.exec();
			modificaWindow->close();
		}
		});
	vLayout->addWidget(sterge);

	modificaWindow->setLayout(vLayout);
	modificaWindow->show();


}

void GUI::guifilter_pret() {
	QWidget* pretWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* pretLabel = new QLabel("Pret: ");
	QLineEdit* pretLine = new QLineEdit;
	formLayout->addRow(pretLabel, pretLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* filt_pret = new QPushButton("&Filtreaza");
	QObject::connect(filt_pret, &QPushButton::clicked, [=]() {
		try {
			this->serv.filter_pret(pretLine->text().toDouble());
			this->reloadMedicamente(this->serv.filter_pret(pretLine->text().toDouble()));
			pretWindow->close();
		}
		catch (const ValidationException& ve) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare validare");
			msgBox.setText(QString::fromUtf8(ve.get_error()));
			msgBox.exec();
			pretWindow->close();
		}
		catch (const RepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
			msgBox.exec();
			pretWindow->close();
		}
		});
	vLayout->addWidget(filt_pret);

	pretWindow->setLayout(vLayout);
	pretWindow->show();


}

void GUI::guifilter_subs() {
	QWidget* pretWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* pretLabel = new QLabel("Substanta activa: ");
	QLineEdit* pretLine = new QLineEdit;
	formLayout->addRow(pretLabel, pretLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* filt_pret = new QPushButton("&Filtreaza");
	QObject::connect(filt_pret, &QPushButton::clicked, [=]() {
		try {
			this->serv.filter_sub(pretLine->text().toStdString());
			this->reloadMedicamente(this->serv.filter_sub(pretLine->text().toStdString()));
			pretWindow->close();
		}
		catch (const ValidationException& ve) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare validare");
			msgBox.setText(QString::fromUtf8(ve.get_error()));
			msgBox.exec();
			pretWindow->close();
		}
		catch (const RepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.get_errorMsg()));
			msgBox.exec();
			pretWindow->close();
		}
		});
	vLayout->addWidget(filt_pret);

	pretWindow->setLayout(vLayout);
	pretWindow->show();


}

void GUI::guiReteta() {
	QWidget* RetetaMain = new QWidget;

	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	QWidget* addForm = new QWidget;
	QFormLayout* lyAdd = new QFormLayout;
	addForm->setLayout(lyAdd);

	QLabel* den = new QLabel ("Denumire ");
	QLabel* prod = new QLabel("Producator ");

	QLineEdit* edit_den = new QLineEdit;
	QLineEdit* edit_prod = new QLineEdit;

	lyAdd->addRow(den, edit_den);
	lyAdd->addRow(prod, edit_prod);

	QPushButton* add = new QPushButton("Adauga la reteta");
	lyAdd->addWidget(add);

	lyLeft->addWidget(addForm);

	//RetetaMain->addWidget(left);
}