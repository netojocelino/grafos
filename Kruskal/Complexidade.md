
## Complexidade

``edges = list( self.graph['edges'] )`` O(Arestas)

``for v in self.graph['vertices']: self.gen_set(v)`` O(Vertices)

``for e in edges:`` O(Arestas)
``   weight, u, v = e``
``   if not(self.search(u) == self.search(v)):`` O( 2 * Arestas )
``    self.join(u, v)`` O( 2*Arestas ) + O(1)
``    mst.add(e)`` O(Arestas+Vertices)


Complexidade final: O(Arestas + Vertices)
