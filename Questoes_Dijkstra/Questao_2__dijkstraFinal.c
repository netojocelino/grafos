#include <stdio.h>
#include <stdlib.h>

int INFINITY = 999999999;//Usado em tabelaCaminhos
int vertices_nao_visitados;//guarda numero de vertices nao visitados pelo algoritmo
int k = 0;

 //Inicia os campos da matriz com 'infinito'
 void inicializarTabelaCaminhos(int l, int c, int matriz[l][c], int origem){
    int i = 0;
   while(i < l){
      if(i == origem) {
         matriz[origem][0] = 0;
         matriz[origem][1] = -1;
        }
      else
      matriz[i][0] = INFINITY;
      i++;
   }
 }


 //Se Vi esta na lista, retorna 1, senao, 0.
 short v_jaVisitado(int i, int lista[]){
    if(lista[i] == -1) return 0;
    return 1;
 }

 //add v aa posicao correspondente ao seu numero
 void add_Vert_ListaVisitados(int v, int lista[]){
     lista[v] = v;
     vertices_nao_visitados--;
 }

 void inicializarListaVerticeVisitado(int N, int lista[]){
     int i = 0;
    while(i < N){
        lista[i] = -1;
        i++;
    }
 }

 //retorna o vertice (ainda nao visitado pelo algoritmo) de menor custo.
 int obterProxVertice(int N, int tabelaCaminhos[N][2], int lista_Visitados[N]){
      int i = 0, vert_menor = -1, menor = INFINITY;
      while(i < N){
         if(tabelaCaminhos[i][0] < menor && !v_jaVisitado(i, lista_Visitados)){
                vert_menor = i;
                menor = tabelaCaminhos[i][0];
           }
           i++;
       }
   return vert_menor;
 }


 //Preenche "tabelaCaminhos" com o resultado da aplicacao do algoritmo de Dijkstra
 void dijkstra(int N, int grafo[N][N], int origem, int tabelaCaminhos[N][2], int lista_Visitados[]){
     int v_atual = origem, i, d1, d2;
     while(vertices_nao_visitados > 0){
       i = 0;
       while(i < N){//vizinhos
          if(grafo[v_atual][i] != 0 && !v_jaVisitado(i, lista_Visitados)){//
            d1 = tabelaCaminhos[v_atual][0] + grafo[v_atual][i];//calcula distancia entre origem e vizinho de v_atual, i
            d2 = tabelaCaminhos[i][0];//Consulta caminho mais curto atual de i
            if(d1 < d2){//atualiza tabela
                tabelaCaminhos[i][0] = d1; //altera menor caminho
                tabelaCaminhos[i][1] = v_atual; //altera vertice anterior de menor caminho
            }

          }//
          i++;
       }
       add_Vert_ListaVisitados(v_atual, lista_Visitados);  //add v_atual a lista de vertices visitados
       v_atual = obterProxVertice(N, tabelaCaminhos, lista_Visitados); //obtem o proximo vertice a ser visitado
     }
     vertices_nao_visitados = N;
 }


 void inicializarTabelaVerticesVisitados(int N, int matriz[N]){
     int i = 0;
     while(i < N){
        matriz[i] = -1;
        i++;
     }
 }

 void instrucoes(){
    printf("\t\t**INSTRUCOES DE USO**\n");
    printf("1. A numeracao dos vertices comeca do 0\n");
    printf("2. Lacos nao sao permitidos. Portanto, onde houver aresta x - x, y - y, colocar 0. Ex. 0 - 0 = 0; 1 - 1 = 0\n");
    printf("3. O programa ADMITE grafos orientados.\n");
    printf("4. Caso o grafo NAO seja orientado, onde houver aresta x - x, y - y, repetir o valor. Ex. 0 - 1 = 8; 1 - 0 = 8\n");
    printf("\n\nVamos comecar!\n\n");
 }


int main()
{
    instrucoes();

    int N;
    printf("Numero de vertices: ");
    scanf ("%d", &N);
    printf("Numero do Vertice de partida: ");
    int origem;
    scanf("%d", &origem);

    vertices_nao_visitados = N;//global

    int grafo [N][N];
    int tabelaVerticesVisitados[N];//guarda os vertices visitados pelo algoritmo
    inicializarTabelaVerticesVisitados(N, tabelaVerticesVisitados);//configura os valores iniciais da tabela


    printf("\n Vamos preencher a matriz de adjacencia! \n\n");
    //Preenchendo grafo
    int i = 0, p;
    while(i < N){
        printf("Vertice %d\n", i);
        int j = 0;
        while(j < N){
            printf("Peso aresta %d - %d: ", i, j);
            scanf("%d", &p);
            grafo[i][j] = p;
            j++;
            printf("\n");
        }
        i++;
    }

    int tabelaCaminhos[N][2];//Guarda o resultado da execucao do alg. Dijkstra
    inicializarTabelaCaminhos(N, 2, tabelaCaminhos, origem);

    int lista_Vert_Visitados[N]; //lista para guardar os vertices ja visitados pelo algoritmo
    inicializarListaVerticeVisitado(N, lista_Vert_Visitados);

    dijkstra(N,grafo, origem, tabelaCaminhos, lista_Vert_Visitados);

    //Exibe resultado da aplicacao do algoritmo
    printf("Vertice \t |Menor distancia a partir de %d        | Vertice anterior\n", origem);
    i = 0;
    while(i < N) {
       printf("%d \t\t\t%d  \t\t\t\t\t%d\n",i,tabelaCaminhos[i][0], tabelaCaminhos[i][1]);
       i++;
    }
    i = 0;
    printf("\n\nVisitados\n");
    while(i < N) printf("%d\n", lista_Vert_Visitados[i++]);
    return 0;
}
