
#include "parser.h"

using namespace std;

const int posicionNombreArchivo = 1;

int main(int argc, char* argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    for (int i = 0; i < 50; ++i) {
        demeToken().imprimirToken();
    }

    finalizarScanner();

    return 0;
}