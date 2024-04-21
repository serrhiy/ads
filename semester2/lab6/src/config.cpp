#include <SFML/Graphics/Color.hpp>
#include <string>
#include "config.hpp"

namespace config {
  const char* TITLE{ "Lytvynenko Serhiy, IM-31" };
  const unsigned WIDTH{ 800 };
  const unsigned HEIGHT{ 800 };
  const float LINE_WIDTH{ 3.f };
  const float VERTEX_RADIUS{ 50.f };
  const int SMOOTHING{ 8 };
  const sf::Color LINE_COLOR{ sf::Color::White };
  const sf::Color BACKGROUND_COLOR{ sf::Color::Black };
  const sf::Color ACTIVE_VERTEX_COLOR{ sf::Color::Red };
  const std::string FONT_PATH{ "./fonts/arial.ttf" };
  const unsigned TEXT_SIZE{ 32 };
  const unsigned LABEL_SIZE{ 24 };
  const float ARROWS_LENGTH{ 15 };
  const unsigned CURVE_ITEMS{ 20 };
  const int n1{ 3 }, n2{ 1 }, n3{ 1 }, n4{ 2 };
  const float k{ 1.f - n3 * 0.01f - n4 * 0.005f - 0.15f };
  const size_t VERTICES_COUNT{ 10 + n3 };
  const size_t SIDES{ 4 };
  const int SEED{ n1 * 1000 + n2 * 100 + n3 * 10 + n4 };
}