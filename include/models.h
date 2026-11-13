#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <fstream>

// ==========================================
// SERIALIZADOR BINARIO (Protección de RAM)
// ==========================================
namespace SerializadorBinario {
    inline void escribirString(std::ofstream& out, const std::string& str) {
        size_t tam = str.size();
        out.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        out.write(str.c_str(), tam);
    }
    
    inline void leerString(std::ifstream& in, std::string& str) {
        size_t tam = 0;
        in.read(reinterpret_cast<char*>(&tam), sizeof(tam));
        str.resize(tam);
        if (tam > 0) in.read(&str[0], tam);
    }
}

// ==========================================
// 1. EVENTO MEDICO
// ==========================================
struct EventoMedico {
    std::string fecha;
    std::string tipo; 
    std::string descripcion;
    bool alta_medica;

    EventoMedico(std::string f = "", std::string t = "", std::string d = "", bool alta = true) 
        : fecha(f), tipo(t), descripcion(d), alta_medica(alta) {}
};

// ==========================================
// 2. LISTA ENLAZADA ARTESANAL (Reemplazo Temporal)
// ==========================================
struct NodoMedico {
    EventoMedico evento;
    NodoMedico* siguiente;
    NodoMedico(const EventoMedico& e) : evento(e), siguiente(nullptr) {}
};

class ListaMedica {
private:
    NodoMedico* cabeza;
public:
    ListaMedica() : cabeza(nullptr) {}
    ~ListaMedica() { limpiar(); }

    ListaMedica(const ListaMedica& otra) : cabeza(nullptr) {
        if (!otra.cabeza) return;
        cabeza = new NodoMedico(otra.cabeza->evento);
        NodoMedico* actual = cabeza;
        NodoMedico* actualOtra = otra.cabeza->siguiente;
        while (actualOtra) {
            actual->siguiente = new NodoMedico(actualOtra->evento);
            actual = actual->siguiente;
            actualOtra = actualOtra->siguiente;
        }
    }

    ListaMedica& operator=(const ListaMedica& otra) {
        if (this != &otra) {
            limpiar();
            ListaMedica temp(otra);
            cabeza = temp.cabeza;
            temp.cabeza = nullptr;
        }
        return *this;
    }

    void limpiar() {
        while (cabeza != nullptr) {
            NodoMedico* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    void insert_first(const EventoMedico& e) {
        NodoMedico* nuevo = new NodoMedico(e);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    bool is_empty() const { return cabeza == nullptr; }

    EventoMedico get_first() const {
        if (cabeza) return cabeza->evento;
        return EventoMedico(); 
    }
};

// ==========================================
// 3. CLASE BASE: PERSONA
// ==========================================
class Persona {
protected:
    std::string cedula_id;
    std::string nombre;
    int fecha_nacimiento; 

public:
    Persona(std::string id = "", std::string nom = "", int fecha_nac = 0)
        : cedula_id(id), nombre(nom), fecha_nacimiento(fecha_nac) {}
    virtual ~Persona() {} 
};

// ==========================================
// 4. JUGADOR (Entidad Final y Nodo Hash)
// ==========================================
class Jugador : public Persona {
private:
    std::string posicion;
    int dorsal;
    std::string categoria;
    bool solvente_pago;
    bool elegible_comet;
    int goles;
    int asistencias;
    int minutos_jugados;
    int asis_entrenamientos;
    int total_entrenos;

public:
    ListaMedica historial_medico; // Usamos nuestra lista segura

    Jugador(std::string id = "", std::string nom = "", int fecha_nac = 0, 
            std::string pos = "", int dor = 0, std::string cat = "")
        : Persona(id, nom, fecha_nac), posicion(pos), dorsal(dor), categoria(cat),
          solvente_pago(true), elegible_comet(true), 
          goles(0), asistencias(0), minutos_jugados(0), 
          asis_entrenamientos(0), total_entrenos(0) {}

    std::string getCedula() const { return cedula_id; }
    std::string getNombre() const { return nombre; }
    
    void registrarAsistencia(bool asistio) {
        total_entrenos++;
        if (asistio) asis_entrenamientos++;
    }
    
    float getPorcentajeAsistencia() const {
        if (total_entrenos == 0) return 100.0f; 
        return (static_cast<float>(asis_entrenamientos) / total_entrenos) * 100.0f;
    }

    void suspenderPorPago() { solvente_pago = false; }
    void registrarPago() { solvente_pago = true; }

    bool esConvocable() {
        if (!solvente_pago) return false;
        if (!elegible_comet) return false;
        
        if (!historial_medico.is_empty()) {
            EventoMedico ultimo_evento = historial_medico.get_first();
            if (ultimo_evento.tipo == "Lesion" && !ultimo_evento.alta_medica) {
                return false; 
            }
        }
        return true;
    }

    void imprimirFicha() {
        std::cout << "\n=========================================\n";
        std::cout << "FICHA TECNICA: " << nombre << " [#" << dorsal << "]\n";
        std::cout << "Categoria: " << categoria << " | Posicion: " << posicion << "\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "Goles: " << goles << " | Asistencias: " << asistencias 
                  << " | Minutos: " << minutos_jugados << "\n";
        std::cout << "Asistencia a Entrenamientos: " << getPorcentajeAsistencia() << "%\n";
        std::cout << "-----------------------------------------\n";
        
        std::cout << "ESTADO (Semaforo): ";
        if (esConvocable()) {
            std::cout << "[VERDE] - CONVOCABLE\n";
        } else {
            std::cout << "[ROJO] - NO CONVOCABLE\n";
            if (!solvente_pago) std::cout << " -> Motivo: Insolvencia Administrativa.\n";
            if (!historial_medico.is_empty() && !historial_medico.get_first().alta_medica) {
                std::cout << " -> Motivo: Baja Medica (" << historial_medico.get_first().descripcion << ").\n";
            }
        }
        std::cout << "=========================================\n";
    }
};

#endif // MODELS_H