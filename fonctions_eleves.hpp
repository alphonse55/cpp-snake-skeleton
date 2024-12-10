#include <vector>
#include <array>
#include <utility>

// 😇 Je suis gentil je vous ai fait le tracé du terrain 😇
std::vector<int> backgroundSetup(const int &nx, const int &ny)
{
  std::vector<int> bg(nx * ny, 0);
  int i;
  for (i = 0; i < nx; i++)
  {
    bg[i] = 1;
  }
  for (i = 0; i < nx; i++)
  {
    bg[(ny - 1) * nx + i] = 1;
  }
  for (i = 0; i < ny; i++)
  {
    bg[i * nx] = 1;
  }
  for (i = 0; i < ny; i++)
  {
    bg[i * nx + nx - 1] = 1;
  }

  return bg;
}

///////////////////////////////////////////////////////////////////////////////
/////// 🧑‍💻 FROM HERE you must complete 🧑‍💻 ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void add_snake(const std::vector<std::pair<int, int>> &snake, std::vector<int> &bg, int nx, int ny)
{
  for (const auto& segment : snake) {
    bg[segment.second*nx + segment.first] = 3;
  }
}

void remove_snake(const std::vector<std::pair<int, int>> &snake, std::vector<int> &bg, int nx, int ny)
{
  for (const auto& segment : snake) {
    bg[segment.second*nx + segment.first] = 0;
  }
}

std::array<int, 2> snake_movement(char key, std::array<int, 2> dxdy)
{
  switch (key) {
    case 'd': // Right
        return {1, 0};
    case 'q': // Left
        return {-1, 0};
    case 'z': // Up
        return {0, -1};
    case 's': // Down
        return {0, 1};
    default: // Invalid input
      return dxdy; // No movement
  }
}

bool verifyBorder(const std::vector<std::pair<int, int>> &snake, int nx, int ny)
{
  for (int i = 0; i<snake.size(); i++) {
    if (snake[i].first >= nx || snake[i].first <= 0 || snake[i].second >= ny || snake[i].second <= 0){
      return true;
    }
    for (int j = i+1; j<snake.size(); j++){
      if (snake[i] == snake[j]){
        return true;
      }
    }
  }
  return false;
}

std::vector<std::pair<int, int>> setupSnake(int snake_len)
{
  std::vector<std::pair<int, int>> snake(snake_len);
  int i;
  for (i = 0; i < snake_len; i++)
  {
    snake[i].first = 10 + i;
    snake[i].second = 10;
  }
  return snake;
}

void update_snake_coordinates(std::vector<std::pair<int, int>> &snake, bool eat, std::array<int, 2> dxdy)
{
  if (eat == false){
    snake.erase(snake.begin());
  }
  std::pair<int, int> newSegment = {snake.back().first + dxdy[0], snake.back().second + dxdy[1]};
  snake.push_back(newSegment);
}