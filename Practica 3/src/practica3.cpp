#include <iostream>
#include <stdlib.h>
#include <string.h>

#define inicio 0
#define Q0 1
#define Q1 2
#define Q2 3
#define Q3 4
#define fin 6
#define error 7



void escritura(std::string expresion) {
    FILE* arch = fopen("C.txt", "a+");
    for (int i = 0; i < expresion.size(); ++i) {
        fprintf(arch, "%c", expresion[i]);
    }
    fprintf(arch, "\n");
    fclose(arch); 
}


int main ( ) {
    
    std::string res, recorrido, bandera = "", bandera2 = "";
    int i = 0, estado = inicio, PcP = 0, PcR = 0, aux = 0;

    char exprMate[150 + 1];
    FILE* arch = fopen("M.txt", "r");
    while(!feof(arch)) {
        fscanf(arch, "%s", exprMate);
        recorrido += exprMate;
    }
    fclose(arch);
    std::cout << "El contenido del archivo 'M.txt es:\t" << exprMate << "\n";


    for (int j = 0; j <= recorrido.size() + 1; j++) {
        
        switch (estado) {

            case inicio:
                if (recorrido[i] == '(') {
                    estado = Q0;
                    break;
                }
                
                if (recorrido[i] == ')') {
                    estado = Q1;
                    break;
                } 

                if (recorrido[i] == 'l') {
                    estado = Q2;
                    break;
                }

                if (recorrido[i] == '\\') {
                    estado = Q3;
                    break;
                }

                if (recorrido[i] == '+' || recorrido[i] == '-' || recorrido[i] == '*' || recorrido[i] == '/' || recorrido[i] == '=') {
                    res += recorrido[i];
                    i++;
                    j = i;
                    break;
                } else {
                    res += recorrido[i];
                    i++;
                    j = i;
                    break; 
                }

                if (recorrido[i] == ' ') {
                    estado = fin;
                    j = i;
                    break;
                } else {
                    estado = fin;
                    j = i;
                    break;
                }



            case Q0:
                i++;
                {
                    int aux = i;
                    if (recorrido[i] == '\\') {
                        while(recorrido[i] != ')') {
                            i++;
                        }
                        i = i + 2;
                        if (recorrido[i] == '^') {
                            res += "pow(";
                            PcP = PcP + 1;
                            i = aux;
                            j = i;
                            estado = inicio;
                            break;
                        } else {
                            bandera2 = bandera;
                            estado = inicio;
                            i = aux;
                            j = i;
                            break;
                        }
                    }
                    while(recorrido[i] != ')') {
                        i++;
                        if (i > recorrido.size()) {
                            std::cout << "Falta un paréntesis en la expresión\n";
                            estado = error;
                            j = i;
                            break;
                        }
                    }
                    i++;
                    if (recorrido[i] == '^') {
                        res += "pow((";
                        PcP = PcP + 1;
                        i = aux;
                        estado = inicio;
                        j = i;
                        break;
                    } else {
                        res += '(';
                        i = aux;
                        estado = inicio;
                        j = i;
                        break;
                    }
                }



            case Q1:

                if (PcP == 0 || (PcP == 0 && PcR == 0)) {
                    if (aux >= 1) {
                        res += ')';
                        res += ')';
                        aux--;
                        i++;
                        estado = inicio;
                        j = i;
                        break;
                    } else {
                        res += ')';
                        i++;
                        estado = inicio;
                        j = i;
                        break;
                    }

                } else if (PcR >= 1) {
                    res += "),(1/";
                    res += bandera;
                    bandera.clear();
                    res += ")";
                    PcR--;
                    PcP--;
                    i++;
                    estado = inicio;
                    j = i;
                    break;
                } else if (bandera2 != "0" && PcR >= 1) {
                    res += "),(1/";
                    res += bandera2;
                    res += "))";
                    PcR--;
                    i++;
                    j = i;
                    estado = inicio;
                    break;
                } else {
                    res += ')';
                    res += ',';
                    i = i + 2;
                    j = i;
                    aux++;
                    PcP--;
                    estado = inicio;
                    break;
                }


            case Q2:
                res += "log(";
                i += 4;
                j = i;
                estado = inicio;
                break;



            case Q3:
                i++;
                if (recorrido[i] == '2') {
                    res += "sqrt";
                    i += 2;
                    j = i;
                    estado = inicio;
                    break;
                } else {
                    while (recorrido[i] != '/') {
                        bandera += recorrido[i];
                        i++;
                    }
                i++;
                res += "pow(";
                PcR++;
                PcP++;
                j = i;
                estado = inicio;
                break;
                }
            

            case fin:
                j = strlen(exprMate + 1);
                res += "\n";
                break;

            case error:
                std::cout << "La expresión es incorrecta\n";
                j = strlen(exprMate) + 1;
                break;
        }

    }
    
    std::cout << "La traduccion en lenguaje C es:\t " << res << "\n";
    escritura(res);

}