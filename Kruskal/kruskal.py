#-*- coding: utf-8 -*-
#python 3.6


class Graph:
 """
  Classe que recebe um grafo e faza busca mst Krukal
 """
 def __init__(self, g):
  # var que guarda todos os vertices pais
  self._parent = dict()
  # var que guarda o grau de um dado vertice
  self._neight = dict()
  # var que guarda o grafo
  self.graph = g #dict()
 
 # metodo que cria um novo grafo, sobrescrevendoo antigo
 def reset(self, g):
  self.__init__(g)
 # Função que monta o conjunto de informações
 def gen_set(self, v):
  # var que salva o pai de um dado vertice
  self._parent[v] = v
  # var que guarda o grau de um vertice
  self._neight[v] = 0
  
 # busca o pai de um dado vertice de forma recursiva
 def search(self, v):
  if (self._parent[v] == v):
   return self._parent[v]
  else:
   return self.search( self._parent[v] )
  
 # une dois vertices, quando não estão conectados
 def join(self, u, v):
  uroot = self.search(u)
  vroot = self.search(v)
  # verifica e os vertices estão conectados por um pai em comum
  if vroot != uroot:
   # verifica qual o meno custoso de alterar e seta quem estará conectado
   if self._neight[uroot] > self._neight[vroot]:
    self._parent[vroot] = uroot
   else:
    self._parent[uroot] = vroot
   # verifica se foi alterado o grau de um elemento
   if self._neight[uroot] == self._neight[vroot]:
    self._neight[vroot] += 1
  
 # metodo para gerar a arvore minima do grafo inicializado
 def kruskal(self):
  # var que guarda a arvore minima
  mst = set()
  # lista de arestass do grafo
  edges = list( self.graph['edges'] )
  # ordenar as arestas do menor para o maior
  edges.sort()
  
  # gera um conjunto de vertices
  for v in self.graph['vertices']:
   self.gen_set(v)
   
  # para cada aresta, junta elas quando é o caso
  for e in edges:
   weight, u, v = e
   if not(self.search(u) == self.search(v)):
    self.join(u, v)
    mst.add(e)
  # retorna a arvore geradora mínima
  # uma tupla-3 contendo o peso dela e os nós conectados
  print("Arvore geradora mínima ")
  return sorted(mst)
  








# Função auxilar que trata uma entrada gerando um array
def read_(entry = "1  2  3  4   "):
  entry = entry.split(" ")
  out = []
  for x in entry:
   if x != "":
    out.append(x)
  return out


# Recebe o array de vertices com pesos e cria a matrix 
# entrada padrão = [ "peso vertice1 vertive2" , ... ]
def _edge(vertices = ["1 1 2","2 1 3","3 1 4","4 3 4"]):
 mtx = []
 for y in vertices:
  weight, orig, dest = read_(y)
  mtx.append( (int(weight), orig, dest) )
 edges = []
 for v1 in vertices:
  for v2 in vertices:
   if v1 != v2 and not((v2,v1) in edges):
    edges.append( (v1, v2) )
 return mtx

# gerar um array de tamanho IxJ preenchido com 0
def gen_arr(i,j=None):
 j = i if (j is None) else j
 arr = []
 for x in range(i):
  ar = []
  for y in range(j):
   ar.append(0)
  arr.append(ar)
 return arr

# função para usuario qualquer testar com input
def user(): 
 # ler todos os nome de vertices
 v = read_(input("vertices (eg: \"A B C D\"): "))
 # cria um array de tamanho VxV sendo V a quantidade de vertices
 arr = gen_arr( len( v) )
 # ler todas as arestas
 e = _edge(input("edge %d (eg: \"peso vertice1 vertice 2\") <ENTER>: "%(i)) for i in range(len(v)))
 # cria o grafo
 gr = Graph({"vertices": v,"edges": set(e)})
 print("\n")
 # retorna a tripla de vrtices com o peso
 print(gr.kruskal())


# função para testar por paramento
def param(vertices = "A B C D" , edges = ["1 A B","2 A C","3 A D","4 C D"] ):
 # ler todos os nome de vertices
 v = read_(vertices)
 # cria um array de tamanho VxV sendo V a quantidade de vertices
 arr = gen_arr( len( v ) )
 # ler todas as arestas
 e = _edge(edges)
 # criar o grafo
 gr = Graph({"vertices": v,"edges": set(e)})
 print("\n")
 # imprimir tuplas-3 de vertices da arvore
 print(gr.kruskal())	

if __name__ == '__main__':
 # usar user()
 # "vertices: " exemplo: "A B C"
 # "edge: " exemplo: "1 a b" <enter> "3 a c" <enter> "2 b c"
 user()
 # usar param(string vertices, string[] weight_vertices)
 # vertices: string contendo todos os vertices separados por virgula (eg: "A B C D")
 # weight_vertices: array dee string contendo o peso da aresta e os vertices incidentes
 # ex: seja A (Aracaju) D (N S Dores) R (Ribeiropolis) I (Itabaiana) G (N S Gloria)
 #param("A D R I G", ["73 A D", "57 A I", "34 D R", "22 R I", "45 D G", "40 G R", "60 G I"])
