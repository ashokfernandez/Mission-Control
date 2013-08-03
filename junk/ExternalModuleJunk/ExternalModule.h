// External Module

typedef struct _ExternPackage{
	void (*init)(void);	
	void (*run)(void);
} ExternPackage;

ExternPackage *NewPackage(void);

//void EXinit(void);

//void EXrun(void);





