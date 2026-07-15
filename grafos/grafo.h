#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>

struct Arista {
    int destino;
    int peso;
    struct Arista* siguiente;
};

class Grafo {
private:
    int numVertices;
    struct Arista** adj; 
    bool dirigido;

public:
    Grafo(int vertices, bool esDirigido = false);
    ~Grafo();

    void agregarArista(int u, int v, int peso = 1);
    void mostrarGrafo();
    
    void BFS(int inicio);
    void DFS(int inicio);
    
    void dijkstra(int inicio);
};

#endif 