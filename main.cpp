
#include <stack>
#include "lexer/lexer.h"
#include "gramaticas/Gramatica.h"
#include "gramaticas/GTablaFollows.h"
#include "gramaticas/nombresTerminales.h"
#include "semantico/tablaHash.h"
#include "semantico/erroresSemanticos.h"
#include "semantico/simbolos/simboloConstante.h"
#include "semantico/simbolos/simboloTipoDefinido.h"
#include "semantico/simbolos/simboloVariable.h"

#define LITERAL_ENTERO 0
#define LITERAL_CARACTER 1
#define LITERAL_STRING 2
#define LITERAL_BOOLEAN 3
#define LITERAL_CONJUNTO 4
#define LITERAL_FRACCION 5

#define TIPO_DATO_AJUSTE 47
#define TIPO_DATO_YOROSOR 0
#define TIPO_DATO_LIRIKH 1
#define TIPO_DATO_LAQAT 2
#define TIPO_DATO_AKAT 3
#define TIPO_DATO_YANQOKH 4
#define TIPO_DATO_KHALASSAR 5
#define TIPO_DATO_MARILAT 6
#define TIPO_DATO_RISSAT 7

#define IDENTIFICADOR 0

//Los tipos ya existentes en el lenguaje, entero, conjunto, registro, arreglo, ... son los siguientes
#define TIPO_BASE(X) ((47 <= (X) && (X) <= 53) || (X) == 55)

using namespace std;


bool esFollow(int i, int j);

int mapearTipoConstante(int familia);

int mapearTipoPorFamilia(int familia);

void procesarTipoDefinido(token *TA, tablaHash *tablaSimbolos);

const int posicionNombreArchivo = 1;
bool banderaErrorSintactico = false;
bool banderaErrorSemantico = false;

int tiposDeDatoPorLiteral[] = {-1,
                               LITERAL_ENTERO,
                               LITERAL_CARACTER,
                               LITERAL_STRING,
                               LITERAL_BOOLEAN,
                               LITERAL_BOOLEAN,
                               LITERAL_CONJUNTO};
int tiposDeDatoPorFamilia[] = {TIPO_DATO_YOROSOR,
                               TIPO_DATO_LIRIKH,
                               TIPO_DATO_LAQAT,
                               TIPO_DATO_AKAT,
                               TIPO_DATO_YANQOKH,
                               TIPO_DATO_KHALASSAR,
                               TIPO_DATO_MARILAT,
                               -1,
                               TIPO_DATO_RISSAT};

simboloConstante *constanteTemporal = new simboloConstante();
simboloTipoDefinido *tipoDefinidoTemporal = new simboloTipoDefinido();
simboloVariable *variableTemporal = new simboloVariable();
string identificador;

int main(int argc, char *argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    tablaHash *tablaSimbolos = new tablaHash(4096);

    token *TA = demePrimerToken();
    stack<int> PilaParsing;
    stack<int> PilaAuxiliar;

    PilaParsing.push(NO_TERMINAL_INICIAL);


    int EAP = 0;
    int regla = 0;

    while (TA->codigoFamilia != MARCA_DERECHA) {
        EAP = PilaParsing.top();
        PilaParsing.pop();
        if (TERMINAL(EAP)) {
            if (EAP == TA->codigoFamilia) {
                TA = demeToken();
            } else {
                banderaErrorSintactico = true;
                cout << "Error: Se esperaba un: '" << strTerminales[EAP] << "' y obtuve un: " << TA->lexema
                     << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                     << TA->columnaFin << '\n';
                int bandera = 1;
                do {
                    PilaAuxiliar.push(10);
                    PilaAuxiliar.push(38);
                    PilaAuxiliar.push(39);
                    PilaAuxiliar.push(40);
                    PilaAuxiliar.push(41);
                    PilaAuxiliar.push(42);
                    PilaAuxiliar.push(43);
                    PilaAuxiliar.push(156);

                    do {
                        if (EAP == TA->codigoFamilia) {
                            bandera = 0;
                        } else {
                            EAP = PilaAuxiliar.top();
                            PilaAuxiliar.pop();
                        }

                    } while (!PilaAuxiliar.empty() && bandera);
                    PilaAuxiliar.push(10);
                    PilaAuxiliar.push(156);
                    if (bandera) { TA = demeToken(); }

                } while (TA->codigoFamilia != MARCA_DERECHA && bandera);
            }

        } else if (NO_TERMINAL(EAP)) {
            regla = TablaParsing[EAP - NO_TERMINAL_INICIAL][TA->codigoFamilia];
            if (regla < 0) {
                banderaErrorSintactico = true;
                cout << "Error gramatical " << regla << '\t';
                cout << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                     << TA->columnaFin << '\n';
                //int follow = 0;
                int i = MAX_FOLLOWS;
                while (i--) {
                    TA = demeToken();
                    if (esFollow(EAP - NO_TERMINAL_INICIAL, TA->codigoFamilia)) {
                        //follow = 1;
                        break;
                    }
                }
            } else {
                int i = 0;
                while ((LadosDerechos[regla][i] > -1) && (i < MAX_LADO_DER)) {
                    PilaParsing.push(LadosDerechos[regla][i++]);
                }
            }

        } else { //simbolo semantico
            switch (EAP) {
                case ValidarExistenciaIdentificador:
                    if (tablaSimbolos->buscar(TA->lexema)) {
                        printff(errorIdentificadorDuplicado, TA->lexema, TA->fila, TA->columnaInicio);
                        banderaErrorSemantico = true;
                    }
                    break;
                case PrepararSimboloConstante:
                    delete constanteTemporal;
                    constanteTemporal = new simboloConstante(TA->lexema);
                    break;
                case ActualizarSimboloConstante:
                    constanteTemporal->tipo = mapearTipoConstante(TA->codigoFamilia);
                    tablaSimbolos->insertar(constanteTemporal);
                    break;
                case PrepararSimboloTipoDefinido:
                    delete tipoDefinidoTemporal;
                    tipoDefinidoTemporal = new simboloTipoDefinido(TA->lexema);
                    break;
                case ActualizarSimboloTipoDefinido:
                    procesarTipoDefinido(TA, tablaSimbolos);
                    break;
                case ValidarIdentificadorDeclarado:
                    if (!tablaSimbolos->buscar(TA->lexema)) {
                        printff(errorIdentificadorNoDeclarado, TA->lexema, TA->fila, TA->columnaInicio);
                        banderaErrorSemantico = true;
                    }
                    break;
            }
        }
    }

    PilaParsing.pop();
    if (!PilaParsing.empty()) {
        cout << "Fin de archivo inesperado" << '\n';
        finalizarScanner();
        return 0;
    }

    finalizarScanner();

    if (banderaErrorSintactico || banderaErrorSemantico || getError())
        return 0;

    cout << "Compilacion terminada.\n";
    return 0;

}

bool esFollow(int i, int j) {
    bool result = false;
    int k = 1;
    while (TablaFollows[i][k] >= 0) {
        if (j == TablaFollows[i][k]) { result = true; }
        k++;
    }
    return result;
}

int mapearTipoConstante(int familia) {
    if (familia == 117)
        return LITERAL_FRACCION;
    return tiposDeDatoPorLiteral[familia];
}

int mapearTipoPorFamilia(int familia) {
    return tiposDeDatoPorFamilia[familia - TIPO_DATO_AJUSTE];
}

void procesarTipoDefinido(token *TA, tablaHash *tablaSimbolos) {
    if (TIPO_BASE(TA->codigoFamilia))
        tipoDefinidoTemporal->tipoBase = mapearTipoPorFamilia(TA->codigoFamilia);
    if (TA->codigoFamilia == IDENTIFICADOR) {
        simbolo *simboloTemporal = tablaSimbolos->buscar(TA->lexema);
        if (simboloTemporal) {
            if (simboloTemporal->clasificador == simboloTemporal->_simboloTipoDefinido) {
                simboloTipoDefinido *simboloTipoDefinidoTemp = static_cast<simboloTipoDefinido *>(simboloTemporal);
                tipoDefinidoTemporal->tipoBase = simboloTipoDefinidoTemp->tipoBase;
            } else {
                printff(errorElementoNoEsTipoDefinido, TA->lexema, TA->fila, TA->columnaInicio);
                tipoDefinidoTemporal->tipoBase = -1;
                banderaErrorSemantico = true;
            }
        } else {
            printff(errorIdentificadorNoDeclarado, TA->lexema, TA->fila, TA->columnaInicio);
            tipoDefinidoTemporal->tipoBase = -1;
            banderaErrorSemantico = true;
        }
    }
    tablaSimbolos->insertar(tipoDefinidoTemporal);
}