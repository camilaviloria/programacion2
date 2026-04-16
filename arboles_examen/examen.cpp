#include <iostream>
#include <cmath>

using namespace std;

struct Nodo {
    int dato;
    Nodo *izq, *der;
    Nodo(int v) : dato(v), izq(nullptr), der(nullptr) {}
};

Nodo* construirArbol(int* valores, int n, int i) {
    if (i >= n) return nullptr;
    
    Nodo* raiz = new Nodo(valores[i]);
    raiz->izq = construirArbol(valores, n, 2 * i + 1);
    raiz->der = construirArbol(valores, n, 2 * i + 2);
    
    return raiz;
}

void encontrarCaminos(Nodo* nodo, int* caminoActual, int nivel, 
                      int** todosCaminos, int* todasSumas, int* tamaniosCaminos, int& contadorCaminos) {
    if (!nodo) return;

    caminoActual[nivel] = nodo->dato;

    if (!nodo->izq && !nodo->der) {
        int suma = 0;
        todosCaminos[contadorCaminos] = new int[nivel + 1];
        
        for (int i = 0; i <= nivel; i++) {
            todosCaminos[contadorCaminos][i] = caminoActual[i];
            suma += caminoActual[i];
        }
        
        todasSumas[contadorCaminos] = suma;
        tamaniosCaminos[contadorCaminos] = nivel + 1;
        contadorCaminos++;
    } else {
        encontrarCaminos(nodo->izq, caminoActual, nivel + 1, todosCaminos, todasSumas, tamaniosCaminos, contadorCaminos);
        encontrarCaminos(nodo->der, caminoActual, nivel + 1, todosCaminos, todasSumas, tamaniosCaminos, contadorCaminos);
    }
}

int main() {
    int n;
    cout << "cuántos nodos tendrá el árbol?: ";
    cin >> n;

    if (n <= 0) return 0;

    int* valores = new int[n];
    for (int i = 0; i < n; i++) {
        cout << "valor nodo " << i + 1 << ": ";
        cin >> valores[i];
    }

    Nodo* raiz = construirArbol(valores, n, 0);

    int** todosCaminos = new int*[n];
    int* todasSumas = new int[n];
    int* tamaniosCaminos = new int[n];
    int* caminoAuxiliar = new int[n]; 
    int contadorCaminos = 0;

    encontrarCaminos(raiz, caminoAuxiliar, 0, todosCaminos, todasSumas, tamaniosCaminos, contadorCaminos);

    if (contadorCaminos > 0) {
        double sumaTotal = 0;
        for (int i = 0; i < contadorCaminos; i++) {
            sumaTotal += todasSumas[i];
        }
        double promedio = sumaTotal / contadorCaminos;
        cout << "\npromedio de las sumas: " << promedio << endl;

        int indiceCercano = 0;
        double minDif = abs(todasSumas[0] - promedio);

        for (int i = 1; i < contadorCaminos; i++) {
            double difActual = abs(todasSumas[i] - promedio);
            if (difActual < minDif) {
                minDif = difActual;
                indiceCercano = i;
            }
        }

        cout << "camino más cercano (Suma = " << todasSumas[indiceCercano] << "): ";
        for (int i = 0; i < tamaniosCaminos[indiceCercano]; i++) {
            cout << todosCaminos[indiceCercano][i] << (i == tamaniosCaminos[indiceCercano] - 1 ? "" : " -> ");
        }
        cout << endl;
    }

    delete[] valores;
    delete[] todasSumas;
    delete[] tamaniosCaminos;
    delete[] caminoAuxiliar;
    for(int i = 0; i < contadorCaminos; i++) delete[] todosCaminos[i];
    delete[] todosCaminos;

    return 0;
}