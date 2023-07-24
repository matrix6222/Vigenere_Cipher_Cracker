#include "klasy.hpp"



int main(const int argc, const char* argv[]) {
	Parametry* param = new Parametry(argc, argv);
	if (!param->error) {
		Szyfry* szyfr = nullptr;
		if      (param->t == 1) {
			szyfr = new Vigenere(param);
		}
		else if (param->t == 2) {
			szyfr = new Cezar(param);
		}
		else if (param->t == 3) {
			szyfr = new Bacon(param);
		}
		if      (param->a == 1) {
			std::string cache = szyfr->decrypt();
			if (!szyfr->error) {
				std::cout << cache << std::endl;
				if (param->o != "") {
					std::ofstream file;
					file.open(param->o);
					file << cache;
					file.close();
				}
			}
			else {
				std::cout << "blad" << std::endl;
			}
		}
		else if (param->a == 2) {
			std::string cache = szyfr->encrypt();
			if (!szyfr->error) {
				std::cout << cache << std::endl;
				if (param->o != "") {
					std::ofstream file;
					file.open(param->o);
					file << cache;
					file.close();
				}
			}
			else {
				std::cout << "blad" << std::endl;
			}
		}
		else if (param->a == 3) {
			Crack* crack = new Crack(szyfr);
			crack->crackWithoutKey();
			delete crack;
		}
		delete param;
		delete szyfr;
		return 0;
	}
	else {
		delete param;
		return 0;
	}
}