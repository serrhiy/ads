#pragma once
#include <SFML/Graphics/Color.hpp>
#include <string>

namespace config {
  extern const char* TITLE;
  extern const unsigned WIDTH;
  extern const unsigned HEIGHT;
  extern const float LINE_WIDTH;
  extern const float VERTEX_RADIUS;
  extern const int SMOOTHING;
  extern const sf::Color LINE_COLOR;
  extern const sf::Color BACKGROUND_COLOR;
  extern const sf::Color ACTIVE_VERTEX_COLOR;
  extern const std::string FONT_PATH;
  extern const unsigned TEXT_SIZE;
  extern const unsigned LABEL_SIZE;
  extern const float ARROWS_LENGTH;
  extern const unsigned CURVE_ITEMS;
  extern const int n1, n2, n3, n4;
  extern const float k;
  extern const size_t VERTICES_COUNT;
  extern const size_t SIDES;
  extern const int SEED;
}

