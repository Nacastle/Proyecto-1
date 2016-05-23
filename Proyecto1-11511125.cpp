#include <ncurses.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using std::string;
using std::cout;
using std::endl;
using std::cin;

void mostrar1(string[],string[],int);
void Selecion(string[],string[],int);
bool GaneRoyal(string[]);
void EvaluaPares(string[],bool[]);
bool GaneEscaleraColor(string[]);
bool Escalera(string[]);
void cleanScreen();
void tabla();


int main(int argc, char const *argv[])
{
	int DineroUsuario;
	int UsuarioApuesta = 0;

	//Verificadores de gane.
	/*
	Las posiciones van ordenadas de manera que la posicion 0 = evaluara Escalera real y asi sucesivamente con el 1 = Escalera de color y asi consecutivamente hasta el de pareja si no es ninguno de ellos automaticamente perdera.
	*/
	bool verificar[9] = {false,false,false,false,false,false,false,false,false};

	//Variables de juego.
	string cartas[52] = {"AC","2C","3C","4C","5C","6C","7C","8C","9C","10C","JC","QC","KC","AP","2P","3P","4P","5P","6P","7P","8P","9P","10P","JP","QP","KP","AD","2D","3D","4D","5D","6D","7D","8D","9D","10D","JD","QD","KD","AT","2T","3T","4T","5T","6T","7T","8T","9T","10T","JT","QT","KT"};
	string mano[5] = {};
	string juego1[5] = {};
	
	initscr();
	start_color();
	init_pair(1,COLOR_CYAN,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	int opcion;
	mvprintw(0,0,"Bienvenido ingrese cualquier numero para entrar y 3 para Salir.");
	opcion = getch()-'0';
	while(opcion != 3){
		mvprintw(0,0,"Ingrese una opcion:\n1.Nuevo Juego.\n2.Cargar Dineros\n3.Salir");
		opcion = getch()-'0';
		int CargarDinero = 0;
		cleanScreen();
		if (opcion == 1)
		{
			//Inicio de juego.
			//cout << "Ingrese cuanto de dinero tiene: " << endl;
			int control;
			char valores;
			string datos = "";
			cleanScreen();
			mvprintw(5,0,"Ingrese cuanto de dinero tiene: ");
			while((control=getch())!=10){
				mvprintw(5,0,"Ingrese cuanto de dinero tiene: ");
				if (control > 47 && control < 58)
				{
					valores=control;
					datos.push_back(valores);
					mvprintw(6,0,"%s",datos.c_str());
				}
				else{
					mvprintw(6,0,"%s",datos.c_str());
				}
				DineroUsuario = atoi(datos.c_str());
			}
			datos.clear();
			cleanScreen();

			mvprintw(10,0,"Cuanto dinero quiere apostar?: ");
			while(UsuarioApuesta == 0 || UsuarioApuesta>DineroUsuario){
				while((control=getch())!=10){
					mvprintw(10,0,"Cuanto dinero quiere apostar?: ");
					if (control > 47 && control < 58)
					{
						valores=control;
						datos.push_back(valores);
						mvprintw(11,0,"%s",datos.c_str());
					}else{
						mvprintw(11,0,"%s",datos.c_str());
					}
					UsuarioApuesta = atoi(datos.c_str());
				}
				datos.clear();
			}
			cleanScreen();
			
			//Automaticamente ya la apuesta no forma parte del dinero de El/Ella.
			DineroUsuario = DineroUsuario - UsuarioApuesta;

			//Jugar llenando la mano.
			int tamanoMano = 5;
			void tabla();
			mvprintw(10,50,"Estas son sus cartas :3");
			mostrar1(cartas,juego1,tamanoMano);
			for (int i = 0; i < 5; ++i)
			{
				mvprintw(14,5*i,"%s",juego1[i].c_str());
				//cout << juego1[i] << "\t";
			}

			// mvprintw(19,0,"Cuantas cartas quiere?: ");
			// while((control=getch())!=10){
			// 	mvprintw(19,0,"Cuantas cartas quiere?: ");
			// 	if (control > 47 && control < 58)
			// 	{
			// 		valores=control;
			// 		datos.push_back(valores);
			// 		mvprintw(20,0,"%s",datos.c_str());
			// 	}else{
			// 		mvprintw(20,0,"%s",datos.c_str());
			// 	}
			// 	tamanoMano = atoi(datos.c_str());
			// }
			// datos.clear();
			mvprintw(19,0,"Cuantas cartas quiere?: ");
			tamanoMano = getch()-'0';
			//cout << "Cuantas cartas quiere?: " << endl;
			//cin >> tamanoMano;

			//Si no muestra nada Culpa de esto de abajo.
			cleanScreen();
			if (tamanoMano < 5)
			{
				Selecion(juego1,mano,tamanoMano);
				//mvprintw(0,0,"1");
				int cartasRestantes = 5 - tamanoMano;
				//mvprintw(0,0,"2");
				mostrar1(cartas,juego1,cartasRestantes);
				//mvprintw(0,0,"3");
				for (int i = 0; i < cartasRestantes; i++)
				{
					mano[tamanoMano + i] = juego1[i];
				}
			}
			
			for (int i = 0; i < 5; ++i)
			{
				mvprintw(26,3*i,"%s",mano[i].c_str());
				//cout << mano[i] << "\t";
			}
			
			cout << endl;
			//Juega con los dos turnos.
			mano[0] = "JC";
			mano[1] = "JD";
			mano[2] = "6T";
			mano[3] = "6C";
			mano[4] = "3D";

			verificar[0] = GaneRoyal(mano);
			verificar[1] = GaneEscaleraColor(mano);
			verificar[5] = Escalera(mano);
			EvaluaPares(mano,verificar);
			
			int Victoria = -1;
			refresh();
			for (int i = 0; i < 9; ++i)
			{
				if (verificar[i] == true)
				{
					mvprintw(0,0,"Ganado de la forma: %d",i);
					//cout << "Gano " << i;
					Victoria = i;
					break;
				}
			}
			void tabla();
			if (Victoria == -1)
			{
				mvprintw(5,0,"Usted es un Perdedor.");
				//cout << "Usted es un Perdedor." << endl;
			}else if (Victoria == 0)
			{
				UsuarioApuesta = UsuarioApuesta * 250;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				//cout << "Ha ganado: " << UsuarioApuesta;
				//cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 1)
			{
				UsuarioApuesta = UsuarioApuesta * 50;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta;
				// cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 2)
			{
				UsuarioApuesta = UsuarioApuesta * 25;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta;
				// cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 3)
			{
				UsuarioApuesta = UsuarioApuesta * 6;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta;
				// cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 4)
			{
				UsuarioApuesta = UsuarioApuesta * 5;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta;
				// cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 5)
			{
				UsuarioApuesta = UsuarioApuesta * 4;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta;
				// cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 6)
			{
				UsuarioApuesta = UsuarioApuesta * 3;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta;
				// cout << "Su nuevo Fondo es: " << DineroUsuario;
			}else if (Victoria == 7)
			{
				UsuarioApuesta = UsuarioApuesta * 2;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta << endl;
				// cout << "Su nuevo Fondo es: " << DineroUsuario << endl;
			}else if (Victoria == 8)
			{
				UsuarioApuesta = UsuarioApuesta * 1;
				DineroUsuario = DineroUsuario + UsuarioApuesta;
				CargarDinero = CargarDinero + DineroUsuario;
				mvprintw(5,0,"Ha ganado: %d",UsuarioApuesta);
				mvprintw(6,0,"Ha ganado: %d",DineroUsuario);
				// cout << "Ha ganado: " << UsuarioApuesta << endl;
				// cout << "Su nuevo Fondo es: " << DineroUsuario << endl;
			}
			cout << endl;
			
		}else if (opcion == 2)
		{
			cleanScreen();
			mvprintw(10,20,"Felicidades ha guardado su dinero. :3");
			DineroUsuario = DineroUsuario + CargarDinero;
		}
	}
	
	attroff(COLOR_PAIR(1));
	refresh();
	
	endwin();
	return 0;
}

void tabla(){
	mvprintw(10,0,"*****************************************\n*\tRoyal Flush - 250x\t\t*\n*\tStraight Flush - 50x\t\t*\n*\tFour of a Kind - 25x\t\t*\n*\tFull House - 6x to 9x\t\t*\n*\tFlush - 5x or 6x\t\t*\n*\tStraight - 4x\t\t\t*\n*\tThree of a Kind - 3x\t\t*\n*\tTwo Pair - 2x\t\t\t*\n*\tPair of Jacks or Better - 1x\t*\n*****************************************");
}

void cleanScreen(){
	int x,y;
	getmaxyx(stdscr,x,y);
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			mvprintw(j,i," ");
		}
	}
	move(0,0);
}

//Llenar la mesa de cartas.
void mostrar1(string carta[], string juego1[],int tamano){
	srand (time(NULL));
	int random;
	for (int i = 0; i < 5; ++i)
	{
		juego1[i] = "1";
	}
	for (int i = 0; i < tamano; ++i)
	{
		random = rand() % 52 + 1;
		while(carta[random] == "1"){
			random = rand() % 52 + 1;
		}
		juego1[i] = carta[random];
		carta[random] = "1";
	}
}

//Tomar cartas de la mesa.
void Selecion(string juego1[], string mano[],int tamano){
	int control;
	int posicion = 0;
	char valores;
	string datos = "";

	for (int i = 0; i < tamano; ++i)
	{
		/*//mvprintw(0,0,"1");
		mvprintw(22,0,"Escoja la posicion: ");
		while((control=getch())!=10){
			//mvprintw(1,0,"2%d",control);
			mvprintw(22,0,"Escoja la posicion: ");
			if (control > 47 && control < 58)
			{

				//mvprintw(2,0,"3%d",control);
				valores=control;
				datos.push_back(valores);
				int posicion = valores - 48;
				mvprintw(23,0,"%s",datos.c_str());
			}else{
				//mvprintw(3,0,"4%d",control);
				mvprintw(23,0,"%s",datos.c_str());
			}
			//mvprintw(4,0,"5%d",control);
			posicion = atoi(datos.c_str());
		}
		datos.clear();
		mvprintw(5,0,"6%d",posicion);
		//int getch(void);
		//addstr("Escoja la posicion: ");
		//getnstr(valores,posicion);
		//posicion = valores - 48;*/
		mvprintw(22,0,"Escoja la posicion: ");
		posicion = getch()-'0';
		mvprintw(0,0,"%d",posicion);
		//cout << "Escoja la posicion: " << endl;
		//cin >> posicion;
		mano[i] = juego1[posicion];
		
	}
}

bool GaneRoyal(string mano[]){
	string Corazon[5] = {"AC","KC","QC","JC","10C"};
	string Pica[5] = {"AP","KP","QP","JP","10P"};
	string Diamante[5] = {"AD","KD","QD","JD","10D"};
	string Trebol[5] = {"AT","KT","QT","JT","10T"};
	int contador1 = 1;
	int contador2 = 1;
	int contador3 = 1;
	int contador4 = 1;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (Corazon[i] == mano[j])
			{
				contador1++;
			}
			if (Pica[i] == mano[j])
			{
				contador2++;
			}
			if (Diamante[i] == mano[j])
			{
				contador3++;
			}
			if (Trebol[i] == mano[j])
			{
				contador4++;
			}
		}
	}
	if (contador1 == 6 || contador2 == 6 || contador3 == 6 || contador4 == 6)
	{
		return true;
	}
	else{
		return false;
	}
}

bool GaneEscaleraColor(string mano[]){
	string Corazon1[5] = {"2C","3C","4C","5C","6C"};
	string Corazon2[5] = {"3C","4C","5C","6C","7C"};
	string Corazon3[5] = {"4C","5C","6C","7C","8C"};
	string Corazon4[5] = {"5C","6C","7C","8C","9C"};
	string Corazon5[5] = {"6C","7C","8C","9C","10C"};
	string Corazon6[5] = {"7C","8C","9C","10C","JC"};
	string Corazon7[5] = {"8C","9C","10C","JC","QC"};
	string Corazon8[5] = {"9C","10C","JC","QC","KC"};

	string Pica1[5] = {"2P","3P","4P","5P","6P"};
	string Pica2[5] = {"3P","4P","5P","6P","7P"};
	string Pica3[5] = {"4P","5P","6P","7P","8P"};
	string Pica4[5] = {"5P","6P","7P","8P","9P"};
	string Pica5[5] = {"6P","7P","8P","9P","10P"};
	string Pica6[5] = {"7P","8P","9P","10P","JP"};
	string Pica7[5] = {"8P","9P","10P","JP","QP"};
	string Pica8[5] = {"9P","10P","JP","QP","KP"};

	string Diamante1[5] = {"2D","3D","4D","5D","6D"};
	string Diamante2[5] = {"3D","4D","5D","6D","7D"};
	string Diamante3[5] = {"4D","5D","6D","7D","8D"};
	string Diamante4[5] = {"5D","6D","7D","8D","9D"};
	string Diamante5[5] = {"6D","7D","8D","9D","10D"};
	string Diamante6[5] = {"7D","8D","9D","10D","JD"};
	string Diamante7[5] = {"8D","9D","10D","JD","QD"};
	string Diamante8[5] = {"9D","10D","JD","QD","KD"};

	string Trebol1[5] = {"2T","3T","4T","5T","6T"};
	string Trebol2[5] = {"3T","4T","5T","6T","7T"};
	string Trebol3[5] = {"4T","5T","6T","7T","8T"};
	string Trebol4[5] = {"5T","6T","7T","8T","9T"};
	string Trebol5[5] = {"6T","7T","8T","9T","10T"};
	string Trebol6[5] = {"7T","8T","9T","10T","JT"};
	string Trebol7[5] = {"8T","9T","10T","JT","QT"};
	string Trebol8[5] = {"9T","10T","JT","QT","KT"};
	int contador1 = 1;
	int contador2 = 1;
	int contador3 = 1;
	int contador4 = 1;
	int contador5 = 1;
	int contador6 = 1;
	int contador7 = 1;
	int contador8 = 1;
	int contador9 = 1;
	int contador10 = 1;
	int contador11 = 1;
	int contador12 = 1;
	int contador13 = 1;
	int contador14 = 1;
	int contador15 = 1;
	int contador16 = 1;
	int contador17 = 1;
	int contador18 = 1;
	int contador19 = 1;
	int contador20 = 1;
	int contador21 = 1;
	int contador22 = 1;
	int contador23 = 1;
	int contador24 = 1;
	int contador25 = 1;
	int contador26 = 1;
	int contador27 = 1;
	int contador28 = 1;
	int contador29 = 1;
	int contador30 = 1;
	int contador31 = 1;
	int contador32 = 1;


	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			//Corazon
			if (Corazon1[i] == mano[j])
			{
				contador1++;
			}
			if (Corazon2[i] == mano[j])
			{
				contador2++;
			}
			if (Corazon3[i] == mano[j])
			{
				contador3++;
			}
			if (Corazon4[i] == mano[j])
			{
				contador4++;
			}
			if (Corazon5[i] == mano[j])
			{
				contador5++;
			}
			if (Corazon6[i] == mano[j])
			{
				contador6++;
			}
			if (Corazon7[i] == mano[j])
			{
				contador7++;
			}
			if (Corazon8[i] == mano[j])
			{
				contador8++;
			}
			//Pica
			if (Pica1[i] == mano[j])
			{
				contador9++;
			}
			if (Pica2[i] == mano[j])
			{
				contador10++;
			}
			if (Pica3[i] == mano[j])
			{
				contador11++;
			}
			if (Pica4[i] == mano[j])
			{
				contador12++;
			}
			if (Pica5[i] == mano[j])
			{
				contador13++;
			}
			if (Pica6[i] == mano[j])
			{
				contador14++;
			}
			if (Pica7[i] == mano[j])
			{
				contador15++;
			}
			if (Pica8[i] == mano[j])
			{
				contador16++;
			}
			//Diamante
			if (Diamante1[i] == mano[j])
			{
				contador17++;
			}
			if (Diamante2[i] == mano[j])
			{
				contador18++;
			}
			if (Diamante3[i] == mano[j])
			{
				contador19++;
			}
			if (Diamante4[i] == mano[j])
			{
				contador20++;
			}
			if (Diamante5[i] == mano[j])
			{
				contador21++;
			}
			if (Diamante6[i] == mano[j])
			{
				contador22++;
			}
			if (Diamante7[i] == mano[j])
			{
				contador23++;
			}
			if (Diamante8[i] == mano[j])
			{
				contador24++;
			}
			//Trebol
			if (Trebol1[i] == mano[j])
			{
				contador25++;
			}
			if (Trebol2[i] == mano[j])
			{
				contador26++;
			}
			if (Trebol3[i] == mano[j])
			{
				contador27++;
			}
			if (Trebol4[i] == mano[j])
			{
				contador28++;
			}
			if (Trebol5[i] == mano[j])
			{
				contador29++;
			}
			if (Trebol6[i] == mano[j])
			{
				contador30++;
			}
			if (Trebol7[i] == mano[j])
			{
				contador31++;
			}
			if (Trebol8[i] == mano[j])
			{
				contador32++;
			}
		}
	}
	if (contador1 == 5 || contador2 == 5 || contador3 == 5 || contador4 == 5 || contador5 == 5 || contador6 == 5 || contador7 == 5 || contador8 == 5|| contador9 == 5 || contador10 == 5 || contador11 == 5 || contador12 == 5 || contador13 == 5 || contador14 == 5 || contador15 == 5 || contador16 == 5 || contador17 == 5 || contador18 == 5 || contador19 == 5 || contador20 == 5 || contador21 == 5 || contador22 == 5 || contador23 == 5 || contador24 == 5 || contador25 == 5 || contador26 == 5 || contador27 == 5 || contador28 == 5 || contador29 == 5 || contador30 == 5 || contador31 == 5 || contador32 == 5)
	{
		return true;
	}
	else{
		return false;
	}
}

void EvaluaPares(string mano[],bool gane[]){
	string cartas[52] = {"AC","2C","3C","4C","5C","6C","7C","8C","9C","10C","JC","QC","KC","AP","2P","3P","4P","5P","6P","7P","8P","9P","10P","JP","QP","KP","AD","2D","3D","4D","5D","6D","7D","8D","9D","10D","JD","QD","KD","AT","2T","3T","4T","5T","6T","7T","8T","9T","10T","JT","QT","KT"};
	int posiciones[5];
	int prueba;
	int pares1 = 1,pares2 = 1,pares3 = 1,pares4 = 1;
	int color1 = 0,color2 = 0,color3 = 0,color4 = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 52; j++)
		{
			if (mano[i] == cartas[j])
			{
				posiciones[i] = j;
			}
		}
	}

	//Primera lineadel Deck.
	for (int i = 0; i < 5; i++)
	{
		if (posiciones[i] >= 0 && posiciones[i] <= 12)
		{
			color1++;
			prueba = posiciones[i] + 13;
			for (int j = 0; j < 5; j++)
			{
				if (prueba == posiciones[j])
				{
					pares1++;
					posiciones[j] = -1;
				}
			}
			prueba = prueba + 13;
			for (int k = 0; k < 5; k++)
			{
				if (prueba == posiciones[k])
				{
					pares1++;
					posiciones[k] = -1;
				}
			}
			prueba = prueba + 13;
			for (int a = 0; a < 5; a++)
			{
				if (prueba == posiciones[a])
				{
					pares1++;
					posiciones[a] = -1;
				}
			}
			posiciones[i] = -1;
		}
		//Segunda linea del deck.
		else if (posiciones[i] >= 13 && posiciones[i] <= 25)
		{
			color2++;
			prueba = posiciones[i] - 13;
			for (int j = 0; j < 5; j++)
			{
				if (prueba == posiciones[j])
				{
					pares2++;
					posiciones[j] = -1;
				}
			}
			prueba = posiciones[i] + 13;
			for (int k = 0; k < 5; k++)
			{
				if (prueba == posiciones[k])
				{
					pares2++;
					posiciones[k] = -1;
				}
			}
			prueba = prueba + 13;
			for (int a = 0; a < 5; a++)
			{
				if (prueba == posiciones[a])
				{
					pares2++;
					posiciones[a] = -1;
				}
			}
			posiciones[i] = -1;
		}
		//Tercera linea del Deck.
		else if (posiciones[i] >= 26 && posiciones[i] <= 38)
		{
			color3++;
			prueba = posiciones[i] - 13;
			for (int j = 0; j < 5; j++)
			{
				if (prueba == posiciones[j])
				{
					pares3 = pares3 + 1;
					posiciones[j] = -1;
				}
			}
			prueba = prueba - 13;
			for (int k = 0; k < 5; k++)
			{
				if (prueba == posiciones[k])
				{
					pares3 = pares3 + 1;
					posiciones[k] = -1;
				}
			}
			prueba = posiciones[i] + 13;
			for (int a = 0; a < 5; a++)
			{
				if (prueba == posiciones[a])
				{
					pares3 = pares3 + 1;
					posiciones[a] = -1;
				}
			}
			posiciones[i] = -1;
		}
		//Cuarta linea del Deck.
		else if (posiciones[i] >= 39 && posiciones[i] <= 51)
		{
			color4++; 
			prueba = posiciones[i] - 13;
			for (int j = 0; j < 5; j++)
			{
				if (prueba == posiciones[j])
				{
					pares4 = pares4 + 1;
					posiciones[j] = -1;
				}
			}
			prueba = prueba - 13;
			for (int k = 0; k < 5; k++)
			{
				if (prueba == posiciones[k])
				{
					pares4 = pares4 + 1;
					posiciones[k] = -1;
				}
			}
			prueba = prueba - 13;
			for (int a = 0; a < 5; a++)
			{
				if (prueba == posiciones[a])
				{
					pares4++;
					posiciones[a] = -1;
				}
			}
			posiciones[i] = -1;
		}
	}
	
	if (pares1 == 4 || pares2 == 4 || pares3 == 4 || pares4 == 4)
	{
		gane[2] = true;
	} else if ((pares1 == 3 || pares2 == 3 || pares3 == 3 || pares4 == 3) && (pares1 == 2 || pares2 == 2 || pares3 == 2 || pares4 == 2))
	{
		gane[3] = true;
	}else if (color1 == 5 || color2 == 5 || color3 == 5 || color4 == 5)
	{
		gane[4] = true;
	}else if ((pares1 == 3 || pares2 == 3 || pares3 == 3 || pares4 == 3))
	{
		gane[6] = true;
	}else if ((pares1 == 2 && pares2 == 2) ||  (pares1 == 2 && pares3 == 2) || (pares1 == 2 && pares4 == 2) || (pares2 == 2 && pares3 == 2) || (pares2 == 2 && pares4 == 2) || (pares3 == 2 && pares4 == 2))
	{
		gane[7] = true;
	}else if ((pares1 == 2 || pares2 == 2 || pares3 == 2 || pares4 == 2))
	{
		gane[8] = true;
	}
}

bool Escalera(string mano[]){
	string cartas[52] = {"AC","2C","3C","4C","5C","6C","7C","8C","9C","10C","JC","QC","KC","AP","2P","3P","4P","5P","6P","7P","8P","9P","10P","JP","QP","KP","AD","2D","3D","4D","5D","6D","7D","8D","9D","10D","JD","QD","KD","AT","2T","3T","4T","5T","6T","7T","8T","9T","10T","JT","QT","KT"};
	int Escalera1[4] = {0,13,26,39};
	int Escalera2[4] = {1,14,27,40};
	int Escalera3[4] = {2,15,28,41};
	int Escalera4[4] = {3,16,29,42};
	int Escalera5[4] = {4,17,30,43};
	int Escalera6[4] = {5,18,31,44};
	int Escalera7[4] = {6,19,32,45};
	int Escalera8[4] = {7,20,33,46};
	int Escalera9[4] = {8,21,34,47};
	int Escalera10[4] = {9,22,35,48};
	int Escalera11[4] = {10,23,36,49};
	int Escalera12[4] = {11,24,37,50};
	int Escalera13[4] = {12,25,38,51};
	int posiciones1[5];
	int numerosDeCartas[5];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 52; j++)
		{
			if (mano[i] == cartas[j])
			{
				posiciones1[i] = j;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Escalera1[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 1;
			}
			else if (Escalera2[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 2;
			}
			else if (Escalera3[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 3;
			}
			else if (Escalera4[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 4;
			}
			else if (Escalera5[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 5;
			}
			else if (Escalera6[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 6;
			}
			else if (Escalera7[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 7;
			}
			else if (Escalera8[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 8;
			}
			else if (Escalera9[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 9;
			}
			else if (Escalera10[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 10;
			}
			else if (Escalera11[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 11;
			}
			else if (Escalera12[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 12;
			}
			else if (Escalera13[j] == posiciones1[i])
			{
				numerosDeCartas[i] = 13;
			}
		}
	}
	int temp;
	for (int q = 0; q < 5; ++q)
	{
		for (int w = 0; w < 5 - 1; ++w)
		{
			if (numerosDeCartas[w] > numerosDeCartas[w + 1])
			{
				temp = numerosDeCartas[w];
				numerosDeCartas[w] = numerosDeCartas[w + 1];
				numerosDeCartas[w + 1] = temp;
			}
		}
	}

	if ((numerosDeCartas[1] == (numerosDeCartas[0] + 1)) && (numerosDeCartas[2] == (numerosDeCartas[1] + 1)) && (numerosDeCartas[3] == (numerosDeCartas[2] + 1)) && (numerosDeCartas[4] == (numerosDeCartas[3] + 1)))
	{
		return true;
	}else{
		return false;
	}
}
