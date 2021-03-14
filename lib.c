/*Vasilescu Alexandru Madalin-321CB */
#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Alocarea structurii de baza de date cu adaugarea numelui
t_db* alloc_DB(char *ptr){
	t_db* DataBase=(t_db*)malloc(sizeof(t_db));
	if(!DataBase) return NULL;
	strcpy(DataBase->name,ptr);
	DataBase->tables=NULL;
	return DataBase;

}
//Alocarea unei coloane
t_column* alloc_column(char *ptr){
	t_column* column=(t_column*) malloc(sizeof(t_column));
	if(!column) return NULL;
	strcpy(column->name,ptr);
	column->next=NULL;
	return column; 
}

//Alocarea unei celule de tip Integer
t_intCell* alloc_intCell(char *ptr){
	t_intCell* aux=(t_intCell*) malloc(sizeof(t_intCell));
	if(!aux) return NULL;
	aux->value=atoi(ptr);
	aux->next=NULL;
	return aux;
}
//Alocarea unei linii de tip Integer 
t_intLine* alloc_intline(char *ptr){
	char delimitator[]=" \n";
	t_intLine* line=(t_intLine*) malloc(sizeof(t_intLine));
	if(!line) return NULL;
	ptr=strtok(NULL,delimitator);
	while(ptr){
		//Apelez o functie care imi populeaza lista de celule
	if(inserare_intcelula(&line->cells,ptr)==0) return NULL;
		ptr=strtok(NULL,delimitator);
	}
	return line;
}
//Alocarea unei celule de tip Float
t_floatCell* alloc_floatCell(char *ptr){
	t_floatCell* aux=(t_floatCell*) malloc(sizeof(t_intCell));
	if(!aux) return NULL;
	aux->value=atof(ptr);
	aux->next=NULL;
	return aux;
}
//Alocarea unei linii de tip Float
t_floatLine* alloc_floatline(char *ptr){
	char delimitator[]=" \n";
	t_floatLine* line=(t_floatLine*) malloc(sizeof(t_floatLine));
	if(!line) return NULL;
	ptr=strtok(NULL,delimitator);
	while(ptr){
		//Apelez o functie care imi populeaza lista de celule
	if(inserare_floatcelula(&line->cells,ptr)==0) return NULL;	
		ptr=strtok(NULL,delimitator);
	}

	return line;
}
//Alocare unei celule de tip String
t_stringCell* alloc_stringCell(char *ptr){
	t_stringCell* aux=(t_stringCell*) malloc(sizeof(t_intCell));
	if(!aux) return NULL;
	aux->value=(char*) malloc(MAX_COLUMN_NAME_LEN);
	strcpy(aux->value,ptr);
	aux->next=NULL;
	return aux;
}
//Alocarea unei liste de tip String
t_stringLine* alloc_stringline(char *ptr){

	char delimitator[]=" \n";
	t_stringLine* line=(t_stringLine*) malloc(sizeof(t_stringLine));
	if(!line) return NULL;
	ptr=strtok(NULL,delimitator);
	while(ptr){
		//Apelez o functie care imi populeaza lista de celule
		if(inserare_stringcelula(&line->cells,ptr)==0) return NULL;
		ptr=strtok(NULL,delimitator);
	}
	return line;
} 
//Alocarea unui tabel cu toate campurile oferite la intrare
t_table* alloc_table(char *ptr,char *cmd){
	char delimitator[]=" \n";
	t_table *table=(t_table*) malloc(sizeof(t_table));
	if(!table) return NULL;
	strcpy(table->name,ptr);
	ptr=strtok(NULL,delimitator);
	if(!ptr){
		printf("Unknown command:\"%s\".",cmd);
		free(table);
		return NULL;
	}
	if(strcmp(ptr,"INT")==0) table->type=INT;
	else if(strcmp(ptr,"FLOAT")==0) table->type=FLOAT;
	else if(strcmp(ptr,"STRING")==0) table->type=STRING;
	else{
		printf("Unknown data type:\"%s\".",ptr);
		free(table);
		return NULL;
	}
	table->columns=NULL;
	table->lines=NULL;
	table->next=NULL;
	ptr=strtok(NULL,delimitator);
	while(ptr){
		t_column* column=alloc_column(ptr);
		if(!column){
				eliberare_coloane(&table->columns);
				free(table);
				return NULL;
			}
			inserare_coloana(&table->columns,column);
		ptr=strtok(NULL,delimitator);
	}
	return table;
}
//Insereaza la final o celula de tip Integer intr-o lista de celule
int inserare_intcelula(t_intCell **cells, char *ptr){
	t_intCell *u=NULL,*p=*cells,*aux;
	if(p){

		while(p->next) p=p->next;
		u=p;
	}
	aux=alloc_intCell(ptr);
	if(!aux) return 0;
	if(u==NULL)
		*cells=aux;
	else{
		u->next=aux;
		u->next->next=NULL;
	}
	return 1;
}
//Insereaza la final o celula de tip Float intr-o lista de celule
int inserare_floatcelula(t_floatCell **cells, char *ptr){
	t_floatCell *u=NULL,*p=*cells,*aux;

	if(p){
		while(p->next) p=p->next;
		u=p;
	}

	aux=alloc_floatCell(ptr);
	if(!aux) return 0;
	if(u==NULL)
		*cells=aux;
	else{
		u->next=aux;
		u->next->next=NULL;
	}
	return 1;
}
//Insereaza la final o celula de tip String intr-o lista de celule
int inserare_stringcelula(t_stringCell **cells, char *ptr){
	t_stringCell *u=NULL,*p=*cells,*aux;
	if(p){
		while(p->next) p=p->next;
		u=p;
	}
	aux=alloc_stringCell(ptr);
	if(!aux) return 0;
	if(u==NULL)
		*cells=aux;
	else{
		u->next=aux;
		u->next->next=NULL;
	}
	return 1;
}
//Insereaza o linie de tabel intr-o lista de linii (cu Integer)
int inserare_intline(t_intLine **lines,char *ptr){
	t_intLine *u=NULL, *p=*lines,*aux;
	if(p){
		while(p->next) p=p->next;
		u=p;
	}
	aux=alloc_intline(ptr);
	if(!aux) return 0;
	if(u==NULL)
		*lines=aux;
	else
		u->next=aux;
	return 1;
}
//Insereaza o linie de tabel intr-o lista de linii (cu Float)
int inserare_floatline(t_floatLine **lines,char *ptr){
	t_floatLine *u=NULL, *p=*lines,*aux;
	if(p){
		while(p->next) p=p->next;
		u=p;
	}

	aux=alloc_floatline(ptr);

	if(!aux) return 0;

	if(u==NULL)
		*lines=aux;
	else
		u->next=aux;
		
	return 1;
}
//Insereaza o linie de tabel intr-o lista de linii (cu String)
int inserare_stringline(t_stringLine **lines,char *ptr){
	t_stringLine *u=NULL, *p=*lines,*aux;
	if(p){
		while(p->next) p=p->next;
		u=p;
	}
	aux=alloc_stringline(ptr);
	if(!aux) return 0;
	if(u==NULL)
		*lines=aux;
	else
		u->next=aux;
	return 1;
}
//Elibereaza o lista de coloane
//Se elibereaza doar coloana deoarece numele este static
void eliberare_coloane(t_column **columns){
	t_column *aux;
	while (*columns){
		aux=*columns;
		*columns=(*columns)->next;
		free(aux);
	}
}
//Insereaza o coloana de tabel intr-o lista de coloane
int inserare_coloana(t_column ** columns, t_column *column){
	t_column* u=NULL, *p= *columns;
	if(p!=NULL){
		while(p->next) p=p->next;
		u=p;
	}
	if(u==NULL) *columns=column;
	else u->next=column;
	return 1;
}
//Insereaza un tabel intr-o lista le tabele
int inserare_table(t_table ** tables,t_table *table){
	t_table* u=NULL, *p= *tables;
	if(p!=NULL){
		while(p->next) p=p->next;
		u=p;
	}
	if(u==NULL) *tables=table;
	else u->next=table;
	return 1;

}
//Cauta un tabel in lista de tabele dupa nume
//Daca nu s-a gasit intoarce null
//Daca s-a gasit intoarce tabelul
t_table* find(char *name,t_table *tables){
	if(!tables) return NULL;
	t_table *t=tables;
	while(t){
		if(strcmp(t->name,name)==0)
			return t;
		t=t->next;
	}
	return NULL;
}
//Cauta o coloana intr-o lista de coloane
//Intoarce indexul ei in lista
//Daca nu s-a gasit colaoa intoarce -1
int find_column(char *name,t_column* columns){
	t_column* column=columns;
	int i=0;
	while(column){
		if(strcmp(column->name,name)==0)
			return i;
		i++;
		column=column->next; 
	}
	return -1;
}
//Elibereaza o celula de tip int (Nu merge bine)
void eliberare_intcells(t_intCell **cells){
	t_intCell *cell;
	while(*cells){
		cell=*cells;
		*cells=(*cells)->next;
		free(cell);
	}
}
//Elibereaza o celula de tip float (Nu merge bine)
void eliberare_floatcells(t_floatCell **cells){
	t_floatCell *cell;
	while(*cells){
		cell=*cells;
		*cells=(*cells)->next;
		free(cell);
	}
}
//Elibereaza o celula de tip string (Nu merge bine)
void eliberare_stringcells(t_stringCell **cells){
	t_stringCell* cell;
	while(*cells){
		cell=*cells;
		*cells=(*cells)->next;
		free(cell->value);
		free(cell);
	}
}
//Elibereaza o linie de tip float 
//Am comentat linia pentru a se vedea unde trebuia facuta elibereaea
void eliberare_floatline(t_floatLine **lines){
	t_floatLine *aux;
	while (*lines){
		aux=*lines;
		*lines=(*lines)->next;
		eliberare_floatcells(&aux->cells);
		free(aux);
	}
}

//Elibereaza o linie de tip string 
//Am comentat linia pentru a se vedea unde trebuia facuta elibereaea
void eliberare_stringline(t_stringLine **lines){
	t_stringLine *aux;
	while (*lines){
		aux=*lines;
		*lines=(*lines)->next;
		eliberare_stringcells(&aux->cells);
		free(aux);
	}
}

//Elibereaza o linie de tip integer
//Am comentat linia pentru a se vedea unde trebuia facuta elibereaea
void eliberare_intline(t_intLine **lines){
	t_intLine *aux;
	while (*lines){
		aux=*lines;
		*lines=(*lines)->next;
		eliberare_intcells(&aux->cells);
		free(aux);
	}
}
//Elibereaza intregul tabel
void eliberare_tabel(t_table* table){
	eliberare_coloane(&table->columns);
	free(table->columns);
	if(table->type==INT) eliberare_intline((t_intLine**)&table->lines);
	if(table->type==FLOAT) eliberare_floatline((t_floatLine**)&table->lines);
	if(table->type==STRING) eliberare_stringline((t_stringLine**)&table->lines);
	free(table->lines);
}