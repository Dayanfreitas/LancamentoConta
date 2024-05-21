#include <stdio.h>
#include "../include/display.h"

#define INCOMING "+"
#define EXPENSE "-"

void line() {
  printf("\n");
}

void lines(int n) {
  for (int i = 0; i < n; i++) {
    line();
  }
}

void separetor(char c, int n) {
  for (int i = 0; i < n; i++) {
    printf("%c", c);
  }
}

char* cseparetor(int n) {
	// Aloca memória para a string com n caracteres mais o terminador nulo
	char *string = malloc((n + 1) * sizeof(char));
	if (string == NULL) {
		return NULL; // Se a alocação falhar, retorna NULL
	}

	// Preenche a string com o caractere '='
	for (int i = 0; i < n; i++) {
		string[i] = '=';
	}

	// Adiciona o terminador nulo no final da string
	string[n] = '\0';

	return string;
}

void showOptions() {
  header();

  printf("Insira a opção desejada");
  lines(2);
	printf("1 - Cadastrar nova Receita(Ganhos)\n");
	printf("2 - Cadastrar nova Despesa(Gastos)\n");
	printf("3 - Listagem de Registros\n");
	printf("0 - Sair e Salvar\n");
	printf(">>>");
}

void header() {
  separetor('*', 27);
  line();
  separetor('*', 27);
  line();
	printf("************MENU***********");
  line();
  separetor('*', 27);
  line();
}

void displayIncoming() {
	printf("1 - Cadastrar nova Receita (%s)", INCOMING);
  line();
	
  printf("=============================");
  line();
  printf("===Cadastro de receita(%s)===", INCOMING);
  line();
	printf("=============================");

  lines(2);
}

void displayExpense() {
	printf("2 - Cadastrar nova Despesa(%s)", EXPENSE);
  line();

	printf("=============================");
  line();
	printf("===Cadastro de despesa(%s)===", EXPENSE);
  line();
	printf("=============================");
  lines(2);
}

void displayMovement() {
	printf("3 - Listagem de Registros");
  line();
}
