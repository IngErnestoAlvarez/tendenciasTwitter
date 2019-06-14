#include "strutil.h"
#include <string.h>
#include <stdlib.h>

#define TAM_MIN 4

char* substr(const char* string, size_t k){
    char* nueva;
    //if(k<0) return NULL;
    //Cuando K es menor a la cantidad de caracteres de string
    if(strlen(string) >= k){
        nueva = malloc(sizeof(char)*(k+1));
        if(!nueva) return NULL;
        memcpy(nueva, string, k);
        nueva[k] = 0;
    }
    //Cuando K es mayor a la longitud de string
    else{
        nueva = malloc(sizeof(char)*(strlen(string)+1));
        if(!nueva) return NULL;
        memcpy(nueva, string, strlen(string));
        nueva[strlen(string)] = '\0';
    }
        return nueva;
}

char** redimensionar(char** v, size_t cant){
    char** aux = realloc(v, sizeof(char*) * cant);
    if(!aux) return v;
    return aux;
}

char **split(const char *str, char sep){
    char** strv = malloc(sizeof(char*));
    if(!strv) return NULL;
    size_t pos_sep_ant = 0, pos_strv = 0;
    
    size_t i = 0;
    while(str[i] != '\0'){
        if (str[i] == sep){
            strv[pos_strv] = substr(str + pos_sep_ant, i - pos_sep_ant);
            pos_strv++;
            pos_sep_ant = i + 1;
            strv = redimensionar(strv, sizeof(char*)* (pos_strv+1));
        }
        i++;
    }
    strv[pos_strv] = substr(str + pos_sep_ant, i - pos_sep_ant);
    pos_strv++;
    strv = redimensionar(strv, sizeof(char*)* (pos_strv+1));
    strv[pos_strv] = NULL;
    return strv;
}
/*Devuelve el largo de caracteres entre todas los strings, y devuelve al puntero cant_sep
* la cantidad de strings que tiene strv.
*/
size_t ver_largo_total_strv(char** strv, size_t* cant_sep){
    size_t largo = 0;
    while(strv[*cant_sep] != NULL){
        largo += strlen(strv[*cant_sep]);
        (*cant_sep)++;
    }
    (*cant_sep)--;
    return largo;
}
char *join(char **strv, char sep){
    if(!strv) return NULL;
    if(!strv[0]){
        char* string = malloc(sizeof(char));
        string[0] = 0;
        return string;
    }
    
    size_t cant_sepa = 0;
    size_t tam = ver_largo_total_strv(strv, &cant_sepa);
    char* string = malloc(sizeof(char) * (tam+cant_sepa+1));
    if(tam+(cant_sepa) < 1){
        string[0] = 0;
        return string;
    }
    if(!string) return NULL;
    size_t cant_actual = 0;
    for(size_t i = 0; i < (cant_sepa); i++){
        strcpy(string+cant_actual, strv[i]);
        cant_actual += strlen(strv[i]);
        if(sep){
            string[cant_actual] = sep;
            cant_actual++;
        }
    }
    strcpy(string + cant_actual, strv[cant_sepa]);
    string[tam+cant_sepa] = '\0';
    return string;

}

void free_strv(char *strv[]){
    int i = 0;
    while(strv[i] != NULL){
        free(strv[i]);
        i++;
    }
    free(strv);
} 
