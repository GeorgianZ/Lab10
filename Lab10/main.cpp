#include "Lab10.h"
#include "GUI.h"
#include <iostream>
#include <QtWidgets/QApplication>


void test_all();

int main(int argc, char *argv[])
{	
	QApplication a(argc, argv);
	FileRepo repo{ "fileRepo.txt" };
	Validate val;
	Service serv{ repo, val };
	//Console consola{ serv };
	GUI gui{ serv };
	test_all();
	//consola.run();
	gui.show();

    return a.exec();
}

void test_all()
{
	std::cout << "Start tests!\n";
	test_domain();
	test_repoExp();
	test_repo();
	test_add_service();
	test_sterge_service();
	test_modifica_service();
	test_find();
	test_filter_pret();
	test_filter_sub();
	test_sort();
	test_reteta();
	test_map();
	test_undo();
	cout << "Finish tests!\n";
}