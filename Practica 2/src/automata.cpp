#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int vectorToInt (vector<int> vector) {
    int numero = 0;
    for (int i = 0; i < vector.size(); ++i) {
        numero += vector[i] * pow(10, vector.size() - 1 - i);
    }
    return numero;
}

struct numero {
    int dato[2];
    enum tipo {entero, flotante};
};

int estado = 0;
vector<int> ladoIzq;
vector<int> ladoDer;

void q0 (char c) {
    if (c == '.') {
        estado = 1; //No hay dígitos del lado izquierdo del punto.
    } else if (isdigit(c)) {
        estado = 2; //Hay uno o más dígitos del lado izquierdo del punto.
        ladoIzq.push_back(c - '0');
    }
}

void q1 (char c) {
    if (c == '.') {
        estado = 3; //Estado 'trampa' -> hay más de un punto en la cadena de entrada.
    } else if (isdigit(c)) {
        estado = 1; //Se mantiene en el mismo estado, sigue aceptando dígitos.
        ladoDer.push_back(c - '0');
    }
}

void q2 (char c) {
    if (c == '.') {
        estado = 1;
    } else if (isdigit(c)) {
        estado = 2; //Se mantiene en el mismo estado, sigue aceptando dígitos.
        ladoIzq.push_back(c - '0');
    }
}

int automata (string cadena) {
    for (int i = 0; i < cadena.length(); ++i) {
        if (cadena[i] == '.' || isdigit(cadena[i])) {   //Si el símbolo de entrada es un punto o un dígito, ejecuta:
            if (estado == 0) {
                q0(cadena[i]);
            } else if (estado == 1) {   
                q1(cadena[i]);
            } else if (estado == 2) {
                q2(cadena[i]);
            } else if (estado == 3) {
                //No es posible salir de este estado (estado 'trampa).
            }
        }
    }
    return estado;
}

int main ( ) {
    cout << "Ingrese la cadena a procesar: ";
    string entrada;
    cin >> entrada;

    automata(entrada);

    numero num;
    num.dato[0] = vectorToInt(ladoIzq);
    num.dato[1] = vectorToInt(ladoDer);

    switch (estado) {
    case 1:
        cout << "\nCadena aceptada.\n";
        cout << "\tTipo: Flotante.\n";
        cout << "\tNumero: " << num.dato[0] << "." << num.dato[1];
        break;
    
    case 2:
        cout << "\nCadena aceptada.\n";
        cout << "\tTipo: Entero.\n";
        cout << "\tNumero: " << num.dato[0];
        break;

    case 3:
        cout << "\nCadena no aceptada";
        break;
    }
}