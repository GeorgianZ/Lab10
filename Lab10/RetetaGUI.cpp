#include "RetetaGUI.h"

RetetaGUI::RetetaGUI(Service& service) : service{ service } {

	this->initRetetaComponents();
	this->connectRetetaSignalSlots();
	this->populateList(RetetaList, service.getReteta());
}

void RetetaGUI::populateList(QListWidget* list, const vector<Medicament>& med) {
	list->clear();

	for (const auto& m : med) {
		std::stringstream stream;
		stream << m;
		new QListWidgetItem(QString::fromUtf8(stream.str().substr(0, stream.str().length() - 1)), list);
	}
}

void RetetaGUI::initRetetaComponents() {
	QHBoxLayout* retetaLayout = new QHBoxLayout;
	RetetaList = new QListWidget;
	retetaLayout->addWidget(RetetaList);

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	denumireLine = new QLineEdit;
	producatorLine = new QLineEdit;
	addButton = new QPushButton("Adauga");
	formLayout->addRow(denumireLine, addButton);

	randomLine = new QLineEdit;
	randomButton = new QPushButton("Random");
	formLayout->addRow(randomLine, randomButton);

	exportLine = new QLineEdit;
	exportButton = new QPushButton("Export");
	formLayout->addRow(exportLine, exportButton);

	golesteButton = new QPushButton("Goleste");
	formLayout->addRow(golesteButton);

	btnDrawWindow = new QPushButton{ "Draw window." };
	btnDrawWindow->setStyleSheet("background-color: pink");
	retetaLayout->addWidget(btnDrawWindow);

	formWidget->setLayout(formLayout);
	retetaLayout->addWidget(formWidget);

	this->setLayout(retetaLayout);
}

void RetetaGUI::connectRetetaSignalSlots() {
	service.getList().addObserver(this);
	QObject::connect(addButton, &QPushButton::clicked, [this]() {
		try {
			this->service.addToReteta(denumireLine->text().toStdString(), "");
			denumireLine->clear();
			auto m = this->service.getReteta();
			this->populateList(RetetaList, m);
		}
		catch (const RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
		}
		});
	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new ServiceGUI2Draw{ service.getList() };
		drawWindow->show();
		});

	QObject::connect(randomButton, &QPushButton::clicked, [this]() {
		try {
			this->service.addRandom(randomLine->text().toInt());
			randomLine->clear(); 
			auto m = this->service.getReteta();
			this->populateList(RetetaList, m);
		}
		catch (const RepoException& re) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_errorMsg()));
		}
		});

	/*QObject::connect(exportButton, &QPushButton::clicked, [this]() {
		if (service.getReteta().size() == 0)
			f << "Reteta este goala!\n";
		else
			for (auto x : service.getReteta())
				f << "Denumire " << x.get_denumire() << " | Producator " << x.get_producator() << " | Substanta activa " << x.get_substanta_activa() << " | Pret " << x.get_pret() << "\n";
		});*/
	QObject::connect(golesteButton, &QPushButton::clicked, [this]() {
		this->populateList(RetetaList, vector<Medicament>());
		});
}
