def bellman_ford(grafo, origem):
    #  1: prepare a distânca e o predecessor para cada nó.
    distancia, predecessor = dict(), dict()
    for no in grafo:
        distancia[no], predecessor[no] = float('inf'), None
    distancia[origem] = 0

    # 2: Relaxe as arestas
    for _ in range(len(grafo) - 1):
        for no in grafo:
            for vizinho in grafo[no]:
                # Se a distância entre o nó e o vizinho for menor que a atual, guarde-a
                if distancia[vizinho] > distancia[no] + grafo[no][vizinho]:
                    distancia[vizinho], predecessor[vizinho] = distancia[no] + grafo[no][vizinho], no

    # 3: Verifique se há ciclos de peso negativo
    for no in grafo:
        for vizinho in grafo[no]:
            assert distancia[vizinho] <= distancia[no] + grafo[no][vizinho], "Negative weight cycle."
 
    return distancia, predecessor
    
if __name__ == '__main__':
    grafo = {
        'a': {'b': -1, 'c':  4},
        'b': {'c':  3, 'd':  2, 'e':  2},
        'c': {},
        'd': {'b':  1, 'c':  5},
        'e': {'d': -3}
    }

    distancia, predecessor = bellman_ford(grafo, origem='a')

    print (distancia)
    
    grafo = {
        'a': {'c': 3},
        'b': {'a': 2},
        'c': {'b': 7, 'd': 1},
        'd': {'a': 6},
    }
 
    distancia, predecessor = bellman_ford(grafo, origem='a')

print (distancia)
