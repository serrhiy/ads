n1, n2, n3, n4 = 3, 1, 1, 2
k = 1 - n3 * 0.02 - n4 * 0.005 - 0.25

VERTICES_COUNT = 10 + n3
WIDTH = 1000
HEIGHT = 800
LINE_WIDTH = 3
LINE_COLOR = 'white'
ARROWS_LENGTH = 15
VERTEX_RADIUS = 50
STEP = VERTEX_RADIUS * 3.5
TITLE = 'Lytvynenko Serhiy, IM-31'

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