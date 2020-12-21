//******************************************************************************
//    Nom du fichier : GLcd.c
//    Auteur : Alain Champagne                  
//    Date de création : 16-03-2006 
//    Date de modification pour le STM32F4 : 23-12-2015
//    Fonction de controle d'un ecran graphique de type KS0108.
// 
//******************************************************************************
//Include
#include "GLcd.h"
#include "Font.h"
#include <stdbool.h>
#include "ST.h"
//**********************************ucInputGLcd*********************************
//    Nom de la fonction : ucInputGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 02-04-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Lecture d'une donnée sur les registres de l'écran LCD Graph.
//                  KS0108.  La donnée est présente à une adresse spécifiée en 
//                  paramètre d'entrée. 
//
//    Appel : ucData ucInputGLcd(0x04);
//            Permet de lire la donnée sur le dispositif à l'adresse 0x04. 
//           
//    Fonctions appelées : ucReadIO.
//    Paramètres d'entrée : ucAdresse.
//    Paramètres de sortie : unsigned char.               
//    Variables utilisées : ucDonnee, ucTest.            
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
uint8_t ucInputGLcd(uint8_t ucAdresse)
{
  uint8_t ucDonnee, ucTest;      
  
  ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);
  while ((ucTest & 0x80) == 0x80)                      //Attente du BUSY FLAG.
    ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);        

  ucDonnee = ucReadIO (CS0, 1, (ucAdresse | 0x04));    //Lire la donnee.  
  return(ucDonnee);                                    //Retourner la donnee.  
} 
//fin routine ucInputGLcd-------------------------------------------------------


//*********************************vOutputGLcd**********************************
//    Nom de la fonction : vOutputGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 02-04-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Ecriture d'une donnée sur les registres de l'écran KS0108.
//                  La donnée est écrite à une adresse spécifiée en paramètre 
//                  d'entrée. 
//
//    Appel : vOutputGLcd(0x04, 0x55);
//            Permet d'écrire la donnée 0x55 sur le dispositif à l'adresse 0x04. 
//     
//    Fonctions appelées : ucReadIO, vWriteIO.
//    Paramètres d'entrée : ucAdresse, ucDonnee.
//    Paramètres de sortie : Aucun.               
//    Variables utilisées :  ucTest.         
//    Equate : Aucun	
//    #Define : Aucun   
//                                    
//******************************************************************************   
void vOutputGLcd(uint8_t ucAdresse, uint8_t ucDonnee)
{   
  uint8_t ucTest; 
  
  ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);  
  while ((ucTest & 0x80) == 0x80)                    //Attente du BUSY FLAG.
    ucTest = ucReadIO (CS0, 1, ADRBUSYFLAG);
  
  vWriteIO(ucDonnee, CS0, 1, (ucAdresse & 0x0B));    //Ecriture de la donnee.
}    
//fin routine vOutputGLcd-------------------------------------------------------


//***********************************vInitGLcd**********************************
//    Nom de la fonction : vInitGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Initialisation de l'ecran graphique KS0108.
//
//    Appel : vInitGLcd();
//            Initialise l'écran selon des paramètres établis. 
//           
//    Fonctions appelées : vOutputGLcd.
//    Paramètres d'entrée : Aucun.
//    Paramètres de sortie : Aucun.                
//    Variables utilisées : Aucun. 
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vInitGLcd(void)
{
//Cote gauche 
  vOutputGLcd(ADRINSTRLEFTW, 0x3E);  //Display OFF. 
  vOutputGLcd(ADRINSTRLEFTW, 0xC0);  //Start line.     
  vOutputGLcd(ADRINSTRLEFTW, 0xB8);  //Page a 0.
  vOutputGLcd(ADRINSTRLEFTW, 0x40);  //Adresse Y a 0.      
  vOutputGLcd(ADRINSTRLEFTW, 0x3F);  //Display ON.
//Cote droit  
  vOutputGLcd(ADRINSTRRIGHTW, 0x3E);  //Display OFF.
  vOutputGLcd(ADRINSTRRIGHTW, 0xC0);  //Start line.     
  vOutputGLcd(ADRINSTRRIGHTW, 0xB8);  //Page a 0.
  vOutputGLcd(ADRINSTRRIGHTW, 0x40);  //Adresse Y a 0.      
  vOutputGLcd(ADRINSTRRIGHTW, 0x3F);  //Display ON.
  vPutBMPGLcd(ucST);
  HAL_Delay(1000);
  vClearGLcd(0x00);
}
//fin routine vInitGLcd---------------------------------------------------------


//**********************************vClearGLcd**********************************
//    Nom de la fonction : vClearGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Effacer l'ecran graphique KS0108.
//
//    Appel : vClearGLcd(0x00); 
//            Place tous les pixel à 0, donc efface l'écran.
//
//    Fonctions appelées : vOutputGLcd()
//    Paramètres d'entrée : ucData
//    Paramètres de sortie : Aucun                
//    Variables utilisées : i et j
//    Equate : Aucun
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW, ADRDATALEFTW, ADRDATARIGHTW
//                                    
//******************************************************************************
void vClearGLcd(uint8_t ucData)
{
  int i, j;

  for (j=0; j<8; j++)
  {              
    vOutputGLcd(ADRINSTRRIGHTW, (0xB8+j));  //Page                                 
    vOutputGLcd(ADRINSTRLEFTW, (0xB8+j));   //Page    
    for (i=0; i<64; i++)
    {
      vOutputGLcd(ADRDATALEFTW, ucData); 
    }     
    for (i=0; i<64; i++)
    {
      vOutputGLcd(ADRDATARIGHTW, ucData); 
    }     
  }     
}   
//fin routine vClearGLcd--------------------------------------------------------


//********************************vPutPixelGLcd*********************************
//    Nom de la fonction : vPutPixelGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Placer un pixel en x et y sur l'ecran graphique KS0108. 
//                  X = 0 a 127 et Y = 0 a 63.  Pour placer le pixel, on doit
//                  lire la position 8 bits, à l'écran, et masquer le bit à 
//                  afficher.  La lecture doit être faite deux fois (directive
//                  du manufacturier) et on doit replacer le curseur après 
//                  chaque lecture.
//           
//    Appel : vPutPixelGLcd(10,10); 
//            Active un pixel à la position 10, 10.
//
//    Fonctions appelées : vOutputGLcd()ucInputGLcd()
//    Paramètres d'entrée : ucX et ucY
//    Paramètres de sortie : Aucun             
//    Variables utilisées : ucAdresse, ucData, ucDataY, ucDataOld
//    Equate : Aucun	
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW
//                                    
//******************************************************************************
void vPutPixelGLcd(uint8_t ucX, uint8_t ucY)
{
  uint8_t ucData, ucDataY, ucDataOld; 
  uint8_t ucAdresse;
//Choix du cote de l'ecran    
  if (ucX >= 64) 
  { 
    ucAdresse = ADRINSTRRIGHTW;
    ucX = ucX - 64;
  }  
  else
    ucAdresse = ADRINSTRLEFTW; 
//Position de l'adresse (Set Address).
  ucData = 0x40 | ucX; 
  ucDataY = ucData; 
  vOutputGLcd((ucAdresse & 0x03), ucDataY);
//Position de la page (Set Page).
  ucData = 0xB8 | ucY/8;
  vOutputGLcd((ucAdresse & 0x03), ucData); 
//Lecture de l'octet en memoire a deux reprises.
  ucDataOld = ucInputGLcd(ucAdresse | 0x0C);
//Repositionner le curseur.  
  vOutputGLcd((ucAdresse & 0x03), ucDataY);
  vOutputGLcd((ucAdresse & 0x03), ucData); 
  ucDataOld = ucInputGLcd(ucAdresse | 0x0C); 
//Repositionner le curseur.
  vOutputGLcd((ucAdresse & 0x03), ucDataY);
  vOutputGLcd((ucAdresse & 0x03), ucData); 
//Ecriture du pixel.
  ucData = 0x01;
  ucData = ucDataOld | (ucData << ucY % 8);
  vOutputGLcd((ucAdresse | 0x08), ucData);  
}      
//fin routine vPutPixelGLcd-----------------------------------------------------


//********************************vClearPixelGLcd*******************************
//    Nom de la fonction : vClearPixelGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Effacer un pixel en x et y sur l'ecran graphique KS0108. 
//                  X = 0 a 127 et Y = 0 a 63.  Pour effacer le pixel, on doit
//                  lire la position 8 bits, à l'écran, et masquer le bit à 
//                  afficher.  La lecture doit être faite deux fois (directive
//                  du manufacturier) et on doit replacer le curseur après 
//                  chaque lecture.
//
//    Appel : vClearPixelGLcd(10,10); 
//            Désactive un pixel à la position 10, 10.
//           
//    Fonctions appelées : vOutputGLcd(), ucInputGLcd().
//    Paramètres d'entrée : ucX et ucY.
//    Paramètres de sortie : Aucun.                
//    Variables utilisées : ucAdresse, ucData, ucDataY, ucDataOld. 
//    Equate : Aucun	
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW
//                                
//******************************************************************************
void vClearPixelGLcd(uint8_t ucX, uint8_t ucY)
{
  uint8_t ucAdresse;  
  uint8_t ucData, ucDataY, ucDataOld;
   
//Choix du cote de l'ecran    
  if (ucX >= 64) 
  { 
    ucAdresse = ADRDATARIGHTW;
    ucX = ucX - 64;
  }  
  else
    ucAdresse = ADRDATALEFTW;     
//Position de l'adresse Y.
  ucData = 0x40 | ucX; 
  ucDataY = ucData; 
  vOutputGLcd((ucAdresse & 0x03), ucDataY);
//Position de la page.
  ucData = 0xB8 | ucY/8;
  vOutputGLcd((ucAdresse & 0x03), ucData); 
//Lecture de l'octet en memoire a deux reprises.  
  ucDataOld = ucInputGLcd(ucAdresse | 0x0C); 
//Repositionner le curseur.  
  vOutputGLcd((ucAdresse & 0x03), ucDataY);
  vOutputGLcd((ucAdresse & 0x03), ucData); 
  ucDataOld = ucInputGLcd(ucAdresse | 0x0C); 
//Repositionner le curseur.  
  vOutputGLcd((ucAdresse & 0x03), ucDataY);
  vOutputGLcd((ucAdresse & 0x03), ucData); 
//Ecriture du pixel. 
  ucData = 0x01;
  ucData = ucData << (ucY % 8);
  ucData = ucData ^ 0xFF; 
  ucData = ucData & ucDataOld;  
  vOutputGLcd((ucAdresse | 0x08), ucData);  
}  
//fin routine vClearPixelGLcd---------------------------------------------------


//*******************************vDrawLineGLcd**********************************
//    Nom de la fonction : vDrawLineGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 20-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Dessiner une ligne de la coordonnee (X1Y1) avec une  
//                  direction (H ou V) et une longueur.
//
//    Appel : vDrawLineGLcd(0, 0, 20, 'H');
//            Trace une ligne horizontale de 20 pixel dont l'origine est 0, 0.
//           
//    Fonctions appelées : vPutPixelGLcd()
//    Paramètres d'entrée : ucX, ucY, ucLong, ucDir
//    Paramètres de sortie : Aucun
//    Variables utilisées : i
//    Equate : Aucun	
//    #Define : ADRINSTRRIGHTW, ADRINSTRLEFTW
//                                    
//******************************************************************************
void vDrawLineGLcd(uint8_t ucX, uint8_t ucY, uint8_t ucLong, uint8_t ucDir)
{   
int i;
  if (ucDir == 'H')
  {
     for (i = 0; i <= ucLong; i ++)
     {
       vPutPixelGLcd(ucX+i, ucY); 
     }    
  }
  if (ucDir == 'V')
  {
     for (i = 0; i <= ucLong; i ++)
     {
       vPutPixelGLcd(ucX, ucY+i); 
     }
  }                                 
}
//fin routine vDrawLineGLcd----------------------------------------------------- 


//******************************vDrawRectangleGLcd******************************
//    Nom de la fonction : vDrawRectangleGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 18-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Dessiner un rectangle aux coordonnees (X1Y1, X2Y2).
//
//    Appel : vDrawRectangleGLcd(1,1,20,20);
//            Traçage d'un rectangle dont la diagonale est positionnée
//            aux coordonnées X1=1, Y1=1 et X2=20, Y2=20.
//
//    Fonctions appelées : vPutPixelGLcd()
//    Paramètres d'entrée : ucX1, ucY1, ucX2 et ucY2
//    Paramètres de sortie : Aucun     
//    Variables utilisées : ucLong et ucHaut, i
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vDrawRectangleGLcd(uint8_t ucX1, uint8_t ucY1, uint8_t ucX2, uint8_t ucY2)
{
  uint8_t ucLong, ucHaut;
  uint8_t i;
  
  ucLong = ucX2 - ucX1;
  ucHaut = ucY2 - ucY1; 
//Tracer les lignes horizontales.   
  for (i = 0; i <= ucLong; i ++)
  {
     vPutPixelGLcd(ucX1+i, ucY1); 
     vPutPixelGLcd(ucX1+i, ucY2); 
  }                             
//Tracer les lignes verticales.   
  for (i = 0; i <= ucHaut; i ++)
  {
     vPutPixelGLcd(ucX1, ucY1+i); 
     vPutPixelGLcd(ucX2, ucY1+i); 
  }  
}
//fin routine vDrawRectangleGLcd------------------------------------------------


//********************************vDrawCircleGLcd*******************************
//    Nom de la fonction : vDrawCircleGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 18-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Dessiner un cercle de rayon ucRayon a la coordonnee ucX et
//                  ucY.
//    
//    Appel : vDrawCircleGLcd(20, 50, 10);
//            Traçage d'un cercle de 10 de rayon dont le centre est situé
//            aux coordonnées X=20, Y=50.
//
//    Fonctions appelées : vPutPixelGLcd()
//    Paramètres d'entrée : ucX, ucY et ucRayon
//    Paramètres de sortie : Aucun    
//    Variables utilisées : iSwitch, iX, iY, ucD
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vDrawCircleGLcd(uint8_t ucX, uint8_t ucY, uint8_t ucRayon)
{
  int iSwitch=0, iX=0, iY=0;
  unsigned char ucD;
  
  ucD = ucY - ucX;
  iY = ucRayon;
  iSwitch = 3 - (2 * ucRayon);
  while (iX <= iY)
  {
     vPutPixelGLcd((ucX + iX),(ucY + iY));
     vPutPixelGLcd((ucX + iX),(ucY - iY));
     vPutPixelGLcd((ucX - iX),(ucY + iY));
     vPutPixelGLcd((ucX - iX),(ucY - iY));    
     vPutPixelGLcd((ucY + iY - ucD),(ucY + iX));     
     vPutPixelGLcd((ucY + iY - ucD),(ucY - iX));     
     vPutPixelGLcd((ucY - iY - ucD),(ucY + iX));     
     vPutPixelGLcd((ucY - iY - ucD),(ucY - iX));  
     
     if (iSwitch < 0)
     {
        iSwitch += (4 * iX + 6);
     }                          
     else
     {
        iSwitch += (4 * (iX - iY) + 10);
        iY --;
     }        
     iX++; 
  }
}
//fin routine vDrawCircleGLcd---------------------------------------------------


//**********************************vPutCharGLcd********************************
//    Nom de la fonction : vPutCharGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 17-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Ecriture d'un caractere a une position Ligne Colonne sur 
//                  l'ecran GLCD. Il est possible d'utiliser les colonnes 0 a 15 
//                  et les lignes 0 a 7 pour le FONT 7, les colonnes 0 a 19 et 
//                  les lignes 0 a 7 pour le FONT 5 et les colonnes 0 a 31 et  
//                  les lignes 0 a 7 pour le FONT 3.
//           
//    Exemple d'appel : vPutCharGLcd('A', 1, 0, 3);
//                      Écrit le caractère A de grosseur de font 3 à la ligne 1
//                      et la colonne 0.
//
//    Fonctions appelées : vOutputGLcd()
//    Paramètres d'entrée : ucChar, ucLigne et ucColonne
//    Paramètres de sortie : Aucun
//    Variables utilisées : uiAdresse, i, iChar, ucX et ucData
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vPutCharGLcd(uint8_t ucChar, uint8_t ucLigne, uint8_t ucColonne, uint8_t ucFont)
{      
uint8_t ucAdresse; 
int8_t i, iChar; 
uint8_t ucX, ucData;  
  iChar = ucChar - 0x20;                //Choix de la ligne dans le tableau.  
  if (ucFont == 3)                      //Si on utilise le font de 3 pixels.
  {
    ucX = (ucColonne * 4);              //Calcul de la position en X.
  }
  if (ucFont == 5)                      //Si on utilise le font de 5 pixels.
  { 
    ucX = ((ucColonne * 6) + 4);        //Calcul de la position en X.
  }
  if (ucFont == 7)                      //Si on utilise le font de 3 pixels.
  {
    ucX = (ucColonne * 8);              //Calcul de la position en X.
  }                                      
  //Choix du cote de l'ecran    
  if (ucX >= 64) 
  { 
    ucAdresse = ADRDATARIGHTW;
    ucX = ucX - 64;
  }  
  else
    ucAdresse = ADRDATALEFTW;     
//Position de l'adresse Y.
  ucData = 0x40 | ucX;  
//  LCDDI = 0;    
  vOutputGLcd((ucAdresse & 0x07), ucData);
//Position de la page. 
  ucData = 0xB8 | ucLigne;
  vOutputGLcd((ucAdresse & 0x07), ucData); 
//  LCDDI = 1;     
  if (ucFont == 3)                      //Si on utilise le font de 3 pixels.
  {
    for (i = 0; i <= 2; i++)
    {    
      ucData = ucFontSystem3x6[iChar][i];
      vOutputGLcd((ucAdresse | 0x08), ucData);  
    }
  }
  if (ucFont == 5)                      //Si on utilise le font de 5 pixels.
  { 
    for (i = 0; i <= 4; i++)
    {    
      ucData = ucFontSystem5x8[iChar][i];
      vOutputGLcd((ucAdresse | 0x08), ucData);  
    } 
  }
  if (ucFont == 7)                      //Si on utilise le font de 7 pixels.
  {
    for (i = 0; i <= 6; i++)
    {    
      ucData = ucFontSystem7x8[iChar][i];
      vOutputGLcd((ucAdresse | 0x08), ucData);  
    }
  }
}
//fin routine vPutCharGLcd------------------------------------------------------


//*********************************vPutStringGLcd*******************************
//    Nom de la fonction : vPutStringGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 17-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Écriture d'un ligne de caractères a une position Ligne sur 
//                 l'écran GLCD. Il est possible d'utiliser les lignes 0 a 7 et
//                 les FONT 3 ou 5.  32 caractères de font 3, 20 caractères de
//                 font 5 et 16 caractères de font 7 par lignes.
//           
//    Exemple d'appel : vPutStringGLcd(ucTab, 0, 3);
//                      Écrit une chaîne de caractères de font 3 provenant d'un 
//                      tableau ucTab à la ligne 0.
//
//    Fonctions appelées : vPutCharGLcd()
//    Paramètres d'entrée : ucChar, ucLigne et ucColonne
//    Paramètres de sortie : Aucun
//    Variables utilisées : uiAdresse, i
//    Equate : Aucun	
//    #Define : Aucun
//                                    
//******************************************************************************
void vPutStringGLcd(uint8_t ucTab[], int8_t iLigneLcd, uint8_t ucFont)
{
  int i; 
  {
     if (ucFont == 3)
     {
        for (i = 0; i <= 31; i++)
        {
          vPutCharGLcd(ucTab[i], iLigneLcd, i, 3);
        }
     }
     if (ucFont == 5)
     {
        for (i = 0; i <= 19; i++)
        {
          vPutCharGLcd(ucTab[i], iLigneLcd, i, 5);
        }
     } 
     if (ucFont == 7)
     {
        for (i = 0; i <= 15; i++)
        {
          vPutCharGLcd(ucTab[i], iLigneLcd, i, 7);
        }
     }
  }
}  
//fin routine vPutStringGLcd----------------------------------------------------


//**********************************vPutBMPGLcd*********************************
//    Nom de la fonction : vPutBMPGLcd
//    Auteur : Alain Champagne                  
//    Date de création : 15-03-2006   
//    Date de modification pour le STM32F4 : 23-12-2015
//    Description : Affiche un BMP à l'écran graphique KS0108.
//
//    Appel : vPutBMPGLcd(ucTab[]); 
//            Dessine un fichier BMP de 128 X 64 à l'écran.
//           
//    Fonctions appelées : vOutputGLcd()
//    Paramètres d'entrée : Aucun
//    Paramètres de sortie : Aucun                
//    Variables utilisées : i et j
//    Equate : Aucun	
//    #Define : ADRDATALEFTW, ADRDATARIGHTW
//                                    
//******************************************************************************
void vPutBMPGLcd(uint8_t ucTab[])
{
  int8_t i, j;  
//  LCDDI = 0; 
  vOutputGLcd((ADRDATALEFTW & 0x07), 0x40);  //Adresse Y a 0.  
  vOutputGLcd((ADRDATARIGHTW &0x07), 0x40);  //Adresse Y a 0. 
  for (j=0; j<8; j++)
  {              
//  LCDDI = 0;    
    vOutputGLcd((ADRDATARIGHTW & 0x07), (0xB8+j));  //Page                                 
    vOutputGLcd((ADRDATALEFTW & 0x07), (0xB8+j));   //Page     
//  LCDDI = 1;
    for (i=0; i<64; i++)
    {
      vOutputGLcd((ADRDATALEFTW | 0x08), ucTab[i + (j * 128)]); 
    }     
    for (i=0; i<64; i++)
    {
      vOutputGLcd((ADRDATARIGHTW | 0x08), ucTab[i + 64 + (j * 128)]); 
    }     
  }     
}   
//fin routine vPutBMPGLcd-------------------------------------------------------

//***************************************************************************//
void vWriteByteLCD (bool bSide, unsigned char ucLine, unsigned char ucCol, unsigned char ucData)
//                                                                           //
// Description:                                                              //
//                                                                           //
// Parametre d'entre:              aucun                                     //
//                                                                           //
// Parametre de sortie:            aucun                                     //
//                                                                           //
//***************************************************************************//

{
        vOutputGLcd(0x01+bSide, (0x40+ucCol));
        vOutputGLcd(0x01+bSide, (0xB8+ucLine));
        vOutputGLcd(0x09+bSide, ucData);  
}

//***************************************************************************//
unsigned char ucReadByteLCD (bool bSide, unsigned char ucLine, unsigned char ucCol)
//                                                                           //
// Description:                                                              //
//                                                                           //
// Parametre d'entre:              aucun                                     //
//                                                                           //
// Parametre de sortie:            aucun                                     //
//                                                                           //
//***************************************************************************//

{
        unsigned char ucData;
        unsigned char i;
        
        for(i=0;i<2;i++)
        {
          vOutputGLcd(0x01+bSide, (0x40+ucCol));
          vOutputGLcd(0x01+bSide, (0xB8+ucLine));
          ucData = ucInputGLcd(0x0D+bSide);
        }

        return (ucData);
}

//***************************************************************************//
                            void vScrollLCD (void)
//                                                                           //
// Description:                                                              //
//                                                                           //
// Parametre d'entre:              aucun                                     //
//                                                                           //
// Parametre de sortie:            aucun                                     //
//                                                                           //
//***************************************************************************//

{
  uint8_t x;
  uint8_t y;
  uint8_t z;  
  uint8_t ucTemp;
  
  //  Y = Ligne, X = Colonne, Z = Cote (moitie gauche ou droite)
  for(y=0;y<7;y++)  
  {
    for(z=0;z<2;z++)
    {
      for(x=0;x<64;x++)
      { 
        ucTemp = ucReadByteLCD (z,y+1,x);        
        vWriteByteLCD (z,y,x,ucTemp);
      }
    }
  }
  // Clear la derniere ligne.
  for(z=0;z<2;z++)
  {
    vOutputGLcd(0x01+z, (0xBF));
    for(x=0;x<64;x++)vOutputGLcd(0x09+z, 0x00);
  }
}

//***************************************************************************//
                  void vLineScrollLCD (unsigned char ucLine)
//                                                                           //
// Description:                                                              //
//                                                                           //
// Parametre d'entre:              aucun                                     //
//                                                                           //
// Parametre de sortie:            aucun                                     //
//                                                                           //
//***************************************************************************//

{
  uint8_t x;  
  uint8_t ucTemp;
  
  for(x=0;x<63;x++)
  { 
    ucTemp = ucReadByteLCD (1,ucLine,x+1);    
    vWriteByteLCD (1,ucLine,x,ucTemp);   
  }
  
  ucTemp = ucReadByteLCD(0,ucLine,0);
  vWriteByteLCD (1,ucLine,0x7F,ucTemp);  
  
  for(x=0;x<62;x++)
  { 
    ucTemp = ucReadByteLCD(0,ucLine,x+1);    
    vWriteByteLCD (0,ucLine,x,ucTemp);    
  }
  
  vWriteByteLCD (0,ucLine,127,0x00);
}

//***************************************************************************//
void vHEXtoLCD (unsigned char ucLine, unsigned char ucCol, unsigned char ucHex, unsigned char ucFont)
//                                                                           //
// Description: Affiche une valeur hexadecimal sur le LCD. La colonne        //
//		demande est celle ou s'affichera les MSB.                    //
//                                                                           //
// Parametre d'entre:      (Ligne, Colonne, valeur a ecrire)	             //
//                                                                           //
// Parametre de sortie:                   aucun                              //
//                                                                           //
//***************************************************************************//

	{
		unsigned char ucTemp;
		
		ucTemp = ucHex>>4;
		if (ucTemp > 9) ucTemp += 0x37;
		else ucTemp += 0x30;
		vPutCharGLcd(ucTemp, ucLine, ucCol, ucFont);
		ucTemp = ucHex & 0x0F;
		if (ucTemp > 9) ucTemp += 0x37;
		else ucTemp += 0x30;
		vPutCharGLcd(ucTemp, ucLine, (ucCol+1), ucFont);
	}

//***************************************************************************//  
void vDECtoLCD (unsigned char ucLine, unsigned char ucCol, unsigned char ucDec, unsigned char Font)
//                                                                           //
// Description:  Affiche une valeur decimal entre 0 et 99 sur le LCD.        //
//		 La colonne demande est celle ou s'affichera les dizaines.   //
//		 Un 0 au dizaine ne sera pas affiche.                        //
//                                                                           //
// Parametre d'entre:        (Ligne, Colonne, valeur a ecrire)	             //
//                                                                           //
// Parametre de sortie:                   aucun                              //
//                                                                           //
//***************************************************************************//
							 
  {
        if (ucDec/10 == 0) vPutCharGLcd(' ', ucLine, ucCol, Font);
        else vPutCharGLcd(((ucDec/10)+ 0x30), ucLine, ucCol, Font);
        vPutCharGLcd(((ucDec%10)+ 0x30), ucLine, ucCol+1, Font);
  }