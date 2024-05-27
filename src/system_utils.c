
#include <stdio.h>
#include <stdlib.h>
#include "../include/system_utils.h"

// Definição de uma macro para limpar a tela, dependendo do sistema operacional
#ifdef _WIN32
	#define CLEAR_SCREEN "cls"
#else
	#define CLEAR_SCREEN "clear"
#endif

void pause() {
	printf("\nPressione qualquer tecla para continuar...");
	getchar();
}


void clean(){
	system(CLEAR_SCREEN);
}

