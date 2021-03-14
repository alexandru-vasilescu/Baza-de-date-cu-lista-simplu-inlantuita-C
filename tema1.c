/*Vasilescu Alexandru Madalin-321CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"

//Verifica daca elementul cu indicele x din lista satisface relatia
// (lines[index] 'symbol' value)
// Am 3 functii asemanatoare cate una pentru fiecare tip(int,float,string)
int verificareint(t_intLine* lines,char *value,char* symbol,int index){
	int x=atoi(value);
	t_intCell* cells=lines->cells;
	while(index>0){
		index--;
		cells=cells->next;
	}
	if(strcmp(symbol,">")==0){
		if(cells->value > x) return 1;
	}else if(strcmp(symbol,">=")==0){
		if(cells->value >= x) return 1;
	}else if(strcmp(symbol,"<")==0){
		if(cells->value < x) return 1;
	}else if(strcmp(symbol,"<=")==0){
		if(cells->value <= x) return 1;
	}else if(strcmp(symbol,"==")==0){
		if(cells->value == x) return 1;
	}else if(strcmp(symbol,"!=")==0){
		if(cells->value != x) return 1;
	}
	return 0;
}
int verificarefloat(t_floatLine* lines,char *value,char* symbol,int index){
	float x=atof(value);
	t_floatCell* cells=lines->cells;
	while(index>0){
		index--;
		cells=cells->next;
	}
	if(strcmp(symbol,">")==0){

		if(cells->value > x) return 1;
	}else if(strcmp(symbol,">=")==0){

		if(cells->value >= x) return 1;
	}else if(strcmp(symbol,"<")==0){

		if(cells->value < x) return 1;
	}else if(strcmp(symbol,"<=")==0){

		if(cells->value <= x) return 1;
	}else if(strcmp(symbol,"==")==0){

		if(cells->value == x) return 1;
	}else if(strcmp(symbol,"!=")==0){

		if(cells->value != x) return 1;
	}
	return 0;
}
int verificarestring(t_stringLine* lines,char *value,char* symbol,int index){
	t_stringCell* cells=lines->cells;
	while(index>0){
		index--;
		cells=cells->next;
	}
	if(strcmp(symbol,">")==0){
		if(strcmp(cells->value,value)>0) return 1;
	}else if(strcmp(symbol,">=")==0){
		if(strcmp(cells->value,value)>=0) return 1;
	}else if(strcmp(symbol,"<")==0){
		if(strcmp(cells->value,value)<0) return 1;
	}else if(strcmp(symbol,"<=")==0){
		if(strcmp(cells->value,value)<=0) return 1;
	}else if(strcmp(symbol,"==")==0){
		if(strcmp(cells->value,value)==0) return 1;
	}else if(strcmp(symbol,"!=")==0){
		if(strcmp(cells->value,value)!=0) return 1;
	}
	return 0;
}
//Sterge toate liniile care satisfac relatia din lista
void delete_intline(t_intLine**line,char* value, char* symbol,int index){
	t_intLine *p=*line,*previous=NULL;
	while(p){
		if (verificareint(p,value,symbol,index)==1){
			if(previous==NULL)
				*line=p->next;
			else 
				previous->next=p->next;
			eliberare_intcells(&p->cells);
			free(p);
		}else{
			previous=p;
		}
		p=p->next;
	}
}
//Sterge toate liniile care satisfac relatia din lista
void delete_floatline(t_floatLine**line,char* value, char* symbol,int index){
	t_floatLine *p=*line,*previous=NULL;
	while(p){
		if (verificarefloat(p,value,symbol,index)==1){
			if(previous==NULL)
				*line=p->next;
			else 
				previous->next=p->next;
			eliberare_floatcells(&p->cells);
			free(p);
		}else{
			previous=p;
		}
		p=p->next;
	}
}
//Sterge toate liniile care satisfac relatia din lista
void delete_stringline(t_stringLine**line,char* value, char* symbol,int index){
	t_stringLine *p=*line,*previous=NULL;
	while(p){
		if (verificarestring(p,value,symbol,index)==1){
			if(previous==NULL)
				*line=p->next;
			else 
				previous->next=p->next;
			eliberare_stringcells(&p->cells);
			free(p);
		}else{
			previous=p;
		}
		p=p->next;
	}
}
//Sterge un tabel din lista de tabele
void delete_table(t_table** table,char* name){
	t_table *p=*table,*previous=NULL;
	while(p){
		if(strcmp(p->name,name)==0){
			if(previous==NULL){
				*table=p->next;
			}
			else
				previous->next=p->next;
			eliberare_tabel(p);
			free(p);
			return;
		}else{
			previous=p;
		}
		p=p->next;
	}
}
//Se apeleaza cand este ceruta comanda DELETE la intrare

void delete(char *ptr, t_db* DataBase){
	//Verifica daca tabelul exista in baza de date dupa nume
	char name[MAX_TABLE_NAME_LEN];
	char delimitator[]=" \n";
	t_table* table;
	ptr=strtok(NULL,delimitator);
	strcpy(name,ptr);
	table=find(name,DataBase->tables);
	if(!table){
		
		printf("Table \"%s\" not found in database.\n",ptr);
		while(ptr)
			ptr=strtok(NULL,delimitator);
		return;
	}
	//Verifica daca mai primeste si alti parametri in afara de nume
	//Daca primeste coloana simbol si valoare apeleaza o functie de delete_line
	ptr=strtok(NULL,delimitator);
	if(ptr){
		char column[MAX_COLUMN_NAME_LEN];
		strcpy(column,ptr);
		int i=find_column(ptr,table->columns);
			if(i==-1){ 
				
				printf("Table \"%s\" does not contain column \"%s\".\n",name,ptr);
				while(ptr)
					ptr=strtok(NULL,delimitator);
		}else{
			ptr=strtok(NULL,delimitator);
			char symbol[2];
			strcpy(symbol,ptr);
			ptr=strtok(NULL,delimitator);
			if(table->type==INT){
				delete_intline((t_intLine**)&table->lines,ptr,symbol,i);
			}else
			if(table->type==FLOAT){
				delete_floatline((t_floatLine**)&table->lines,ptr,symbol,i);
			}else 
			if(table->type==STRING){
				delete_stringline((t_stringLine**)&table->lines,ptr,symbol,i);
			}
			
		}
		return;
	}
	//Daca nu primeste alt parametru apeleaza functia de stergere a tabelului
	delete_table(&DataBase->tables,name);
}
//Functia care afiseaza o linie de tabel cu elemente de tip Integer
void print_line_int(t_intLine *line){
	t_intCell* cells=line->cells;
	int nrcifre=0,value;
	if(!cells) return;
	while(cells){
		value=cells->value;
		printf("%d",cells->value);
		if(value<0) {
			nrcifre++;
			value=value*(-1);
		}
		if(value==0) nrcifre=1;
		while(value>0){
			value/=10;
			nrcifre++;
		}
		for(int i=nrcifre;i<=MAX_COLUMN_NAME_LEN;i++)
			printf(" ");
		cells=cells->next;
		nrcifre=0;
	}
	printf("\n");
}
//Functia care afiseaza o linie de tabel cu elemente de tip Float
void print_line_float(t_floatLine *line){
	t_floatCell* cells=line->cells;
	int nrcifre=7,value;
	if(!cells) return;
	while(cells){
		value=(int)cells->value;
		printf("%0.6f",cells->value);
		if(value==0)nrcifre++;
		if(value<0) {
			nrcifre++;
			value=value*(-1);
		}
		while(value>0){
			value/=10;
			nrcifre++;
		}
		for(int i=nrcifre;i<=MAX_COLUMN_NAME_LEN;i++)
			printf(" ");
		cells=cells->next;
		nrcifre=7;
	}
	printf("\n");
}
//Functia care afiseaza o linie de tabel cu elemente de tip String
void print_line_string(t_stringLine *line){
	t_stringCell* cells=line->cells;
	if(!cells) return;
	while(cells){
		printf("%s",cells->value);
		for(int i=strlen(cells->value);i<=MAX_COLUMN_NAME_LEN;i++)
			printf(" ");
		cells=cells->next;
	}
	printf("\n");
}
//Functia care afiseaza numele coloanelor tabelului
void print_column(t_table *table){
	t_column* column=table->columns;
	int i;
	if(!column) return;
	while(column){
		printf("%s",column->name);
		for(i=strlen(column->name);i<=MAX_COLUMN_NAME_LEN;i++)
			printf(" ");
		column=column->next;
	}
	printf("\n");
	column=table->columns;
	while(column){
		for(i=0;i<MAX_COLUMN_NAME_LEN;i++)
			printf("-");
		printf(" ");
		column=column->next;
	}
	printf("\n");
}
//Functia de afisare a unui intreg tabel
void print_table(t_table *table){
	
	print_column(table);
	
		if(table->type==INT){
			t_intLine *line=(t_intLine*)table->lines;
			while(line){
				print_line_int(line);
				line=line->next;

			}
	 	}else	
			if(table->type==FLOAT){
				t_floatLine *line=(t_floatLine*)table->lines;
				while(line){
					print_line_float(line);
					line=line->next;

				}
			}else
			if(table->type==STRING) {
				t_stringLine *line=(t_stringLine*)table->lines;
				while(line){
					print_line_string(line);
					line=line->next;
				}
			}
	printf("\n");
}
//Functie de afisare a intregii baze de date
void print_db(t_db* DataBase){
	printf("DATABASE: %s\n\n",DataBase->name);
	t_table* tables=DataBase->tables;
	while(tables){
		printf("TABLE: %s\n",tables->name);
		print_table(tables);
		tables=tables->next;
	}
}
//Functia de cautare apelata cu comanda SEARCH primita ca input
//Afiseaza toate listele care satisfac conditia ceruta
void search(char* ptr,t_db* DataBase){
	char delimitator[]=" \n"; 
	t_table *table;
	ptr=strtok(NULL,delimitator);
	char name[MAX_COLUMN_NAME_LEN];
	strcpy(name,ptr);
	table=find(name,DataBase->tables);
	if(!table){
		
		printf("Table \"%s\" not found in database.\n",ptr);
		while(ptr)
			ptr=strtok(NULL,delimitator);
		return;
	}

	ptr=strtok(NULL,delimitator);
	int i=find_column(ptr,table->columns);
	if(i==-1){ 
			
		printf("Table \"%s\" does not contain column \"%s\".\n",name,ptr);
		while(ptr)
			ptr=strtok(NULL,delimitator);
		return;
	}
	printf("TABLE: %s\n",name);
	print_column(table);
	char symbol[2];
	ptr=strtok(NULL, delimitator);
	strcpy(symbol,ptr);
	ptr=strtok(NULL, delimitator);
	if(table->type==INT){
		t_intLine* line=(t_intLine*)table->lines;
		while(line){
			if (verificareint(line,ptr,symbol,i)==1)
				print_line_int(line);
			line=line->next;
		}
	}else
	if(table->type==FLOAT){
		t_floatLine* line=(t_floatLine*)table->lines;
		while(line){
			if(verificarefloat(line,ptr,symbol,i)==1)
				print_line_float(line);
			line=line->next;
		}
	}else
	if(table->type==STRING){
		t_stringLine* line=(t_stringLine*)table->lines;
		while(line){
			if(verificarestring(line,ptr,symbol,i)==1)
				print_line_string(line);
			line=line->next;
		}
	}
	printf("\n");

}
//Functie care adauga o linie intr-un tabel
void add (char *ptr, t_db* DataBase){
	char name[MAX_TABLE_NAME_LEN];
	char delimitator[]=" \n";
	ptr=strtok(NULL,delimitator);
	strcpy(name,ptr);
	t_table* table=find(name,DataBase->tables);
	if(table==NULL){
		
		printf("Table \"%s\" not found in database.\n",name);
		while(ptr)
			ptr=strtok(NULL,delimitator);
		return ;
	}
	if(table->type==INT){
		if(inserare_intline((t_intLine**)&table->lines,ptr)==0)return ;
	}
	else if(table->type==FLOAT){

		if(inserare_floatline((t_floatLine**)&table->lines,ptr)==0)return ;
	}
	else if(table->type==STRING){
		if(inserare_stringline((t_stringLine**)&table->lines,ptr)==0)return ;
	}

}
//Functie care sterge toate liniile dintr-un tabel
void clear(char *ptr,t_db* DataBase){
	char name[MAX_COLUMN_NAME_LEN];
	char delimitator[]=" \n";
	ptr=strtok(NULL,delimitator);
	t_table* table=find(name,DataBase->tables);
	if(table==NULL){
		printf("Table \"%s\" not found in database.\n",name);
		return;
	}
	if(table->type==INT) eliberare_intline((t_intLine**)&table->lines);
	if(table->type==FLOAT) eliberare_floatline((t_floatLine**)&table->lines);
	if(table->type==STRING) eliberare_stringline((t_stringLine**)&table->lines);
}
//Functie care sterge toate tabelele dintr-o baza de date
void distruge_tables(t_table** tables){
	t_table *aux;
	while(*tables){
		aux=*tables;
		*tables=(*tables)->next;
		eliberare_tabel(aux);
		free(aux);
	}
}
//Functie care sterge o baza de date
void delete_db(t_db *DataBase){
	distruge_tables(&DataBase->tables);
	free(DataBase->tables);
}
int main(){
	//Variabila folosita pentru a citi comanda
	char string[MAX_CMD_LEN];
	char delimitator[]=" \n";
	//Variabila folosita pentru a memora comanda in caz de comanda gresita
	char copy_cmd[MAX_CMD_LEN];
	t_db* DataBase=NULL;
	//Variabila folosita pentru a vedea daca s-a ajuns la comanda DELETE_DB
	int check=0;
	t_table* table;
	while(1){
		//Se citeste de la stdin
		fgets(string, MAX_CMD_LEN, stdin);
		//Se copiaza comanda in variabila auxiliara
		strcpy(copy_cmd,string);
		//Se separa elementele comenzii in functie de spatiu si newline
		char *ptr=strtok(string,delimitator);
		//Se verifica ce comanda s-a primit la input 
		//Se apleaza functii in functie de comanda primita
		while(ptr){
			//Se initializeaza baza de date
			if(strcmp(ptr,"INIT_DB")==0){
				ptr=strtok(NULL,delimitator);
				DataBase=alloc_DB(ptr);
				if(DataBase==NULL) return 0;
				//Se creaza tabele
			}else if(strcmp(ptr,"CREATE")==0){
				ptr=strtok(NULL,delimitator);
				//Se verifica daca exista deja in baza de date
				if(find(ptr,DataBase->tables)!=NULL){
					printf("Table \"%s\" already exists.",ptr);
				}else{
					table=alloc_table(ptr,copy_cmd);
					if(!table) return 0;
					inserare_table(&DataBase->tables,table);
				}
				//Se sterg tabele sau linii din tabele
			}else if(strcmp(ptr,"DELETE")==0){
				delete(ptr,DataBase);
				//Se adauga linii in tabele
			}else if(strcmp(ptr,"ADD")==0){
				add(ptr,DataBase);
				//Se afiseaza un tabel
			}else if(strcmp(ptr,"PRINT")==0){
				ptr=strtok(NULL,delimitator);
				//Se verifica daca tabelul exista
				table=find(ptr,DataBase->tables);
				if(table==NULL)
					printf("Table \"%s\" not found in database.\n",ptr);
				else {
					printf("TABLE: %s\n",ptr);
					print_table(table);
				}
				//Se afiseaza baza de date in intregime
			}else if(strcmp(ptr,"PRINT_DB")==0)
					print_db(DataBase);
				//Se afiseaza linii care indeplinesc o conditie dintr-un tabel
			else if(strcmp(ptr,"SEARCH")==0)
					search(ptr,DataBase);
				//Se sterg toate liniile dintr-un tabel
			else if(strcmp(ptr,"CLEAR")==0)
				clear(ptr,DataBase);
				//Se sterge toata baza de date
			else if(strcmp(ptr,"DELETE_DB")==0){ 
				delete_db(DataBase);
				free(DataBase);
				check=1;
				//Daca nu este comanda buna se afiseaza acest lucru
			}else{
				ptr=strtok(copy_cmd,"\n");
				printf("Unknown command: \"%s\".\n",ptr);
			}
			ptr=strtok(NULL,delimitator);
		}
		//Daca am primit comanda DELETE_DB, check=1 si se iese din program;
		if(check) break;
	}	

	return 0;
}