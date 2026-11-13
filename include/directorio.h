#ifndef DIRECTORIO_H
#define DIRECTORIO_H

#include "models.h"
#include <iostream>

// Nodo para el encadenamiento separado en la Tabla Hash
struct NodoHash {
    Jugador dato;
    NodoHash* siguiente;
    NodoHash(const Jugador& j) : dato(j), siguiente(nullptr) {}
};

class SistemaClub {
private:
    NodoHash** tabla; 
    size_t capacidad; // Tamaño primo de cubetas
    size_t cantidad_jugadores;

    // Función Hash Polinomial (DJB2) para strings (cédulas)
    size_t funcionHash(const std::string& clave) const {
        size_t hash = 5381;
        for (char c : clave) {
            hash = ((hash << 5) + hash) + c; 
        }
        return hash % capacidad;
    }

public:
    // Constructor
    SistemaClub(size_t cap = 101) : capacidad(cap), cantidad_jugadores(0) {
        tabla = new NodoHash*[capacidad];
        for (size_t i = 0; i < capacidad; ++i) {
            tabla[i] = nullptr;
        }
    }

    // DESTRUCTOR: Previene Memory Leaks liberando TODA la memoria dinámica
    ~SistemaClub() {
        for (size_t i = 0; i < capacidad; ++i) {
            NodoHash* actual = tabla[i];
            while (actual != nullptr) {
                NodoHash* temp = actual;
                actual = actual->siguiente;
                delete temp; 
            }
        }
        delete[] tabla; 
    }

    // CRUD: Inserción O(1)
    void registrarJugador(const Jugador& j) {
        size_t indice = funcionHash(j.getCedula());
        NodoHash* nuevo = new NodoHash(j);
        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;
        cantidad_jugadores++;
    }

    // CRUD: Búsqueda O(1). Devuelve PUNTERO para poder modificarlo (Update)
    Jugador* buscarJugador(const std::string& cedula) {
        size_t indice = funcionHash(cedula);
        NodoHash* actual = tabla[indice];
        
        while (actual != nullptr) {
            if (actual->dato.getCedula() == cedula) {
                return &(actual->dato); // Devuelve la dirección de memoria exacta
            }
            actual = actual->siguiente;
        }
        return nullptr; // No encontrado
    }
};

#endif // DIRECTORIO_H