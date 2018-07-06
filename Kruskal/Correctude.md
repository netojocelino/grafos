Seja G um grafo conectado e não-direcionado a entrada do algoritmo e T a saída da árvore geradora mínima.

Seja T' um subgrafo de G.
Seja T* uma árvore geradora mínima de G.
Seja F o conjunto de vértices conectatos sem ciclo.


## Prova que é uma árvore geradora

Assumindo T' uma floresta, ela não tem ciclos, por definição.

Seja F um conjunto vazio, então, uma aresta incidente em **v** deve ser considerava pelo algoritmo, pois não geraria ciclo algum e geraria uma conexão de G. Além que a primeira aresta deve ser inserida, por que não cria um ciclo, o que iria contra a definição de F.

Suponha que T' não seja conectada e existe dois ou mais componentes, os componentes devem ser conectados por alguma aresta em G, e não em T, o que geraria uma contradição de T'.


## Prova que é Árvore Geradora Mínima (AGM)

Sabendo que T* é uma AGM, se T' = T* então T' é uma AGM, caso contrário, existe uma aresta **e** em T* que possui um peso maior em T'. Desta forma, T' + **e** contém um ciclo C, que para cada aresta em C, o peso de **e** deve ser maior das demais. Seja **f** uma aresta de menor peso em C.

Considere T" = T' - {**e**} U {**f**}
T" é uma Árvore Geradora.
T" tem mais arestas em comum com T* que com T'.
O peso de todas as arestas de T" são menores.
Como T* é uma AGM, então as igualdades não são verdadeiras, e concluimos que T' é uma AGM.
