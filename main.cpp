
#include "parser.h"
#include "MuroLadrillos.h"

using namespace std;

const int posicionNombreArchivo = 1;

int main(int argc, char* argv[]) {

    iniciarScanner(argv[posicionNombreArchivo]);

    //MuroLadrillos murito;

    //murito.iniciarHTML("Muro de ladrillos.html");

    token portaTokens = demeToken();

    while (portaTokens.codigoFamilia != 118){
        //if (portaTokens.codigoFamilia != -1)
            //murito.agregarLineaHTML(portaTokens);
        portaTokens.imprimirToken();
        portaTokens = demeToken();

    }

    //murito.cerrarHTML();

    //finalizarScanner();

    return 0;
}