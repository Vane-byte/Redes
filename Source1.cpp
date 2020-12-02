#include<iostream>
#include<stdio.h>
#include<ctime>
#include <iomanip>

int longi ;
int verti;
clock_t t0=-1, t1;

struct arista {
	int vorigen;
	int vdestino;
	int peso;

	arista* sgtarista=nullptr;
};
struct vertice {
	int nombre;
	int aristas=0;
	int distancia = 999999;
	int previo = -1;

	arista* parista = nullptr;
	vertice* sgtvertice = nullptr;
};
struct grafo {
	int vertices;
	int aristas;

	vertice* pvertice = nullptr;
};

vertice* Devolververtice(grafo* grafito, int num) {		//Devuelve el vertice segun el numero indicado
	vertice* ptrvertice = grafito->pvertice;
	for (int i = 0; i < num; i++) {
		ptrvertice = ptrvertice->sgtvertice;
	}
	return ptrvertice;
}
bool relajacion(grafo* grafito, vertice* vert) {
	int cantidad = vert->aristas;
	arista* ptrarista = vert->parista;
	bool cambios = false;
	for (int i = 0; i < cantidad; i++) {		//Se evalua cada arista de un vertice
		vertice* destino = Devolververtice(grafito, ptrarista->vdestino); //Se obtiene el vertice destino del nodo en cuestion
		if (ptrarista->peso + vert->distancia < destino->distancia) { //si la nueva distancia calculada a traves de la arista que coecta los vértices es 
			destino->previo = ptrarista->vorigen+1;						//menor a la distancia menor del vertice destino, se actualizaran los valores correspondientes
			destino->distancia = ptrarista->peso + vert->distancia;
			cambios = true;			//Se efectuó un cambio
		}
		
		ptrarista = ptrarista->sgtarista;
		
	}
	return cambios;
}
void creartabla(grafo* grafito) {		//Encargada de imprimir los resutados obtenidos
	vertice* ptrvertice = grafito->pvertice;
	std::cout << "IDK" << "\tDIST" << "\tPREVIO" << std::endl;
	for (int i = 0; i < longi; i++) {
		std::cout << ptrvertice->nombre << "\t" << ptrvertice->distancia<< "\t" << ptrvertice->previo<< std::endl;
		ptrvertice = ptrvertice->sgtvertice;
	}
}
void iteraciones(grafo* grafito,vertice *vert) {
	bool cambios = true;
	int cont = 0;		//cuenta las veces que se ejecuta la operacion
	
	while (cambios != false and cont<longi-1) { //el while se detendrá cuando no se efectuen cambios en alguna iteracion o cuando se efectuan nodos-1 veces
		cambios=false; 
		for (int i = 0; i < longi; i++) {		//recorre cada nodo
			if (vert->distancia < 999999)		//se conoce como llegar a dicho nodo
				cambios = cambios + relajacion(grafito, vert);		//Basta que se actualice la distancia de algun nodo para que cambios se vuelca true
			vert = vert->sgtvertice;
			if (vert == nullptr) {	//Una vez que se llega al ultimo nodo, se vuelve a inciar con el primero
				vert = grafito->pvertice;
			}
		}
		cont++;
	}
}

void  imprimiraristas(grafo* grafito) {	//imprime las aristas salientes de cada vertice
	vertice* ptrvertice = grafito->pvertice;
	arista* ptrarista = nullptr;
	//Imprime informacion genenral del grafo
	std::cout << "numero de vertices del grafo:" << grafito->vertices << std::endl;
	std::cout << "numero de aristas del grafo:" << grafito->aristas << std::endl;
	std::cout << "ARISTAS" << std::endl;
	for (int i = 0; i < longi; i++) {	//recorre cada vertice
		int naristas = ptrvertice->aristas;
		ptrarista = ptrvertice->parista;
		std::cout << "Aristas de vertice" << i + 1 << ": " << std::endl;
		for (int j = 0; j < naristas; j++) {	//recorre cada arista de un vertice
			std::cout << j+1<< ": "<< ptrarista->vorigen + 1 << "--" << ptrarista->peso << "-->" << ptrarista->vdestino + 1 << std::endl;
			ptrarista = ptrarista->sgtarista;
		}
		ptrvertice = ptrvertice->sgtvertice;	
	}

}

grafo* RecibirMatriz() {
	int valor;
	int cont = 0;

	grafo* grafito = new grafo();		//Se crea el grafo que contendrá los vértices
	arista* antarista = nullptr;
	vertice* antvertice = nullptr;

	grafito->vertices = longi;
	
	std::cout << "Ingresar matriz:";
	
	for (int i = 0; i < longi; i++) {		//Para evaluar cada nodo
		vertice* ptrvertice = new vertice();
		ptrvertice->nombre = i + 1;
		int acont = 0;
		if (i == verti)
			ptrvertice->distancia = 0;			//Al vertice a partir del cual se busca las conexiones con los otros se le pone de distancia como 0

		for (int j = 0; j < longi; j++) {		//Para evaluar la relacion de un nodo con los demás
			
			std::cin >> valor;
			if (valor != 0) {
				arista* ptrarista = new arista();
				ptrarista->peso = valor;
				ptrarista->vdestino = j;
				ptrarista->vorigen = i;
				
				if (ptrvertice->parista == nullptr) 
					ptrvertice->parista = ptrarista;
				
				else 
					antarista->sgtarista = ptrarista;
				antarista = ptrarista;
				cont++;				//Cuenta la cantidad total de aristas
				acont++;			//Cuenta la cantidad de aristas de cada nodo
			}
		}
		if (grafito->pvertice == nullptr)
			grafito->pvertice = ptrvertice;
		else
			antvertice->sgtvertice = ptrvertice;
		ptrvertice->aristas = acont;			//a cada vertice se le asigna el numero de aristas a las que puede llegar
		antvertice = ptrvertice;
	}
	t0 = clock();
	grafito->aristas = cont;
	return grafito;
	
}
int main() {
	std::cout << "Ingresar cantidad de nodos: ";
	std::cin >> longi;

	std::cout << "Ingresar vertice de partida (primer vertice = 0): ";
	std::cin >> verti;
	
	grafo* grafito= RecibirMatriz();
	
	//imprimiraristas(grafito);						//no es relevante para la ejecucion del codigo, sirve para mostrar aristas
	iteraciones(grafito, Devolververtice(grafito,verti));
	
	creartabla(grafito);
	t1 = clock();						//Toma el tiempo de finalizacion de ejecucion 
	double tiempo = double(t1 - t0) / double(CLOCKS_PER_SEC);
	std::cout << "Tiempo transcurrido: " << std::fixed << tiempo << std::setprecision(5);			//muestra el tiempo que demoro
}
