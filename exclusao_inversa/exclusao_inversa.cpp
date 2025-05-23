#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <string.h>

using namespace std;

struct aresta_peso {
    int v;
    int w;
    int peso;
};

struct vertice
{
    int pai;
    int rank;
};

bool ord_maior(aresta_peso& a, aresta_peso& b) {
    return a.peso > b.peso;
}

int cnt = 0;
void DFSrec(vector<vector<int> >& adj, vector<int>& pre, int v)
{
	pre[v] = cnt++;
	for(int i=0; i< adj[v].size(); i++)
	{
		int w = adj[v][i];
		if(pre[w] == -1)
			DFSrec(adj, pre, w);
	}
}

void DFS(vector<vector<int> >& adj, vector<int>& pre)
{
	cnt = 0;
	int n = adj.size();

	for(int v=0; v<n; v++)
		pre[v] = -1;

	DFSrec(adj, pre, 0);

}

bool dfs_bool(vector<vector<int>>& adj)
{
    int n = adj.size();
    vector<int> pre(n, -1);
    DFS(adj, pre);
    for(int i = 0; i < n; i++)
    {
        if (pre[i] == -1){
            return false;
        }
    }

    return true;
}

void help()
{
    cout << "-h : mostra o help\n-o <arquivo> : redireciona a saida para o \"arquivo\"\n-f <arquivo> : indica o \"arquivo\" que contem o grafo de entrada\n-s : mostra a solucao";
}

int main(int argc, char *argv[]) {
    string arq_entrada;
    string arq_saida;
    int i_argv = 1;
    int cont_print_saida = 0;
    int cont_arq_saida = 0;
    int cont_custo = 0;
    
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
            arq_entrada = argv[i_argv];
            cont_custo = 1;
        }
        else if (!strcmp(argv[i_argv], "-o"))
        {
            i_argv+=1;
            arq_saida = argv[i_argv];
            cont_arq_saida = 1;
        }
        else if (!strcmp(argv[i_argv], "-s"))
        {
            cont_custo = 0;
            cont_print_saida = 1;
        }
        i_argv+=1;
    }

    int n, m;

    ifstream arquivo_entrada(arq_entrada);

    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    arquivo_entrada >> n >> m;
    arquivo_entrada.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<aresta_peso> arestas(m);
    vector<vector<int>> adj(n, vector<int>());

    int v, w, p;
    for(int i = 0; i < m; i++) {
        arquivo_entrada >> v >> w >> p;
        arquivo_entrada.ignore(numeric_limits<streamsize>::max(), '\n');
        v -= 1;
        w -= 1;
        arestas[i].v = v;
        arestas[i].w = w;
        arestas[i].peso = p;
        adj[v].push_back(w);
		adj[w].push_back(v);
    }

    sort(arestas.begin(), arestas.end(), ord_maior);
    vector<aresta_peso> res(n-1);

    int controle = 0;
    int atual = 0;
    int total_peso = 0;

    while (controle < (n-1))
    {
        v = arestas[atual].v;
        w = arestas[atual].w;
        auto p_v = find(adj[w].begin(), adj[w].end(), v);
        auto p_w = find(adj[v].begin(), adj[v].end(), w);
        adj[v].erase(p_w);
        adj[w].erase(p_v);

        if (!dfs_bool(adj))
        {
            res[controle].v = v;
            res[controle].w = w;
            res[controle].peso = arestas[atual].peso;
            total_peso += arestas[atual].peso;
            adj[v].push_back(w);
            adj[w].push_back(v);
            controle+=1;
        }
        atual+=1;
    }

    if (cont_custo == 1) {
        cout << total_peso << endl;
    }

    if (cont_arq_saida == 1)
    {
        ofstream arquivo_saida(arq_saida);
        if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
        }
        for (int i=0; i < res.size(); i++)
        {
            arquivo_saida << "(" << res[i].v << "," << res[i].w << ")" << " ";
        }
        cout << endl;
    }

    if (cont_print_saida == 1)
    {
        for (int i=0; i < res.size(); i++)
        {
            cout << "(" << res[i].v << "," << res[i].w << ")" << " ";
        }
        cout << endl;
    }
    return 0;

}