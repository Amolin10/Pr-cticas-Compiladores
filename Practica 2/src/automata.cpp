#include <iostream>
#include <vector>
using namespace std;

/* Uso de Type enum
int main ( ) {
    
    enum tipo {entero, flotante};
    tipo numero = flotante;
    if (numero == entero) {
        std::cout << "Hola";
    } else if (numero == flotante) {
        std::cout << "Adios";
    }

}*/

struct numero {
    int dato[2];
    enum tipo {entero, flotante};
};

int estado = 0;
vector<string> ladoIzq;
vector<string> ladoDer;

void q0 (char c) {
    if (c == '.') {
        estado = 1; //No hay dígitos del lado izquierdo del punto.
    } else if (isdigit(c)) {
        estado = 2; //Hay uno o más dígitos del lado izquierdo del punto.
    }
}

void q1 (char c) {
    if (c == '.') {
        estado = 3; //Estado 'trampa' -> hay más de un punto en la cadena de entrada.
    } else if (isdigit(c)) {
        estado = 1; //Se mantiene en el mismo estado, sigue aceptando dígitos.
    }
}

void q2 (char c) {
    if (c == '.') {
        estado = 1;
    } else if (isdigit(c)) {
        estado = 2; //Se mantiene en el mismo estado, sigue aceptando dígitos.
    }
}

int automata (string cadena) {
    for (int i = 0; i < cadena.length(); ++i) {
        if (cadena[i] == '.' || isdigit(cadena[i])) {   //Si el símbolo de entrada es un punto o un dígito, ejecuta:
            if (estado == 0) {
                q0(cadena[i]);
            } else if (estado == 1) {
                q1(cadena[i]);
            } else if (estado ==2) {
                q2(cadena[i]);
            } else if (estado == 3) {
                //No es posible salir de este estado (estado 'trampa).
            }
        }
    }
    return estado;
}

int main ( ) {
    string entrada = "dwef2.2.31aa2b3";
    automata(entrada);
    cout << estado;
}


