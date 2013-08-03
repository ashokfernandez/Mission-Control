// External Module
#include <stdio.h>
#include "ExternalModule.h"

void EXinit(void){
	printf("INIT\n");
}

void EXrun(void){
	printf("RUN\n");
}

static ExternPackage ThisPackage = {
	.init = &EXinit,
	.run = &EXrun,
};

ExternPackage *NewPackage(void){
	return &ThisPackage;
}


