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

  const matrix_t matrix{
    { 2, 1, 5, 0 },
    { 2, 0, 0, 0 },
    { 0, 1, 0, 6 },
    { 0, 0, 5, 6 },
  };

  drawGraph(window, matrix);
  window.display();
  // const vertex::Vertex v1{ 200, 200, 1 };
  // const vertex::Vertex v2{ 400, 600, 2 };

  // vertex::draw(window, v1);
  // vertex::draw(window, v2);
  // vertex::arcConnect(window, v1, v2, std::string{ "4" });
  // vertex::arcConnect(window, v2, v1, std::string{ "6" });
  // vertex::lineConnect(window, v1, v2, std::string{ "4" });
  // vertex::lineConnect(window, v2, v1, std::string{ "6" }, true);
  window.display();

  utils::pollEvents(window);
  return 0;
}