#pragma once
#include "Observer.h"
#include "Medicament.h"
#include "Reteta.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 256

class CosReadOnlyGUI : public QWidget, public Observer {
private:
	Reteta& cos;

public:
	CosReadOnlyGUI(Reteta& cos);

	void update() override;

	void paintEvent(QPaintEvent* event) override;

	~CosReadOnlyGUI() {
		//this->cos.removeObserver(this);
	}
};


