#include "funcionesAuxiliares.h"

lista_t* leer_tweets(FILE* archivo, size_t cantidad_de_lineas){
	
	lista_t* lista_de_tweets = lista_crear();
	size_t contador_de_lineas = 0;
	while(contador_de_lineas < cantidad_de_lineas){		
		char* tweet = leer_hasta_char(archivo,'\n');
		if(tweet) lista_insertar_ultimo(lista_de_tweets,tweet);
		contador_de_lineas++;
	}

	return lista_de_tweets;
}

char* leer_hasta_char(FILE* archivo,char caracter){
	char* string = malloc(sizeof(char));
	char c = (char) fgetc(archivo);
	size_t aux = 0;
	bool palabra=false;
	while(c != -1 && c != caracter){		
		if(c != caracter){
			string[aux] = c;
			aux++;
			string = realloc(string, sizeof(char) * (aux+1));
		} 
		c = (char) fgetc(archivo);
		palabra=true;
	}
	string[aux] = '\0';  // aux+1?
	if(!palabra){
		free(string);
		return NULL;
	}
	return string;
}