// Grafo e teoria usados: https://www.youtube.com/watch?v=dZpE_7Nr-Zk
// Usar o grafo do vídeo acima para tirar prova de funcionamento do algoritmo
// Esse algoritmo foi feito em IDE online. Portanto, para evitar problemas com dependências,
// teste-o em https://onlinegdb.com/Hyx8hCruQ

#include "vector" 
#include "iostream"
#include "algorithm"  
#include "climits"
#include "fstream"
#include "sstream"

using namespace std;

struct Aresta
{
	// Para armazenar fluxo atual e capacidade de aresta

	int fluxo, capacidade;

	// Uma aresta u--->v tem vértice de início como u e de fim como v
	int u, v;

	Aresta(int fluxo, int capacidade, int u, int v)
	{
		this->fluxo = fluxo;
		this->capacidade = capacidade;
		this->u = u;
		this->v = v;
	}
};

// Representa um Vertice
struct Vertice
{
	int h, e_fluxo;

	Vertice(int h, int e_fluxo) // h -> altura
	{
		this->h = h;
		this->e_fluxo = e_fluxo; // Fluxo de excesso
	}
};

// Representa um fluxo de rede
class Grafo
{
    
public:
    int V; // No. de vertices
	vector<Vertice> vertice;
	vector<Aresta> aresta;

	// Função para empurrar o fluxo de excesso de u
	bool push(int u); // manterei nome em inglês(nativo)

	// Função para remarcar um vértice
	void relabel(int u); // manterei nome em inglês(nativo)

	// Essa função é chamada para inicializar
	void preflow(int s);// preflow - manterei nome em inglês(nativo)

	// Função para reverter a aresta
	void atualizaFluxoReverso(int i, int fluxo);

	Grafo(int V); // Construtor

	// Função para adicionar aresta ao G
	void addAresta(int u, int v, int w);

	// Retorna fluxo máximo da origem ao destino(de s para t)
	vector<int> getFluxoMaximo(int s, int t);
};

Grafo::Grafo(int V)
{
	this->V = V;

	// Todos os vértices são inicializados com altura 0
	// e 0 de fluxo de excesso
	for (int i = 0; i < V; i++)
		vertice.push_back(Vertice(0, 0));
}

void Grafo::addAresta(int u, int v, int capacidade)
{
	// fluxo é inicializado com 0 para todas as arestas
	aresta.push_back(Aresta(0, capacidade, u, v));
}

void Grafo::preflow(int s)
{
	// Fazendo do h(altura) do vértice de origem o número de vértices do grafos
	// Altura dos outros vértices é igual a 0 
	vertice[s].h = vertice.size();

	for (int i = 0; i < aresta.size(); i++)
	{
		// Se aresta atual vai da fonte
		if (aresta[i].u == s)
		{
			// Fluxo é igual à capacidade
			aresta[i].fluxo = aresta[i].capacidade;

			// Inicialize o fluxo de excesso para o adjacente de v

			vertice[aresta[i].v].e_fluxo += aresta[i].fluxo;

			// Adicionar um aresta de v para s em grafo residual com capacidade igual a 0
			aresta.push_back(Aresta(-aresta[i].fluxo, 0, aresta[i].v, s));
		}
	}
}

// retorna índice de transbordamento de Vertice
int overFlowVertice(vector<Vertice>& vertice)
{
	for (int i = 1; i < vertice.size() - 1; i++)
	if (vertice[i].e_fluxo > 0)
			return i;

	// -1 se não transbordar Vertice
	return -1;
}

// Atualize fluxo reverso para fluxo adicionado
void Grafo::atualizaFluxoReverso(int i, int fluxo)
{
	int u = aresta[i].v, v = aresta[i].u;

	for (int j = 0; j < aresta.size(); j++)
	{
		if (aresta[j].v == v && aresta[j].u == u)
		{
			aresta[j].fluxo -= fluxo;
			return;
		}
	}

	// adicionando aresta reversa em grafo residual
	Aresta e = Aresta(0, fluxo, u, v);
	aresta.push_back(e);
}

// To push fluxo from overflowing vertice u
bool Grafo::push(int u)
{
	// Atravessar todas as arestas para encontrar um adjacente (de u)
	// para o qual o fluxo pode ser empurrado
	for (int i = 0; i < aresta.size(); i++)
	{
		// Cheque se o u da aresta atual é o mesmo dado do vértice transbordante
		if (aresta[i].u == u)
		{
			// Se fluxo é igual à capacidade então não é possível empurrar
			if (aresta[i].fluxo == aresta[i].capacidade)
				continue;

			// Empurrar só é possível se a altura do adjacente for menor que a altura do vértice transbordante
			if (vertice[u].h > vertice[aresta[i].v].h)
			{
				// Fluxo a ser empurrado é igual ao mínimo(função) de fluxo restante em aresta e excesso de fluxo.
				int fluxo = min(aresta[i].capacidade - aresta[i].fluxo,
							vertice[u].e_fluxo);

				// Reduzir o excesso de fluxo para vértice transbordante
				vertice[u].e_fluxo -= fluxo;

				// Aumentar o fluxo de excesso para adjacente
				vertice[aresta[i].v].e_fluxo += fluxo;

				// Adicione fluxo residual (com capacidade 0 e fluxo negativo)
				aresta[i].fluxo += fluxo;

				atualizaFluxoReverso(i, fluxo);

				return true;
			}
		}
	}
	return false;
}

// function para remarcar vértice u - Relabel
void Grafo::relabel(int u)
{
	// Inicialize a altura mínima de um adjacente
	int mh = INT_MAX;
	
	// Encontre o adjacente com altura mínima
	for (int i = 0; i < aresta.size(); i++)
	{
		if (aresta[i].u == u)
		{
			// se o fluxo é igual a capacidade, então não há remarcação
			if (aresta[i].fluxo == aresta[i].capacidade)
				continue;

			// Atualizar altura mínima
			if (vertice[aresta[i].v].h < mh)
			{
				mh = vertice[aresta[i].v].h;

				// Atualizando altura de u
				vertice[u].h = mh + 1;
			}
		}
	}
}

// Essa é a função que calcula o fluxo máximo e retorna uma lista de valores de fluxo para cada aresta, como pedido na questão
vector<int> Grafo::getFluxoMaximo(int s, int t)
{
    preflow(s);
    vector<int> result;
 
    // loop até que nenhum dos vértices estejam em overflow
    while (overFlowVertice(vertice) != -1)
    {
        int u = overFlowVertice(vertice);
        if (!push(u))
            relabel(u);
    }
 
    for (int i = 0; i <= vertice.size(); i++)
	{
        result.resize(i);
	}
	
	cout << "Esses são os valores de fluxo de cada uma das arestas do grafo, seguindo ordem dos dados dado no arquivo 'grafo.txt': \n";
	
    for (int i = 0; i <= vertice.size(); i++)
	{
		cout << aresta[i].fluxo <<  "\n";
	    result[i] = aresta[i].fluxo;
	}
	

       
	cout << "O fluxo máximo é " << vertice.back().e_fluxo <<  "\n";
	
	return  result;
}

// função auxíliar para separar string e colocá-la em vetor
vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

// Função principal para teste do programa
int main()
{
    int V = 6;
	Grafo g(V);

	// Inicialize source(origem) e sink(destino)
	int s = 0, t = 5;
    
    vector<string> vetor;
    vector<int> vetorResultado;
    
    string line;
    ifstream myfile ("grafo.txt"); // ifstream = padrão ios:in
      
    if (myfile.is_open())
      {
        while (! myfile.eof() ) //enquanto end of file for false continua
        {
          getline (myfile,line); // como foi aberto em modo texto(padrão)
                                 //e não binário(ios::bin) pega cada linha
          vetor = split(line, " ");
          
          g.addAresta(stoi(vetor[0]), stoi(vetor[1]), stoi(vetor[2]));
          
          //cout << line << endl; //imprimir arquivo em console
        }
        myfile.close();
      }
    
    else cout << "Não foi possível abrir arquivo"; 
	
	// Vetor para pegar resultado da função que retorna lista(nesse caso foi usado vetor) de fluxo de cada aresta ao final da operação de para encontrar fluxo máximo 
    vetorResultado = g.getFluxoMaximo(s, t);
    
	// Teste de impressão e de resultado
    for (int i = 0; i <= vetorResultado.size(); i++)
	{
		cout << "Valor de posição "<< i << " da lista de fluxo de cada aresta  : "<< vetorResultado[i]<<  "\n";
	    
	}
	
	
	return 0;
}