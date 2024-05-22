
#ifndef ACCOUNTING_H
#define ACCOUNTING_H

struct accountForm {
 	char description[100];  
	float value;
};

typedef struct accountForm AccountForm;

int isIncoming(int opc);
int isExpense(int opc);
int isSeeListMovements(int opc);

int isExit(int opc);

#endif