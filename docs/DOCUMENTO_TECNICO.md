# Documento Técnico: Sistema Integral de Gestión Deportiva y Táctica - Fútbol
**Autor:** Edmundo Gabriele Vitale Dugarte
**Cátedra:** Programación 3 (ULA)

## 1. Resumen del Proyecto
El presente proyecto consiste en el desarrollo de un software backend robusto en C++ diseñado para la administración integral de un club de fútbol. El sistema automatiza el control estadístico, administrativo y médico de los jugadores (desde categorías inferiores hasta profesionales), empleando estructuras de datos dinámicas y algoritmos de alta eficiencia en gestión de memoria.

## 2. Objetivos Claros
*   **Objetivo General:** Desarrollar un sistema de gestión deportiva en C++ que centralice la información de los atletas mediante estructuras de datos no lineales, asegurando tiempos de respuesta óptimos (O(1)).
*   **Objetivos Específicos:**
    *   Diseñar el modelado de clases de la entidad Jugador mediante POO.
    *   Implementar un motor de búsqueda instantáneo basado en Tablas Hash para el directorio del club.
    *   Desarrollar un "Semáforo Médico y Administrativo" autónomo que valide la elegibilidad del jugador en tiempo real.

## 3. Desarrollo y Avances Semanales

### Semana 1: Arquitectura Base y Motor Hash
*Fecha: Noviembre 2026*

**Aspectos Teóricos y Técnicos Desarrollados:**
1.  **Modelado y Herencia (POO):** Se estableció la jerarquía de clases instanciando `Persona` como clase base y `Jugador` como entidad principal.
2.  **Directorio Hash (O(1)):** Se implementó la clase `SistemaClub` operando como una Tabla Hash con encadenamiento separado. Se utilizó la función polinomial de dispersión **DJB2** para transformar la cédula (string) en un índice numérico uniforme. Se configuró un tamaño de tabla base de 101 (número primo) para minimizar colisiones.
3.  **Gestión de Fugas de Memoria:** La estructura Hash cuenta con un destructor especializado (`~SistemaClub`) que recorre iterativamente las listas de encadenamiento liberando la memoria dinámica (`delete`) al cierre del programa, previniendo *memory leaks*.
4.  **Listas Enlazadas Simples (Historial Médico):** Se integró una TDA de Lista Enlazada Simple propia (`ListaMedica`) acoplada a cada jugador. Las inserciones operan bajo una lógica `insert_first` (O(1)) para colocar los partes médicos recientes en la cabeza de la estructura. 
5.  **Lógica de Negocio (Semáforo):** El método `esConvocable()` evalúa en tiempo real las variables booleanas administrativas (solvencia y COMET) y el estado lógico del nodo en la cabeza del historial médico.