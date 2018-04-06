
#include "parser.h"
#include "MuroLadrillos.h"

using namespace std;

const int posicionNombreArchivo = 1;

int main(int argc, char* argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    MuroLadrillos murito;



    token portaTokens = demeToken();

    while (portaTokens.codigoFamilia != 159){
        murito.agregarLineaHTML(portaTokens);
        portaTokens = demeToken();
    }

    murito.escribirHTML("pixa.html");

    finalizarScanner();

    return 0;
}