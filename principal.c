#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

typedef struct {
	int dia;
	int mes;
    int ano; 
}date; 
struct ficha_de_conta{
	date data;
 	char descricao[100];  
	float valor;
};
struct ficha_de_conta receita;
struct ficha_de_conta despesa;  

void limpar();
void exibirMenu();
void buscarData();
void mostrarData();
void cadastrarReceita();
void cadastrarDispesa();

int main(){
	exibirMenu();
	return 0;
}

void exibirMenu(){
    FILE *fp;
	char opcao[10];
	int opc;
	
	limpar();
	printf("***************************\n");
	mostrarData();
	printf("***************************\n");	
	printf("************MENU***********\n");
  	printf("***************************\n");
  	printf("Insira a opcao desejada\n\n");
	printf("1 - Cadastrar nova Receita(Ganhos)\n");
	printf("2 - Cadastrar nova Despesa(Gastos)\n");
	printf("3 - Listagem de Registros\n");
    printf(">>>");

	gets(opcao);
	opc = atoi(opcao);
	limpar();
	switch(opc){
        case 1:
     		printf("1 - Cadastrar nova Receita(Ganhos)\n");
     		cadastrarReceita();
			fp = fopen ("arquivo.txt", "w");
			fprintf(fp,"=================================\n");
            fprintf(fp,"MOVIMENTECAO:Receita\n");            
            fprintf(fp,"Data :%d/%d/%d",receita.data.dia,receita.data.mes,receita.data.ano);
            fprintf(fp,"\t\tDESCRICAO: %s",receita.descricao);
            fprintf(fp,"\t\tVALOR: %.2f\n",receita.valor);	
			fclose(fp);
			break;
		case 2:
			printf("2 - Cadastrar nova Despesa(Gastos)\n");
			cadastrarDispesa();
			fp = fopen ("arquivo.txt", "w");
			fprintf(fp,"=================================\n");
            fprintf(fp,"MOVIMENTECAO:Despesa\n");            
            fprintf(fp,"Data :%d/%d/%d",despesa.data.dia,despesa.data.mes,despesa.data.ano);
            fprintf(fp,"\t\tDESCRICAO: %s",despesa.descricao);
            fprintf(fp,"\t\tVALOR: %.2f\n",despesa.valor);	
			fclose(fp);
			break;
		case 3:
			printf("3 - Listagem de Registros\n");
			fp = fopen("arquivo.txt", "r");
			int c;
            while (!feof(fp))
            {
                c = fgetc(fp);
                printf("%c",c);
            }
            fclose(fp);
            printf("%c\n",c);
            system("pause");
			break;
		default:
			printf("Opcao ivalida!\n");
			system("pause");
	}
	fflush(stdin);
	exibirMenu();
}

void limpar(){
	system("cls");
}
void buscarData(){
	time_t mytime;
	mytime = time(NULL);
	struct tm tm = *localtime(&mytime);
	
	receita.data.dia = tm.tm_mday;
	receita.data.mes = tm.tm_mon + 1;
	receita.data.ano = tm.tm_year + 1900;
	
}
void mostrarData(){
	buscarData();
	printf("Data: %d/%d/%d\n", receita.data.dia,receita.data.mes,receita.data.ano);
}
void cadastrarReceita(){
	printf("=========================\n");
	printf("===Cadastro de receita===\n");
	printf("=========================\n");
	printf("\n");
	printf("Digite a descricao:");
	scanf("%s",receita.descricao);
    // fgets(receita.descricao, sizeof(90), stdin);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f",&receita.valor);
}

void cadastrarDispesa(){
	printf("=========================\n");
	printf("===Cadastro de despesa===\n");
	printf("=========================\n");
	printf("\n");
	printf("Digite a descricao:");
	scanf("%s",despesa.descricao);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f",&despesa.valor);
	
	printf("%s\n",despesa.descricao);
	printf("%f\n",despesa.valor);
	system("pause");
}