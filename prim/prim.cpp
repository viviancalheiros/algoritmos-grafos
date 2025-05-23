#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <string.h>
#include <fstream>
#include <limits>

using namespace std;

struct Aresta {
    int destino;
    int peso;
};

struct No {
    int custo; //prioridade
    int pai; //de onde vem
};

bool lerGrafo(int m, ifstream& arquivoEntrada, vector<vector<Aresta>>& grafo) {
    for (int i = 0; i < m; i++) {
        int v, w, p;
        arquivoEntrada >> v >> w >> p;
        
        //valida indice dos vertices
        if (v < 1 || v >= grafo.size() || w < 1 || w >= grafo.size()) {
            cerr << "vertice invalido" << endl;
            return false;
        }
        grafo[v].push_back({w, p});
        grafo[w].push_back({v, p}); //teorema do aperto de mão
    }
    return true;
}

void iniciaCusto (vector<No>& arvore, int raiz) {
    for (int i = 1; i < arvore.size(); i++) {
        arvore[i].custo = INT_MAX;
        arvore[i].pai = -1;
    }
    arvore[raiz].pai = raiz;
    arvore[raiz].custo = 0;
}

void prim (vector<vector<Aresta>>& grafo, vector<No>& arvore, int raiz) {
    int n = grafo.size() - 1;
    vector<bool> naArvore(n+1, false); //se o vertice ja esta na arvore
    priority_queue<
        //peso/prioridade, num
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > fila;
    fila.push({0, raiz});

    while (!fila.empty()) {
        int w = fila.top().second; //num do vertice
        int c = fila.top().first; //peso
        fila.pop();
        if (naArvore[w]) continue;
        naArvore[w] = true;
        for (int i = 0; i < grafo[w].size(); i++) {
            int v = grafo[w][i].destino;
            int p = grafo[w][i].peso;
            if (!naArvore[v] && p < arvore[v].custo) {
                arvore[v].custo = p;
                arvore[v].pai = w;
                fila.push({p, v});
            }
        }
    }
}

bool ehConexo (vector<No>& arvore) {
    for (int i = 1; i < arvore.size(); i++) {
        if (arvore[i].pai == -1) return false;
    }
    return true;
}

int calcularCusto (vector<No>& arvore) {
    int custo = 0;
    for (int i = 1; i < arvore.size(); i++) {
        if (arvore[i].pai != -1 && arvore[i].custo != INT_MAX) {
            custo += arvore[i].custo;
        }
    }
    return custo;
}

void help()
{
    cout << "-h: mostra o help" << endl << endl;
    cout << "Para ler o arquivo de entrada:\n./<executavel> -f <arquivo de entrada> -i <vertice inicial>" << endl << endl;
    cout << "Para ler o arquivo e exibir as arestas:\n./<executavel> -f <arquivo de entrada> -i <vertice inicial> -s" << endl << endl;
    cout << "Para salvar o arquivo de saida:\n<comandos anteriores> -o <arquivo de saida>" << endl << endl;
}


int main (int argc, char *argv[]) {
    string nomeEntrada;
    string nomeSaida;
    int i_argv = 1;
    int cont_print_saida = 0;
    int cont_arq_saida = 0;
    int v = 1;

    while (i_argv < argc)
    {
        if (!strcmp(argv[i_argv], "-h"))
        {
            help();
            return 0;
        }
        else if (!strcmp(argv[i_argv], "-f"))
        {
            i_argv+=1;
            nomeEntrada = argv[i_argv];
        }
        else if (!strcmp(argv[i_argv], "-o"))
        {
            i_argv+=1;
            nomeSaida = argv[i_argv];
            cont_arq_saida = 1;
        }
        else if (!strcmp(argv[i_argv], "-s"))
        {
            cont_print_saida = 1;
        }
        else if (!strcmp(argv[i_argv], "-i"))
        {
            i_argv+=1;
            //stoi converte a string em int
            v = stoi(argv[i_argv]);
        }
        i_argv+=1;
    }
    int n, m;
    ifstream arquivoEntrada(nomeEntrada);
    if (!arquivoEntrada.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    arquivoEntrada >> n >> m;
    vector<vector<Aresta>> grafo(n+1);
    if(!lerGrafo(m, arquivoEntrada, grafo)) {
        return 1;
    };

    vector<No> arvore(n+1);
    iniciaCusto(arvore, v);

    prim(grafo, arvore, v);
    int custo = calcularCusto(arvore);
    if (!cont_print_saida && !cont_arq_saida) 
        cout << custo << endl;

    if (cont_arq_saida == 1) {
        ofstream arquivoSaida(nomeSaida);
        if (!arquivoSaida.is_open()) {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return 1;
        }
        for (int i = 1; i < arvore.size(); i++) {
            if (i != arvore[i].pai) {
                if (i < arvore[i].pai)
                    arquivoSaida << "(" << i << "," << arvore[i].pai << ") ";
                else 
                    arquivoSaida << "(" << arvore[i].pai << "," << i << ") ";
            }
        }
        arquivoSaida << endl;
    }

    if (cont_print_saida == 1) {
        for (int i = 1; i < arvore.size(); i++) {
            if (i != arvore[i].pai) {
                if (i < arvore[i].pai)
                    cout << "(" << i << "," << arvore[i].pai << ") ";
                else 
                    cout << "(" << arvore[i].pai << "," << i << ") ";
            }
        }
        cout << endl;
    }

    return 0;
}