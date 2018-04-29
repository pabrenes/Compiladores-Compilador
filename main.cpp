#include "Gramatica.h"
#include "parser.h"
#include <stack>

using namespace std;

const int posicionNombreArchivo = 1;

int main(int argc, char *argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    token* TA = demePrimerToken();
    stack<int> PilaParsing;
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
                cout << "ERROR: Se esperaba un: '" << EAP << "' y obtuve un: " << TA->lexema << '\n' << '\t' << '\t'
                     << " en linea: " << TA->fila << " columnaInicio: " << TA->columnaInicio << " columnaFin: "
                     << TA->columnaFin;
                return 0;
            }
        } else {
            regla = TablaParsing[EAP - NO_TERMINAL_INICIAL][TA->codigoFamilia];
            if (regla < 0) {
                cout << "Error gramatical " << regla << '\n' << '\t' << '\t' << " en linea: " << TA->fila
                     << " columnaInicio: " << TA->columnaInicio << " columnaFin: " << TA->columnaFin;
                return 0;
            } else {
                int i = 0;
                while ((LadosDerechos[regla][i] > -1) && (i < MAX_LADO_DER)) {
                    PilaParsing.push(LadosDerechos[regla][i++]);
                }
            }
        }
    }

    PilaParsing.pop();
    if (!PilaParsing.empty()) {
        cout << "Fin de archivo inesperado" << '\n';
    } else {
        cout << "Sintaxis correcta";
    }

    finalizarScanner();

    return 0;
}