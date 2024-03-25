from config import canvas_options
import tkinter as tk
import math
import random

float_random = lambda min, max: random.random() * (max - min) + min

minmax = lambda x, y: (min(x, y), max(x, y))

partial = lambda fn, *a, **kw: lambda *p, **k: fn(*a, *p, **kw, **k)

is_neighbors = lambda length, x, y: x == y - 1 or y == length - 1 and x == 0

def in_one_line(length, ranges, x, y):
  split = math.ceil(length / ranges)
  last_range = length % split
  if last_range == 0:
    last_range = split
  last = length - last_range
  if x == 0 and y >= last and y < length:
    return True
  start = x - x % split
  end = start + split
  return y >= start and y <= end

def create_window(title, width, height):
  root = tk.Tk()
  root.geometry('%dx%d' % (width, height))
  root.title(title)
  canvas = tk.Canvas(root, canvas_options)
  canvas.pack(fill=tk.BOTH, expand=1)
  return (root, canvas)

def index_filter(arr, fn):
  result = []
  for i, item in enumerate(arr):
    if fn(item):
      result.append(i)
  return result

calculate_step = lambda width, count, sides: (
  width / (math.ceil(count / sides) + 1)
)

zip_vertices = lambda data: ((f'v{i}', n) for i, n in enumerate(data))