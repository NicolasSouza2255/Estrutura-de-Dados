
// ALUNOS ERICK GARCIA E NICOLAS SOUZA


#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

ofstream arquivoLog("log.txt");

char Str[300];
int Truco = 1;

int Trucado1 = 0;
int Trucado2 = 0;
int respostatruco;
int coringa = 0;

int pontosdupla1 = 0, pontosdupla2 = 0;
int qtdJogador = 0;
string Jogadores[4] = { "Erick", "Nicolas", "Fulano", "Ciclano" };
string naipe[4] = { "Moles", "Espadas", "Copas", "Paus" };
int NumeroCarta[10] = { 4, 5, 6, 7, 11, 12, 13, 1, 2, 3 };

struct Carta {
	int NumCarta;
	string naipe;
};

int const maximo = 40;
struct Lista {
	Carta carta[maximo];
	int quantidade;
	Carta coringa;
};

int const maxplayer = 4;
struct Jogador {
	Lista cartaJogador;
	string nomeJogador;
};

void InicializarLista(Lista& l)
{
	l.quantidade = 0;
}

void CriarBaralho(Lista& l)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Carta carta;
			carta.naipe = naipe[i];
			carta.NumCarta = NumeroCarta[j];
			l.carta[l.quantidade] = carta;
			l.quantidade++;
		}
	}
}

void EmbaralharCartas(Lista& l, Lista& novaLista)
{
	srand(time(NULL));
	if (novaLista.carta[1].NumCarta > 0)
	{
		for (int i = 0; i < 40; i++)
		{
			novaLista.carta[i].NumCarta = NULL;
			novaLista.carta[i].naipe = "";
		}
	}

	for (int i = 0; i < maximo; i++)
	{
		int posicao = rand() % maximo;
		Carta carta = l.carta[i];

		if (novaLista.carta[posicao].NumCarta <= 0)
		{
			novaLista.carta[posicao] = carta;
			novaLista.quantidade++;
		}
		else
		{
			i--;
		}
	}
}

void DistribuirCartas(Jogador& jogador, Lista& l)
{
	jogador.nomeJogador = Jogadores[qtdJogador];
	for (int i = 0; i < 3; i++)
	{
		jogador.cartaJogador.carta[i].NumCarta = l.carta[l.quantidade - 1].NumCarta;
		jogador.cartaJogador.carta[i].naipe = l.carta[l.quantidade - 1].naipe;
		jogador.cartaJogador.quantidade++;
		l.quantidade--;
	}
	qtdJogador++;
}

void MostrarCoringa(Lista& l)
{
	coringa = l.carta[l.quantidade].NumCarta;
}

void JogarVez(Jogador& jogador1, Jogador& jogador2, Jogador& jogador3, Jogador& jogador4)
{
	int qtdTurnoseqp1 = 0, qtdTurnoseqp2 = 0;
	for (int i = 0; i < 3; i++)
	{
		if (qtdTurnoseqp1 == 2)
		{
			pontosdupla1++;
			cout << "A dupla: " << jogador1.nomeJogador << " e " << jogador3.nomeJogador << " ganharam a rodada e agora estao com: " << pontosdupla1 << " pontos!" << endl;
		}
		else if (qtdTurnoseqp2 == 2)
		{
			pontosdupla2++;
			cout << "A dupla: " << jogador2.nomeJogador << " e " << jogador4.nomeJogador << " ganharam a rodada e agora estao com: " << pontosdupla2 << " pontos!" << endl;
		}

		int contador1 = 0, contador2 = 0, contador3 = 0, contador4 = 0;
		while (jogador1.cartaJogador.carta[i].NumCarta != NumeroCarta[contador1])
		{
			contador1++;
		}
		while (jogador2.cartaJogador.carta[i].NumCarta != NumeroCarta[contador2])
		{
			contador2++;
		}
		while (jogador3.cartaJogador.carta[i].NumCarta != NumeroCarta[contador3])
		{
			contador3++;
		}
		while (jogador4.cartaJogador.carta[i].NumCarta != NumeroCarta[contador4])
		{
			contador4++;
		}

		if (jogador1.cartaJogador.carta[i].NumCarta == coringa)
		{
			int contadorNaipe = 0;
			while (jogador1.cartaJogador.carta[i].naipe != naipe[contadorNaipe])
			{
				contador1++;
				contadorNaipe++;
			}
		}

		if (jogador2.cartaJogador.carta[i].NumCarta == coringa)
		{
			int contadorNaipe = 0;
			while (jogador2.cartaJogador.carta[i].naipe != naipe[contadorNaipe])
			{
				contador2++;
				contadorNaipe++;
			}
		}

		if (jogador3.cartaJogador.carta[i].NumCarta == coringa)
		{
			int contadorNaipe = 0;
			while (jogador3.cartaJogador.carta[i].naipe != naipe[contadorNaipe])
			{
				contador3++;
				contadorNaipe++;
			}
		}

		if (jogador4.cartaJogador.carta[i].NumCarta == coringa)
		{
			int contadorNaipe = 0;
			while (jogador4.cartaJogador.carta[i].naipe != naipe[contadorNaipe])
			{
				contador4++;
				contadorNaipe++;
			}
		}

		arquivoLog << "=============================================Cartas Jogadas ==========================================================" << endl;
		arquivoLog << "O jogador: " << jogador1.nomeJogador << " jogou: " << jogador1.cartaJogador.carta[i].NumCarta << " de " << jogador1.cartaJogador.carta[i].naipe << endl;
		arquivoLog << "O jogador: " << jogador2.nomeJogador << " jogou: " << jogador2.cartaJogador.carta[i].NumCarta << " de " << jogador2.cartaJogador.carta[i].naipe << endl;
		arquivoLog << "O jogador: " << jogador3.nomeJogador << " jogou: " << jogador3.cartaJogador.carta[i].NumCarta << " de " << jogador3.cartaJogador.carta[i].naipe << endl;
		arquivoLog << "O jogador: " << jogador4.nomeJogador << " jogou: " << jogador4.cartaJogador.carta[i].NumCarta << " de " << jogador4.cartaJogador.carta[i].naipe << endl;

		cout << "=============================================Cartas Jogadas ==========================================================" << endl;
		cout << "O jogador: " << jogador1.nomeJogador << " jogou: " << jogador1.cartaJogador.carta[i].NumCarta << " de " << jogador1.cartaJogador.carta[i].naipe << endl;
		cout << "O jogador: " << jogador2.nomeJogador << " jogou: " << jogador2.cartaJogador.carta[i].NumCarta << " de " << jogador2.cartaJogador.carta[i].naipe << endl;
		cout << "O jogador: " << jogador3.nomeJogador << " jogou: " << jogador3.cartaJogador.carta[i].NumCarta << " de " << jogador3.cartaJogador.carta[i].naipe << endl;
		cout << "O jogador: " << jogador4.nomeJogador << " jogou: " << jogador4.cartaJogador.carta[i].NumCarta << " de " << jogador4.cartaJogador.carta[i].naipe << endl;
		cout << endl;

		if (contador1 > contador2 && contador1 > contador3 && contador1 > contador4)
		{
			qtdTurnoseqp1++;
			arquivoLog << "O jogador : " << jogador1.nomeJogador << " jogou a carta mais alta" << endl;
			cout << "O jogador: " << jogador1.nomeJogador << " jogou a carta mais alta" << endl;
		}

		if (contador2 > contador1 && contador2 > contador3 && contador2 > contador4)
		{
			qtdTurnoseqp2++;
			arquivoLog << "O jogador : " << jogador2.nomeJogador << " jogou a carta mais alta" << endl;
			cout << "O jogador: " << jogador2.nomeJogador << " jogou a carta mais alta" << endl;
		}

		if (contador3 > contador1 && contador3 > contador2 && contador3 > contador4)
		{
			qtdTurnoseqp1++;
			arquivoLog << "O jogador : " << jogador3.nomeJogador << " jogou a carta mais alta" << endl;
			cout << "O jogador: " << jogador3.nomeJogador << " jogou a carta mais alta" << endl;
		}

		if (contador4 > contador1 && contador4 > contador2 && contador4 > contador3)
		{
			qtdTurnoseqp2++;
			arquivoLog << "O jogador : " << jogador4.nomeJogador << " jogou a carta mais alta" << endl;
			cout << "O jogador: " << jogador4.nomeJogador << " jogou a carta mais alta" << endl;
		}

		cin.get();

		if (qtdTurnoseqp1 >= 2 || qtdTurnoseqp2 >= 2) {
			i++;
		}

	}
	if (pontosdupla1 >= 11) {
		Trucado2 = 2;
	}
	if (pontosdupla2 >= 11) {
		Trucado1 = 2;
	}
	if (qtdTurnoseqp1 > qtdTurnoseqp2)
	{
		pontosdupla1 += Truco + Trucado1;
		cout << "A dupla: " << jogador1.nomeJogador << " e " << jogador3.nomeJogador << " ganharam a rodada e agora estao com: " << pontosdupla1 << " pontos!" << endl;
	}
	else
	{
		pontosdupla2 += Truco + Trucado2;
		cout << "A dupla: " << jogador2.nomeJogador << " e " << jogador4.nomeJogador << " ganharam a rodada e agora estao com: " << pontosdupla2 << " pontos!" << endl;
	}
	cin.get();
}

void ItsTimeToTruco(Jogador& jogadorTrucado, Jogador& jogador2, Jogador& jogador3, Jogador& jogador4)
{
	Truco = 1;
	srand(time(NULL));
	int truco = rand() % 4 + 1;
	if (truco == 3)
	{
		Truco = 3;
		cout << endl;
		cout << "============================================== TRUCO POHA =========================================================" << endl;
		cout << " ========================================= " << jogadorTrucado.nomeJogador << " Pediu Truco ===================================================" << endl;
		cout << endl;

		truco = rand() % 3 + 1;
		if (truco == 1) {
			Truco = 6;
			cout << endl;
			cout << "============================================== SEIS KARALHO =======================================================";
			cout << endl;

			respostatruco = rand() % 2 + 1;
			if (respostatruco == 1) {
				cout << " ========================================= " << jogador2.nomeJogador << " Pediu Seis ===================================================" << endl;
			}
			else {
				cout << " ========================================= " << jogador4.nomeJogador << " Pediu Seis ===================================================" << endl;
			}

			truco = rand() % 3 + 1;
			if (truco == 2) {
				Truco = 9;
				cout << endl;
				cout << "============================================== NOVEEEEEEE =========================================================" << endl;
				cout << endl;
				respostatruco = rand() % 2 + 1;

				if (respostatruco == 1) {
					cout << " ========================================= " << jogadorTrucado.nomeJogador << " Pediu Nove ===================================================" << endl;
				}
				else {
					cout << " ========================================= " << jogador3.nomeJogador << " Pediu Nove ===================================================" << endl;
				}

				truco = rand() % 3 + 1;
				if (truco == 1) {
					Truco = 12;
					cout << endl;
					cout << "============================================== VAM DE 12 ENTAO ================================================" << endl;
					cout << endl;

					respostatruco = rand() % 2 + 1;
					if (respostatruco == 1) {
						cout << " ========================================= " << jogador2.nomeJogador << " Pediu Doze ===================================================" << endl;
					}
					else {
						cout << " ========================================= " << jogador4.nomeJogador << " Pediu Doze ===================================================" << endl;
					}
				}
			}
			cout << endl;
		}
	}
}

void VerQuemTrucou(Jogador& jogador1, Jogador& jogador2, Jogador& jogador3, Jogador& jogador4) {
	int trucoplayer = 0;
	if (pontosdupla1 < 11 && pontosdupla2 < 11) {
		trucoplayer = rand() % 4 + 1;
	}

	if (pontosdupla1 == 11) {
		do
		{
			trucoplayer = rand() % 4 + 1;
		} while (trucoplayer != 1 && trucoplayer != 3);
	}

	if (pontosdupla2 == 11) {
		do
		{
			trucoplayer = rand() % 4 + 1;
		} while (trucoplayer != 2 && trucoplayer != 4);
	}

	switch (trucoplayer) {
	case 1:
		ItsTimeToTruco(jogador1, jogador2, jogador3, jogador4);
		break;
	case 2:
		ItsTimeToTruco(jogador2, jogador3, jogador4, jogador1);
		break;
	case 3:
		ItsTimeToTruco(jogador3, jogador4, jogador1, jogador2);
		break;
	case 4:
		ItsTimeToTruco(jogador4, jogador1, jogador2, jogador3);
		break;

	default:

		break;
	}
}

int main()
{

	Lista lista;
	Lista listaEmbaralhada;
	Jogador jogador1;
	Jogador jogador2;
	Jogador jogador3;
	Jogador jogador4;

	do
	{

		InicializarLista(lista);
		CriarBaralho(lista);
		InicializarLista(listaEmbaralhada);
		EmbaralharCartas(lista, listaEmbaralhada);
		DistribuirCartas(jogador1, listaEmbaralhada);
		DistribuirCartas(jogador2, listaEmbaralhada);
		DistribuirCartas(jogador3, listaEmbaralhada);
		DistribuirCartas(jogador4, listaEmbaralhada);
		VerQuemTrucou(jogador1, jogador2, jogador3, jogador4);
		JogarVez(jogador1, jogador2, jogador3, jogador4);
		qtdJogador = 0;

		if (pontosdupla1 >= 12)
		{
			cout << "A dupla: " << jogador1.nomeJogador << " e " << jogador3.nomeJogador << " ganhou a partida que ficou: " << pontosdupla1 << " a " << pontosdupla2 << endl;
			break;
		}
		else if (pontosdupla2 >= 12)
		{
			cout << "A dupla: " << jogador2.nomeJogador << " e " << jogador4.nomeJogador << " ganhou a partida que ficou: " << pontosdupla2 << " a " << pontosdupla1 << endl;
			break;
		}
	} while (pontosdupla1 < 12 || pontosdupla2 < 12);
}