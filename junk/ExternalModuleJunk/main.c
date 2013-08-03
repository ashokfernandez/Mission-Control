#include "ExternalModule.h"

int main(void){
	ExternPackage *ThisPackage;
	ThisPackage = NewPackage();

	ThisPackage->init();
	ThisPackage->run();
	return 1;

}
