# Sistema Integral de Gestión Deportiva y Táctica (Fútbol) 

## Resumen del Proyecto
El proyecto consiste en el desarrollo de un software "Offline-First" programado en C++, diseñado para centralizar y optimizar la gestión operativa, médica y táctica de academias y clubes de fútbol (categorías Sub-12 a Sub-16). El sistema usara estructuras de datos (Árboles AVL, Mapas Hash, Listas Enlazadas y Pilas) implementadas con el framework DESIGNAR.

## Requerimientos y Dependencias
*   **Compilador:** MinGW-w64 (GCC) para Windows / GCC para Linux.
*   **Gestor de compilación:** Make o CMake.
*   **Estructura de Datos Obligatoria:** Framework `DESIGNAR`.
*   **Librería Gráfica:** SFML o Raylib (para la pizarra táctica 2D).

## Instrucciones de Compilación (Paso a Paso)

### Para Windows (Instrucciones detalladas):
1. Instalar un entorno de compilación C++ como **MinGW-w64** y configurar las variables de entorno en el sistema.
2. Abrir la terminal en la carpeta raíz del proyecto.
3. Compilar los archivos fuente ejecutando el comando correspondiente (ejemplo con g++):
   ```bash
   g++ src/main.cpp -o sistema_futbol.exe -Iinclude
