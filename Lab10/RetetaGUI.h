#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <vector>
#include <qpushbutton.h>
#include <qaction.h>
#include <qlayout.h>
#include <QPainter>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include "Medicament.h"
#include "Service.h"

//
//#include <fstream>
//
//ofstream f("file1.cvs");

using std::vector;

class ServiceGUI2Draw : public QWidget, public Observer {
private:
	Reteta& wishlist;
protected:
	void paintEvent(QPaintEvent*) override {
		int x = 10, y = 10, w = 10;
		QPainter p{ this };
		p.setPen(Qt::blue);
		for (const auto t : wishlist.getReteta()) {
			p.drawRect(x, y, w, t.get_pret());
			x += 50;
		}
	}
public:
	ServiceGUI2Draw(Reteta& wishlist) :wishlist{ wishlist } {
		wishlist.addObserver(this);
		update();
	}
	void update() override {
		repaint();
	}
	~ServiceGUI2Draw() {
		wishlist.removeObserver(this);
	}
};

class RetetaGUI : public QWidget, public Observer
{
private:
    Service& service;

    void populateList(QListWidget* list, const vector<Medicament>& med);
    void initRetetaComponents();
    void connectRetetaSignalSlots();
	

	QPushButton* btnDrawWindow;
    QListWidget* RetetaList;
    QLabel* denumire;
    QLabel* producator;
    QLineEdit* denumireLine;
    QPushButton* addButton;
    QLineEdit* producatorLine;
    QLineEdit* randomLine;
    QPushButton* randomButton;
    QLineEdit* exportLine;
    QPushButton* exportButton;
    QPushButton* golesteButton;

public:
    RetetaGUI(Service& service);
	void update() override {
		populateList(RetetaList, service.getReteta());
	}
};


