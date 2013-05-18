// TRANSMITAM AVISOS AQUI :^P//
/* ORLANDO: Este � s� um teste do curses e do gerador aleat�rio.
Pro git funcionar com a gente, � melhor as implementa��es ficarem em arquivos diferentes. Da� n�o d� conflito na hora de sincronizar. :-S
*/
#include "curses.h" // include: http://sourceforge.net/projects/pdcurses/files/ manual: http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/
#include "xorshift.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;

void Setup(void);
void Input(void);
void Update(void);
void Render(void);
void Close(void);
using namespace std::this_thread;

// globais
xorshift randomEngine;
bool isRunning = true;
int key;
// fun��es protot�picas
int Random(int min, int max);
int rolledDie;
bool isRolling = false;
int main(int argc, char* argv[])
{
	// Configura��o
	Setup();

	// La�o L�dico
	while (isRunning)
	{
		// Exibir resultados
		Render();
		// Intera��es
		Input();
		// Atualizar dados l�dicos
		Update();

	}

	Close();
	return 0;
}


void Setup(void)
{
	// motor aleat�rio
	randomEngine.seed(time(nullptr));
	// Inicializar console
	initscr();								// cria objeto stdscr (tela principal)
	start_color();							
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));

	//raw();					/* Buffer de linha desabilitado	*/
	keypad(stdscr, true);	/* Captar F1, F2 etc..		*/
	noecho();				/* N�o ecoar na tela quando fizer um getch */

// abertura
}

void Input(void)
{
	key = getch();     /* refresh, accept single keystroke of input */
	switch (key)
	{
	case 'r':
		{
			rolledDie = Random(1,20);
			isRolling = true;
		}
	default:
		break;
	}
}

void Update(void)
{

}

void Render(void)
{	
	// limpar tela
	clear();
	// Desenha
	printw("Ol�, Mundo!\n");
	if(isRolling)
	{
		printw("Voc� tirou %d\n", rolledDie);
		if(rolledDie == 20)
			printw("Golpe fulminante!!!");
		else if(rolledDie == 1)
			printw("Voc� errou desastrosamente :^(");
	}
	// Atualizar tela
	wrefresh(stdscr);
}

void Close(void)
{
	// apagar aloca��es
	//delete randomEngine;
	// Encerrar curses
	endwin();
}

int Random(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	int i = dist(randomEngine);
	return i;
}
