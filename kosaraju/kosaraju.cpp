#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string.h>

#include <algorithm>

using namespace std;

int cont_pos = 0;

void zerar_cont_pos()
{
    cont_pos = 0;
}

void inic_visita(vector<int>& ordem_visita)
{
    int n = ordem_visita.size();
    for(int i=1; i<=n; i++){
        ordem_visita[i] = i;
    }
}

void DFSrec(vector<vector<int> >& adj, vector<int>& controle, vector<int>& pos , vector<int>& comp_fort_conexas, int cont_comp, int v)
{
	controle[v] = 0;
    comp_fort_conexas[v] = cont_comp;
	for(int i=0; i< adj[v].size(); i++)
	{
		int w = adj[v][i];
		if (controle[w] == -1)
		{
			DFSrec(adj, controle, pos, comp_fort_conexas, cont_comp, w);
		}   
	}
	pos[v] = cont_pos++;
}

void DFS(vector<vector<int> >& adj, vector<int>& controle, vector<int>& pos, vector<int>& ordem_visita, vector<int>& comp_fort_conexas)
{
    controle.assign(controle.size(), -1);
    pos.assign(pos.size(), -1);
    cont_pos = 0;
	int n = adj.size();
    int cont_comp = 0;
    for (int v=1; v<=n; v++)
    {
        if (controle[ordem_visita[v]] == -1)
        {
			DFSrec(adj, controle, pos, comp_fort_conexas, cont_comp, ordem_visita[v]);
            cont_comp++;
        }
    }
}

void help()
{
    cout << "-h: mostra o help" << endl << endl;
    cout << "Para ler o arquivo de entrada:\n./<executavel> -f <arquivo de entrada>" << endl << endl;
    cout << "Para salvar o arquivo de saida:\n<comandos anteriores> -o <arquivo de saida>" << endl << endl;
}

int main(int argc, char *argv[])
{
    string arq_entrada;
    string arq_saida;
    int i_argv = 1;
    int cont_arq_saida = 0;

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
        }
        else if (!strcmp(argv[i_argv], "-o"))
        {
            i_argv+=1;
            arq_saida = argv[i_argv];
            cont_arq_saida = 1;
        }
        i_argv+=1;
    }

	// Leitura do grafo
	int n, m;
    ifstream arquivo_entrada(arq_entrada);
    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
	arquivo_entrada >> n >> m;
    arquivo_entrada.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	vector<vector<int> > adj_original(n+1, vector<int>());
    vector<vector<int> > adj_inversa(n+1, vector<int>());
    vector<int> ordem_visita(n+1);
    vector<int> comp_fort_conexas(n+1);
	
    int v, w;
	for(int i=0; i<m;i++)
	{
		arquivo_entrada >> v >> w;
        arquivo_entrada.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		adj_original[v].push_back(w);
        adj_inversa[w].push_back(v);
	}

	vector<int> controle(n+1, -1);
	vector<int> pos(n+1, -1);
    inic_visita(ordem_visita);
	DFS(adj_inversa, controle, pos, ordem_visita, comp_fort_conexas);

    for(int i=1; i<=n; i++){
        ordem_visita[(n-(pos[i]))] = i; 
    }

    DFS(adj_original, controle, pos, ordem_visita, comp_fort_conexas);

    int c = 0;
    if (cont_arq_saida == 1)
    {
        ofstream arquivo_saida(arq_saida);
        if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
        }

        while (c != -1)
        {
            c = -1;
            for (int i = 1; i <= n; i++)
            {
                if (c == -1)
                {
                    if (comp_fort_conexas[i] != -1)
                    {
                        c = comp_fort_conexas[i];
                        cout << i << " ";
                        arquivo_saida << i << " ";
                        comp_fort_conexas[i] = -1;
                    }
                }
                else
                {
                    if (comp_fort_conexas[i] == c)
                    {
                        cout << i << " ";
                        arquivo_saida << i << " ";
                        comp_fort_conexas[i] = -1;
                    }
                }
            }
            if (c != -1)
            {
                cout << endl;
                arquivo_saida << endl;
            }
        }
    }else{
        while (c != -1)
        {
            c = -1;
            for (int i = 1; i <= n; i++)
            {
                if (c == -1)
                {
                    if (comp_fort_conexas[i] != -1)
                    {
                        c = comp_fort_conexas[i];
                        cout << i << " ";
                        comp_fort_conexas[i] = -1;
                    }
                }
                else
                {
                    if (comp_fort_conexas[i] == c)
                    {
                        cout << i << " ";
                        comp_fort_conexas[i] = -1;
                    }
                }
            }
            if (c != -1)
            {
                cout << endl;
            }
        }
    }

    
    
}
