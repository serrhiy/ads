#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "utils.hpp"
#include "vertex.hpp"
#include "matrix.hpp"
#include "draw.hpp"
#include <iostream>

using matrix::matrix_t;

void drawGraph(sf::RenderWindow& window, const matrix_t& matrix) {
  utils::clearWindow(window, config::BACKGROUND_COLOR);
  draw::drawGraph(window, matrix, config::SIDES, config::WIDTH);
  window.display();
}

int main(int argc, const char* argv[]) {
  sf::RenderWindow window;
  utils::manageWindow(window, config::WIDTH, config::HEIGHT, config::TITLE);
  utils::clearWindow(window, config::BACKGROUND_COLOR);

  auto directed{ matrix::adjacencyMatrix(11, config::SEED, config::k) };
  std::cout << directed << std::endl;
  drawGraph(window, directed);

  utils::pollEvents(window);
  return 0;
}