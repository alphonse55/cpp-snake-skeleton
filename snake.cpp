#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <thread>
#include <fstream>

#include "fonctions_prof.hpp"
#include "fonctions_eleves.hpp"


void startGame(int &n, int &lap, const int &nx, const int &ny, std::vector<std::pair<int, int>> &snake, std::vector<int> &bg)
{
  char key;
  std::array<int, 2> dxdy = {1, 0};
  std::array<int, 2> food = {0, 0};
  internal::createFood(bg, food, nx, ny);
  while (true)
  {
    n += 1;
    lap = 100 + 100/n;
    internal::frameSleep(lap);
    if (internal::keyEvent())
    {
      std::cin >> key;
      dxdy = snake_movement(key, dxdy);
    }
    internal::backgroundClear();
    add_snake(snake, bg, nx, ny);
    internal::printFrame(nx, ny, bg);
    remove_snake(snake, bg, nx, ny);
    bool out = verifyBorder(snake, nx, ny);
    if (out)
    {
      std::cerr << "" << std::endl;
      exit(1);
    }
    bool eat = internal::eatFood(food, snake);
    if (eat)
    {
      internal::createFood(bg, food, nx, ny);
    }
    update_snake_coordinates(snake, eat, dxdy);
  }
}

int main()
{
  const int nx = 50;
  const int ny = 25;
  int lap = 200;
  int snake_len = 10;
  int n = 0;

  std::vector<int> background = backgroundSetup(nx, ny);
  internal::printFrame(nx, ny, background);

  std::vector<std::pair<int, int>> snake = setupSnake(snake_len);

  startGame(n, lap, nx, ny, snake, background);
  return 0;
}