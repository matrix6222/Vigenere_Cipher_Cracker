#ifndef KLASY_HPP
#define KLASY_HPP
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <fstream>


template<class A, class B, class C> class MyMap {
private:
	struct element {
		A first;
		B second;
		C third;
		element* next;
	};
	int len = 0;
	element* tab = new element;
	int maxLen;
	void wsadzElement(A val1, B val2, C val3) {
		element* ptab = this->tab;
		if (this->len == 0) {
			ptab->first = val1;
			ptab->second = val2;
			ptab->third = val3;
			this->len++;
		}
		else {
			element* potab = ptab;
			for (int x = 0; x < this->len; x++) {
				if (ptab->first > val1) {
					if (x == 0) {
						element* pntab = new element;
						pntab->first = val1;
						pntab->second = val2;
						pntab->third = val3;
						pntab->next = this->tab;
						this->tab = pntab;
						this->len++;
						return;
					}
					else {
						potab->next = new element;
						potab->next->first = val1;
						potab->next->second = val2;
						potab->next->third = val3;
						potab->next->next = ptab;
						this->len++;
						return;
					}
					break;
				}
				potab = ptab;
				ptab = ptab->next;
			}
			potab->next = new element;
			potab->next->first = val1;
			potab->next->second = val2;
			potab->next->third = val3;
			this->len++;
		}
		return;
	}
	void usunPierwszyElement() {
		element* ptab = this->tab->next;
		delete this->tab;
		this->tab = ptab;
		this->len--;
	}
public:
	~MyMap() {
		element* ptab = this->tab;
		element* pntab = ptab->next;
		for (int x = 0; x < this->len - 1; x++) {
			delete ptab;
			ptab = pntab;
			pntab = ptab->next;
		}
		delete ptab;
	}
	MyMap(int maxLen) {
		this->maxLen = maxLen;
	}
	void insert(A val1, B val2, C val3) {
		this->wsadzElement(val1, val2, val3);
		if (this->len > this->maxLen) {
			this->usunPierwszyElement();
		}
	}
	friend std::ostream& operator<<(std::ostream& stream, const MyMap& obj) {
		element* ptab = obj.tab;
		for (int x = 0; x < obj.len; x++) {
			stream << "pewnosc: " << round(ptab->first * 100) << "%, klucz: " << ptab->second << ", tekst jawny: " << ptab->third << std::endl;
			ptab = ptab->next;
		}
		return stream;
	}
};



class NeuralNet {
private:
	double relu(double x);
	double sigmoid(double x);
public:
	double forward(std::string word);
};



class Parametry {
private:
	bool flags[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	bool czy_dozwolony_znak(const char& znak);
	bool czy_dozwolone_znaki(const std::string& text);
	bool czy_zawiera_spacje(const std::string& text);
	bool czy_klucz_zawiera_spacje();
	bool czy_szyfrogram_becon_jest_poprawny();
	bool zgodnosc();
public:
	const std::string charset = "abcdefghijklmnopqrstuvwxyz ";
	unsigned long s = 0;
	unsigned long e = 0;
	bool u = 0;
	int v = 1;
	int t = 0;
	int a = 0;
	std::string d;
	std::string k;
	std::string o;
	bool error = 0;
	Parametry(const int& argc, const char* argv[]);
	void print_help();
};



class Szyfry {
protected:
	int char_to_int(const char& x);
	char int_to_char(const int& x);
	std::string char_to_code(const char& x, const std::string& key_ab);
	char code_to_char(const std::string& code, const std::string& key_ab);
public:
	bool error = 0;
	Parametry* config;
	virtual std::string encrypt();
	virtual std::string decrypt();
};



class Vigenere : public Szyfry {
public:
	Vigenere(Parametry* config);
	std::string encrypt();
	std::string decrypt();
};



class Cezar : public Szyfry {
public:
	Cezar(Parametry* config);
	std::string encrypt();
	std::string decrypt();
};



class Bacon : public Szyfry {
public:
	Bacon(Parametry* config);
	std::string encrypt();
	std::string decrypt();
};



class Crack {
private:
	Szyfry* cipher;
	std::string keygen(const long& x);
	std::vector<std::string> split(std::string& co, char& c);
public:
	Crack(Szyfry* cipher);
	void crackWithoutKey();
};



#endif