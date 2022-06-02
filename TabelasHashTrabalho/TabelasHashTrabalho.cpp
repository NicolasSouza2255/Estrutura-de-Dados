#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;
int aux;
int numerolinha = 0;

struct TDado {
	string Texto;
	int chave;
	int frequencia = 1;
};

int const tamanhoMax = 10;
struct THashFechado {
	TDado* arrayFechada = new TDado[1];
	int colisoes = 0;
};

struct Dado {
	string Texto;
	int chave;
	Dado* proximo = nullptr;
	int frequencia = 1;
};

struct THashEncadeada {
	Dado* arrayEncadeadoHash[tamanhoMax];
	int contadorColision = 0;
};

//armazena no array encadeado
void ArmazernarEncadeada(int valorHash, string texto, THashEncadeada& hashEncadeada)
{
	Dado* dado = new Dado;
	dado->chave = valorHash;
	dado->Texto = texto;
	dado->proximo = nullptr;
	int mod = valorHash % tamanhoMax;
	if (hashEncadeada.arrayEncadeadoHash[mod] == NULL)
	{
		hashEncadeada.arrayEncadeadoHash[mod] = dado;
	}
	else
	{
		hashEncadeada.contadorColision++;
		Dado* nav = hashEncadeada.arrayEncadeadoHash[mod];
		if (nav->chave == valorHash) {
			nav->frequencia++;
			hashEncadeada.contadorColision--;
			return;
		}

		while (nav->proximo != nullptr)
		{
			nav = nav->proximo;
			if (nav->chave == valorHash) {
				nav->frequencia++;
				hashEncadeada.contadorColision--;
				return;
			}
		}
		nav->proximo = dado;
	}
}

string BuscarEncadeado(int valorHash, THashEncadeada& hashEncadeada) {
	int mod = valorHash % tamanhoMax;
	if (hashEncadeada.arrayEncadeadoHash[mod] == NULL) {
		return "Nao tem nada";
	}
	else
	{
		if (hashEncadeada.arrayEncadeadoHash[mod]->chave == valorHash)
		{
			return hashEncadeada.arrayEncadeadoHash[mod]->Texto;
		}
		else
		{
			Dado* nav = hashEncadeada.arrayEncadeadoHash[mod];
			while (nav != nullptr)
			{
				if (nav->chave == valorHash) {
					return nav->Texto;
				}
				else {
					nav = nav->proximo;
				}
			}
			return "Nao Foi possivel Encontrar";
		}
	}
}

void RemoverEncadeado(int chave, THashEncadeada& hashEncadeada) {
	int mod = chave % tamanhoMax;

	if (hashEncadeada.arrayEncadeadoHash[mod] == NULL) {
		cout << "Nao tem na Lista para Remover";
	}
	else
	{
		if (hashEncadeada.arrayEncadeadoHash[mod]->chave == chave)
		{
			Dado* Apagar = hashEncadeada.arrayEncadeadoHash[mod];
			hashEncadeada.arrayEncadeadoHash[mod] = Apagar->proximo;
			hashEncadeada.contadorColision--;
			delete Apagar;
		}
		else
		{
			Dado* nav = hashEncadeada.arrayEncadeadoHash[mod];
			while (nav->proximo->chave != chave)
			{
				nav = nav->proximo;
				if (nav->proximo == NULL) {
					cout << "Nao tem nada na lista para remover";
					return;
				}
			}

			Dado* Apagar = nav->proximo;
			nav->proximo = Apagar->proximo;

			delete Apagar;
		}
	}
}

// calcula hash, pega a palavra, tira a pontuação e retorna a hash como numero linha;
// três tipos de calculo hash explicados no relatório
int FuncHash1(string texto) {
	numerolinha = 0;
	int contador = 1;
	// remove pontuação
	texto.erase(remove_if(texto.begin(), texto.end(), ispunct), texto.end());
	for (int i = 0; i < texto.size(); i++) {
		if (texto[i] == ' ') {
			cout << "\n";
			return numerolinha;
		}
		else {
			numerolinha += texto[i] * contador;
		}
		contador++;
	}
	return numerolinha;
}

int FuncHash2(string texto) {
	numerolinha = 0;
	int contador = 1;
	// remove pontuação
	texto.erase(remove_if(texto.begin(), texto.end(), ispunct), texto.end());
	for (int i = 0; i < texto.size(); i++) {
		if (texto[i] == ' ') {
			cout << "\n";
			return numerolinha * 2;
		}
		else {
			numerolinha += texto[i] * contador;
		}
		contador++;
	}
	return numerolinha * 2;
}

int FuncHash3(string texto) {
	numerolinha = 0;
	int contador = 1;
	// remove pontuação
	texto.erase(remove_if(texto.begin(), texto.end(), ispunct), texto.end());

	for (int i = 0; i < texto.size(); i++) {
		if (texto[i] == ' ') {
			cout << "\n";
			return numerolinha / 2;
		}
		else {
			numerolinha += texto[i] * contador;
		}
		contador++;
	}
	return numerolinha / 2;
}

void imprimirValorArrayEncadeado(THashEncadeada& hashEncadeada)
{
	Dado* nav;
	int contador = 0;
	do {
		cout << "Parte do array [" << contador + 1 << "]: ";
		nav = hashEncadeada.arrayEncadeadoHash[contador];
		if (hashEncadeada.arrayEncadeadoHash[contador] == NULL)
		{
			cout << "Nada";
		}
		else
		{
			if (hashEncadeada.arrayEncadeadoHash[contador] != NULL && nav->proximo == NULL)
			{
				cout << "| Chave: " << nav->chave << " Texto: " << nav->Texto << " [" << nav->frequencia << "]";
			}
			else
			{
				while (nav->proximo != nullptr)
				{
					cout << "| Chave: " << nav->chave << " Texto: " << nav->Texto << " [" << nav->frequencia << "]" << " ";
					nav = nav->proximo;
				}
				cout << " | Chave: " << nav->chave << " Texto: " << nav->Texto << " [" << nav->frequencia << "]" << " ";
			}
		}
		cout << endl;
		cout << endl;
		contador++;
	} while (contador < tamanhoMax);
	cout << "Foram feitas: " << hashEncadeada.contadorColision << " colisoes";
}

void ArmazenarFechado(int valorHash, THashFechado& hashFechado, string texto, int valor)
{
	int mod = valorHash % valor;
	int contador = mod;
	if (hashFechado.arrayFechada[mod].chave == NULL)
	{
		hashFechado.arrayFechada[mod].chave = valorHash;
		hashFechado.arrayFechada[mod].Texto = texto;
	}
	else
	{
		if (hashFechado.arrayFechada[mod].chave == valorHash) {
			hashFechado.arrayFechada[mod].frequencia++;
			return;
		}
		while (hashFechado.arrayFechada[mod].chave != NULL)
		{
			hashFechado.colisoes++;
			mod++;
		}
		if (hashFechado.arrayFechada[mod].chave == NULL)
		{
			hashFechado.arrayFechada[mod].chave = valorHash;
			hashFechado.arrayFechada[mod].Texto = texto;
		}
		else
		{
			if (mod == valor)
				mod = 0;
			while (hashFechado.arrayFechada[mod].chave != NULL)
			{
				hashFechado.colisoes++;
				mod++;

				if (mod == contador)
					break;
			}
			if (hashFechado.arrayFechada[mod].chave == NULL)
			{
				hashFechado.arrayFechada[mod].chave = valorHash;
				hashFechado.arrayFechada[mod].Texto = texto;
			}
		}
	}
}

void inicializarHashFechada(THashFechado& hashFechado, int quantidade)
{
	for (int i = 0; i < quantidade; i++)
	{
		hashFechado.arrayFechada[i].chave = 0;
		hashFechado.arrayFechada[i].Texto = "";
	}
}

void inicializarHashEncadeada(THashEncadeada& hashEncadeada)
{
	//inicializar tudo da hash encadeada como null;
	for (int i = 0; i < tamanhoMax; i++)
	{
		hashEncadeada.arrayEncadeadoHash[i] = NULL;
	}
}

int contarPalavrasArquivo()
{
	int contatadorPalavras = 0;
	ifstream myfile("Teste.txt"); // ifstream = padrão ios:in
	if (myfile.is_open())
	{
		while (!myfile.eof()) //enquanto end of file for false continua
		{
			string word;
			while (myfile >> word)
			{
				contatadorPalavras++;
			}
		}
		myfile.close();
	}
	else 
		cout << "Unable to open file";
	return contatadorPalavras;
}

void imprimirValorArrayFechado(THashFechado& hashFechado, int valorArray)
{
	for (int i = 0; i < valorArray; i++)
	{
		if (hashFechado.arrayFechada[i].chave != NULL)
			cout << "Hash: " << hashFechado.arrayFechada[i].chave << "| Palavra: " << hashFechado.arrayFechada[i].Texto << " [" << hashFechado.arrayFechada[i].frequencia << "]" << endl;
		else
			cout << "Nada" << endl;
	}
	cout << endl;
	cout << "Colisões realizadas: " << hashFechado.colisoes << endl;
}

void RemoverHashFechada(THashFechado& hashFechado, int valorArray, int hash)
{
	int i = 0;
	while (i < valorArray)
	{
		if (hashFechado.arrayFechada[i].chave != hash)
		{
			i++;
		}
		hashFechado.arrayFechada[i].chave = NULL;
		hashFechado.arrayFechada[i].Texto = "";
	}
}

void EncontrarHashFechada(THashFechado& hashFechado, int valorArray, int hash)
{
	int i = 0;
	while (i < valorArray)
	{
		if (hashFechado.arrayFechada[i].chave != hash)
		{
			i++;
		}
		else
		{
			cout << "Posicao no array: " << i << " Valor da hash: " << hashFechado.arrayFechada[i].chave << " valor da palavra: " << hashFechado.arrayFechada[i].Texto << endl;
		}
	}
}

int main() {
	int quantidade = 0;
	int hash = 0;
	int contatadorPalavras = 0;
	THashEncadeada hashEncadeada;
	THashFechado hashFechado;
	string line;

	quantidade = contarPalavrasArquivo();
	int valorArray = (quantidade * 0.30) + quantidade;
	hashFechado.arrayFechada = new TDado[valorArray];
	inicializarHashEncadeada(hashEncadeada);
	inicializarHashFechada(hashFechado, valorArray);

	ifstream myfile("Teste2.txt"); // ifstream = padrão ios:in
	if (myfile.is_open())
	{
		while (!myfile.eof()) //enquanto end of file for false continua
		{
			string word;
			while (myfile >> word)
			{
				contatadorPalavras++;
				hash = FuncHash3(word);
				ArmazernarEncadeada(hash, word, hashEncadeada);
				ArmazenarFechado(hash, hashFechado, word, valorArray);
				hash = 0;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	imprimirValorArrayFechado(hashFechado, valorArray);
	cout << endl;
	cout << endl;
	imprimirValorArrayEncadeado(hashEncadeada);
	return 0;
}