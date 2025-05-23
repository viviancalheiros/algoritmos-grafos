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

bool ord_menor(aresta_peso& a, aresta_peso& b) {
    return a.peso < b.peso;
}

void mad_set(vector<vertice>& vet_vertice)
{
    for(int i = 1; i < vet_vertice.size(); i++)
    {
        vet_vertice[i].pai = i;
        vet_vertice[i].rank = 1;
    }
}

int find(int v, vector<vertice>& vet_vertice)
{
    if (vet_vertice[v].pai != v ){
        vet_vertice[v].pai = find(vet_vertice[v].pai, vet_vertice);
    }
    return vet_vertice[v].pai;
}

void uniao(int v, int w, vector<vertice>& vet_vertice)
{
    if (vet_vertice[v].rank >= vet_vertice[w].rank)
    {
        vet_vertice[w].pai = v;
        if (vet_vertice[v].rank == vet_vertice[w].rank)
        {
            vet_vertice[v].rank +=1;
        }
    }
    else
    {
        vet_vertice[v].pai = w;
    }
}

void help()
{
    cout << "-h: mostra o help" << endl << endl;
    cout << "Para ler o arquivo de entrada:\n./<executavel> -f <arquivo de entrada> -i <vertice inicial>" << endl << endl;
    cout << "Para ler o arquivo e exibir as arestas:\n./<executavel> -f <arquivo de entrada> -i <vertice inicial> -s" << endl << endl;
    cout << "Para salvar o arquivo de saida:\n<comandos anteriores> -o <arquivo de saida>" << endl << endl;
}

int main(int argc, char *argv[]) {
    string arq_entrada;
    string arq_saida;
    int i_argv = 1;
    int cont_print_saida = 0;
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
        else if (!strcmp(argv[i_argv], "-s"))
        {
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

    int v, w, p;
    for(int i = 0; i < m; i++) {
        arquivo_entrada >> v >> w >> p;
        arquivo_entrada.ignore(numeric_limits<streamsize>::max(), '\n');
        arestas[i].v = v;
        arestas[i].w = w;
        arestas[i].peso = p;
    }

    // Ordena as arestas por peso crescente
    sort(arestas.begin(), arestas.end(), ord_menor);
    vector<aresta_peso> res(n-1);
    vector<vertice> vet_vertice(n+1); 

    mad_set(vet_vertice);

    int controle = 0;
    int atual = 0;
    while (controle < (n-1))
    {
        if (find(arestas[atual].v, vet_vertice) != find(arestas[atual].w, vet_vertice))
        {
            res[controle].v = arestas[atual].v;
            res[controle].w = arestas[atual].w;
            res[controle].peso = arestas[atual].peso;
            controle+=1;
            uniao(find(arestas[atual].v, vet_vertice), find(arestas[atual].w, vet_vertice), vet_vertice);
        }
        atual+=1;
    }

    int total = 0;
    if (cont_arq_saida == 1)
    {
        ofstream arquivo_saida(arq_saida);
        if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
        }
        for (int i=0; i < res.size(); i++)
        {
            if (res[i].v < res[i].w) 
                arquivo_saida << "(" << res[i].v << "," << res[i].w << ")" << " ";
            else 
                arquivo_saida << "(" << res[i].w << "," << res[i].v << ")" << " ";
        }
        cout << endl;
    }
    
    if (cont_print_saida == 1)
    {
        for (int i=0; i < res.size(); i++)
        {
            if (res[i].v < res[i].w)
                cout << "(" << res[i].v << "," << res[i].w << ")" << " ";
            else 
                cout << "(" << res[i].w << "," << res[i].v << ")" << " ";
        }
        cout << endl;
    }

    for (int i=0; i < res.size(); i++)
    {
        total += res[i].peso;
    }

    if (!cont_arq_saida && !cont_print_saida) {
        cout << total << endl;
    }
    //cout << endl << endl;

    return 0;


}