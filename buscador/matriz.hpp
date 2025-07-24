#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>  
#include <iomanip>   
#include <stdexcept> 

class Matriz {
private:
    double** datos; 
    int filas;      
    int columnas;  

    void copiarDatos(const Matriz& otra);
    void liberarDatos();                  
    double calcularDeterminanteCofactores(double** subMatriz, int n) const;

public:

    Matriz();
    Matriz(int f, int c);
    Matriz(const Matriz& otra);
    Matriz& operator=(const Matriz& otra);
    ~Matriz();
    void llenarMatriz() const;
    void mostrarMatriz() const;
    Matriz transpuesta()const;
    double determinante()const;
    Matriz suma(const Matriz& otra) const;
    Matriz multiplicacion(const Matriz& otra)const;
    bool esIgual(const Matriz& otra)const;
};

#endif 
