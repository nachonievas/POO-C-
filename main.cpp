#include <iostream> 
#include <vector>   
#include <cstring>
#include <string>  
#include <fstream>
#include "clase.h" 
using namespace std;

cola fichaTecnica;
cola TramiteBaja;
cola Reclamos;
Pila sinServicioEspecificado;
Tramite tramite;

int totalInstalacion = 0;
int totalBaja = 0;
int totalReclamos = 0;
int totalErrores = 0;

void leerConteoBinario() {
    ifstream archivo("conteoTramites.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "Archivo binario no encontrado. (NO ESTA CREADO TODAVIA)" << endl;
        return;
    }

    struct ConteoTramites {
        char area[50];
        int cantidadTramites;
    };

    ConteoTramites conteo;
    while (archivo.read(reinterpret_cast<char*>(&conteo), sizeof(conteo))) {
        if (string(conteo.area) == "Instalacion") {
            totalInstalacion = conteo.cantidadTramites; }
        else if (string(conteo.area) == "Baja") { 
            totalBaja = conteo.cantidadTramites;}
        else if (string(conteo.area) == "Reclamos") { 
            totalReclamos = conteo.cantidadTramites; }
        else if (string(conteo.area) == "Errores") { totalErrores = conteo.cantidadTramites; }
    }
    archivo.close();
}

void leerArchivo() {
    ifstream f("tramites.txt");
    if (!f) {
        cout << "Error al abrir tramites.txt\n";
        exit(EXIT_FAILURE);
    } 

    string linea; 
    getline(f, linea);  

    while (f >> tramite.numeroTramite >> tramite.tipoTramite >> tramite.fecha
             >> tramite.hora >> tramite.servicio >> tramite.numeroCliente) {

        if (tramite.tipoTramite == "instalacion" && tramite.servicio != "Error") {
            fichaTecnica.push(tramite);
            totalInstalacion++;
        } 
        else if (tramite.tipoTramite == "baja" && tramite.servicio != "Error") {
            TramiteBaja.push(tramite);
            totalBaja++;
        } 
        else if (tramite.tipoTramite == "reclamo" && tramite.servicio != "Error") {
            Reclamos.push(tramite);
            totalReclamos++;
        }
        if (tramite.servicio == "Error") {
            sinServicioEspecificado.push(tramite);
            totalErrores++;
        }
    }
    f.close();

    cout << "Total acumulado de trámites de Instalación: " << totalInstalacion << endl;
    cout << "Total acumulado de trámites de Baja: " << totalBaja << endl;
    cout << "Total acumulado de Reclamos: " << totalReclamos << endl;
    cout << "Total acumulado de errores (sin servicio especificado): " << totalErrores << endl;
}

void crearArchivoBinario() {
    ofstream archivo("conteoTramites.bin", ios::binary);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo binario." << endl;
        return;
    }

    struct ConteoTramites {
        char area[50];          
        int cantidadTramites;  
    };

    ConteoTramites conteo;

    strcpy(conteo.area, "Instalacion");
    conteo.cantidadTramites = totalInstalacion;
    archivo.write(reinterpret_cast<const char*>(&conteo), sizeof(conteo));

    strcpy(conteo.area, "Baja");
    conteo.cantidadTramites = totalBaja;
    archivo.write(reinterpret_cast<const char*>(&conteo), sizeof(conteo));

    strcpy(conteo.area, "Reclamos");
    conteo.cantidadTramites = totalReclamos;
    archivo.write(reinterpret_cast<const char*>(&conteo), sizeof(conteo));

    strcpy(conteo.area, "Errores");
    conteo.cantidadTramites = totalErrores;
    archivo.write(reinterpret_cast<const char*>(&conteo), sizeof(conteo));

    archivo.close();
}

int main() {
    leerConteoBinario();
    leerArchivo();        
    crearArchivoBinario();  
}
