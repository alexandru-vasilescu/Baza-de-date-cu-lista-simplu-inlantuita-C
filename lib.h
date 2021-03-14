/*Vasilescu Alexandru Madalin-321CB */
#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

// int
typedef struct intCell {
	int    value;
	struct intCell* next;
} t_intCell;

typedef struct intLine {
	t_intCell*      cells;
	struct intLine* next;
} t_intLine;

// float
typedef struct floatCell {
	float  value;
	struct floatCell* next;
} t_floatCell;

typedef struct floatLine {
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell {
	char*  value;
	struct stringCell* next;
} t_stringCell;

typedef struct stringLine {
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine;

// cell type
typedef enum {
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column {
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column;

// table
typedef struct table {
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	void*         lines;  // t_intLine* | t_floatLine* | t_stringLine*
	struct table* next;
} t_table;

// database
typedef struct db {
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;

//Functii de alocare pentru fiecare structura in parte
t_db* alloc_DB(char *ptr);
t_column* alloc_column(char *ptr);
t_intCell* alloc_intCell(char *ptr);
t_intLine* alloc_intline(char *ptr);
t_floatCell* alloc_floatCell(char *ptr);
t_floatLine* alloc_floatline(char *ptr);
t_stringCell* alloc_stringCell(char *ptr);
t_stringLine* alloc_stringline(char *ptr);
t_table* alloc_table(char *ptr,char *cmd);
//Functii de inserare
int inserare_stringline(t_stringLine **lines,char *ptr);
int inserare_floatline(t_floatLine **lines,char *ptr);
int inserare_intline(t_intLine **lines,char *ptr);
int inserare_stringcelula(t_stringCell **cells, char *ptr);
int inserare_floatcelula(t_floatCell **cells, char *ptr);
int inserare_intcelula(t_intCell **cells, char *ptr);
int inserare_coloana(t_column ** columns, t_column *column);
int inserare_table(t_table ** tables,t_table *table);
//Functii de cautare a unui tabel in database sau a unei coloane in tabel
t_table* find(char *name,t_table *tables);
int find_column(char *name,t_column* columns);
//Functii de eliberare de memorie
void eliberare_coloane(t_column **columns);
void eliberare_intcells(t_intCell **cells);
void eliberare_floatcells(t_floatCell **cells);
void eliberare_stringcells(t_stringCell **cells);
void eliberare_tabel(t_table* table);
void eliberare_intline(t_intLine **lines);
void eliberare_stringline(t_stringLine **lines);
void eliberare_floatline(t_floatLine **lines);

#endif