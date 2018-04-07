//
// Created by Pablo Brenes on 24 mar 2018.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "token.h"
#include "automata.h"

using namespace std;

const int ajuste = 160;
const int estadoInicial = 1;
const int estadoError = 0;
const char endln = '\n';
const char separadorExtension = '.';
const string extension = "lht";

const string errorArchivoNoAccesible = "Error 404, el archivo no pudo ser abierto para lectura";
const string errorFormatoNoReconocible = "Error 405, formato de archivo no reconocible";

const int largoBuffer = 1024;

char buffer[largoBuffer + 1];
int indiceBuffer = 0;
int filaActual = 1;
int columnaActual = 0;
ifstream fuente;

bool revisarExtension(const string &nombreArchivo) {
    int posicion = nombreArchivo.find_last_of(separadorExtension);
    string extensionArchivo = nombreArchivo.substr((unsigned int) (posicion + 1));
    return extensionArchivo == extension;
}

bool tieneExtension(const string &nombreArchivo) {
    unsigned int posicion = nombreArchivo.find(separadorExtension);
    return posicion != string::npos;
}

void cargarNuevoBuffer() {
    buffer[0] = buffer[1024];
    char temporal;
    for (int i = 1; i < largoBuffer + 1; i++) {
        fuente.get(temporal);
        if (fuente.eof()) {
            fill(buffer + i, buffer + largoBuffer + 1, 0);
            break;
        }
        buffer[i] = temporal;
    }
    indiceBuffer = 0;
}

bool iniciarScanner(char archivoFuente[]) {

    string pathFuente = archivoFuente;

    if (tieneExtension(pathFuente)) {
        if (!revisarExtension(pathFuente)) {
            cout << errorFormatoNoReconocible << endln;
            return false;
        }
    } else {
        pathFuente = pathFuente + separadorExtension + extension;
    }

    fuente = ifstream(pathFuente, ios::in);

    if (fuente) {
        cargarNuevoBuffer();
    } else {
        cout << errorArchivoNoAccesible << endln;
    }

}

char demeCaracter() {
    if (indiceBuffer == 1024) {
        cargarNuevoBuffer();
    }
    indiceBuffer++;
    if (buffer[indiceBuffer] != '\0') {
        columnaActual++;
    }
    return buffer[indiceBuffer];
}

void tomeCaracter() {
    indiceBuffer--;
}

void ajustarPuntero() {
    filaActual++;
    columnaActual = 0;
}

int mapearCaracter(char caracter) {
    if (caracter == '\t')
        return 0;
    if (caracter == '\n')
        return 1;
    if (caracter == '\0')
        return 72;
    caracter -= 30;
    if (caracter > 92)
        caracter += 6;
    if (caracter > 66)
        caracter -= 32;
    return caracter;
}

token demeToken() {
    string lexema;                                                                                                      //Espacio para el lexema
    char caracterTemporal = demeCaracter();                                                                             //Leo el primer caracter
    int caracterMapeado = mapearCaracter(caracterTemporal);
    estadoAnterior = estadoInicial;                                                                                     //El primer estado anterior siempre es el inicial
    estadoActual = automata[estadoInicial][caracterMapeado] - ajuste;                                                   //Voy del estado inicial al que dicte el caracter leido
    token nuevoToken = token(filaActual, columnaActual);                                                                //Creo el token con los puntos actuales
    while (estadoActual > 0) {                                                                                          //Automata
        lexema += caracterTemporal;
        if (caracterTemporal == '\n') {
            ajustarPuntero();
            nuevoToken.aumentarFilaInicio();
            lexema.erase(0);
        }
        //else if (caracterTemporal == '\t') {
        //    nuevoToken.aumentarColumnaInicio();
        //    lexema.erase(0);
        //} else if (caracterTemporal == ' ') {
        //    //manejar el caso del ha nakhaan, supongo que lo sensato es saber en cual estado estoy si en de n luego de leer espacio en el ha
        //    nuevoToken.aumentarColumnaInicio();
        //    lexema.erase(0);
        //}
        caracterTemporal = demeCaracter();
        caracterMapeado = mapearCaracter(caracterTemporal);
        estadoAnterior = estadoActual;
        estadoActual = automata[estadoActual][caracterMapeado] - ajuste;
    }
    if (estadoActual == estadoError) {
        nuevoToken.asignarCodigoError(69);
    }
    if (caracterTemporal == '\n'){
        ajustarPuntero();
    }
    if (caracterTemporal != '\t' && caracterTemporal != '\n' && caracterTemporal != ' ') {                              //Verifico que no me haya comido algo importante
        tomeCaracter();                                                                                                 //De ser devuelvo el caracter al buffer
    }
    nuevoToken.asignarLexema(lexema);                                                                                   //Guardo el lexema en el token
    nuevoToken.asignarColumnaFin(lexema.length());
    nuevoToken.asignarCodigoFamilia(estadoActual + ajuste);                                                             //El ultimo estado seria el final que coincide con la familia
    return nuevoToken;
}

bool finalizarScanner() {
    if (fuente.is_open()) {
        fuente.close();
    }

}