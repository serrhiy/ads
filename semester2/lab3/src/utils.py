from config import STEP, VERTEX_RADIUS
from config import canvas_options
from vertex import Vertex
import tkinter as tk
import math

cases = (
  lambda x, y, s: (x + s, y),  # right
  lambda x, y, s: (x, y + s),  # down
  lambda x, y, s: (x - s, y),  # left
  lambda x, y, s: (x, y - s),  # up
)

def split_int(x, ranges):
  high = math.ceil(x / ranges)
  sum = high
  result = []
  while sum <= x:
    result.append(high)
    sum += high
  if sum - high < x:
    result.append(x - sum + high)
  return result

def create_vertices(ranges):
  posx, posy = STEP + VERTEX_RADIUS, STEP
  vertex_index = 0
  vertices = []
  for i in range(len(ranges)):
    cnt = ranges[i]
    next_position = cases[i % len(cases)]
    for _ in range(cnt):
      vertex = Vertex(posx, posy, vertex_index)
      vertices.append(vertex)
      posx, posy = next_position(posx, posy, STEP)
      vertex_index += 1
  return vertices

minmax = lambda x, y: (min(x, y), max(x, y))

partial = lambda fn, *args: lambda *pars: fn(*args, *pars)

is_neighbors = lambda length, x, y: x == y - 1 or y == length - 1 and x == 0

def in_one_line(length, ranges, x, y):
  last = length - ranges[-1]
  if x == 0 and y >= last and y < length:
    return True
  start = x - x % ranges[0]
  end = start + ranges[0]
  return y >= start and y <= end

def create_window(title, width, height):
  root = tk.Tk()
  root.geometry('%dx%d' % (width, height))
  root.title(title)
  canvas = tk.Canvas(root, canvas_options)
  canvas.pack(fill=tk.BOTH, expand=1)
  return (root, canvas)
