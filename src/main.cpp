#include <iostream>
#include <string>
#include <limits>
#include "../include/models.h"
#include "../include/directorio.h"

// Limpieza de pantalla multiplataforma
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// Blindaje contra cuelgues del teclado (Si escriben letras en vez de números)
int leerEnteroSeguro() {
    int valor;
    while (!(std::cin >> valor)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Ingrese un numero valido: ";
    }
    return valor;
}

void pausar() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main() {
    // Instanciamos la Tabla Hash en RAM (101 cubetas)
    SistemaClub gestorGV(101); 
    int opcion = 0;

    while (opcion != 5) {
        system(CLEAR);
        std::cout << "=========================================\n";
        std::cout << " SISTEMA DE GESTION DEPORTIVA 'GV' \n";
        std::cout << "=========================================\n";
        std::cout << "1. Registrar Nuevo Jugador\n";
        std::cout << "2. Consultar Ficha de Jugador (Busqueda O(1))\n";
        std::cout << "3. Registrar Evento Medico (Lesion)\n";
        std::cout << "4. Registrar Asistencia a Entrenamiento\n";
        std::cout << "5. Salir\n";
        std::cout << "Opcion: ";
        opcion = leerEnteroSeguro();

        if (opcion == 1) {
            system(CLEAR);
            std::string ced, nom, pos, cat;
            int dor;
            std::cout << "Cedula/ID (Ej. 123): "; std::cin >> ced;
            std::cout << "Nombre Completo: "; std::cin.ignore(); std::getline(std::cin, nom);
            std::cout << "Posicion: "; std::cin >> pos;
            std::cout << "Dorsal: "; dor = leerEnteroSeguro();
            std::cout << "Categoria (Ej. Sub-15): "; std::cin >> cat;
            
            gestorGV.registrarJugador(Jugador(ced, nom, 20100101, pos, dor, cat));
            std::cout << "\n[+] Jugador registrado exitosamente.\n";
            pausar();
        }
        else if (opcion == 2) {
            system(CLEAR);
            std::string ced;
            std::cout << "Ingrese Cedula a buscar: "; std::cin >> ced;
            
            // Busca al jugador instantáneamente y lo imprime si existe
            Jugador* j = gestorGV.buscarJugador(ced);
            if (j) j->imprimirFicha();
            else std::cout << "\n[-] Error: Jugador no encontrado en la base de datos.\n";
            pausar();
        }
        else if (opcion == 3) {
            system(CLEAR);
            std::string ced;
            std::cout << "Cedula del jugador lesionado: "; std::cin >> ced;
            
            Jugador* j = gestorGV.buscarJugador(ced);
            if (j) {
                std::string desc;
                std::cout << "Descripcion de la lesion: "; std::cin.ignore(); std::getline(std::cin, desc);
                
                // Usamos la lista enlazada artesanal (insert_first)
                EventoMedico nuevaLesion("20261112", "Lesion", desc, false);
                j->historial_medico.insert_first(nuevaLesion);
                
                std::cout << "\n[!] Lesion registrada. El semaforo bloqueador se ha activado.\n";
            } else {
                std::cout << "\n[-] Error: Jugador no encontrado.\n";
            }
            pausar();
        }
        else if (opcion == 4) {
             system(CLEAR);
            std::string ced;
            std::cout << "Cedula del jugador: "; std::cin >> ced;
            
            Jugador* j = gestorGV.buscarJugador(ced);
            if (j) {
                int asis;
                std::cout << "Asistio al entrenamiento de hoy? (1 = Si, 0 = No): ";
                asis = leerEnteroSeguro();
                j->registrarAsistencia(asis == 1);
                std::cout << "\n[+] Asistencia procesada. Rendimiento actual: " << j->getPorcentajeAsistencia() << "%\n";
            } else {
                std::cout << "\n[-] Error: Jugador no encontrado.\n";
            }
            pausar();
        }
    }
    
    return 0;
}