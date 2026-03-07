#include "lista.h"
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>

cola_t *cola_crear()
{
	return (cola_t *)lista_crear();
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	return lista_insertar((lista_t *)cola, elemento);
}

void *cola_desencolar(cola_t *cola)
{
	return lista_sacar_de_posicion((lista_t *)cola, 0);
}

bool cola_vacia(cola_t *cola)
{
	return cola_tamanio(cola) == 0;
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio((lista_t *)cola);
}

void *cola_frente(cola_t *cola)
{
	if (cola_vacia(cola)) {
		return NULL;
	}
	return lista_obtener_elemento((lista_t *)cola, 0);
}

void cola_destruir(cola_t *cola)
{
	lista_destruir((lista_t *)cola);
}