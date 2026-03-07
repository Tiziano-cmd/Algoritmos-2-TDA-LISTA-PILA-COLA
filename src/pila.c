#include "lista.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

pila_t *pila_crear()
{
	return (pila_t *)(lista_crear());
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	return lista_insertar_en_posicion((lista_t *)pila, 0, elemento);
}

size_t pila_tamanio(pila_t *pila)
{
	return lista_tamanio((lista_t *)pila);
}

void *pila_desapilar(pila_t *pila)
{
	return lista_sacar_de_posicion((lista_t *)pila, 0);
}

bool pila_vacia(pila_t *pila)
{
	return pila_tamanio(pila) == 0;
}

void *pila_tope(pila_t *pila)
{
	if (pila_vacia(pila)) {
		return NULL;
	}
	return lista_obtener_elemento((lista_t *)pila, 0);
}

void pila_destruir(pila_t *pila)
{
	lista_destruir((lista_t *)pila);
}