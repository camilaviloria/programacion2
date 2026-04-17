#include "grafo.h"

int main() {
    Grafo g(5);

    g.agregarArista(0, 1, 4);
    g.agregarArista(0, 2, 2);
    g.agregarArista(2, 1, 1);
    g.agregarArista(1, 3, 5);
    g.agregarArista(2, 3, 8);
    g.agregarArista(3, 4, 3);

    g.BFS(0);
    g.dijkstra(0);

    return 0;
} 