#include <stdio.h>
#include <assert.h>

#include "mcu_mem.h"
#include "object.h"

/* Test Settings
 */
#define MEMORY_HEAP_SIZE    340

//typedef pobj ((obj_t *) &st_obj);




/* Test main
 */
int main(void)
{
    DEPLOY_PROCEDURE_init_heap(MEMORY_HEAP_SIZE)
    
    // Ha de prevalecer la primera inicialización
    DEPLOY_PROCEDURE_init_heap(1)
    assert(memory_info() == MEMORY_HEAP_SIZE);
    printf("Heap initialization: passed\n");

    // Prueba de asignación estática a través del objeto dummy
    obj_dummy_t st_obj;
    
    obj_set_id(obj_p(st_obj), 1);
    obj_set_name(obj_p(st_obj), "estatic obj");

    printf("Objeto asignado estáticamente: id: %d, Nombre: %s\n",
            obj_get_id(obj_p(st_obj)), 
            obj_get_name(obj_p(st_obj)) 
            );

    assert(obj_repo_count() == 0);
    // Podemos liberar este objeto y dejarlo en el repositorio.
    // aunque st_obj siempre conservará la referencia al elemento 
    // lo cual es un peligro, que se podría manejar con un flag interno
    obj_repo_drop(obj_p(st_obj));
    assert(obj_repo_count() == 1);

    printf("Se ha depositado este elemento en el repositorio\n");
    
    obj_t *obj = obj_repo_catch();
    assert(obj == obj_p(st_obj));

    #define NUM_OBJ 5
    obj_t* vect[NUM_OBJ];

    for(int i = 0; i != NUM_OBJ; i++){
        vect[i] = obj_repo_catch();
        obj_set_id(vect[i], i+10);
    }
    

    assert(memory_info() + NUM_OBJ * obj_size() == MEMORY_HEAP_SIZE);




    printf("\n\tHa pasado el test satisfactoriamente\n\n");
    return 0;
}
