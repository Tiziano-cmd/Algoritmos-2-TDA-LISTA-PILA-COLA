#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {
	void *elementos;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_primero;
	nodo_t *nodo_fin;
	size_t cantidad;
};

struct lista_iterador {
	lista_t *lista;
	nodo_t *nodo_referencia;
};

lista_t *lista_crear()
{
	lista_t *lista = calloc(3, sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	return lista;
}

bool lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL) {
		return false;
	}
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (nodo == NULL) {
		return false;
	}
	nodo->elementos = elemento;
	if (lista->cantidad == 0) {
		lista->nodo_primero = nodo;
		lista->nodo_fin = nodo;
	} else {
		lista->nodo_fin->siguiente = nodo;
		lista->nodo_fin = nodo;
	}
	lista->cantidad++;
	return true;
}

bool lista_insertar_en_posicion(lista_t *lista, int posicion, void *elemento)
{
	if (lista == NULL) {
		return false;
	}
	if (posicion < 0 || (size_t)posicion > lista_tamanio(lista)) {
		return false;
	} else if ((size_t)posicion == lista_tamanio(lista)) {
		bool insertado = lista_insertar(lista, elemento);
		if (!insertado) {
			return false;
		}
		return true;
	}
	nodo_t *nodo_nuevo = calloc(1, sizeof(nodo_t));
	if (nodo_nuevo == NULL) {
		return false;
	}
	nodo_nuevo->elementos = elemento;
	if (posicion == 0) {
		nodo_nuevo->siguiente = lista->nodo_primero;
		lista->nodo_primero = nodo_nuevo;
	}

	else {
		nodo_t *temp = lista->nodo_primero;
		for (int i = 0; i < posicion - 1; i++) {
			temp = temp->siguiente;
		}
		nodo_nuevo->siguiente = temp->siguiente;
		temp->siguiente = nodo_nuevo;
	}
	lista->cantidad++;
	return true;
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista == NULL) {
		return 0;
	}
	return lista->cantidad;
}

void *lista_obtener_elemento(lista_t *lista, int posicion)
{
	if (lista == NULL) {
		return NULL;
	}
	if (lista->cantidad == 0) {
		return NULL;
	} else if (posicion < 0) {
		return NULL;
	}
	nodo_t *aux = lista->nodo_primero;
	for (size_t i = 0; i < lista_tamanio(lista); i++) {
		if (i == (size_t)posicion) {
			return aux->elementos;
		}
		aux = aux->siguiente;
	}
	return NULL;
}

int lista_buscar_posicion(lista_t *lista, void *elemento)
{
	if (lista == NULL) {
		return -1;
	}
	nodo_t *aux = lista->nodo_primero;
	for (size_t i = 0; i < lista_tamanio(lista); i++) {
		if (aux->elementos == elemento) {
			return (int)i;
		}
		aux = aux->siguiente;
	}
	return -1;
}

void *lista_sacar_de_posicion(lista_t *lista, int posicion)
{
	if (lista == NULL) {
		return NULL;
	}
	if (posicion < 0 || (size_t)posicion >= lista_tamanio(lista)) {
		return NULL;
	}
	nodo_t *nodo_actual = lista->nodo_primero;
	void *elemento_obtenido = nodo_actual->elementos;
	if (posicion == 0) {
		lista->nodo_primero = nodo_actual->siguiente;
		free(nodo_actual);
		lista->cantidad--;
		return elemento_obtenido;
	}
	if ((size_t)posicion == lista_tamanio(lista) - 1) {
		while (nodo_actual->siguiente != lista->nodo_fin) {
			nodo_actual = nodo_actual->siguiente;
		}
		lista->nodo_fin = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
		elemento_obtenido = nodo_actual->elementos;
		free(nodo_actual);
		lista->nodo_fin->siguiente = NULL;
		lista->cantidad--;
		return elemento_obtenido;
	}
	nodo_t *nodo_a_eliminar = nodo_actual;
	for (int i = 0; i < posicion - 1; i++) {
		nodo_actual = nodo_actual->siguiente;
	}
	nodo_a_eliminar = nodo_actual->siguiente;
	nodo_actual->siguiente = nodo_a_eliminar->siguiente;
	elemento_obtenido = nodo_a_eliminar->elementos;
	free(nodo_a_eliminar);
	lista->cantidad--;
	return elemento_obtenido;
}

void *lista_sacar_elemento(lista_t *lista, void *elemento)
{
	if (lista == NULL) {
		return NULL;
	}
	int posicion = lista_buscar_posicion(lista, elemento);
	void *elem = lista_sacar_de_posicion(lista, posicion);
	if (posicion != -1 && elem != NULL) {
		return elem;
	}
	return NULL;
}

void *lista_buscar(lista_t *lista, bool (*criterio)(void *, void *),
		   void *contexto)
{
	if (lista == NULL || criterio == NULL) {
		return NULL;
	}
	nodo_t *nodo_temporal = lista->nodo_primero;
	int i = 0;
	while ((size_t)i < lista_tamanio(lista)) {
		if (criterio(nodo_temporal->elementos, contexto)) {
			return nodo_temporal->elementos;
		}
		nodo_temporal = nodo_temporal->siguiente;
		i++;
	}
	return NULL;
}

int lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *contexto)
{
	if (lista == NULL || f == NULL) {
		return 0;
	}
	int llamadas_a_f = 0;
	nodo_t *nodo_aux = lista->nodo_primero;
	int i = 0;
	while ((size_t)i < lista_tamanio(lista)) {
		if (!f(nodo_aux->elementos, contexto)) {
			llamadas_a_f++;
			return llamadas_a_f;
		}
		nodo_aux = nodo_aux->siguiente;
		llamadas_a_f++;
		i++;
	}
	return llamadas_a_f;
}

void lista_destruir(lista_t *lista)
{
	if (lista == NULL) {
		return;
	}
	nodo_t *aux = lista->nodo_primero;
	while (aux != NULL) {
		nodo_t *temp = aux;
		aux = aux->siguiente;
		free(temp);
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL) {
		return NULL;
	}
	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (iterador == NULL) {
		return NULL;
	}
	iterador->lista = lista;
	iterador->nodo_referencia = lista->nodo_primero;
	return iterador;
}

bool lista_iterador_quedan_elementos_por_recorrer(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return false;
	}
	return iterador->nodo_referencia != NULL;
}

void lista_iterador_proxima_iteracion(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return;
	}
	if (!lista_iterador_quedan_elementos_por_recorrer(iterador)) {
		return;
	}
	iterador->nodo_referencia = iterador->nodo_referencia->siguiente;
}

void *lista_iterador_obtener_elemento(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return NULL;
	}
	if (!lista_iterador_quedan_elementos_por_recorrer(iterador)) {
		return NULL;
	}
	return iterador->nodo_referencia->elementos;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		return;
	}
	free(iterador);
}
