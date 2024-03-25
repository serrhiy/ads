
n1, n2, n3, n4 = 3, 1, 1, 2

seed = n1 * 1000 + n2 * 100 + n3 * 10 + n4

VERTICES_COUNT = 10 + n3
WIDTH = 800
HEIGHT = 800
LINE_WIDTH = 3
LINE_COLOR = 'white'
ARROWS_LENGTH = 15
VERTEX_RADIUS = 50
SIDES = 4

canvas_options = {
  'bg': 'black',
  'borderwidth': 0,
  'highlightthickness': 0,
}

line_options = {
  'fill': LINE_COLOR,
  'width': LINE_WIDTH,
}

text_options = {
  'fill': LINE_COLOR,
  'font': 14,
}

oval_options = {
  'outline': LINE_COLOR,
  'width': LINE_WIDTH,
}