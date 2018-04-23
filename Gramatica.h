/*
 * Gramatica.h
 *
 * 2018/04/22 17:05:11
 *
 * Archivo generado por GikGram 2.0
 *
 * Copyright © Olminsky 2011 Derechos reservados
 * Reproduccion sin fines de lucro permitida
 */
#pragma once

#ifndef INC_Gramatica_h_
	#define INC_Gramatica_h_

	/* Constantes necesarias para un driver de parsing */
	#define TERMINAL(X)  ((0 <= (X)) && ((X) <= 118))
	#define NO_TERMINAL(X)  ((119 <= (X)) && ((X) <= 249))
	#define MARCA_DERECHA 118
	#define NO_TERMINAL_INICIAL 119
	#define MAX_LADO_DER 11

	/* Constantes con las rutinas semanticas */
	/* NO SE DETECTARON SiMBOLOS SEMaNTICOS EN LA GRAMaTICA */

	/* Prototipos de las tablas */
	extern const int TablaParsing[131][NO_TERMINAL_INICIAL];
	extern const int LadosDerechos[279][MAX_LADO_DER];

#endif /* INC_Gramatica_h_ */
