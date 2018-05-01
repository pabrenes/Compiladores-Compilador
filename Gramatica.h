/*
 * Gramatica.h
 *
 * 2018/04/29 15:59:19
 *
 * Archivo generado por GikGram 2.0
 *
 * Copyright © Olminsky 2011 Derechos reservados
 * Reproducción sin fines de lucro permitida
 */
#pragma once

#ifndef INC_Gramatica_h_
#define INC_Gramatica_h_

/* Constantes necesarias para un driver de parsing */

#define TERMINAL(X)  ((0 <= (X)) && ((X) <= 118))
#define NO_TERMINAL(X)  ((119 <= (X)) && ((X) <= 242))
#define MARCA_DERECHA 118
#define NO_TERMINAL_INICIAL 119
#define MAX_LADO_DER 11

/* Constantes con las rutinas semánticas */
/* NO SE DETECTARON SÍMBOLOS SEMÁNTICOS EN LA GRAMÁTICA */

/* Prototipos de las tablas */
extern const int TablaParsing[124][NO_TERMINAL_INICIAL];
extern const int LadosDerechos[268][MAX_LADO_DER];

/* Constantes necesarias para el algoritmo de recuperación de errores */
#define MAX_FOLLOWS 93

/* Prototipo de la tabla de follows */
extern const int TablaFollows[124][MAX_FOLLOWS];

extern const char* strTerminales[119];

#endif /* INC_Gramatica_h_ */
