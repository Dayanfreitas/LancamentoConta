#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  NOME_ARQUIVO "Movimentacao.txt"
#define  MODO_ARQUIVO "a"

// Definição de uma macro para limpar a tela, dependendo do sistema operacional
#ifdef _WIN32
	#define CLEAR_SCREEN "cls"
#else
	#define CLEAR_SCREEN "clear"
#endif


typedef struct {
	int dia;
	int mes;
	int ano; 
} date; 

struct ficha_de_conta{
	date data;
 	char descricao[100];  
	float valor;
};

struct ficha_de_conta lancamento;



void cleanScreen();
void exibirMenu();
void buscarData();
void mostrarData();
void cadastrarReceita();
void cadastrarDispesa();
void salvarMovimento(int movimento,FILE *fp);

int main(){
	exibirMenu();
	return 0;
}

void exibirMenu(){
	FILE *fp;
	char choice[10];	
	int opc;

	cleanScreen();
	printf("***************************\n");
	mostrarData();
	printf("***************************\n");	
	printf("************MENU***********\n");
	printf("***************************\n");
	printf("Insira a opcao desejada\n\n");
	printf("1 - Cadastrar nova Receita(Ganhos)\n");
	printf("2 - Cadastrar nova Despesa(Gastos)\n");
	printf("3 - Listagem de Registros\n");
	printf("0 - Sair e Salvar\n");
	printf(">>>");

	fgets(choice, sizeof(choice), stdin);
	opc = atoi(choice);
	printf("Opcao: %d\n", atoi(choice));

	cleanScreen();
	switch(opc){
        case 1:
     		printf("1 - Cadastrar nova Receita(Ganhos)\n");
     		cadastrarReceita();
			salvarMovimento(opc, fp);
			break;
		case 2:
			printf("2 - Cadastrar nova Despesa(Gastos)\n");
			cadastrarDispesa();
			salvarMovimento(opc, fp);
			break;
		case 3:
			printf("3 - Listagem de Registros\n");
			fp = fopen(NOME_ARQUIVO, "r");
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
		case 0:
			salvarMovimento(opc,fp);
		default:
			printf("Opcao ivalida!\n");
			system("pause");
	}
	fflush(stdin);
	exibirMenu();
}

void cleanScreen(){
	system(CLEAR_SCREEN);
}

void buscarData(){
	time_t mytime;
	mytime = time(NULL);
	struct tm tm = *localtime(&mytime);
	
	lancamento.data.dia = tm.tm_mday;
	lancamento.data.mes = tm.tm_mon + 1;
	lancamento.data.ano = tm.tm_year + 1900;
	
}
void mostrarData(){
	buscarData();
	printf("Data: %d/%d/%d\n", lancamento.data.dia,lancamento.data.mes,lancamento.data.ano);
}
void cadastrarReceita(){
	printf("=========================\n");
	printf("===Cadastro de receita===\n");
	printf("=========================\n");
	printf("\n");
	printf("Digite a descricao:");
	scanf("%s",lancamento.descricao);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f",&lancamento.valor);
}

void cadastrarDispesa(){
	printf("=========================\n");
	printf("===Cadastro de despesa===\n");
	printf("=========================\n");
	printf("\n");
	printf("Digite a descricao:");
	scanf("%s",lancamento.descricao);
	fflush(stdin);
	printf("Digite o valor:");
	scanf("%f",&lancamento.valor);
}
void salvarMovimento(int movimento,FILE *fp) {
	int movimentoReceita = 1;
	int movimentoDespesa = 2;
	int sair = 0;
	float static totalReceita = 0;
	float static totalDespesa = 0;
	float static total = 0;
	
	fp = fopen (NOME_ARQUIVO, MODO_ARQUIVO);

	if(movimento == movimentoReceita){
		totalReceita += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Receita\n");        
	}
	else if (movimento == movimentoDespesa){
		totalDespesa += lancamento.valor; 
		fprintf(fp,"=================================\n");
		fprintf(fp,"MOVIMENTECAO:Despesa\n");
	}else if ( movimento == sair ){	
		total = totalReceita - totalDespesa;
		fprintf(fp,"==============\n",total);	
		fprintf(fp,"TOTAL:%.2f\n",total);	
		fprintf(fp,"==============\n",total);	
		fclose(fp);
		exit(0);
	}

	fprintf(fp,"Data :%d/%d/%d",lancamento.data.dia,lancamento.data.mes,lancamento.data.ano);
	fprintf(fp,"\t\tDESCRICAO: %s",lancamento.descricao);
	fprintf(fp,"\t\tVALOR: %.2f\n",lancamento.valor);

	total = totalReceita - totalDespesa;
	fprintf(fp,"TOTAL RECEITA:%.2f",totalReceita);	
	fprintf(fp,"\tTOTAL DESPESA:%.2f",totalDespesa);	
	fprintf(fp,"\tTOTAL:%.2f\n",total);	

	fclose(fp);	
}