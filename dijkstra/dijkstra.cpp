#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Aresta {
    int destino;
    int peso;
};

bool lerGrafo(const string& arquivoEntrada, vector<vector<Aresta>>& grafo) {
    ifstream arquivo(arquivoEntrada);
    if (!arquivo.is_open()) {
        cerr << "erro ao abrir arquivo" << endl;
        return false;
    }

    int n, m;
    arquivo >> n >> m;
    grafo.resize(n);
    for (int i = 0; i < m; i++) {
        int v, w, p;
        arquivo >> v >> w >> p;
        v--; w--;
        //valida indice dos vertices
        if (v < 0 || v >= n || w < 0 || w >= n) {
            cerr << "vertice invalido" << endl;
            return false;
        }
        grafo[v].push_back({w, p});
        grafo[w].push_back({v, p}); //teorema do aperto de mão
    }
    return true;
}

void Dijkstra(vector<vector<Aresta>>& grafo, int raiz, vector<int>& dist) {
    int n = grafo.size();
    dist.assign(n, INT_MAX);
    dist[raiz] = 0;

    //"heap-min"
    priority_queue<
        pair<int, int>, 
        vector<pair<int, int>>, 
        greater<pair<int, int>>> fila;
    fila.push({0, raiz});

    while (!fila.empty()) {
        int u = fila.top().second; //pega o 1° vertice da fila
        int d = fila.top().first; //pega seu peso
        fila.pop();
        if (d > dist[u]) continue;
        for (int i = 0; i < grafo[u].size(); i++) {
            int w = grafo[u][i].destino;
            int prioridade = d + grafo[u][i].peso;
            if (prioridade < dist[w]) {
                dist[w] = prioridade;
                fila.push({prioridade, w});
            }
        }
    }
    for (int i = 0; i < dist.size(); i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }
}

void help()
{
    cout << "-h: mostra o help" << endl << endl;
    cout << "Para ler o arquivo de entrada:\n./<executavel> -f <arquivo de entrada> -i <vertice inicial>" << endl << endl;
    cout << "Para salvar o arquivo de saida:\n<comandos anteriores> -o <arquivo de saida>" << endl << endl;
}

int main(int argc, char* argv[]) {
    string nomeEntrada, nomeSaida;
    int i_argv = 1;
    int cont_print_saida = 0;
    int cont_arq_saida = 0;
    int v = 0;

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
            if (i_argv >= argc) {
                cerr << "erro! sem valor de v inicial" << endl;
                return 1;
            }
            //stoi converte a string em int
            v = stoi(argv[i_argv]);
        }
        i_argv+=1;
    }

    vector<vector<Aresta>> grafo;
    if(!lerGrafo(nomeEntrada, grafo))
        return 1;

    vector<int> dist;
    Dijkstra(grafo, v, dist);

    // Imprimir resultados no formato exigido
    for (int i = 0; i < dist.size(); ++i) {
        cout << i + 1 << ":" << dist[i];
        if (i != dist.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}