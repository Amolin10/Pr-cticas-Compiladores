#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define Q4 4

std::string leerM( ) {
   std::ifstream archivo;
    archivo.open("M.txt", std::ios::in);
    std::string expresion;
    if (archivo.fail()) {
        std::cout << "No se pudo abrir el archivo M.txt\n";
        exit(1);
    }
    std::getline(archivo, expresion);
    archivo.close();
    return expresion;
}

void escribirC(std::string expresion) {
    std::ofstream archivo;
    archivo.open("C.txt", std::ios_base::app);
    if(archivo.fail()) {
        std::cout << "Error al intentar abrir el C.txt\n";
        exit(1);
    }
    archivo << expresion;
    archivo.close();
    std::cout << "La traduccion en lenguaje C es:\t " << expresion << "\n";
}

void escritura(std::string expresion) {
    FILE* arch = fopen("C.txt", "a+");
    for (int i = 0; i < expresion.size(); ++i) {
        fprintf(arch, "%c", expresion[i]);
    }
    fprintf(arch, "\n");
    fclose(arch); 
}

int automata (char c, std::vector<char> parentesis) {
    if (c == '(') {
        parentesis.push_back('(');
        return Q1;
    } else if (c == ')') {
        parentesis.pop_back();
        return Q2;
    } else if (c == 92) {  // 92 = '\'
        return Q3;
    } else if (c == 'l') {
        return Q4;
    }
    return -1;
}


int main ( ) {
    
    std::string traduccion;
    std::string acumulado;
    std::string acumuladoAux;
    std::string expresionM = leerM();
    std::cout << "El contenido del archivo 'M.txt es:\t" << expresionM << "\n"; 

    int i = 0;
    int estado = Q0;

    int PcP = 0;
    int PcR = 0;
    int aux = 0;
    int temp;
    
    std::vector<char> parentesis;

    

    for (int j = 0; j <= expresionM.size() + 1; j++) {
        
        switch (estado) {

            case Q0:
                estado = automata(expresionM[i], parentesis);
                if (estado == -1) {
                    traduccion += expresionM[i];
                    i++;
                    j = i;
                    estado = Q0;
                }
                break; 
                
            case Q1:
                i++;
                temp = i;
                if (expresionM[i] == 92) {
                    while(expresionM[i] != ')') {
                        i++;
                    }
                    i = i + 2;
                    if (expresionM[i] == '^') {
                        traduccion += "pow(";
                        parentesis.push_back('(');
                        PcP = PcP + 1;
                        i = temp;
                        j = i;
                        estado = Q0;
                        break;
                    } else {
                        acumuladoAux = acumulado;
                        estado = Q0;
                        i = temp;
                        j = i;
                        break;
                    }
                }
                while(expresionM[i] != ')') {
                    i++;
                    if (i > expresionM.size()) {
                        std::cout << "La expresión es incorrecta\n";
                        return -1;
                    }
                }
                i++;
                if (expresionM[i] == '^') {
                    traduccion += "pow((";
                    parentesis.push_back('(');
                    parentesis.push_back('(');
                    PcP = PcP + 1;
                    i = temp;
                    estado = Q0;
                    j = i;
                    break;
                } else {
                    traduccion += '(';
                    parentesis.push_back('(');
                    i = temp;
                    estado = Q0;
                    j = i;
                    break;
                }

            case Q2:
                if (PcP == 0) {
                    if (aux >= 1) {
                        traduccion += ')';
                        traduccion += ')';
                        parentesis.pop_back();
                        parentesis.pop_back();
                        aux--;
                        i++;
                        estado = Q0;
                        j = i;
                        break;
                    } else {
                        traduccion += ')';
                        parentesis.pop_back();
                        i++;
                        estado = Q0;
                        j = i;
                        break;
                    }

                } else if (PcR >= 1) {
                    traduccion += "),(1/";
                    traduccion += acumulado;
                    acumulado.clear();
                    traduccion += ")";
                    parentesis.pop_back();
                    PcR--;
                    PcP--;
                    i++;
                    estado = Q0;
                    j = i;
                    break;
                } else if (!acumuladoAux.empty() && PcR >= 1) {
                    traduccion += "),(1/";
                    traduccion += acumuladoAux;
                    traduccion += "))";
                    parentesis.pop_back();
                    parentesis.pop_back();
                    PcR--;
                    i++;
                    j = i;
                    estado = Q0;
                    break;
                } else {
                    traduccion += ')';
                    parentesis.pop_back();
                    traduccion += ',';
                    i = i + 2;
                    j = i;
                    aux++;
                    PcP--;
                    estado = Q0;
                    break;
                }

            case Q3:
                i++;
                if (expresionM[i] == '2') {
                    traduccion += "sqrt";
                    i += 2;
                    j = i;
                    estado = Q0;
                    break;
                } else {
                    while (expresionM[i] != '/') {
                        acumulado += expresionM[i];
                        i++;
                    }
                i++;
                traduccion += "pow(";
                parentesis.push_back('(');
                PcR++;
                PcP++;
                j = i;
                estado = Q0;
                break;
                }

            case Q4:
                traduccion += "log(";
                parentesis.push_back('(');
                i += 4;
                j = i;
                estado = Q0;
                break;
        }

    }
    escribirC(traduccion);
}