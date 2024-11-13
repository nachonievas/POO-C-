#include <iostream>
#include <string>
using namespace std;

struct Tramite {
    int numeroTramite;
    string tipoTramite;
    string fecha;
    string hora;
    string servicio;
    int numeroCliente;
};

class cola {
private:
    static const int MAX = 400; 
    int frente, final;
    Tramite tramites[MAX]; 

public:
    cola();
    void push(Tramite tramite);
    Tramite pop();
    bool empty();
    bool full();
    void mostrar();
    int contar();
};

cola::cola() {
    frente = 0;
    final = 0;
}

bool cola::empty() {
    return frente == final;
}

bool cola::full() {
    return (final + 1) % MAX == frente;
}

void cola::push(Tramite t) {
    if (!full()) {
        tramites[final] = t;
        final = (final + 1) % MAX;
    } else {
        cout << "La cola está llena. No se puede agregar más trámites." << endl;
    }
}

Tramite cola::pop() {
    if (!empty()) {
        Tramite t = tramites[frente];
        frente = (frente + 1) % MAX;
        return t;
    } else {
        cout << "La cola está vacía." << endl;
        return {}; 
    }
}

void cola::mostrar() {
    if (empty()) {
        cout << "La cola está vacía." << endl;
        return;
    }

    cout << "Contenido de la cola: " << endl;
    for (int i = frente; i != final; i = (i + 1) % MAX) {
        cout << "Número de Trámite: " << tramites[i].numeroTramite << ", "
             << "Tipo de Trámite: " << tramites[i].tipoTramite << ", "
             << "Fecha: " << tramites[i].fecha << ", "
             << "Hora: " << tramites[i].hora << ", "
             << "Servicio: " << tramites[i].servicio << ", "
             << "Número de Cliente: " << tramites[i].numeroCliente << endl;
    }
}
int cola::contar() {
    if (empty()) return 0; 
    if (final >= frente) {
        return final - frente; 
    } else {
        return MAX - frente + final; 
    }
}

class Pila {
private:
    static const int MAX = 400;
    int tope;
    Tramite tramites[MAX];  

public:
    Pila();
    void push(Tramite tramite);  
    Tramite pop();  
    bool empty();  
    bool full();  
    void mostrar();
    int contar();
};

Pila::Pila() {
    tope = -1;
}

bool Pila::empty() {
    return tope == -1;
}

bool Pila::full() {
    return tope == MAX - 1;
}

void Pila::push(Tramite t) {
    if (!full()) {
        tramites[++tope] = t;
    } else {
        cout << "La pila está llena. No se puede agregar más trámites." << endl;
    }
}

Tramite Pila::pop() {
    if (!empty()) {
        return tramites[tope--];
    } else {
        cout << "La pila está vacía." << endl;
        return {}; 
    }
}
void Pila::mostrar() {
    if (empty()) {
        cout << "La pila está vacía." << endl;
        return;
    }

    cout << "Contenido de la pila (de arriba a abajo): " << endl;
    for (int i = tope; i >= 0; --i) { 
        cout << "Número de Trámite: " << tramites[i].numeroTramite << ", "
             << "Tipo de Trámite: " << tramites[i].tipoTramite << ", "
             << "Fecha: " << tramites[i].fecha << ", "
             << "Hora: " << tramites[i].hora << ", "
             << "Servicio: " << tramites[i].servicio << ", "
             << "Número de Cliente: " << tramites[i].numeroCliente << endl;
    }
}
int Pila::contar() {
    return tope + 1; 
}