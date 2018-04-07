//
// Created by Pablo Brenes on 6 abr 2018.
//

#include "MuroLadrillos.h"
#include "token.h"

using namespace std;

/* en el constructor solo se inicializa el buffer para crear el string de salida */
MuroLadrillos::MuroLadrillos() {

}

void MuroLadrillos::iniciarHTML(std::string nombreArchivo) {

    archivoHTML = ofstream(nombreArchivo, ios::out | ios::trunc);

    if (archivoHTML) {
        archivoHTML << "<!DOCTYPE html>\n"
                       "<html>\n"
                       "<head>\n"
                       "<title>Muro de Ladrillos</title>\n"
                       "</head>\n"
                       "<body>";
    } else {
        cout << "Imposible crear un archivo para el muro de ladrillos" << endl;
    }


}

void MuroLadrillos::agregarLineaHTML(token tokenActual) {
    string strSpan;
    string lexema = tokenActual.lexema;
    string color = MuroLadrillos::vectorColores[tokenActual.codigoFamilia];
    string colorFont = MuroLadrillos::colorLetra[tokenActual.codigoFamilia];
    strSpan = "\n\t<span style=\"background-color: "+ color +"; color: "+ colorFont + "\">"+ lexema + "</span>\n";
    archivoHTML << strSpan;
}

void MuroLadrillos::cerrarHTML() {
    string cerrar = "\n"
                    "</body>\n"
                    "</html>";
    archivoHTML << cerrar;
    archivoHTML.close();
}
