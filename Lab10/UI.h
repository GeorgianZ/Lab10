#pragma once
#include "Service.h"

class Console {
private:
	Service& serv;
public:
	Console(Service& serv) : serv{ serv } {};
	/*
	* Stergem constructorul de copiere
	*/
	Console(const Console& ot) = delete;
	void printMenu();
	void print();
	void ui_add();
	void ui_delete();
	void ui_modify();
	void ui_find();
	void ui_filter();
	void ui_sort();
	void run();
	void ui_reteta();
	void printRetetaMenu();
	void reteta_add();
	void reteta_add_rand();
	void reteta_sterge();
	void reteta_export();
	void ui_undo();
};
