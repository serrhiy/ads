from math import cos, sin, atan2, sqrt, pi
from dataclasses import dataclass
from config import (
  line_options, 
  text_options,
  oval_options,
  ARROWS_LENGTH,
  VERTEX_RADIUS,
)

@dataclass
class Vertex:
  x: int
  y: int
  text: str | int

rotate = lambda x, y, l, f: (
  x + l * cos(f),
  y + l * sin(f),
)

def vertex_arrows(canvas, x, y, fi, delta):
  lx, ly = rotate(x, y, ARROWS_LENGTH, fi + delta)
  rx, ry = rotate(x, y, ARROWS_LENGTH, fi - delta)
  canvas.create_line(lx, ly, x, y, line_options, width=2)
  canvas.create_line(x, y, rx, ry, line_options, width=2)

def vertex_draw(canvas, vertex):
  x, y = vertex.x, vertex.y
  x1, y1 = x + VERTEX_RADIUS, y + VERTEX_RADIUS 
  x2, y2 = x - VERTEX_RADIUS, y - VERTEX_RADIUS
  canvas.create_oval(x1, y1, x2, y2, oval_options)
  canvas.create_text(x, y, text=vertex.text, **text_options)

def vertex_line(canvas, v1, v2, arrows=False):
  x1, y1 = v1.x, v1.y
  x2, y2 = v2.x, v2.y
  fi = atan2(y2 - y1, x2 - x1)
  x3, y3 = rotate(x1, y1, VERTEX_RADIUS, fi)
  x4, y4 = rotate(x2, y2, VERTEX_RADIUS, fi + pi)
  canvas.create_line(x3, y3, x4, y4, line_options)
  if arrows:
    vertex_arrows(canvas, x4, y4, fi + pi, pi / 8)

def vertex_arc(canvas, v1, v2, arrows=False):
  fi = atan2(v2.y - v1.y, v2.x - v1.x)
  x3, y3 = rotate(v1.x, v1.y, VERTEX_RADIUS, fi) # - pi / 2
  x4, y4 = rotate(v2.x, v2.y, VERTEX_RADIUS, fi + pi) # + pi / 2
  meadle = sqrt((x4 - x3)**2 + (y4 - y3)**2) / 2
  length = sqrt((3 * VERTEX_RADIUS)**2 + meadle**2)
  f = -atan2(3 * VERTEX_RADIUS, meadle)
  x5, y5 = rotate(x3, y3, length, f + fi)
  canvas.create_line(x3, y3, x5, y5, x4, y4, line_options, smooth=1)
  if arrows:
    vertex_arrows(canvas, x4, y4, fi + pi - f, pi / 8)

def vertex_loop(canvas, vertex, arrows=False):
  x = vertex.x
  y = vertex.y - VERTEX_RADIUS
  x1, y1 = rotate(x, y, VERTEX_RADIUS, -pi / 4)
  x2, y2 = rotate(x, y, VERTEX_RADIUS, -3 * pi / 4)
  canvas.create_line(x, y, x1, y1, x2, y2, x, y, line_options)
  if arrows:
    vertex_arrows(canvas, x, y, pi / 4 + pi, pi / 8)