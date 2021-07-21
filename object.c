#include <assert.h>
#include "mcu_mem.h"
#include "object.h"

/* Definición privada
 */
struct object { 
    int id;
    char* name;   
    char flags; 
};

/**
 * Devuelve el tamaño del tipo obj_t
 */ 
size_t obj_size()
{
    return sizeof(obj_t);
}

/** 
 * Permite verificar que la definición dummy tiene el mismo tamaño que la
 * definición privada.
 */
void assert_dummy_size()
{
    assert(sizeof(obj_t) == sizeof(obj_dummy_t));
}

int obj_set_id(obj_t* self, int id) {return self->id = id;}
int obj_get_id(obj_t* self) {return self->id;}

char* obj_set_name(obj_t* self, char *name) { return self->name = name; }
char* obj_get_name(obj_t* self) { return self->name; }


/*
 * Repositorio de objetos obj_t para gestión dinámica de ciclo de vida.
 */
repo_t* obj_repository;

/**
 * Trata de obtener un objeto del repositorio, si este está vacío
 * crea un objeto nuevo.
 * en cualquier caso devuelve un puntero al objeto obtenido.
 */ 
obj_t* obj_repo_catch()
{
    obj_t* obj = (obj_t*) obj_repository;

    if(obj) {
        obj_repository = obj_repository->next;
    }
    else {
        obj = memory_static_alloc(sizeof(obj_t));
    }
    return obj;
}

/**
 * Devuelve el objeto al repositorio.
 * Observa como el par de funciones: obj_catch, obj_drop va llenando
 * el repositorio hasta que este alcance el tamaño requerido por la aplicación
 */ 
obj_t * obj_repo_drop(obj_t *obj)
{
    ((repo_t*)obj)->next = obj_repository;
    obj_repository = (repo_t*) obj;
    return NULL;
}

size_t obj_repo_count()
{
    size_t count = 0;
    for(repo_t* repo = obj_repository; repo; repo = repo->next) ++count;
    return count;
}
