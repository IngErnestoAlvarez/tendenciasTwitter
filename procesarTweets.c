#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "minsketch.h"

/*************************************************/
/***********FUNCIONES AUXILIARES*********************/
/*************************************************/
bool validar_parametros(int argc,char* argv[]){
	if(argc != 3){
		fprintf(stderr, "Error: La cantidad de parametros no es valida.");
		return false;
	}
	if(atoi(argv[1]) <= 0){
		fprintf(stderr, "Error: El numero de lineas a leer no es valido.");
		return false;
	}
	if(atoi(argv[2])<= 0){
		fprintf(stderr, "Error: El numero de tendencias que pides no es valido");
		return false;
	}
	return true;
}
/*************************************************/
/***********FUNCION PRINCIPAL*********************/
/*************************************************/
int main(int argc, char *argv[]){
	if(!validar_parametros(argc, argv)) return -1;	

	return 0;
}
