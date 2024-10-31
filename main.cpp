#include <iostream>
#include <string>
#include <vector>
#include <fstream>  // Para trabajar con archivos
#include <sstream>  // Para manejar la separación de texto

using namespace std;

struct Cita {
    string idUsuario;
    string nombre;
    string fecha;
    string hora;
};

vector<Cita> citas;

// Función para mostrar el menú de opciones
void mostrarMenu() {
    cout << "\nMenu de Sistema de Citas\n";
    cout << "1. Consultar disponibilidad de horario\n";
    cout << "2. Solicitar una cita\n";
    cout << "3. Cancelar una cita\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}

// Función para consultar disponibilidad de citas
void consultarDisponibilidad() {
    cout << "Seleccione el año (AAAA): ";
    string year;
    cin >> year;
    cout << "Seleccione el mes (01-12): ";
    string mes;
    cin >> mes;
    cout << "Seleccione el dia (01-31): ";
    string dia;
    cin >> dia;

    // Formato de fecha esperado: DD/MM/AAAA
    string fechaFiltro = dia + "/" + mes + "/" + year;

    bool citasEncontradas = false;
    cout << "\nCitas para el dia " << dia << "/" << mes << "/" << year << ":\n";
    for (const auto& cita : citas) {
        if (cita.fecha == fechaFiltro) {
            cout << "- Cita a las " << cita.hora << " para " << cita.nombre << "\n";
            citasEncontradas = true;
        }
    }

    if (!citasEncontradas) {
        cout << "No hay citas programadas para esta fecha.\n";
    }
}

// Función para solicitar una nueva cita
void solicitarCita(const string& idUsuario, const string& nombre) {
    cout << "Ingrese fecha de la cita (DD/MM/AAAA): ";
    string fecha;
    cin >> fecha;
    cout << "Ingrese hora de la cita (HH:MM): ";
    string hora;
    cin >> hora;

    Cita nuevaCita = { idUsuario, nombre, fecha, hora };
    citas.push_back(nuevaCita);
    cout << "Cita registrada con exito\n";
}

// Función para cancelar una cita existente
void cancelarCita(const string& idUsuario) {
    cout << "Ingrese la fecha de la cita a cancelar (DD/MM/AAAA): ";
    string fecha;
    cin >> fecha;
    cout << "Ingrese la hora de la cita a cancelar (HH:MM): ";
    string hora;
    cin >> hora;

    auto it = citas.begin();
    bool encontrada = false;
    while (it != citas.end()) {
        if (it->idUsuario == idUsuario && it->fecha == fecha && it->hora == hora) {
            it = citas.erase(it);
            cout << "Cita cancelada con exito\n";
            encontrada = true;
            break;
        } else {
            ++it;
        }
    }
    if (!encontrada) {
        cout << "No se encontro una cita con esos detalles\n";
    }
}

// Función para guardar las citas en un archivo
void guardarCitas() {
    ofstream archivo("citas.txt");
    if (archivo.is_open()) {
        for (const auto& cita : citas) {
            archivo << cita.idUsuario << "," << cita.nombre << "," 
                    << cita.fecha << "," << cita.hora << "\n";
        }
        archivo.close();
        cout << "Citas guardadas correctamente en el archivo.\n";
    } else {
        cout << "Error al abrir el archivo para guardar las citas.\n";
    }
}

// Función para cargar las citas desde un archivo
void cargarCitas() {
    ifstream archivo("citas.txt");
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            Cita cita;
            getline(ss, cita.idUsuario, ',');
            getline(ss, cita.nombre, ',');
            getline(ss, cita.fecha, ',');
            getline(ss, cita.hora, ',');

            citas.push_back(cita);
        }
        archivo.close();
        cout << "Citas cargadas correctamente desde el archivo.\n";
    } else {
        cout << "No se encontró un archivo de citas previas.\n";
    }
}

int main() {
    cargarCitas();  // Cargar citas guardadas al inicio del programa

    string idUsuario, nombre;
    cout << "Bienvenido al sistema de citas.\n";
    cout << "Ingrese su identificacion: ";
    cin >> idUsuario;
    cout << "Ingrese su nombre: ";
    cin.ignore();
    getline(cin, nombre);

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                consultarDisponibilidad();
                break;
            case 2:
                solicitarCita(idUsuario, nombre);
                break;
            case 3:
                cancelarCita(idUsuario);
                break;
            case 4:
                guardarCitas();  // Guardar citas antes de salir
                cout << "Saliendo del sistema. Hasta luego!\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
