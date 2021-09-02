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


int main ( ) {
    
    std::string traduccion;
    std::string bandera;
    std::string bandera2;
    int i = 0;
    int estado = Q0;
    int PcP = 0;
    int PcR = 0;
    int aux = 0;
    std::vector<char> parentesis;

    std::string exprMate = leerM();
    std::cout << "El contenido del archivo 'M.txt es:\t" << exprMate << "\n"; 

    for (int j = 0; j <= exprMate.size() + 1; j++) {
        
        switch (estado) {

            case Q0:
                if (exprMate[i] == '(') {
                    parentesis.push_back('(');
                    estado = Q1;
                    break;
                }
                
                if (exprMate[i] == ')') {
                    parentesis.pop_back();
                    estado = Q2;
                    break;
                } 

                if (exprMate[i] == 'l') {
                    estado = Q3;
                    break;
                }

                if (exprMate[i] == 92) {  // 92 = '\'
                    estado = Q4;
                    break;
                }


                traduccion += exprMate[i];
                i++;
                j = i;
                break; 
                
            case Q1:
                i++;
                {
                    int aux = i;
                    if (exprMate[i] == 92) {
                        while(exprMate[i] != ')') {
                            i++;
                        }
                        i = i + 2;
                        if (exprMate[i] == '^') {
                            traduccion += "pow(";
                            parentesis.push_back('(');
                            PcP = PcP + 1;
                            i = aux;
                            j = i;
                            estado = Q0;
                            break;
                        } else {
                            bandera2 = bandera;
                            estado = Q0;
                            i = aux;
                            j = i;
                            break;
                        }
                    }
                    while(exprMate[i] != ')') {
                        i++;
                        if (i > exprMate.size()) {
                            std::cout << "La expresión es incorrecta\n";
                            return -1;
                        }
                    }
                    i++;
                    if (exprMate[i] == '^') {
                        traduccion += "pow((";
                        parentesis.push_back('(');
                        parentesis.push_back('(');
                        PcP = PcP + 1;
                        i = aux;
                        estado = Q0;
                        j = i;
                        break;
                    } else {
                        traduccion += '(';
                        parentesis.push_back('(');
                        i = aux;
                        estado = Q0;
                        j = i;
                        break;
                    }
                }



            case Q2:

                if (PcP == 0 || (PcP == 0 && PcR == 0)) {
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
                    traduccion += bandera;
                    bandera.clear();
                    traduccion += ")";
                    parentesis.pop_back();
                    PcR--;
                    PcP--;
                    i++;
                    estado = Q0;
                    j = i;
                    break;
                } else if (bandera2 != "0" && PcR >= 1) {
                    traduccion += "),(1/";
                    traduccion += bandera2;
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
                traduccion += "log(";
                parentesis.push_back('(');
                i += 4;
                j = i;
                estado = Q0;
                break;



            case Q4:
                i++;
                if (exprMate[i] == '2') {
                    traduccion += "sqrt";
                    i += 2;
                    j = i;
                    estado = Q0;
                    break;
                } else {
                    while (exprMate[i] != '/') {
                        bandera += exprMate[i];
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
            
        }

    }
    
    
    escribirC(traduccion);

}