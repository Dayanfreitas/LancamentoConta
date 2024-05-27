
#include<stdlib.h>
#include "accounting.h"

#define OP_INCOMING 1
#define OP_EXPENSE 2
#define OP_SEE_LIST 3

int isIncoming(int opc) {
	return opc == OP_INCOMING;
}

int isExpense(int opc) {
	return opc == OP_EXPENSE;
}

int isSeeListMovements(int opc) {
	return opc == OP_SEE_LIST;
}

int isExit(int opc) {
	return opc == EXIT_SUCCESS;
}
