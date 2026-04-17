#include "grafo.h" 

Grafo::Grafo(int vertices, bool esDirigido) {
    this->numVertices = vertices;
    this->dirigido = esDirigido;
    adj = (struct Arista**)malloc(vertices * sizeof(struct Arista*));
    for (int i = 0; i < vertices; i++) adj[i] = NULL;
}

Grafo::~Grafo() {
    for (int i = 0; i < numVertices; i++) {
        struct Arista* actual = adj[i];
        while (actual) {
            struct Arista* temp = actual;
            actual = actual->siguiente;
            free(temp);
        }
    }
    free(adj);
}

void Grafo::agregarArista(int u, int v, int peso) {
    struct Arista* nueva = (struct Arista*)malloc(sizeof(struct Arista));
    nueva->destino = v;
    nueva->peso = peso;
    nueva->siguiente = adj[u];
    adj[u] = nueva;

    if (!dirigido) {
        struct Arista* espejo = (struct Arista*)malloc(sizeof(struct Arista));
        espejo->destino = u;
        espejo->peso = peso;
        espejo->siguiente = adj[v];
        adj[v] = espejo;
    }
}

void Grafo::BFS(int inicio) {
    bool* visitado = (bool*)calloc(numVertices, sizeof(bool));
    int* cola = (int*)malloc(numVertices * sizeof(int));
    int frente = 0, final = 0;

    visitado[inicio] = true;
    cola[final++] = inicio;

    printf("\nRecorrido BFS: ");
    while (frente < final) {
        int u = cola[frente++];
        printf("%d ", u);

        struct Arista* temp = adj[u];
        while (temp) {
            if (!visitado[temp->destino]) {
                visitado[temp->destino] = true;
                cola[final++] = temp->destino;
            }
            temp = temp->siguiente;
        }
    }
    printf("\n");
    free(visitado); free(cola);
}

void Grafo::dijkstra(int inicio) {
    int* dist = (int*)malloc(numVertices * sizeof(int));
    bool* visitado = (bool*)calloc(numVertices, sizeof(bool));
    
    for (int i = 0; i < numVertices; i++) dist[i] = 2147483647; // Simular infinito
    dist[inicio] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int u = -1;
        for (int j = 0; j < numVertices; j++)
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) u = j;

        if (u == -1 || dist[u] == 2147483647) break;
        visitado[u] = true;

        struct Arista* temp = adj[u];
        while (temp) {
            if (dist[u] + temp->peso < dist[temp->destino])
                dist[temp->destino] = dist[u] + temp->peso;
            temp = temp->siguiente;
        }
    }

    printf("\ndistancias minimas (Dijkstra) desde %d:\n", inicio);
    for (int i = 0; i < numVertices; i++) 
        printf("hacia %d: %d\n", i, dist[i]);

    free(dist); free(visitado);
} 