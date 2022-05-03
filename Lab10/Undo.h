#pragma once
#include "Repository.h"

class Undo {
private:
	vector<Undo> undoActions;
public:
	Undo() = default;
	virtual void doUndo() = 0;
	virtual ~Undo() {};
};

class UndoAdauga : public Undo {
	Medicament m;
	Repo& rep;
public:
	UndoAdauga(const Medicament& m, Repo& rep) : m{ m }, rep{ rep }{};
	void doUndo() override {
		rep.delete_medicine(m);
	}
};

class UndoSterge : public Undo {
	Medicament m;
	Repo& rep;
public:
	UndoSterge(const Medicament& m, Repo& rep) : m{ m }, rep{ rep }{};
	void doUndo() override {
		rep.add(m);
	}
};

class UndoModifica : public Undo {
	Medicament m;
	Repo& rep;
public:
	UndoModifica(const Medicament& m, Repo& rep) :m{ m }, rep{ rep }{};
	void doUndo() override {
		rep.modify(m);
	}
};
