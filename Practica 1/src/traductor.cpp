#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> leerDiccionario (std::string nombreDic) {
    std::ifstream archivo;
    archivo.open(nombreDic, std::ios::in);
    std::string texto;
    std::vector<std::string> lineas;
    
    if (archivo.fail()) {
        std::cout << "No se pudo abrir el archivo " << nombreDic;
        exit(1);
    }

    int i = 0;
    while (!archivo.eof()) {
        std::getline(archivo, texto);
        lineas.push_back(texto);
        ++i;
    }

    std::cout << "Las plabras en el diccionario " << nombreDic << " son las siguientes:\n";
    for (int i = 0; i < lineas.size() - 1; ++i) {
        std::cout << "\t" << i << ": " << lineas[i] << "\n";
    }
    
    std::cout << "\n";
    archivo.close();
    return lineas;
}

std::vector<std::string> split_getline(std::string str, char delim) {
    std::vector<std::string> resultado;
    std::istringstream isstream(str);
    std::string palabra;

    while(std::getline(isstream, palabra, delim)){
        resultado.push_back(palabra);
    }

    return resultado;
}

std::vector<std::string> traducir(std::vector<std::string> oracion, std::vector<std::string> diccionario, std::vector<std::string> &faltantes) {
    std::vector<std::string> traduccion;
    std::string token;
    for (int i = 0; i < oracion.size(); ++i) {
        bool encontrada = false;
        for (int j = 0; j < diccionario.size(); ++j) {
            if (diccionario[j].rfind(oracion[i], 0) == 0) {
                token = diccionario[j].substr(diccionario[j].find("-"));
                token[0] = 0;
                encontrada = true;
                break;
            } 
        }
        if (encontrada) {
            traduccion.push_back(token);
            //std::cout << token << " ";
        } else {
            traduccion.push_back(oracion[i]);
            faltantes.push_back(oracion[i]);
            //std::cout << oracion[i] << " ";
        }
    }
    return traduccion;
}

int main ( ) {
    
    std::cout << "Traductor Espanol -> Ingles / Ingles -> Espanol\n";
    std::cout << "\tPractica 1 - Compiladores\n";
    std::cout << "\t\tMolina Rincon Armando - 2173000454\n\n";

    std::vector<std::string> espIng = leerDiccionario("Esp-Ing.txt"); 
    std::vector<std::string> ingEsp = leerDiccionario("Ing-Esp.txt");
    std::string cadena;
    std::vector<std::string> resultado;
    std::vector<std::string> traduccion;
    std::vector<std::string> faltantes;

    while (true) {
        std::cout << "Indique la operacion que desea realizar presionando la tecla indicada\n";
        std::cout << "\tTraducir una frase Espanol -> Ingles: 1\n";
        std::cout << "\tTraducir una frase Ingles -> Espanol: 2\n";
        std::cout << "\tSalir del programa: 3\n\n";
        std::cout << "\t\tSeleccion: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore();
        std::cout << "\n";

        switch (opcion) {
            case 1:
                std::cout << "Introduce la frase que deseas traducir.\n\t";
                std::getline(std::cin, cadena);
                resultado = split_getline(cadena, ' ');
                std::cout << "La traduccion de la frase es:\n\t"; 
                traduccion = traducir(resultado, espIng, faltantes);
                for (int i = 0; i < traduccion.size(); i++) {
                    std::cout << traduccion[i] << " ";
                }
                if (!faltantes.empty()) {
                    std::cout << "\nLas siguientes palabras no se encntraron en el diccionario:\n\t";    
                    for (int i = 0; i < faltantes.size(); i++) {
                        std::cout << i << ": " << faltantes[i] << "   ";
                    }
                    faltantes.clear();
                }
                std::cout << "\n\n";
                break;
            case 2:
                std::cout << "Introduce la frase que deseas traducir.\n\t";
                std::getline(std::cin, cadena);
                resultado = split_getline(cadena, ' ');
                std::cout << "La traduccion de la frase es:\n\t"; 
                traduccion = traducir(resultado, ingEsp, faltantes);
                for (int i = 0; i < traduccion.size(); i++) {
                    std::cout << traduccion[i] << " ";
                }
                if (!faltantes.empty()) {
                    std::cout << "\nLas siguientes palabras no se encntraron en el diccionario:\n\t";    
                    for (int i = 0; i < faltantes.size(); i++) {
                        std::cout << i << ": " << faltantes[i] << "   ";
                    }
                    faltantes.clear();
                }
                std::cout << "\n\n";
                break;
            case 3:
                std::cout << "Gracias por utilizar el traductor!";
                exit(1);
        }
        std::cout << "------------------------------------------------------------------------------\n";
    }
    
}



    //Hasta aquí se tienen las palabras-traducción en el vector 'lineas'
/*
    for (int i = 0; i < lineas.size(); ++i) {
        if (lineas[i].rfind("nombre", 0) == 0) {
            std::cout << "\n si esta, es " << i << "\n";
        }
    }


    std::string text = lineas[0];
    std::string delimiter = "-";
    std::string token = text.substr(text.find(delimiter));
    token[0] = 0;
    std::cout << token;
*/


    //Ya puedo encontrar la traducción de una palabra
/*
    for (int i = 0; i < lineas.size(); ++i) {
        if (lineas[i].rfind(resultado[0], 0) == 0) {
            std::string token = lineas[i].substr(lineas[i].find("-"));
            token[0] = 0;
            std::cout << "\n la traduccion de " << resultado[0] << " es "<< token << "\n";
            break;
        } else {
            std::cout << "La traduccion de la palabra " << resultado[0] << " no esta en el diccionario";
        }
    }
*/

/*
    for (int i = 0; i < resultado.size(); ++i) {
        for (int j = 0; j < lineas.size(); ++j) {
            if (lineas[j].rfind(resultado[i], 0) == 0) {
                std::string token = lineas[j].substr(lineas[j].find("-"));
                token[0] = 0;
                std::cout << "La traduccion de " << resultado[i] << " es "<< token;
                break;
            } 
        }
        //std::cout << "La traduccion de la palabra " << resultado[i] << " no esta en el diccionario";
        std::cout << "\n";
    }
*/

/*
void traducir(std::vector<std::string> oracion, std::vector<std::string> diccionario) {
    for (int i = 0; i < oracion.size(); ++i) {
        for (int j = 0; j < diccionario.size(); ++j) {
            if (diccionario[j].rfind(oracion[i], 0) == 0) {
                std::string token = diccionario[j].substr(diccionario[j].find("-"));
                token[0] = 0;
                std::cout << "La traduccion de " << oracion[i] << " es "<< token;
                break;
            } 
        }
        //std::cout << "La traduccion de la palabra " << resultado[i] << " no esta en el diccionario";
        std::cout << "\n";
    }
}
*/