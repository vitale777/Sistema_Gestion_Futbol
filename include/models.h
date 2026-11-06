#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>

// Espacio de nombres para serializar std::string en formato binario (.dat) sin corromper memoria
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
// 1. EVENTO MEDICO (Lista Enlazada)
// ==========================================
class EventoMedico {
private:
    int id_evento;
    std::string fecha_lesion;
    std::string tipo_lesion;
    std::string zona_afectada;
    int dias_baja;
    bool alta_medica;

public:
    EventoMedico() : id_evento(0), dias_baja(0), alta_medica(true) {}
    EventoMedico(int id, const std::string& fecha, const std::string& tipo, const std::string& zona, int dias)
        : id_evento(id), fecha_lesion(fecha), tipo_lesion(tipo), zona_afectada(zona), dias_baja(dias), alta_medica(false) {}

    bool tieneAltaMedica() const { return alta_medica; }
    const std::string& getTipoLesion() const { return tipo_lesion; }

    void guardarEnBinario(std::ofstream& out) const {
        out.write(reinterpret_cast<const char*>(&id_evento), sizeof(id_evento));
        SerializadorBinario::escribirString(out, fecha_lesion);
        SerializadorBinario::escribirString(out, tipo_lesion);
        SerializadorBinario::escribirString(out, zona_afectada);
        out.write(reinterpret_cast<const char*>(&dias_baja), sizeof(dias_baja));
        out.write(reinterpret_cast<const char*>(&alta_medica), sizeof(alta_medica));
    }
};

// ==========================================
// 2. JERARQUÍA POO (Persona -> Jugador)
// ==========================================
class Persona {
protected:
    std::string cedula_id; // Clave Hash O(1)
    std::string nombre;
    int fecha_nacimiento;  // Clave AVL O(log n) formato AAAAMMDD

public:
    Persona() : fecha_nacimiento(0) {}
    Persona(const std::string& ced, const std::string& nom, int fecha)
        : cedula_id(ced), nombre(nom), fecha_nacimiento(fecha) {}
    virtual ~Persona() = default;

    virtual std::string getRol() const = 0;
};

class Jugador : public Persona {
private:
    std::string id_equipo;
    std::string categoria;
    int dorsal;
    bool solvente_pago;
    bool elegible_comet;
    int fila_tactica;
    int col_tactica;
    std::list<EventoMedico> historial_medico; // Reemplazable por Designar::SLList

public:
    Jugador(const std::string& ced, const std::string& nom, int fecha, const std::string& eq, const std::string& cat, int dor)
        : Persona(ced, nom, fecha), id_equipo(eq), categoria(cat), dorsal(dor),
          solvente_pago(true), elegible_comet(true), fila_tactica(-1), col_tactica(-1) {}

    std::string getRol() const override { return "Jugador [" + categoria + "] Dorsal: " + std::to_string(dorsal); }
    const std::string& getNombre() const { return nombre; }

    void registrarLesion(const EventoMedico& ev) { historial_medico.push_back(ev); }

    bool estaAptoParaJugar() const {
        if (!solvente_pago || !elegible_comet) return false;
        if (historial_medico.empty()) return true;
        return historial_medico.back().tieneAltaMedica();
    }

    bool operator<(const Jugador& otro) const {
        if (this->fecha_nacimiento != otro.fecha_nacimiento) return this->fecha_nacimiento < otro.fecha_nacimiento;
        return this->cedula_id < otro.cedula_id;
    }
};

// ==========================================
// 3. EQUIPO (Ordenamiento y Pizarra 2D)
// ==========================================
class Equipo {
private:
    std::string id_equipo;
    std::string categoria;
    int partidos_ganados;
    int partidos_empatados;
    int goles_favor;
    int goles_contra;
    int campo[11][7]; // Matriz táctica 2D

public:
    Equipo(const std::string& nombre_eq, const std::string& cat)
        : id_equipo(nombre_eq), categoria(cat), partidos_ganados(0), partidos_empatados(0),
          goles_favor(0), goles_contra(0) {
        for (int i = 0; i < 11; ++i)
            for (int j = 0; j < 7; ++j) campo[i][j] = 0;
    }

    int getPuntos() const { return (partidos_ganados * 3) + partidos_empatados; }
    int getDiferencial() const { return goles_favor - goles_contra; }
    const std::string& getIdEquipo() const { return id_equipo; }

    static bool compararEquipos(const Equipo& a, const Equipo& b) {
        if (a.getPuntos() != b.getPuntos()) return a.getPuntos() > b.getPuntos();
        if (a.getDiferencial() != b.getDiferencial()) return a.getDiferencial() > b.getDiferencial();
        return a.id_equipo < b.id_equipo;
    }
};

#endif