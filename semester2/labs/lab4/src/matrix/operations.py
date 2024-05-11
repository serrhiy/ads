
def mul_matrix(m1, m2):
  rows = len(m1)
  cols = len(m2[0])
  result = []
  for i in range(rows):
    row = []
    for j in range(cols):
      sum = 0
      for k in range(rows):
        sum += m1[i][k] * m2[k][j]
      row.append(sum)
    result.append(row)
  return result

def sum_col(matrix, i):
  result = 0
  for j in range(len(matrix)):
    result += matrix[j][i]
  return result

def sum_row(row):
  result = 0
  for n in row:
    result += n
  return result

def union(matrix1, matrix2):
  result = []
  length = len(matrix1)
  for i in range(length):
    row = []
    for j in range(length):
      row.append(matrix1[i][j] or matrix2[i][j])
    result.append(row)
  return result

def compose(matrix1, matrix2):
  result = []
  length = len(matrix1)
  for i in range(length):
    row = [0] * length
    for j in range(length):
      for k in range(length):
        if matrix1[i][k] and matrix2[k][j]:
          row[j] = 1
          break
    result.append(row)
  return result

def transitive_closure(matrix, n):
  result = matrix
  p_matrix = matrix
  for _ in range(n - 1):
    p_matrix = compose(p_matrix, matrix)
    result = union(result, p_matrix)
  return result

def transitive_reflexive_closure(matrix, n):
  length = len(matrix)
  identity = [[int(j == i) for j in range(length)] for i in range(length)]
  transitive = transitive_closure(matrix, n)
  return union(identity, transitive)

def strong_connectivity(reachability):
  result = []
  length = len(reachability)
  for i in range(length):
    row = []
    for j in range(length):
      row.append(reachability[i][j] and reachability[j][i])
    result.append(row)
  return result

def strong_connectivity_items(strong_matrix):
  result = []
  all_zeros = hash((0,) * len(strong_matrix))
  table = {}
  for i, row in enumerate(strong_matrix):
    h = hash(tuple(row))
    if h == all_zeros:
      result.append([i])
    index = table.get(h, -1)
    if index == -1:
      result.append([i])
      table[h] = i
    else:
      result[index].append(i)
  return result

def chained_strong_items(matrix, strong_items):
  result = []
  for i, first in enumerate(strong_items):
    for j, second in enumerate(strong_items):
      if i == j: continue
      flag = False
      for m in first:
        for n in second:
          if matrix[m][n]:
            result.append((i, j))
            flag = True
            break
        if flag: break
  return result

def condensation_matrix(matrix, strong_items):
  items = chained_strong_items(matrix, strong_items)
  length = len(strong_items)
  result = []
  for i in range(length):
    row = []
    for j in range(length):
      data = 1 if (i, j) in items else 0
      row.append(data)
    result.append(row)
  return result
