//
// Created by Pablo Brenes on 6 abr 2018.
//

#include "MuroLadrillos.h"
#include "token.h"

using namespace std;

/* en el constructor solo se inicializa el buffer para crear el string de salida */
MuroLadrillos::MuroLadrillos() {
    MuroLadrillos::buffer = "<!DOCTYPE html>\n"
                            "<html>\n"
                            "<head>\n"
                            "<title>Muro de Ladrillos</title>\n"
                            "</head>\n"
                            "<body>";
}

void MuroLadrillos::agregarLineaHTML(token tokenActual) {
    string strSpan;
    string lexema = tokenActual.lexema;
    string color = MuroLadrillos::vectorColores[tokenActual.codigoFamilia];
    string colorFont = MuroLadrillos::colorLetra[tokenActual.codigoFamilia];
    strSpan = "\n\t<span style=\"background-color: "+ color +"; color: "+ colorFont + "\">"+ lexema + "</span>\n";
    MuroLadrillos::buffer += strSpan;
}

void MuroLadrillos::escribirHTML(string nombreArchivo) {
    MuroLadrillos::buffer += "\n"
                             "</body>\n"
                             "</html>";
    ofstream archivoHTML;
    archivoHTML.open(nombreArchivo);
    archivoHTML << MuroLadrillos::buffer;
    archivoHTML.close();
}

const string *MuroLadrillos::getVectorColores() const {
    return vectorColores;
}

const string &MuroLadrillos::getBuffer() const {
    return buffer;
}

void MuroLadrillos::setBuffer(const string &buffer) {
    MuroLadrillos::buffer = buffer;
}
