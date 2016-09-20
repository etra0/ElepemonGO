#ifndef ELEPEMON_H
#define ELEPEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

/*
* A continuacion se presentan las firmas de todas las funciones cuya
* implementacion es OBLIGATORIA. Usted puede crear todas las que quiera
* adicionalmente para ayudarlo en su desarrollo, e incluso integrarlas
* en esta interfaz y documentarlas propiamente.
*/

#define ATTACK_FN "attack"

enum type
{
	NORMAL,
	WATER,
	FIRE,
	PLANT
};

enum effect
{
	NOEFFECT,
	CONFUSED,
	POISONED,
	PARALYZED
};

enum effectiveness
{
	NO,
	NONE,
	NOTVERY,
	SUPER
};

struct attack_result;
struct elepemon;

typedef struct attack_result* (*attack_t)(struct elepemon*, struct elepemon*);

/*
* Esta estructura define el resultado de un ataque.
* Es el tipo de retorno de una funcion de ataque, como lo define la firma
* de puntero a funcion de attack_t
*/
struct attack_result
{
	char* attack_id; // Debe ser nombrado de igual manera que el ataque
	struct elepemon* defensor; // Referencia al elepemon defensor
	struct elepemon* attacker; // Referencia al elepemon atacante
	int damage_done; // Dano realizado
	enum effect effect; // Efecto final (enum effect) [no es mandatorio]
	enum effectiveness effective; // Efectividad final (enum effectiveness)
									//[no es mandatorio]
};

/*
* Esta estructura define los atributos de un elepemon.
* En este tipo de estucturas deben cargarse los valores desde un archivo INI
*/
struct elepemon
{
	char *name; // Nombre del elepemon (seccion INI)
	int hp; // hp
	enum type type; // tipo
	int power; // ataque
	int defense; // defensa

	// Estructura anonima
	struct
	{
		char** attack_ids; // Arreglo de strings. Son los nombres de los ataques
						// ejemplo: {"plant1", "plant2"}
		attack_t* attacks; // Arreglo de attack_t (ver definicion de puntero
							// a funcion mas arriba). Aqui se cargan las
							// funciones dinamicamente que corresponden a los
							// ataques. Estan ordenadas de la misma manera que
							// attack_ids, por lo tanto podemos accederlas por
							// nombre. e.g.: "plant2" tiene la posicion 1 en
							// attack_ids, por lo tanto attacks[1] corresponde
							// a la funcion que realiza el ataque "plant2"
		int attack_count; // Cantidad de elementos en los arreglos attack_ids y
						// attacks

	} attack; // se accede como attack.
};

/*
* Estructura de nodo tipica para generar stacks de elepemones
*/
struct elepemon_node
{
	struct elepemon elepemon;
	struct elepemon_node* next;
};

/*
* Muestra todos los atributos de un elepemon
* @param elepemon el elepemon
*/
void print_elepemon(const struct elepemon* elepemon);

/**
* Inicializa un elepemon (los punteros a NULL y numericos a 0)
* @param elepemon el elepemon
*/
void init_elepemon(struct elepemon* elepemon);

/**
* Libera la memoria interna de un elepemon
* @param elepemon el elepemon
*/
void free_elepemon(struct elepemon* elepemon);

/**
* A partir de un string con nombres de ataques separados por coma (como el
* 	de un archivo de elepemones. e.g.: plant1,plant2) debe retornar un arreglo
* 	de strings alojado en el heap con cada nombre, i.e.: {"plant1", "plant2"}
* @param str string original, e.g.: "plant1,plant2"
* @param *n entero por referencia para almacenar tamanio, e.g.: *n = 2
* @return el arreglo de strings
*/
char** get_attack_ids(const char* str, int* n);

/**
* Carga los ataque de un elepemon. Cuando un elepemon es pasado a esta funcion
* 	ya debe tener inicializado .attack.attack_count y .attack.attack_ids con sus
* 	respectivos valores, e.g.: para attacks=plant1,plant2
* 		.attack.attack_count = 2
* 		.attack.attack_ids = {"plant1", "plant2"}
* 	Esta funcion debe leer cada id, y cargar la funcion llamada ATTACK_FN
*	(definida como macro en este archivo) que esta dentro de la libreria llamada
* 	lib<id>.so en el directorio de ataques, e.g.:
*		attacks/
*			libplant1.so
*			libplant2.so
*	Debe cargarla y asignarla al indice correspondiente en .attack.attacks,
*	e.g.: .attack.attacks[1] = dlsym(handle, ATTACK_FN); <- palta!
* @param attacks_filedir el nombre del directorio de ataques, e.g.: "attacks"
* @param elepemon el elepemon
*/
int load_attacks(const char* attacks_filedir, struct elepemon* elepemon);

/**
* La libreria elepemon debera manejar internamente (probablemente en su
* 	elepemon.c con la estructura de datos que prefiera) las referencias a los
* 	"handles" que le retorne la funcion dlopen() (lea el manual!) para que
* 	puedan ser liberadas correctamente con la funcion dlclose(). La tarea de
* 	esta funcion es usar dlclose() sobre cada handle.
*/
void unload_attacks();

/*
* Debe inicializar una nueva estructura de elepemon e ingresarla en la
*	estructura LIFO
* @param stack referencia al stack enlazado
* @param name nombre del elepemon
* @return nuevo elepemon
*/
struct elepemon_node* push_elepemon(struct elepemon_node** stack, const char* name);

/**
* Obtiene un elepemon por nombre a partir de un stack enlazado
* @param stack el stack
* @param name nombre del elepemon
* @return elepemon encontrado o NULL si no existe
*/
struct elepemon* get_elepemon(struct elepemon_node* stack, const char* name);

/**
* Limpia la memoria pedida en el heap por el stack enlazado
* @param stack el stack
*/
void free_elepemon_stack(struct elepemon_node* stack);


// Agregado

/* Funcion booleana que ve si un stack esta vacio o no
* @param stack pila de elepemones
* @return booleano que describe si esta vacia
*/
int is_empty(struct elepemon_node* stack);

/* Mueve un elemento de un stack a otro
* @param from pila inicial de donde se sacara el nodo
* @param to pila donde llegara el nodo
* @param indice corresponde al indice del elemento en el stack "from"
*/
void move_stack_node(struct elepemon_node** from, struct elepemon_node** to, int indice);

/* Se utiliza para parsear los tipo de string a numero
* @param str corresponde al string que se desea parsear
* @param n puntero al tipo de un elepemon, para modificarlo directamente.
*/
void parse_type(const char *str, enum type *n);

/* Retorna el tamanno de un stack */
int get_stack_size(struct elepemon_node *stack);

/* Verifica si es que un elepemon tiene un ataque dado */
int verify_attack(struct elepemon *elepemon, char *str);

/* Imprime la lista de ataques de un elepemon */
void read_attacks(struct elepemon *elepemon);

/* Encuentra el indice de un elepemon en un stack */
int find_index(struct elepemon_node *stack, struct elepemon *elepemon);

/* Entrega la informacion resultante de cada ataque */
void check_attack(struct attack_result* attack_info);

/* Funcion que imprime la lista de elepemones en un stack */
void print_stack(struct elepemon_node* stack);
#endif // ELEPEMON_H
