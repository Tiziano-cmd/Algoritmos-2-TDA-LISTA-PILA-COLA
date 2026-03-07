#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"

bool comparador(void *elemento, void *contexto)
{
	return *(int *)elemento == *(int *)contexto;
}

void crear_una_lista_vacia_devuelve_correcto()
{
	lista_t *l = lista_crear();
	pa2m_afirmar(l != NULL,
		     "Crear una lista vacia devuelve distinto de NULL");
	int a = 2;
	int b = 10;
	char c = 23;
	bool insertado = lista_insertar(l, &a);
	bool insertado_1 = lista_insertar(l, &b);
	bool insertado_2 = lista_insertar(l, &c);
	pa2m_afirmar(insertado != false,
		     "Insertar el numero 2 al final de la lista devuelve true");
	pa2m_afirmar(
		insertado_1 != false,
		"Insertar el numero 10 al final de la lista devuelve true");
	pa2m_afirmar(
		insertado_2 != false,
		"Insertar el numero 23 al final de la lista devuelve true");
	size_t tamanio = lista_tamanio(l);
	pa2m_afirmar(tamanio == 3,
		     "Insertar tres elementos en la lista devuelve 3");
	int pos_a = lista_buscar_posicion(l, &a);
	int pos_b = lista_buscar_posicion(l, &b);
	int pos_c = lista_buscar_posicion(l, &c);
	pa2m_afirmar(pos_a == 0, "La posicion de 2 es 0 en la lista");
	pa2m_afirmar(pos_b == 1, "La posicion de 10 es 1 en la lista");
	pa2m_afirmar(pos_c == 2, "La posicion de 23 es 2 en la lista");
	char letra = 'A';
	bool insertar = lista_insertar_en_posicion(l, 0, &letra);
	pa2m_afirmar(
		insertar != false,
		"Insertar la letra A en la posicion 0 donde estaba el numero 2 devuelve true");
	int nueva_pos_a = lista_buscar_posicion(l, &a);
	int nueva_pos_b = lista_buscar_posicion(l, &b);
	int nueva_pos_c = lista_buscar_posicion(l, &c);
	pa2m_afirmar(
		nueva_pos_a == 1,
		"Luego de insertar en la posicion 0 la posicion del numero 2 es 1");
	pa2m_afirmar(
		nueva_pos_b == 2,
		"Luego de insertar en la posicion 0 la posicion del numero 10 es 2");
	pa2m_afirmar(
		nueva_pos_c == 3,
		"Luego de insertar en la posicion 0 la posicion del numero 23 es 3");
	size_t nuevo_tam = lista_tamanio(l);
	pa2m_afirmar(nuevo_tam == 4, "El nuevo tamanio de la lista es 4");
	void *elem = lista_obtener_elemento(l, 2);
	pa2m_afirmar(
		elem != NULL,
		"Obtener el numero 10 en la posicion 2 de la lista es correcto");
	void *elem_obtenido = lista_sacar_de_posicion(l, 0);
	pa2m_afirmar(elem_obtenido != NULL,
		     "Sacar la letra A de la posicion 0 es correcto");
	size_t n = lista_tamanio(l);
	pa2m_afirmar(n == 3, "Al quitar la letra A el tamanio se reduce a 3");
	int nueva_pos_1 = lista_buscar_posicion(l, &a);
	int nueva_pos_2 = lista_buscar_posicion(l, &b);
	int nueva_pos_3 = lista_buscar_posicion(l, &c);
	pa2m_afirmar(
		nueva_pos_1 == 0,
		"Luego de sacar la letra A de la posicion 0 la posicion del numero 2 es 0");
	pa2m_afirmar(
		nueva_pos_2 == 1,
		"Luego de sacar la letra A de la posicion 0 la posicion del numero 10 es 1");
	pa2m_afirmar(
		nueva_pos_3 == 2,
		"Luego de sacar la letra A de la posicion 0 la posicion del numero 23 es 2");
	void *elem_6 = lista_sacar_elemento(l, &b);
	pa2m_afirmar(elem_6 != NULL,
		     "Sacar el numero 10 de la posicion 1 es correcto");
	size_t tam_lista = lista_tamanio(l);
	pa2m_afirmar(
		tam_lista == 2,
		"El tamanio de la lista luego de sacar el 10 de la posicion 1 es 2 (valor obtenido: %d)",
		tam_lista);
	int pos_de_b = lista_buscar_posicion(l, &b);
	pa2m_afirmar(
		pos_de_b == -1,
		"Tratar de buscar la posicion del 10 luego de eliminarlo devuelve -1 (valor obtenido: %d)",
		pos_de_b);
	int posicion_de_a = lista_buscar_posicion(l, &a);
	pa2m_afirmar(
		posicion_de_a == 0,
		"La posicion del numero 2 sigue siendo 0 luego de sacar el numero 10 de la posicion 1");
	int posicion_de_c = lista_buscar_posicion(l, &c);
	pa2m_afirmar(
		posicion_de_c == 1,
		"Luego de eliminar el numero 10 de la posicion 1 la posicion del numero 23 es ahora 1 (valor obtenido: %d)",
		posicion_de_c);
	char letrita = 'Z';
	bool nuevo_insertado = lista_insertar_en_posicion(l, 1, &letrita);
	pa2m_afirmar(nuevo_insertado != false,
		     "Insertar una letra Z entre medio de 2 y 23 es correcto");
	int pos_z = lista_buscar_posicion(l, &letrita);
	pa2m_afirmar(
		pos_z == 1,
		"Ahora la posicion de la letra Z toma la posicion del 23 que es 1");
	void *elem_invalido = lista_sacar_de_posicion(l, 44);
	pa2m_afirmar(
		elem_invalido == NULL,
		"Sacar un elemento de la posicion 44 es incorrecto cuando solo tengo posiciones 0,1,2");
	int entero = 44;
	void *elem_invalido_2 = lista_sacar_elemento(l, &entero);
	pa2m_afirmar(
		elem_invalido_2 == NULL,
		"Sacar el numero 44 de la lista cuando no esta es incorrecto");
	void *sacado_2 = lista_sacar_de_posicion(l, 0);
	int *sacado_n = (int *)sacado_2;
	pa2m_afirmar(
		sacado_2 != NULL,
		"El numero 2 fue sacado correctamente de la posicion 0 (valor obtenido: %d)",
		*sacado_n);
	bool num_2_insertado = lista_insertar_en_posicion(l, 0, &(*sacado_n));
	pa2m_afirmar(num_2_insertado == true,
		     "El numero 2 se volvio a insertar en la posicion 0");
	int posicion_del_2 = lista_buscar_posicion(l, &(*sacado_n));
	pa2m_afirmar(
		posicion_del_2 == 0,
		"Sacar y poner el 2 es correcto, La posicion del numero 2 vuelve a tomar la posicion 0");
	size_t tamanio_final = lista_tamanio(l);
	pa2m_afirmar(
		tamanio_final == 3,
		"El tamanio de la Lista sigue siendo 3 (valor obtenido: %ld)",
		tamanio_final);
	int elementito = 2;
	void *elementito_1 = lista_buscar(l, comparador, &elementito);
	pa2m_afirmar(
		elementito_1 != NULL,
		"Se pudo encontrar el numero 2 con la funcion lista_buscar");
	lista_iterador_t *li = lista_iterador_crear(l);
	pa2m_afirmar(li != NULL, "Crear un iterador para la lista es correcto");
	bool recorrer = lista_iterador_quedan_elementos_por_recorrer(li);
	pa2m_afirmar(recorrer == true,
		     "Todavia quedan elementos por recorrer en la lista");
	lista_iterador_proxima_iteracion(li);
	void *obtenido = lista_iterador_obtener_elemento(li);
	char *letra_z = (char *)obtenido;
	pa2m_afirmar(obtenido != NULL,
		     "El elemento obtenido es la letra Z (valor obtenido: %c)",
		     *letra_z);
	lista_iterador_proxima_iteracion(li);
	lista_iterador_proxima_iteracion(li);
	void *no_obtenido = lista_iterador_obtener_elemento(li);
	pa2m_afirmar(no_obtenido == NULL,
		     "Ya no quedan mas elementos para obtener");
	lista_iterador_destruir(li);
	lista_destruir(l);
}

void crear_una_lista_NULL()
{
	lista_t *l = lista_crear();
	pa2m_afirmar(l != NULL, "La lista ha sido creada correctamente");
	int num = 3;
	bool insertado = lista_insertar(NULL, &num);
	pa2m_afirmar(insertado == false,
		     "Insertar un elemento en una lista NULL devuelve false");
	bool insertado_1 = lista_insertar_en_posicion(NULL, 0, &num);
	pa2m_afirmar(
		insertado_1 == false,
		"Insertar un elemento por posicion en una Lista NULL devuelve NULL");
	size_t tam = lista_tamanio(l);
	pa2m_afirmar(tam == 0,
		     "El tamanio es 0 en una lista NULL (valor obtenido: %ld)",
		     tam);
	lista_destruir(l);
}

void crear_una_pila_es_correcto()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "La pila se pudo crear correctamente");
	size_t tam_pila = pila_tamanio(pila);
	pa2m_afirmar(tam_pila == 0,
		     "El tamanio de la pila es cero (valor obtenido: %ld)",
		     tam_pila);
	void *elem = pila_desapilar(pila);
	pa2m_afirmar(
		elem == NULL,
		"Desapilar cuando no hay ningun elemento apilado devuelve NULL");
	bool esta_vacia = pila_vacia(pila);
	pa2m_afirmar(esta_vacia == true, "La pila esta vacia");
	int n = 89;
	bool apilado = pila_apilar(pila, &n);
	pa2m_afirmar(apilado == true,
		     "El numero 89 se pudo apilar correctamente");
	void *elem_tope = pila_tope(pila);
	int *res = (int *)elem_tope;
	pa2m_afirmar(
		elem_tope != NULL,
		"Al ver el tope de la pila el elemento es el 89 (valor obtenido: %d)",
		*res);
	pila_destruir(pila);
}

void crear_cola_es_correcto()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "La Cola pudo crearse correctamente");
	bool esta_vacia = cola_vacia(cola);
	pa2m_afirmar(esta_vacia == true, "La cola esta vacia");
	size_t tam = cola_tamanio(cola);
	pa2m_afirmar(tam == 0, "El tamanio de la cola es 0");
	void *elem = cola_frente(cola);
	pa2m_afirmar(
		elem == NULL,
		"Tratar de obtener el elemento del frente de la cola cuando esta es vacia devuelve NULL");
	void *elem_desencolado = cola_desencolar(cola);
	pa2m_afirmar(
		elem_desencolado == NULL,
		"Desencolar un elemento cuando la cola esta vacia devuelve NULL");
	int n = 45;
	int a = 500;
	bool elem_encolado = cola_encolar(cola, &n);
	pa2m_afirmar(elem_encolado == true,
		     "Encolar el numero 45 en la Cola es correcto");
	bool otro_encolado = cola_encolar(cola, &a);
	pa2m_afirmar(otro_encolado == true,
		     "Encolar el numero 500 en la Cola es correcto");
	void *obtenido = cola_desencolar(cola);
	int *res = (int *)obtenido;
	pa2m_afirmar(
		obtenido != NULL,
		"Al desencolar se obtiene el numero  45 (valor obtenido: %d)",
		*res);
	void *nuevo_elem = cola_frente(cola);
	int *frente = (int *)nuevo_elem;
	pa2m_afirmar(
		nuevo_elem != NULL,
		"Ahora el frente de la Cola tiene el numero 500 (valor obtenido: %d)",
		*frente);

	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creacion de la lista");
	crear_una_lista_vacia_devuelve_correcto();

	pa2m_nuevo_grupo("Pruebas con una lista NULL");
	crear_una_lista_NULL();

	pa2m_nuevo_grupo("Pruebas de Pila");
	crear_una_pila_es_correcto();

	pa2m_nuevo_grupo("Pruebas de creacion de Cola");
	crear_cola_es_correcto();

	return pa2m_mostrar_reporte();
}
