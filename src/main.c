#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/display.h"
#include "../include/date_utils.h"
#include "../include/accounting.h"
#include "../include/system_utils.h"
#include "../include/file_utils.h"

#define  NOME_ARQUIVO "financial_movement.txt"
#define  MODE_FILE_A "a"
#define  MODE_FILE_READ "r"
#define  INVALID_OPTION "Opção inválida!"

AccountForm accountForm;

void accountant();
void readIncoming();
void readExpense();

void saveMovement(int movimento);

int main(){
	accountant();
	return EXIT_SUCCESS;
}

void accountant(){
	char choice[10];	
	int optionsChoice;
	
	pause();
	showOptions();
	fgets(choice, sizeof(choice), stdin);
	optionsChoice = atoi(choice);

	clean();

	if (isIncoming(optionsChoice)) {
		displayIncoming();
		readIncoming();
		saveMovement(optionsChoice);
	} else if (isExpense(optionsChoice)) {
		displayExpense();
		readExpense();
		saveMovement(optionsChoice);
	} else if (isSeeListMovements(optionsChoice)) {
		FILE *file = openFile(NOME_ARQUIVO, MODE_FILE_READ);
		
		displayMovement();
		printFileContent(file);
		
		fclose(file);

		pause();
	} else if (isExit(optionsChoice)) {
		saveMovement(optionsChoice);
	} else {
		clean();
		
		printf(INVALID_OPTION);
		line();
		pause();
	}

	fflush(stdin);
	accountant();
}

void readIncoming() {
	printf("Digite a descrição:");
	scanf("%s", accountForm.description);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f", &accountForm.value);
}

void readExpense() {
	printf("Digite a descrição:");
	scanf("%s", accountForm.description);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f", &accountForm.value);
}

void saveMovement(int movimento) {
	static float revenue = 0;
	static float expenses = 0;
	static float total = 0;
	
	FILE *fp = openFile(NOME_ARQUIVO, MODE_FILE_A);

	if(isIncoming(movimento)){
		char *line = cseparetor(33);	
		
		fprintf(fp,"%s\n", line);
		fprintf(fp,"MOVIMENTECAO: Receita\n");       
		free(line);

		// DESCRIÇÃO DO MOVIMENTO
		fprintf(fp, "Data : %s", dateNow());
		fprintf(fp, "\t\tDESCRICAO: %s", accountForm.description);
		fprintf(fp, "\t\tVALOR: %.2f\n", accountForm.value);

		// CALCULA O TOTAL
		// Salvar no arquivo	
		revenue += accountForm.value; 
		total = revenue - expenses;
		fprintf(fp, "TOTAL RECEITA:%.2f",revenue);	
		fprintf(fp, "\tTOTAL DESPESA:%.2f",expenses);	
		fprintf(fp, "\tTOTAL:%.2f\n",total);	
	}
	else if (isExpense(movimento)){
		char *separetor = cseparetor(33);	

		fprintf(fp, "%s\n", separetor);
		fprintf(fp,"MOVIMENTECAO: Despesa\n");
		free(separetor);

		// DESCRIÇÃO DO MOVIMENTO
		fprintf(fp, "Data : %s", dateNow());
		fprintf(fp, "\t\tDESCRICAO: %s", accountForm.description);
		fprintf(fp, "\t\tVALOR: %.2f\n", accountForm.value);

		// CALCULA O TOTAL
		// Salvar no arquivo	
		expenses += accountForm.value;
		total = revenue - expenses;
		fprintf(fp, "TOTAL RECEITA:%.2f",revenue);	
		fprintf(fp, "\tTOTAL DESPESA:%.2f",expenses);	
		fprintf(fp, "\tTOTAL:%.2f\n",total);	
	}else if (isExit(movimento)){	
		char *separetor = cseparetor(33);

		total = revenue - expenses;
		fprintf(fp, "%s\n", separetor);
		fprintf(fp, "TOTAL: %.2f\n", total);	
		fprintf(fp, "%s\n", separetor);
		free(separetor);

		fclose(fp);
		exit(EXIT_SUCCESS);
	}

	fclose(fp);	
}
