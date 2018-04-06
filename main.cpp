
#include "parser.h"

using namespace std;

const int posicionNombreArchivo = 1;

int main(int argc, char* argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    token portaTokens = demeToken();
    while (portaTokens.codigoFamilia != 159){
        portaTokens.imprimirToken();
        portaTokens = demeToken();
    }

    finalizarScanner();

    return 0;
}