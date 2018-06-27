#A = matriz de adjacência, u = vértice u, v = vértice v
def peso(A, u, v):
    return A[u][v]

#A = matriz de adjacência, u = vértice u
def adjacente(A, u):
    L = []
    for x in range(len(A)):
        if A[u][x] > 0 and x != u:
            L.insert(0,x)
    return L

#Q = fila mínima(mínimos) 
def extrairMin(Q):
    q = Q[0]
    Q.remove(Q[0])
    return q

#Q = fila mínima(mínimos), V = lista de vértices
def diminuirChave(Q, K):
    for i in range(len(Q)):
        for j in range(len(Q)):
            if K[Q[i]] < K[Q[j]]:
                s = Q[i]
                Q[i] = Q[j]
                Q[j] = s

#V = lista de vértices, A = lista de adjacência, r = raiz
def prim(V, A, r):
    u = 0
    v = 0

    # inicializar e definir cada valor da matriz P (pi) para nenhum
    # pi contém o pai de u, então P (v) = u significa que u é o pai de v
    P=[None]*len(V)

    # inicializar e definir cada valor da matriz K (chave) para algum número grande (simular infinito)
    K = [999999]*len(V)

    # inicialize a fila mínima e preencha com todos os vértices em V
    Q=[0]*len(V)
    for u in range(len(Q)):
        Q[u] = V[u]

    # defina a chave da raiz para 0
    K[r] = 0
    diminuirChave(Q, K)    # manter a fila mínima(mínimos)

    # loop enquanto a fila mínima não está vazia
    while len(Q) > 0:
        u = extrairMin(Q)    # extrair primeiro vértice da lista mínima

        # loop através dos vértices adjacentes a u
        Adj = adjacente(A, u)
        for v in Adj:
            w = peso(A, u, v)    # obter o peso da aresta uv

            # prossiga se v estiver em Q e o peso de uv for menor que a chave de v
            if Q.count(v)>0 and w < K[v]:
                # set pai de v para u
                P[v] = u
                # v é a chave para o peso de uv
                K[v] = w
                diminuirChave(Q, K)    # manter a fila mínima(mínimos)
    return P

A = [ [0,  4,  0,  0,  0,  0,   0,  8,  0],
      [4,  0,  8,  0,  0,  0,   0, 11,  0],
      [0,  8,  0,  7,  0,  4,   0,  0,  2],
      [0,  0,  7,  0,  9, 14,   0,  0,  0],
      [0,  0,  0,  9,  0, 10,   0,  0,  0],
      [0,  0,  4, 14, 10,  0,   2,  0,  0],
      [0,  0,  0,  0,  0,  2,   0,  1,  6],
      [8, 11,  0,  0,  0,  0,   1,  0,  7],
      [0,  0,  2,  0,  0,  0,   6,  7,  0]]
V = [ 0, 1, 2, 3, 4, 5, 6, 7, 8 ]

P = prim(V, A, 0)

print (P)

[None, 0, 5, 2, 3, 6, 7, 0, 2]
