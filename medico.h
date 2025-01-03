#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip> 

class CitaMedica;

class Medico {
private:
    std::string nombre;
    int ID;
    std::string especialidad;
    bool disponibilidad;
    std::vector<CitaMedica*> citas;

public:
    // Constructor por defecto
    Medico() 
        : nombre(""), ID(0), especialidad(""), disponibilidad(false) {}
    // Constructor
    Medico(std::string& nombre, int ID, const std::string& especialidad, bool disponibilidad)
        : nombre(nombre), ID(ID), especialidad(especialidad), disponibilidad(disponibilidad) {}

    void setNombre(const std::string& nombre) { this->nombre = nombre; }
    void setID(const int& ID) { this->ID = ID; }
    void setEspecialidad(const std::string& especialidad){ this->especialidad = especialidad; }
    void setDisponibilidad(const bool& disponibilidad){ this->disponibilidad = disponibilidad; }

    void mostrarMedico() const {
        // Como el dato tipo int omite los ceros a la izq, se usa setw y setfill para mostrarlos
        std::cout << "Dr. " << nombre << ", ID: " << std::setw(4) << std::setfill('0') << ID 
        << ", Especialidad: " << especialidad << ", Disponibilidad: " << disponibilidad <<std::endl;
    }

    void registrarMedico() {
        std::cout << "Nombre y apellidos del medico: ";
        std::getline(std::cin, nombre);

        std::cout << "ID del medico (1234): ";
        while (!(std::cin >> ID)) {
            std::cout << "ID invalido. Intenta de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        std::cout << "Especialidad del medico: ";
        std::getline(std::cin, especialidad);

        std::cout << "Medico disponible? (1 para si, 0 para no): ";
        while (!(std::cin >> disponibilidad)) {
            std::cout << "Entrada invalida. Intenta de nuevo (1 para si, 0 para no): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore();
        std::cout << "Medico registrado correctamente: " << nombre << " (ID: " << ID << ")" << std::endl;
    }

    void modificarMedico(std::vector<Medico*>& medicos) {
        int idMedico;
        std::cout << "Ingrese el ID del medico a editar: ";
        while (!(std::cin >> idMedico)) {
            std::cout << "Entrada invalida. Intente de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        auto it = std::find_if(medicos.begin(), medicos.end(),
        [&idMedico](Medico* m) { return m->getID() == idMedico; });

        if (it != medicos.end()) {
            Medico* medico = *it;
            std::cout << "Ingrese el nuevo nombre y apellidos del medico: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, medico->nombre);
            std::cout << "Ingrese el nuevo ID del medico (1234): ";
            while (!(std::cin >> medico->ID)) {
                std::cout << "ID invalido. Intenta de nuevo: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Ingrese la nueva especialidad del medico: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, medico->especialidad);
            std::cout << "Esta disponible el medico? (1 = Si / 0 = No): ";
            while (!(std::cin >> medico->disponibilidad)) {
                std::cout << "Entrada invalida. Intenta de nuevo (1 = Si / 0 = No): ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "Medico modificado correctamente.\n";
        } else {
            std::cout << "Medico no encontrado.\n";
        }
    }

    static void eliminarMedico(std::vector<Medico*>& medicos) {
        int idMedico;
        std::cout << "Ingrese el ID del medico a eliminar: ";
        while (!(std::cin >> idMedico)) { 
            std::cout << "Entrada invalida. Intente de nuevo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();
        std::cout << "Estas seguro de eliminar al medico con ID " << idMedico
                  << "? (1 para confirmar, 0 para cancelar): ";
        int confirmar;
        while (!(std::cin >> confirmar) || (confirmar != 1 && confirmar != 0)) { // Validar entrada
            std::cout << "Entrada invalida. Intente de nuevo (1 para confirmar, 0 para cancelar): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();
        if (confirmar == 1) {
        auto it = std::remove_if(medicos.begin(), medicos.end(), [&idMedico](Medico* m) {
            return m->getID() == idMedico;
        });

            if (it != medicos.end()) {
                delete *it;
                medicos.erase(it);
                std::cout << "Medico eliminado correctamente.\n";
            }else {
                std::cout << "No se encontró un medico con ese ID.\n";
            }
        } else {
            std::cout << "Eliminacion cancelada.\n";
        }
    }

    void añadirCita(CitaMedica* cita) {
        citas.push_back(cita);
    }
    // Metodos de consulta (getters)
    std::string getNombre() const { return nombre; }
    int getID() const { return ID; }
    std::string getEspecialidad() const { return especialidad; }
    bool getDisponibilidad() const { return disponibilidad; }
    // Metodo estatico para obtener el número de campos requeridos
    static int camposRequeridos() { return 4; } // Nombre, ID, Especialidad, Disponibilidad

};

