/**
 * Projet Tomates
 * Teensy 3.2
 * 
 * HC12 Library
 */

/******************************************************************************
 * Dans le main() :
 * 

// Entrée des données dans TransferBinaireOSV3 de type T_DATA_BINAIRE
//TransferBinaireOSV3.type_capteur = THGR810;
//TransferBinaireOSV3.HeureAcqui = time(NULL);
//TransferBinaireOSV3.Temperature = 12.5;
//TransferBinaireOSV3.HR = 33;
//TransferBinaireOSV3.numero = 1;
// Entrée des données dans l'union.
UnionOSV3.Data_Capteur.HeureAcqui = time(NULL);
UnionOSV3.Data_Capteur.type_capteur = THN132N;	//valeur 3 dans enum
UnionOSV3.Data_Capteur.Temperature = 12.5;
UnionOSV3.Data_Capteur.HR = 33;
UnionOSV3.Data_Capteur.numero = 1;


// Test transmission binaire par HC-12
for(int i=0;i<37;i++)
{
	// Attente Buffer libre
	while(!HC_12.writeable());
	// Emission d'un caratere
	HC_12.putc(UnionOSV3.Tab_TU[i]);
	// Affichage par le maitre de l'emission
	FTDI.printf("\r\nEmission de %c",UnionOSV3.Tab_TU[i]);
}

// Calcul d'un seul ROLLING CODE pour simuler changement de piles
if(!Fait_ROOLING_CODE) 
{
	//VAL_ROLLING_CODE = OSV3_ROLLING_CODE();
	VAL_ROLLING_CODE = 65;
	Fait_ROOLING_CODE = true;
}

******************************************************************************/


#ifndef HC12_H
#define HC12_H

#include "mbed.h"

class HC12
{

public:
	typedef enum {THGR810, UVN800, BTHR968, THN132N} list_OSV3;

	/**
	 * HC12 Constructor
	 */
	HC12();

	/**
	 * HC12 Destructor
	 */
	~HC12();

	/**
	 * Codage fonction IT
	 * 
	 * Codage des fonctions d'IT pour reception XBee par IT suite TX en binaire
	 * Aucun caractere de perdu
	 */
	void XBee_IT_RX(void);
	
	/**
	 * Codage des fonctions d'IT pour LCD NEXTION
	 * Aucun caractere de perdu
	 */	
	void LCD_NEXTION_IT_RX(void);
	
	/**
	 * Fonction d'IT associée au BT
	 */
	void Acq_Car_IT(void);
	
	/**
	 * Copie du tableau data_RX dans le tableau Copie_data_RX
	 * Le compilateur ne supporte pas de travailler directement avec un type volatile dans la fonction Extraction_Data
	 */	
	void Copie_de_Tableau(volatile char *s, char *d);



	struct T_DB {
		time_t HeureAcqui; // 4 octets
		float Temperature; // 4 octets
		float HR; // 4 octets
		float UV; // 4 octets
		float UVA; // 4 octets
		float UVB; // 4 octets
		float Pression; // 4 octets
		int numero; // 4 octets
		unsigned char RollingCode; // 1 octet
		list_OSV3 type_capteur; // 4 octets
	}; // sizeof donne 37 octets
	
	struct T_DB Data_Capteur;
	char Tab_TU[37]; // meme taille que T_DB et au même emplacement mémoire.
	
};

#endif