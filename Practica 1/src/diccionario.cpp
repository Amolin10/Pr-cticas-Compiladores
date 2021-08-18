#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

void espIng ( ) {
    std::ofstream archivo;
    archivo.open("Esp-Ing.txt", std::ios_base::app);
    if(archivo.fail()) {
        std::cout << "Error al intentar abrir e archivo Esp-Ing.txt\n";
        exit(1);
    }
    std::cout << "Introduce la palabra que deseas agregar al diccionario Espanol -> Ingles: ";
    std::string palabra;
    std::cin >> palabra;
    archivo << palabra;
    archivo << "-";
    std::cout << "\tIntroduce la traduccion de la palabra " << palabra << ": ";
    std::string traduccion;
    std::cin >> traduccion;
    archivo << traduccion << "\n";
    archivo.close();
    std::cout << "\nSe ha agregado al diccionario Espanol -> Ingles la siguiente palabra y su traduccion:  " << palabra << "-" << traduccion << "\n\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
}

void ingEsp( ) {
    std::ofstream archivo;
    archivo.open("Ing-Esp.txt", std::ios_base::app);
    if(archivo.fail()) {
        std::cout << "Error al intentar abrir e archivo Ing-Esp.txt\n";
        exit(1);
    }
    std::cout << "Introduce la palabra que deseas agregar al diccionario Ingles -> Espanol: ";
    std::string palabra;
    std::cin >> palabra;
    archivo << palabra;
    archivo << "-";
    std::cout << "\tIntroduce la traduccion de la palabra " << palabra << ": ";
    std::string traduccion;
    std::cin >> traduccion;
    archivo << traduccion << "\n";
    archivo.close();
    std::cout << "\nSe ha agregado al diccionario Ingles -> Espanol la siguiente palabra y su traduccion:  " << palabra << "-" << traduccion << "\n\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------\n";
}

int main ( ) {

    std::cout << "Diccionario Espanol -> Ingles / Ingles -> Espanol\n";
    std::cout << "\tPractica 1 - Compiladores\n";
    std::cout << "\t\tMolina Rincon Armando - 2173000454\n\n";

    while(true) {
        std::cout << "Indique la operacion que desea realizar presionando la tecla indicada\n";
        std::cout << "\tAgregar una palabra al diccionario Espanol -> Ingles: 1\n";
        std::cout << "\tAgregar una palabra al diccionario Ingles -> Espanol: 2\n";
        std::cout << "\tSalir del programa: 3\n\n";
        std::cout << "\t\tSeleccion: ";

        int opcion;
        std::cin >> opcion;
        std::cout << "\n";

        switch (opcion) {
            case 1:
                espIng();
                break;
            case 2:
                ingEsp();
                break;
            case 3:
                std::cout << "Gracias por utilizar el diccionario!";
                exit(1);
        } 

    }

}