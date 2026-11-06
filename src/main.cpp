#include <iostream>
#include <limits>
#include <cstdlib>
#include "../include/models.h"

// Limpieza de pantalla multiplataforma
void limpiarPantalla() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Lector de opciones blindado contra letras y símbolos
int leerEnteroSeguro(const std::string& mensaje, int min, int max) {
    int valor;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> valor && valor >= min && valor <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valor;
        }
        std::cout << "\n[!] Error: Opcion invalida. Ingrese un numero entre " << min << " y " << max << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void pausarYLimpiar() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.get();
    limpiarPantalla();
}

int main() {
    limpiarPantalla();
    int opcion = 0;

    // Instancias de prueba
    Equipo equipoTest("El Vigia FC", "Sub-15");
    Jugador jugadorTest("V-30123456", "Carlos Rojas", 20110514, "El Vigia FC", "Sub-15", 10);

    while (opcion != 3) {
        std::cout << "========================================\n";
        std::cout << " SISTEMA DE GESTION DEPORTIVA Y TACTICA \n";
        std::cout << "========================================\n";
        std::cout << "1. Ver estado del Equipo\n";
        std::cout << "2. Registrar lesion al Jugador y ver estado\n";
        std::cout << "3. Salir\n";
        std::cout << "========================================\n";
        
        opcion = leerEnteroSeguro("Seleccione una opcion: ", 1, 3);
        limpiarPantalla();

        if (opcion == 1) {
            std::cout << "--- ESTADO DEL EQUIPO ---\n";
            std::cout << "Equipo: " << equipoTest.getIdEquipo() << "\n";
            std::cout << "Puntos actuales: " << equipoTest.getPuntos() << "\n";
            std::cout << "Diferencial goles: " << equipoTest.getDiferencial() << "\n";
            pausarYLimpiar();
        } 
        else if (opcion == 2) {
            std::cout << "--- PRUEBA MEDICA ---\n";
            std::cout << jugadorTest.getRol() << "\n";
            std::cout << "Estado inicial (Apto): " << (jugadorTest.estaAptoParaJugar() ? "SI" : "NO") << "\n";
            
            std::cout << "\n[Registrando Esguince de Tobillo...]\n";
            EventoMedico lesion(1, "2026-11-05", "Esguince", "Tobillo Derecho", 15);
            jugadorTest.registrarLesion(lesion);
            
            std::cout << "Nuevo estado (Apto): " << (jugadorTest.estaAptoParaJugar() ? "SI" : "NO") << " (Bloqueado para Pizarra)\n";
            pausarYLimpiar();
        }
    }

    std::cout << "Saliendo del sistema...\n";
    return 0;
}