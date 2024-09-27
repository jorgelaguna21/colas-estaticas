#include <iostream>
#include <string>

// Definici�n de la clase persona
class persona {
public:
    std::string nombre;
    std::string carrera;
    int materiasAprobadas;
    float promedioGeneral;

    persona();  // Constructor por defecto
    persona(std::string n, std::string c, int materias, float promedio);  // Constructor con par�metros
    void operator=(const persona& x);  // Sobrecarga del operador de asignaci�n

    friend std::ostream& operator<<(std::ostream& o, const persona& p);  // Sobrecarga del operador <<
    friend std::istream& operator>>(std::istream& o, persona& p);  // Sobrecarga del operador >>
};

// Implementaci�n de la clase persona
persona::persona() : nombre("Jorge"), carrera("sin especificar"), materiasAprobadas(0), promedioGeneral(0.0) {}

persona::persona(std::string n, std::string c, int materias, float promedio)
    : nombre(n), carrera(c), materiasAprobadas(materias), promedioGeneral(promedio) {}

void persona::operator=(const persona& x) {
    nombre = x.nombre;
    carrera = x.carrera;
    materiasAprobadas = x.materiasAprobadas;
    promedioGeneral = x.promedioGeneral;
}

std::ostream& operator<<(std::ostream& o, const persona& p) {
    o << "Nombre: " << p.nombre << "\t Carrera: " << p.carrera
      << "\t Materias Aprobadas: " << p.materiasAprobadas
      << "\t Promedio General: " << p.promedioGeneral << std::endl;
    return o;
}

std::istream& operator>>(std::istream& o, persona& p) {
    std::cout << "\n Inserta nombre: ";
    o >> p.nombre;
    std::cout << "\n Inserta carrera: ";
    o >> p.carrera;
    std::cout << "\n Inserta total de materias aprobadas: ";
    o >> p.materiasAprobadas;
    std::cout << "\n Inserta promedio general: ";
    o >> p.promedioGeneral;
    return o;
}

// Definici�n de la clase Cola
class Cola {
private:
    static const int TAM = 100;  // Tama�o m�ximo de la cola
    persona datos[TAM];  // Arreglo de personas
    int ult = -1;  // �ndice del �ltimo elemento en la cola

public:
    bool vacia() const;  // Verifica si la cola est� vac�a
    bool llena() const;  // Verifica si la cola est� llena
    int ultimo() const;  // Retorna el �ndice del �ltimo elemento
    void enqueue(const persona& elem);  // Agrega un elemento a la cola
    persona dequeue();  // Retira un elemento de la cola

    bool elimina(int pos);  // Elimina un elemento en una posici�n espec�fica
    int inserta(const persona& elem, int pos);  // Inserta un elemento en una posici�n espec�fica

    friend std::ostream& operator<<(std::ostream& o, const Cola& L);  // Sobrecarga del operador <<
};

// Implementaci�n de la clase Cola
bool Cola::vacia() const {
    return ult == -1;
}

bool Cola::llena() const {
    return ult == TAM - 1;
}

int Cola::ultimo() const {
    return ult;
}

std::ostream& operator<<(std::ostream& o, const Cola& L) {
    int i = 0;
    std::cout << "\n";
    while (i <= L.ultimo()) {
        o << L.datos[i];
        i++;
    }
    return o;
}

void Cola::enqueue(const persona& elem) {
    inserta(elem, 0);
}

persona Cola::dequeue() {
    if (vacia()) {
        std::cout << "\n La cola est� vac�a" << std::endl;
        return persona();  // Devuelve una persona por defecto en caso de cola vac�a
    } else {
        ult--;
        return datos[ult + 1];
    }
}

bool Cola::elimina(int pos) {
    if (vacia() || pos < 0 || pos > ult) {
        std::cout << "\n error de eliminaci�n";
        return true;
    }
    int i = pos;
    while (i < ult) {
        datos[i] = datos[i + 1];
        i++;
    }
    ult--;
    return false;
}

int Cola::inserta(const persona& elem, int pos) {
    if (llena() || pos < 0 || pos > ult + 1) {
        std::cout << "\n Error de inserci�n";
        return 0;
    }
    int i = ult + 1;
    while (i > pos) {
        datos[i] = datos[i - 1];
        i--;
    }
    datos[pos] = elem;
    ult++;
    return 1;
}

// Funci�n main
int main() {
    Cola colaSolicitudes;
    int opcion;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Dar de alta la solicitud de un alumno" << std::endl;
        std::cout << "2. Elaborar una constancia" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: // Dar de alta la solicitud de un alumno
                {
                    persona nuevoAlumno;
                    std::cin >> nuevoAlumno;
                    colaSolicitudes.enqueue(nuevoAlumno);
                    std::cout << "Solicitud de constancia encolada correctamente." << std::endl;
                }
                break;

            case 2: // Elaborar una constancia
                if (!colaSolicitudes.vacia()) {
                    persona alumnoAtendido = colaSolicitudes.dequeue();
                    std::cout << "Elaborando constancia para el siguiente alumno:" << std::endl;
                    std::cout << alumnoAtendido << std::endl;
                } else {
                    std::cout << "No hay solicitudes pendientes." << std::endl;
                }
                break;

            case 3: // Salir|
                std::cout << "Saliendo del programa." << std::endl;
                break;

            default:
                std::cout << "Opci�n no v�lida. Intente de nuevo." << std::endl;
                break;
        }

    } while (opcion != 3);

    return 0;
}
