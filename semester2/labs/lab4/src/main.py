import os
from utils import create_window, zip_vertices
from matrix.print import print_matrix, draw_graph, write_routes
from config import WIDTH, HEIGHT, VERTICES_COUNT, SIDES, n3, n4
from matrix.operations import (
  mul_matrix, transitive_reflexive_closure, strong_connectivity, 
  strong_connectivity_items, condensation_matrix
)
from matrix.graph import(
  adjacency_matrix, to_indirected, vertex_degrees_out, vertex_degrees_in, routes,
  vertex_degrees, isolated_vertices, hanging_vertices, is_regular
)

def task1(canvas1, canvas2):
  k = 1.0 - n3 * 0.01 - n4 * 0.01 - 0.3
  directed = adjacency_matrix(VERTICES_COUNT, k)
  print_matrix(directed)
  indirected = to_indirected(directed)
  directed_degrees = vertex_degrees(directed, True)
  indirected_degrees = vertex_degrees(indirected, False)
  out = vertex_degrees_out(directed)
  incoming = vertex_degrees_in(directed)
  isolated = isolated_vertices(directed_degrees)
  hanging = hanging_vertices(directed_degrees)
  print('Degree of a vertex in a directed graph:')
  print(*zip_vertices(directed_degrees))
  print('Degree of a vertex in a indirected graph:')
  print(*zip_vertices(indirected_degrees))
  print('Half-degree of the output of the directed graph:')
  print(*zip_vertices(out))
  print('Half-degree of the input of the directed graph:')
  print(*zip_vertices(incoming))
  if is_regular(directed):
    print('Graph is regular and its degree is', directed_degrees[0])
  else:
    print('Graph isn\'t regular')
  if len(hanging):
    print('Hanging vertices are:')
    print(*zip_vertices(hanging))
  else:
    print('Graph doesn\'t have hanging vertices')
  if len(isolated):
    print('The isolated vertices are:', *isolated)
    print(*zip_vertices(isolated))
  else:
    print('Graph doesn\'t have isolated vertices')
  draw_graph(canvas1, directed, SIDES, True)
  draw_graph(canvas2, indirected, SIDES, False)

def task2(canvas1, canvas2):
  k = 1.0 - n3 * 0.005 - n4 * 0.005 - 0.27
  directed = adjacency_matrix(VERTICES_COUNT, k)
  out = vertex_degrees_out(directed)
  incoming = vertex_degrees_in(directed)
  print('Half-degree of the output of the directed graph:')
  print(*zip_vertices(out))
  print('Half-degree of the input of the directed graph:')
  print(*zip_vertices(incoming))
  directed2 = mul_matrix(directed, directed)
  directed3 = mul_matrix(directed2, directed)
  paths2 = routes(directed, directed2, 2)
  paths3 = routes(directed, directed3, 3)
  write_routes('ruotes2.csv', paths2)
  write_routes('ruotes3.csv', paths3)
  reachability_matrix = transitive_reflexive_closure(directed, VERTICES_COUNT - 1)
  print('reachability matrix:')
  print_matrix(reachability_matrix)
  strong_connectivity_matrix = strong_connectivity(reachability_matrix)
  print('strong connectivity matrix:')
  print_matrix(strong_connectivity_matrix)
  print('strong connectivity items:')
  strong_items = strong_connectivity_items(strong_connectivity_matrix)
  print(*strong_items, sep=', ')
  condensation = condensation_matrix(directed, strong_items)
  draw_graph(canvas1, directed, SIDES, True)
  draw_graph(canvas2, condensation, SIDES, True)

if __name__ == '__main__':
  root1, canvas1 = create_window('Task 1 Directed', WIDTH, HEIGHT)
  root2, canvas2 = create_window('Task 1 Indirected', WIDTH, HEIGHT)
  root3, canvas3 = create_window('Task 2 Directed', WIDTH, HEIGHT)
  root4, canvas4 = create_window('Task 2 Condensation', WIDTH, HEIGHT)
  task1(canvas1, canvas2)
  print('─' * os.get_terminal_size().columns)
  task2(canvas3, canvas4)
  root1.mainloop()
  root2.mainloop()
  root3.mainloop()
  root4.mainloop()