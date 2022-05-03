#pragma once
#include "Medicament.h"
#include <string>
using std::string;

class ValidationException {
private:
	string error;
public:
	ValidationException() = delete;
	ValidationException(string error) : error{ error } {};
	string get_error() const {
		return this->error;
	}
};

class Validate {
public:
	string valideaza(const Medicament& m);
};

