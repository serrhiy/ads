#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <cmath>
#include "config.hpp"
#include "vertex.hpp"
#include "utils.hpp"

using sf::RenderWindow, sf::Vector2f, std::string, vertex::Vertex;

const float PI{ static_cast<float>(M_PI) };

std::pair<float, float> rotate(float x, float y, float l, float fi) {
  return std::make_pair(
    x + l * cos(fi),
    y + l * sin(fi)
  );
}

float toDegrees(float radians) {
  return radians * 180 / PI;
}

float distance(float x1, float y1, float x2, float y2) {
  return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

std::function<Vector2f(size_t)> bezierCurve2Closure(
  const Vector2f& p1,
  const Vector2f& p2,
  const Vector2f& p3,
  int items
) {
  const auto step{ 1.f / items };
  return [&p1, &p2, &p3, step](size_t i) {
    const auto t{ step * i };
    const auto t1{ 1 - t };
    return t1 * t1 * p1 + 2 * t1 * t * p2 + t * t * p3;
  };
}

void drawCircle(RenderWindow& window, const Vector2f& posc, const sf::Color& color) {
  const auto position { Vector2f{
    posc.x - config::VERTEX_RADIUS,
    posc.y - config::VERTEX_RADIUS,
  } };
  sf::CircleShape circle{ config::VERTEX_RADIUS };
  circle.setPosition(position);
  circle.setFillColor(config::BACKGROUND_COLOR);
  circle.setOutlineThickness(config::LINE_WIDTH);
  circle.setOutlineColor(color);
  window.draw(circle);
}

void vertex::drawText(RenderWindow& window, const Vector2f& posc, const string& txt, const sf::Color& color) {
  const auto font{ utils::getFont() };
  auto text{ sf::Text{ txt, font, config::TEXT_SIZE } };
  text.setFillColor(color);
  const auto r{ text.getGlobalBounds() };
  text.setPosition(posc - r.getPosition() - r.getSize() / 2.f);
  window.draw(text);
}

void vertex::draw(RenderWindow& window, const Vertex& vertex, const sf::Color& color) {
  const auto vector{ Vector2f{ vertex.x, vertex.y } };
  drawCircle(window, vector, color);
  drawText(window, vector, std::to_string(vertex.index), color);
}

void line(
  RenderWindow& window,
  const Vector2f& from,
  const Vector2f& to,
  const sf::Color& color
) {
  const auto length{ distance(from.x, from.y, to.x, to.y) };
  const auto fi{ atan2f(to.y - from.y , to.x - from.x) };
  sf::RectangleShape rec{ { length, config::LINE_WIDTH } };
  rec.setFillColor(color);
  rec.setOrigin({ 0, config::LINE_WIDTH / 2 });
  rec.setPosition(from.x, from.y);
  rec.rotate(toDegrees(fi));
  window.draw(rec);
}

void arrows(
  RenderWindow& window,
  float x,
  float y,
  float fi,
  float delta,
  const sf::Color& color
) {
  const auto [lx, ly]{ rotate(x, y, config::ARROWS_LENGTH, fi + delta) };
  const auto [rx, ry]{ rotate(x, y, config::ARROWS_LENGTH, fi - delta) };
  line(window, { lx, ly }, { x, y }, color);
  line(window, { x, y }, { rx, ry }, color);
}

void vertex::lineConnect(
  RenderWindow& window,
  const Vertex& from,
  const Vertex& to,
  bool shift,
  bool dir,
  const sf::Color& color
) {
  const auto fi{ atan2f(to.y - from.y, to.x - from.x) };
  const auto f1{ shift ? fi - PI / 8 : fi  };
  const auto f2{ shift ? fi + PI + PI / 8 : fi + PI };
  const auto [x1, y1]{ rotate(from.x, from.y, config::VERTEX_RADIUS + config::LINE_WIDTH, f1) };
  const auto [x2, y2]{ rotate(to.x, to.y, config::VERTEX_RADIUS + config::LINE_WIDTH, f2) };
  line(window, { x1, y1 }, { x2, y2 }, color);
  if (dir) arrows(window, x2, y2, fi + PI, PI / 8, color);
}

void vertex::arcConnect(
  sf::RenderWindow& window,
  const Vertex& from,
  const Vertex& to,
  bool dir,
  const sf::Color& color
) {
  const auto fi{ atan2f(to.y - from.y, to.x - from.x) };
  const auto [x1, y1]{ rotate(from.x, from.y, config::VERTEX_RADIUS + config::LINE_WIDTH, fi - PI / 6) };
  const auto [x2, y2]{ rotate(to.x, to.y, config::VERTEX_RADIUS + config::LINE_WIDTH, fi + PI + PI / 6) };
  
  const auto dx{ x2 - x1 };
  const auto dy{ y2 - y1 };

  const auto height{ 2.f * config::VERTEX_RADIUS };
  const auto length{ sqrtf(dx * dx + dy * dy) };
  const auto parallel{ sf::Vector2f{ dy, -dx } / length };
  const auto center{ sf::Vector2f{ (x1 + x2) / 2.f, (y1 + y2) / 2.f } };
  const auto top{ center + height * parallel };
  const auto bezier{ bezierCurve2Closure({ x1, y1 }, top, { x2, y2 }, config::CURVE_ITEMS) };
  for (size_t i{ 0 }; i < config::CURVE_ITEMS; i++) {
    line(window, bezier(i), bezier(i + 1), color);
  }
  if (dir) {
    const auto f{ atan2f(top.y - y2, top.x - x2) };
    arrows(window, x2, y2, f, PI / 8, color);
  }
}

void vertex::loop(RenderWindow& window, const Vertex& vertex, bool dir, const sf::Color& color) {
  const float x{ vertex.x };
  const float y{ vertex.y - config::VERTEX_RADIUS - config::LINE_WIDTH };
  const auto [x1, y1]{ rotate(x, y, config::VERTEX_RADIUS, -PI / 4) };
  const auto [x2, y2]{ rotate(x, y, config::VERTEX_RADIUS, -3 * PI / 4) };
  line(window, { x, y }, { x1, y1 }, color);
  line(window, { x1 + config::LINE_WIDTH / 3, y1 }, { x2 - config::LINE_WIDTH / 3, y2 }, color);
  line(window, { x2, y2 }, { x, y }, color);
  if (dir) arrows(window, x, y, PI / 4 + PI, PI / 8, color);
}

float calculateStep(float size, int count, int sides) {
  const float denominator{ ceilf(static_cast<float>(count) / sides) + 1 };
  return static_cast<float>(size) / denominator;
}

const std::function<std::pair<float, float>(int, int, float, float)> cases[] {
  [](int i, int sp, float st, float start) { return std::make_pair(
    start + st * i, start
  ); },
  [](int i, int sp, float st, float start) { return std::make_pair(
    start + st * sp, start + st * i
  ); },
  [](int i, int sp, float st, float start) { return std::make_pair(
    start + st * (sp - i), start + st * sp
  ); },
  [](int i, int sp, float st, float start) { return std::make_pair(
    start, start + st * (sp - i)
  ); }
};

std::function<Vertex(size_t)> vertex::getVertexClosure(size_t count, size_t sides, int width) {
  const int split{ static_cast<int>(ceilf(static_cast<float>(count) / sides)) };
  const float step{ calculateStep(width, count, sides) };
  const float start{ step / 2.f };
  return [split, step, start](size_t index) {
    const int side{ static_cast<int>(floorf(static_cast<float>(index) / split)) };
    const auto [x, y]{ cases[side](index % split, split, step, start) };
    return Vertex{ x, y, index };
  };
}