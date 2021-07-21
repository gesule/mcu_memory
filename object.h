#pragma once
#include <stdlib.h>

/* La definición de la estructura permanece oculta.
 */
typedef struct object obj_t;

/* Definicion equivalente a efectos de asignación estática de memoria
 */
typedef struct {
    int     private_1;
    char*   private_2;
    char    private_3;
} obj_dummy_t;

// Devuelve el puntero de tipo 'obj_t' al objeto de tipo obj_dummy_t
#define obj_p(obj) ((obj_t*) &obj)


size_t obj_size();

void assert_dummy_size();
int obj_set_id(obj_t* self, int id);
int obj_get_id(obj_t* self);

char* obj_set_name(obj_t* self, char *name);
char* obj_get_name(obj_t* self);


obj_t* obj_repo_catch(void);
obj_t * obj_repo_drop(obj_t *obj);
size_t obj_repo_count(void);