/**
 * Ensayo de código de gestión de memoria para MCUs de 8 bits con poca RAM.
 * La idea es proporcionar un mecanismo de asignación estática de memoria en 
 * "Run Time" para facilitar la técnica de encapsulación de datos a través 
 * de estructuras ocultas, sin incurrir en los problemas de incertidumbre
 * y sobrecarga asociados a los sistemas de asignación dinámica como malloc. 
 * 
 * En principio se construye un sistema que no admite devoluciones, lo cual
 * simplifica mucho las cosas y permite mantener el código al mínimo y el
 * tiempo de respuesta constante.
 * 
 * Sobre el sistema anterior se construye un mecanismo de repositorio de 
 * objetos, que permite gestionar dinámicamente estructuras de datos.
 * Se requiere un repositorio diferente por cada tipo de datos que se quiera
 * gestionar dinámicamente. Esto es bastante razonable para firmware.
 */
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "mcu_mem.h"

struct {
    void * block;
    size_t end_index;
    char has_been_initialized;
} memory_heap = {NULL, 0, false};

void memory_heap_setup(void *block, size_t size)
{
    assert(NULL != block);
    assert(0 != size);

    if( !memory_heap.has_been_initialized ) {        
        memory_heap.block = block;
        memory_heap.end_index = size;
        memory_heap.has_been_initialized = true;
    }
}

void* memory_static_alloc(size_t size)
{
    if(size <= memory_heap.end_index) {
        memory_heap.end_index -= size;
        return memory_heap.block + memory_heap.end_index;
    }
    return NULL;
}

size_t memory_info(void)
{
    return memory_heap.end_index;
}


