/*
---------------------------------------------------------
|							|
|		     Machaca Topos			|
|			   1.0				|
|			4 Niveles			|
|							|
|	    Estructura de Computadores 2015		|
|							|
|	(c) 2015 Escuela Superior de Informatica	|
|							|
---------------------------------------------------------
|							|
|		  Josue Gutierrez Duran			|
|		  Ruben Sanchez Sevilla			|
|		Juan Manuel Palacios Navas		|
|	    	   Jaime Muñoz Padilla			|
|		   Sergio Caro Rodrigo			|
|							|
---------------------------------------------------------
*/


/*
-------------------------
|	Librerias	|
-------------------------
*/


// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes libreria time
#include <time.h>


/*
-------------------------
|	Funciones	|
-------------------------
*/

void pausa() ;
int nivel1(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y);
int nivel2 (s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y);
int nivel3(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y);
int nivel4(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y);
int final();
int ganado();
int perdido();
int menuprincipal() ;
void cabecera() ;
int creditos() ;



/*
-------------------------
|	Variables	|
-------------------------
*/

// Inicializacion Variables de Juego
int incremento = 50 ; // Puntos que da un acierto
int decremento = 25 ; // Puntos que quita un error
int tiempo = 60 ; // Tiempo en segundos
int pl1 = 400 ; // Puntos necesarios para superar el nivel 1
int pl2 = 650 ; // Puntos necesarios para superar el nivel 2
int pl3 = 900 ; // Puntos necesarios para superar el nivel 3
int pl4 = 1350 ; // Puntos necesarios para superar el nivel 4



// Variables Primer Nivel
bool op1_1 = false ;
bool op1_2 = false ; 
bool op1_3 = false ;
bool op1_4  = false ; 

// Inicializacion Variables de Sistema
int contador = 0 ;
int numero = 0 ;
int puntos = 0 ;

int estado = 0 ;
int nivel = 1 ;

bool control ;

bool jugar = false ;


/*
-------------------------
|      Temporizador	|
-------------------------
*/


void timeout()
{
	int dificultad ;
	if(jugar){
	
	  	char mytext[32];

	    	sprintf(mytext,"Tiempo: %d                 ", tiempo--);
		NF_WriteText(0, 2, 1,10, mytext);
		NF_UpdateTextLayers();			// Actualiza las capas de texto

		if(tiempo<=0){
	
			sprintf(mytext,"Su Tiempo se ha agotado   ");
			NF_WriteText(0, 2, 1,10, mytext);
			NF_UpdateTextLayers();			// Actualiza las capas de texto
			control = false ;
			contador = 0 ;

		} else {
			if(nivel==1){dificultad=4;}
			if(nivel==2){dificultad=3;}
			if(nivel==3){dificultad=2;}
			if(nivel==4){dificultad=1;}

			if(contador==dificultad){

					numero = rand()%5 ;
					
					control = true ;

					contador = 0 ;
					NF_CreateSprite(1, 4, 4, 4, 60, 65);	// Crea el Sprite Topo
					NF_SpriteOamSet(4);


				}

				if(numero==1){ 

					op1_1 = true ;
					op1_2 = false ; 
					op1_3 = false ;
					op1_4 = false ;
		
					NF_MoveSprite(1,4,60,65); // Mueve el topo
				}

				if(numero==2){
					op1_1 = false ; 
					op1_3 = false ; 
					op1_4 = false ;
					op1_2 = true ;
	
					NF_MoveSprite(1,4,165, 65); // Mueve el topo
				}	

				if(numero==3){
					op1_1 = false ; 
					op1_2 = false ; 
					op1_4 = false ;
					op1_3 = true ;

					NF_MoveSprite(1,4,60, 145); // Mueve el topo
				}	

				if(numero==4){
					op1_1 = false ;
					op1_2 = false ;
					op1_3 = false ;
					op1_4 = true ;

					NF_MoveSprite(1,4, 165, 145); // Mueve el topo
				}

				if(numero==0){
					NF_ShowSprite(1,4,false); // Oculta el topo
				}

				swiWaitForVBlank();				// Espera al sincronismo vertical
				oamUpdate(&oamMain);				// Actualiza a VRAM el OAM Secundario
				oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario

				contador++ ;
		}
	}
}

void enableTimer(){
  
	NF_SPRITEOAM[1][1].hide = true;	
}


/*
-------------------------
|       Cabecera	|
-------------------------
*/


void cabecera(){

	setBrightness(3, -16);

	NF_CreateTiledBg(0, 3, "sp");
	
	s8 c = -16 ; 
	s8 b = -16 ;

	while(!(b==0)){//Mientras que b no sea 0:
		c++;
		if(c==5){
			c= 0;
			b++;
		}
		setBrightness(3, b);
		swiWaitForVBlank();
	}

	s32 time = 60*4;
	swiWaitForVBlank();//Espera el sincronismo vertical

	while(time){//no le hagais mucho caso a la segunda parte, esto se explica más adelante
		swiWaitForVBlank();//Espera sincronismo vertical
		time--;//Restamos uno al tiempo

	}

	c = 0;
	b = 0;

	while(!(b==-16)){
		c++;
		if(c==5){
			c = 0;
			b--;
		}
		setBrightness(3, b);//Cambia la luminosidad
		swiWaitForVBlank();//Espera el sincronismo vertical
	}

	swiWaitForVBlank();//Espera el sincronismo vertical
	// Elimina el fondo de la pantalla superior
	NF_DeleteTiledBg(0, 3);

	// Crea los fondos de la pantalla superior
	NF_CreateTiledBg(0, 3, "arriba");

	// Crea los fondos de la pantalla inferior
	NF_CreateTiledBg(1, 3, "abajo");

	setBrightness(3, 0);
}


/*
-------------------------
|    	Creditos	|
-------------------------
*/


int creditos(){
	
	// Elimina el fondo de la pantalla superior
	NF_DeleteTiledBg(0, 3);
	NF_DeleteTiledBg(1, 3);

	// Crea los fondos de la pantalla superior
	NF_CreateTiledBg(0, 3, "sp");

	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();
	
	u16 n = 32;
	char mytext[32];
	
	while(n!=4){
		sprintf(mytext,"Machaca Topos");
		NF_WriteText(1, 0, 1, n, mytext);
		NF_UpdateTextLayers();
		s32 time = 60 ;
		
		while(time){//no le hagais mucho caso a la segunda parte, esto se explica más adelante
			swiWaitForVBlank();//Espera sincronismo vertical
			time--;//Restamos uno al tiempo
			if(n<32){
				sprintf(mytext,"Escuela Superior Informatica");
				NF_WriteText(1, 0, 1, n+2, mytext);
				NF_UpdateTextLayers();
			}
			if(n<30){
				sprintf(mytext,"Estructura de Computadores  ");
				NF_WriteText(1, 0, 1, n+4, mytext);
				NF_UpdateTextLayers();
			}
			if(n<28){
				sprintf(mytext,"UCLM 2014 - 2015            ");
				NF_WriteText(1, 0, 1, n+6, mytext);
				NF_UpdateTextLayers();
			}
			if(n<26){
				sprintf(mytext,"Josue Gutierrez Duran       ");
				NF_WriteText(1, 0, 1, n+8, mytext);
				NF_UpdateTextLayers();
			}
			if(n<24){
				sprintf(mytext,"Ruben Sanchez Sevilla       ");
				NF_WriteText(1, 0, 1, n+10, mytext);
				NF_UpdateTextLayers();
			}
			if(n<22){
				sprintf(mytext,"Juan Manuel Palacios Navas  ");
				NF_WriteText(1, 0, 1, n+12, mytext);
				NF_UpdateTextLayers();
			}
			if(n<20){
				sprintf(mytext,"Jaime Muñoz Padilla         ");
				NF_WriteText(1, 0, 1, n+14, mytext);
				NF_UpdateTextLayers();
			}
			if(n<18){
				sprintf(mytext,"Sergio Caro Rodrigo         ");
				NF_WriteText(1, 0, 1, n+16, mytext);
				NF_UpdateTextLayers();  
			}
		}
		n-- ;
		n-- ;
		NF_UpdateTextLayers();
	}

			
	NF_UpdateTextLayers();

	u32 time = 60 ;
		
	while(time){//no le hagais mucho caso a la segunda parte, esto se explica más adelante
		swiWaitForVBlank();//Espera sincronismo vertical
		time--;//Restamos uno al tiempo
	}

	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();

	// Elimina el fondo de la pantalla superior
	NF_DeleteTiledBg(0, 3);

	// Crea los fondos de la pantalla superior
	NF_CreateTiledBg(0, 3, "arriba");

	// Crea los fondos de la pantalla inferior
	NF_CreateTiledBg(1, 3, "abajo");

	return 0 ;

}


/*
-------------------------
|    Menu Principal	|
-------------------------
*/


int menuprincipal(){
	
	char mytext[32];
	int salida = 0 ;
	sprintf(mytext,"Elige una Opcion");
	NF_WriteText(1, 0, 7, 2, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa START para Jugar");
	NF_WriteText(1, 0, 5, 10, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa SELECT para");
	NF_WriteText(1, 0, 7, 14, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"ver los Creditos");
	NF_WriteText(1, 0, 7, 15, mytext);  
			
	NF_UpdateTextLayers();


	// Lee el teclado
	bool fin = false ;
	while(!fin){
		scanKeys();
		int keys = keysHeld();
		if(keys & KEY_START){
			salida = 1 ;
			fin = true ;
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}

		if(keys & KEY_SELECT){
			salida = -1 ; 
			fin = true ;
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}
	}

	swiWaitForVBlank() ;
	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();

	return salida ;
}


/*
-------------------------
|        Nivel 1	|
-------------------------
*/

int nivel1(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y)
{
	char mytext[32];
	tiempo = 60 ;
	nivel = 1 ;
	jugar = true ;
	while(tiempo>0){

		NF_ResetCmapBuffers();
		NF_InitCmapBuffers();

		// Carga el mapa de colisiones nivel 1
		NF_LoadColisionMap("maps/Nivel", 1, 256, 264);

		u8 sound_id = 0;
		u8 sonido_id = 0;
		sprintf(mytext, "Nivel: %d ", nivel);

		NF_WriteText(0, 2, 1, 18, mytext);

		// Lee el teclado
		scanKeys();

		unsigned held = keysHeld();
		
		if(held & KEY_TOUCH){
			touchPosition touch;
			touchRead(&touch);

			x = touch.px ;
			y = touch.py ;
		}
 
		if(keysHeld() & KEY_B){
			pausa() ;
		}


		// Limites del movimiento
		if (x < 0) x = 0;

		if (x > 767) x = 767;
		if (y < 0) y = 0;
		if (y > 511) y = 511;

		// Posicion del fondo
		bg_x = (x - 128);
		if (bg_x < 0) bg_x = 0;
		if (bg_x > 512) bg_x = 512;
		bg_y = (y - 96);
		if (bg_y < 0) bg_y = 0;
		if (bg_y > 320) bg_y = 320;

		// Imprime puntuacion final
		sprintf(mytext, "Puntos Acumulados:     ");
		NF_WriteText(0, 2, 1, 12, mytext);
		sprintf(mytext, "Puntos Acumulados:  %d", puntos);
		NF_WriteText(0, 2, 1, 12, mytext);

		NF_UpdateTextLayers();			// Actualiza las capas de texto

		// Imprime siguiente nivel
		if(pl1-puntos>0){
			sprintf(mytext, "Puntos para");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "siguiente nivel:  %d ", pl1-puntos);
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}else{

			sprintf(mytext, "Has desbloqueado       ");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "el siguiente nivel     ");
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}

		

	
		NF_CreateSprite(1, 2, 2, 2, 60, 145);	// Crea el Sprite Topera (3)
		NF_SpriteOamSet(2);

		NF_CreateSprite(1, 3, 3, 3, 165, 145);	// Crea el Sprite Topera (4)
		NF_SpriteOamSet(3);

		NF_CreateSprite(1, 0, 0, 0, 60, 65);	// Crea el Sprite Topera (1)
		NF_SpriteOamSet(0);

		NF_CreateSprite(1, 1, 1, 1, 165, 65);	// Crea el Sprite Topera (2)
		NF_SpriteOamSet(1);

		swiWaitForVBlank();				// Espera al sincronismo vertical
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario


		// Bucle de Partida
		switch (NF_GetTile(1, x, y)) {

			case 1:
				if(op1_1==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
						//NF_ShowSprite(1,4,false); // Oculta el topo
					}
				} else {

					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 2:
				if(op1_2==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0); 
						}
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 3:
				if(op1_3==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 4:
				if(op1_4==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						}
	 				}

				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;
		}


		NF_UpdateTextLayers();			// Actualiza las capas de texto
	
		swiWaitForVBlank();			// Espera al sincronismo vertical

		oamUpdate(&oamSub);			// Actualiza a VRAM el OAM Secundario
	}
	jugar = false ;

	swiWaitForVBlank();				// Espera al sincronismo vertical
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario

	if(puntos>=pl1){

		return -2 ; // Si has ganado
	}else{
		return -3 ; // Si has perdido
	}

}


/*
-------------------------
|        Nivel 2	|
-------------------------
*/

int nivel2(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y)
{
	char mytext[32];
	tiempo = 60 ;
	nivel = 2 ;
	jugar = true ;
	while(tiempo>0){

		NF_ResetCmapBuffers();
		NF_InitCmapBuffers();

		// Carga el mapa de colisiones nivel 2
		NF_LoadColisionMap("maps/Nivel", 1, 256, 264);

		u8 sound_id = 0;
		u8 sonido_id = 0;
		sprintf(mytext, "Nivel: %d ", nivel);

		NF_WriteText(0, 2, 1, 18, mytext);

		// Lee el teclado
		scanKeys();

		unsigned held = keysHeld();
		
		if(held & KEY_TOUCH){
			touchPosition touch;
			touchRead(&touch);

			x = touch.px ;
			y = touch.py ;
		}
 
		if(keysHeld() & KEY_B){
			pausa() ;
		}


		// Limites del movimiento
		if (x < 0) x = 0;

		if (x > 767) x = 767;
		if (y < 0) y = 0;
		if (y > 511) y = 511;

		// Posicion del fondo
		bg_x = (x - 128);
		if (bg_x < 0) bg_x = 0;
		if (bg_x > 512) bg_x = 512;
		bg_y = (y - 96);
		if (bg_y < 0) bg_y = 0;
		if (bg_y > 320) bg_y = 320;

		// Imprime puntuacion final
		sprintf(mytext, "Puntos Acumulados:     ");
		NF_WriteText(0, 2, 1, 12, mytext);
		sprintf(mytext, "Puntos Acumulados:  %d", puntos);
		NF_WriteText(0, 2, 1, 12, mytext);

		NF_UpdateTextLayers();			// Actualiza las capas de texto

		// Imprime siguiente nivel
		if(pl2-puntos>0){
			sprintf(mytext, "Puntos para");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "siguiente nivel:  %d ", pl2-puntos);
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}else{

			sprintf(mytext, "Has desbloqueado       ");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "el siguiente nivel     ");
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}

		

	
		NF_CreateSprite(1, 2, 2, 2, 60, 145);	// Crea el Sprite Topera (3)
		NF_SpriteOamSet(2);

		NF_CreateSprite(1, 3, 3, 3, 165, 145);	// Crea el Sprite Topera (4)
		NF_SpriteOamSet(3);

		NF_CreateSprite(1, 0, 0, 0, 60, 65);	// Crea el Sprite Topera (1)
		NF_SpriteOamSet(0);

		NF_CreateSprite(1, 1, 1, 1, 165, 65);	// Crea el Sprite Topera (2)
		NF_SpriteOamSet(1);

		swiWaitForVBlank();				// Espera al sincronismo vertical
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario


		// Bucle de Partida
		switch (NF_GetTile(1, x, y)) {

			case 1:
				if(op1_1==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
						//NF_ShowSprite(1,4,false); // Oculta el topo
					}
				} else {

					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 2:
				if(op1_2==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0); 
						}
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 3:
				if(op1_3==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 4:
				if(op1_4==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						}
	 				}

				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;
		}


		NF_UpdateTextLayers();			// Actualiza las capas de texto
	
		swiWaitForVBlank();			// Espera al sincronismo vertical

		oamUpdate(&oamSub);			// Actualiza a VRAM el OAM Secundario
	}
	jugar = false ;

	swiWaitForVBlank();				// Espera al sincronismo vertical
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario

	if(puntos>=pl2){

		return -2 ; // Si has ganado
	}else{
		return -3 ; // Si has perdido
	}

}


/*
-------------------------
|        Nivel 3	|
-------------------------
*/

int nivel3(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y)
{
	char mytext[32];
	tiempo = 60 ;
	nivel = 3 ;
	jugar = true ;
	while(tiempo>0){

		NF_ResetCmapBuffers();
		NF_InitCmapBuffers();

		// Carga el mapa de colisiones nivel 3
		NF_LoadColisionMap("maps/Nivel", 1, 256, 264);

		u8 sound_id = 0;
		u8 sonido_id = 0;
		sprintf(mytext, "Nivel: %d ", nivel);

		NF_WriteText(0, 2, 1, 18, mytext);

		// Lee el teclado
		scanKeys();

		unsigned held = keysHeld();
		
		if(held & KEY_TOUCH){
			touchPosition touch;
			touchRead(&touch);

			x = touch.px ;
			y = touch.py ;
		}
 
		if(keysHeld() & KEY_B){
			pausa() ;
		}


		// Limites del movimiento
		if (x < 0) x = 0;

		if (x > 767) x = 767;
		if (y < 0) y = 0;
		if (y > 511) y = 511;

		// Posicion del fondo
		bg_x = (x - 128);
		if (bg_x < 0) bg_x = 0;
		if (bg_x > 512) bg_x = 512;
		bg_y = (y - 96);
		if (bg_y < 0) bg_y = 0;
		if (bg_y > 320) bg_y = 320;

		// Imprime puntuacion final
		sprintf(mytext, "Puntos Acumulados:     ");
		NF_WriteText(0, 2, 1, 12, mytext);
		sprintf(mytext, "Puntos Acumulados:  %d", puntos);
		NF_WriteText(0, 2, 1, 12, mytext);

		NF_UpdateTextLayers();			// Actualiza las capas de texto

		// Imprime siguiente nivel
		if(pl3-puntos>0){
			sprintf(mytext, "Puntos para");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "siguiente nivel:  %d ", pl3-puntos);
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}else{

			sprintf(mytext, "Has desbloqueado       ");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "el siguiente nivel     ");
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}

		

	
		NF_CreateSprite(1, 2, 2, 2, 60, 145);	// Crea el Sprite Topera (3)
		NF_SpriteOamSet(2);

		NF_CreateSprite(1, 3, 3, 3, 165, 145);	// Crea el Sprite Topera (4)
		NF_SpriteOamSet(3);

		NF_CreateSprite(1, 0, 0, 0, 60, 65);	// Crea el Sprite Topera (1)
		NF_SpriteOamSet(0);

		NF_CreateSprite(1, 1, 1, 1, 165, 65);	// Crea el Sprite Topera (2)
		NF_SpriteOamSet(1);

		swiWaitForVBlank();				// Espera al sincronismo vertical
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario


		// Bucle de Partida
		switch (NF_GetTile(1, x, y)) {

			case 1:
				if(op1_1==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
						//NF_ShowSprite(1,4,false); // Oculta el topo
					}
				} else {

					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 2:
				if(op1_2==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0); 
						}
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 3:
				if(op1_3==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 4:
				if(op1_4==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						}
	 				}

				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;
		}


		NF_UpdateTextLayers();			// Actualiza las capas de texto
	
		swiWaitForVBlank();			// Espera al sincronismo vertical

		oamUpdate(&oamSub);			// Actualiza a VRAM el OAM Secundario
	}
	jugar = false ;

	swiWaitForVBlank();				// Espera al sincronismo vertical
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario

	if(puntos>=pl3){

		return -2 ; // Si has ganado
	}else{
		return -3 ; // Si has perdido
	}

}


/*
-------------------------
|        Nivel 4	|
-------------------------
*/

int nivel4(s16 x, s16 y, s16 spr_x, s16 spr_y,s16 bg_x, s16 bg_y)
{
	char mytext[32];
	tiempo = 60 ;
	nivel = 4 ;
	jugar = true ;
	while(tiempo>0){

		NF_ResetCmapBuffers();
		NF_InitCmapBuffers();

		// Carga el mapa de colisiones nivel 4
		NF_LoadColisionMap("maps/Nivel", 1, 256, 264);

		u8 sound_id = 0;
		u8 sonido_id = 0;
		sprintf(mytext, "Nivel: %d ", nivel);

		NF_WriteText(0, 2, 1, 18, mytext);

		// Lee el teclado
		scanKeys();

		unsigned held = keysHeld();
		
		if(held & KEY_TOUCH){
			touchPosition touch;
			touchRead(&touch);

			x = touch.px ;
			y = touch.py ;
		}
 
		if(keysHeld() & KEY_B){
			pausa() ;
		}


		// Limites del movimiento
		if (x < 0) x = 0;

		if (x > 767) x = 767;
		if (y < 0) y = 0;
		if (y > 511) y = 511;

		// Posicion del fondo
		bg_x = (x - 128);
		if (bg_x < 0) bg_x = 0;
		if (bg_x > 512) bg_x = 512;
		bg_y = (y - 96);
		if (bg_y < 0) bg_y = 0;
		if (bg_y > 320) bg_y = 320;

		// Imprime puntuacion final
		sprintf(mytext, "Puntos Acumulados:     ");
		NF_WriteText(0, 2, 1, 12, mytext);
		sprintf(mytext, "Puntos Acumulados:  %d", puntos);
		NF_WriteText(0, 2, 1, 12, mytext);

		NF_UpdateTextLayers();			// Actualiza las capas de texto

		// Imprime siguiente nivel
		if(pl4-puntos>0){
			sprintf(mytext, "Puntos para");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "siguiente nivel:  %d ", pl4-puntos);
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}else{

			sprintf(mytext, "Has desbloqueado       ");
			NF_WriteText(0, 2, 1, 14, mytext);
			sprintf(mytext, "el siguiente nivel     ");
			NF_WriteText(0, 2, 1, 16, mytext);

			NF_UpdateTextLayers();			// Actualiza las capas de texto
		}

		

	
		NF_CreateSprite(1, 2, 2, 2, 60, 145);	// Crea el Sprite Topera (3)
		NF_SpriteOamSet(2);

		NF_CreateSprite(1, 3, 3, 3, 165, 145);	// Crea el Sprite Topera (4)
		NF_SpriteOamSet(3);

		NF_CreateSprite(1, 0, 0, 0, 60, 65);	// Crea el Sprite Topera (1)
		NF_SpriteOamSet(0);

		NF_CreateSprite(1, 1, 1, 1, 165, 65);	// Crea el Sprite Topera (2)
		NF_SpriteOamSet(1);

		swiWaitForVBlank();				// Espera al sincronismo vertical
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario


		// Bucle de Partida
		switch (NF_GetTile(1, x, y)) {

			case 1:
				if(op1_1==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {

					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 2:
				if(op1_2==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0); 
						}
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 3:
				if(op1_3==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						} 
					}
				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;

			case 4:
				if(op1_4==true){
					if(control==true){
						puntos+=incremento ;
						sound_id = NF_PlayRawSound(2, 127, 64, false, 0);
					}
				} else {
					if(control==true){ 
						if(puntos>0){
							puntos-=decremento ;
							sonido_id = NF_PlayRawSound(3, 127, 64, false, 0);
						}
	 				}

				}
				NF_ShowSprite(1,4,false); // Oculta el topo
				control = false ;
				x = 0 ;
				y = 0 ;
				break ;
		}


		NF_UpdateTextLayers();			// Actualiza las capas de texto
	
		swiWaitForVBlank();			// Espera al sincronismo vertical

		oamUpdate(&oamSub);			// Actualiza a VRAM el OAM Secundario
	}
	jugar = false ;

	swiWaitForVBlank();				// Espera al sincronismo vertical
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario

	if(puntos>=pl4){

		return -2 ; // Si has ganado
	}else{
		return -3 ; // Si has perdido
	}

}


/*
-------------------------
|        Perdido	|
-------------------------
*/


int perdido(){

	NF_DeleteSprite(1,3);
	NF_DeleteSprite(1,1);
	NF_DeleteSprite(1,0);
	NF_DeleteSprite(1,2);
	NF_SpriteOamSet(1);

	swiWaitForVBlank();				// Espera al sincronismo vertical
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);				// Actualiza a VRAM el OAM Secundario

	int salida = 0 ;
	char mytext[32];

	sprintf(mytext,"Has perdido");
	NF_WriteText(1, 0, 7, 4, mytext);

	sprintf(mytext,"Elige una Opcion");
	NF_WriteText(1, 0, 7, 4, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa A para Reintentar");
	NF_WriteText(1, 0, 5, 10, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa B para volver");
	NF_WriteText(1, 0, 7, 14, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"al Menu Principal");
	NF_WriteText(1, 0, 7, 15, mytext);  
			
	NF_UpdateTextLayers();


	// Lee el teclado
	bool fin = false ;
	while(!fin){
		scanKeys();
		int keys = keysHeld();
		if(keys & KEY_A){
			salida = nivel ;
			fin = true ;
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}

		if(keys & KEY_B){
			salida = 0 ; 
			fin = true ;
			NF_ClearTextLayer(0, 2);
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}
	}

	swiWaitForVBlank() ;
	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();

	return salida ;
}


/*
-------------------------
|        Ganado		|
-------------------------
*/


int ganado(){

	NF_DeleteSprite(1,3);
	NF_DeleteSprite(1,1);
	NF_DeleteSprite(1,0);
	NF_DeleteSprite(1,2);
	NF_SpriteOamSet(1);

	int salida = 0 ;
	char mytext[32];

	sprintf(mytext,"Has Ganado");
	NF_WriteText(1, 0, 7, 4, mytext);

	sprintf(mytext,"Elige una Opcion");
	NF_WriteText(1, 0, 7, 4, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa A para Siguiente Nivel");
	NF_WriteText(1, 0, 5, 10, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa B para volver");
	NF_WriteText(1, 0, 7, 14, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"al Menu Principal");
	NF_WriteText(1, 0, 7, 15, mytext);  
			
	NF_UpdateTextLayers();


	// Lee el teclado
	bool fin = false ;
	while(!fin){
		scanKeys();
		int keys = keysHeld();
		if(keys & KEY_A){
			salida = nivel++ ;
			fin = true ;
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}

		if(keys & KEY_B){
			salida = 0 ; 
			fin = true ;
			NF_ClearTextLayer(0, 2);
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}
	}

	swiWaitForVBlank() ;
	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();

	return salida ;
}


/*
-------------------------
|        Final		|
-------------------------
*/


int final(){

	int salida = 0 ;
	char mytext[32];

	sprintf(mytext,"Has Ganado el juego");
	NF_WriteText(1, 0, 7, 6, mytext);

	sprintf(mytext,"Elige una Opcion");
	NF_WriteText(1, 0, 7, 8, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa A para");
	NF_WriteText(1, 0, 7, 14, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"volver a empezar");
	NF_WriteText(1, 0, 7, 15, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa B para volver");
	NF_WriteText(1, 0, 7, 17, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"al Menu Principal");
	NF_WriteText(1, 0, 7, 18, mytext);  
			
	NF_UpdateTextLayers();


	// Lee el teclado
	bool fin = false ;
	while(!fin){
		scanKeys();
		int keys = keysHeld();
		if(keys & KEY_A){
			salida = 1 ;
			fin = true ;
			puntos = 0;
			nivel = 1 ;
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}

		if(keys & KEY_B){
			salida = 0 ; 
			fin = true ;
			puntos = 0;
			nivel = 1 ;
			NF_ClearTextLayer(0, 2);
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();
		}
	}

	swiWaitForVBlank() ;
	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();

	return salida ;
}

/*
-------------------------
|        Pausa		|
-------------------------
*/


void pausa(){

	jugar=false;
	NF_ShowSprite(1,3,false);
	NF_ShowSprite(1,1,false);
	NF_ShowSprite(1,0,false);
	NF_ShowSprite(1,2,false);
	NF_ShowSprite(1,4,false) ;
	NF_SpriteOamSet(1);

	char mytext[32];
	
	sprintf(mytext,"PAUSA");
	NF_WriteText(1, 0, 7, 4, mytext);

	NF_UpdateTextLayers();

	sprintf(mytext,"Pulsa START para volver");
	NF_WriteText(1, 0, 7, 14, mytext);  
			
	NF_UpdateTextLayers();

	sprintf(mytext,"al juego");
	NF_WriteText(1, 0, 7, 15, mytext);  
			
	NF_UpdateTextLayers();


	// Lee el teclado
	bool fin = false ;
	while(!fin){
		scanKeys();
		int keys = keysHeld();
		if(keys & KEY_START){
			fin = true ;
			NF_ClearTextLayer(1, 0);
			NF_UpdateTextLayers();

			NF_ShowSprite(1,3,true);
			NF_ShowSprite(1,1,true);
			NF_ShowSprite(1,0,true);
			NF_ShowSprite(1,2,true);
			NF_ShowSprite(1,4,true) ;
			NF_SpriteOamSet(1);
			jugar=true;
		}
	}

	swiWaitForVBlank() ;
	NF_ClearTextLayer(1, 0);
	NF_UpdateTextLayers();

}


/*
-------------------------------------------------
|	Main() - Bloque general del programa	|
-------------------------------------------------
*/

int main(int argc, char **argv) {

	srand(time(NULL)) ;

	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	irqSet(IRQ_TIMER0, &timeout);
	irqEnable(IRQ_TIMER0);
	
	// Temporizador
	consoleDemoInit();
	TIMER_DATA(0) = 0;
	TIMER_CR(0) = TIMER_DIV_256 | TIMER_ENABLE | TIMER_IRQ_REQ;

	irqSet(IRQ_TIMER2, &enableTimer);
	irqEnable(IRQ_TIMER2);
	TIMER_DATA(1) = 0;
	TIMER_CR(1) = TIMER_DIV_1024 | TIMER_ENABLE| TIMER_IRQ_REQ| TIMER_CASCADE;
	TIMER_DATA(2) = 0;
	TIMER_CR(2) = TIMER_DIV_1024 | TIMER_ENABLE| TIMER_IRQ_REQ;
	

	iprintf("\n NitroFS init. Please wait.\n\n");
	iprintf(" Iniciando NitroFS,\n por favor, espere.\n\n");
	iprintf(" Iniciando Juego\nMachacaTopos\n\n");
	swiWaitForVBlank();

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

	// Inicializa el motor 2D
	NF_Set2D(0, 0);				// Modo 2D_0 en ambas pantallas
	NF_Set2D(1, 0);


	// Inicializa el engine de audio de la DS
	soundEnable();

	// Inicializa los fondos tileados
	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitTiledBgSys(0);		// Inicializa los fondos Tileados para la pantalla superior
	NF_InitTiledBgSys(1);		// Iniciliaza los fondos Tileados para la pantalla inferior

	// Inicializa los Sprites
	NF_InitSpriteBuffers();		// Inicializa los buffers para almacenar sprites y paletas
	NF_InitSpriteSys(0);		// Inicializa los sprites para la pantalla superior
	NF_InitSpriteSys(1);		// Inicializa los sprites para la pantalla inferior

	// Inicializa el motor de texto
	NF_InitTextSys(0);			// Inicializa el texto para la pantalla superior

	// Inicializa los buffers de mapas de colisiones
	NF_InitCmapBuffers();

	// Inicializa los buffers de sonido
	NF_InitRawSoundBuffers();


	// Carga los archivos de fondo desde la FAT / NitroFS a la RAM
	NF_LoadTiledBg("bg/Fondo", "abajo", 256, 256);		// Carga el fondo para la capa 3, pantalla inferior
	NF_LoadTiledBg("bg/Fondo2", "arriba", 256, 256);	// Carga el fondo para la capa 3, pantalla superior
	NF_LoadTiledBg("splashes/splash", "sp", 256, 256);		// Carga el fondo para la capa 3, pantalla inferior



	// Carga los archivos de sprites desde la FAT / NitroFS a la RAM
	NF_LoadSpriteGfx("sprite/topera", 0, 32, 32);	// Puntero DiglettVerde
	NF_LoadSpritePal("sprite/topera", 0);

	NF_LoadSpriteGfx("sprite/topera", 1, 32, 32);
	NF_LoadSpritePal("sprite/topera", 1);

	NF_LoadSpriteGfx("sprite/topera", 2, 32, 32);
	NF_LoadSpritePal("sprite/topera", 2);

	NF_LoadSpriteGfx("sprite/topera", 3, 32, 32);
	NF_LoadSpritePal("sprite/topera", 3);

	NF_LoadSpriteGfx("sprite/Ductrio", 4, 32, 32);
	NF_LoadSpritePal("sprite/Ductrio", 4);

	// Transfiere a la VRAM los sprites necesarios
	NF_VramSpriteGfx(1, 0, 0, true);	// Topera
	NF_VramSpritePal(1, 0, 0);

	NF_VramSpriteGfx(1, 1, 1, true);	// Topera
	NF_VramSpritePal(1, 1, 1);

	NF_VramSpriteGfx(1, 2, 2, true);	// Topera
	NF_VramSpritePal(1, 2, 2);

	NF_VramSpriteGfx(1, 3, 3, true);	// Topera
	NF_VramSpritePal(1, 3, 3);

	NF_VramSpriteGfx(1, 4, 4, true);	// Topo
	NF_VramSpritePal(1, 4, 4);

	// Carga la fuente por defecto para el texto
	NF_LoadTextFont("fnt/default", "normal", 256, 256, 0);
	NF_LoadTextFont("fnt/default", "textoabajo", 256, 256, 0);

	// Carga el mapa de colisiones nivel 1
	NF_LoadColisionMap("maps/MenuPrincipal", 0, 256, 264);

	// Carga los samples de sonido en formato RAW
	NF_LoadRawSound("sfx/music", 1, 11025, 2);
	NF_LoadRawSound("sfx/1_Punto_Mas", 2, 32000, 2);
	NF_LoadRawSound("sfx/1_Punto_Menos", 3, 32000, 2);

	// Crea una capa de texto
	NF_CreateTextLayer(0, 2, 0,	"normal");
	NF_CreateTextLayer(1, 0, 0,	"textoabajo");

	cabecera(); // Ejecuta el Splash de Cabecera

	// Variables para el control de movimiento
	s16 x = 128;
	s16 y = 96;
	s16 spr_x, spr_y, bg_x, bg_y = 0;
	
	// Variable para el sonido
	u8 sound_id = 0;

	// Inicia la musica de fondo
	sound_id = NF_PlayRawSound(1, 127, 64, true, 0);

	// Bucle (repite para siempre)
	while(1) {
		if(estado==0){
			estado=menuprincipal(); // Menu Principal
		}
		if(estado==-1){
			estado=creditos() ; // Creditos
		}
		if(nivel==1){
			estado=nivel1(x, y, spr_x, spr_y, bg_x, bg_y) ; // Nivel 1
		}
		if(nivel==2){
			estado=nivel2(x, y, spr_x, spr_y, bg_x, bg_y) ; // Nivel 2
		}
		if(nivel==3){
			estado=nivel3(x, y, spr_x, spr_y, bg_x, bg_y) ; // Nivel 3
		}
		if(nivel==4){
			estado=nivel4(x, y, spr_x, spr_y, bg_x, bg_y) ; // Nivel 4
		}
		if(nivel==5){
			estado=final() ; // Final
		}
		if(estado==-3){
			estado=perdido() ; // Si has perdido
		}
		if(estado==-2){
			estado=ganado() ; // Si has ganado
		}
	}



	return 0 ; 

}
