#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::abs;
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State {
  kEmpty,
  kObstacle,
  kClosed
};

vector<State> ParseLine(string line) {
  istringstream sline(line);
  int n;
  char c;
  vector<State> row;

  while (sline >> n >> c && c == ',') {
    if (n == 0) {
      row.push_back(State::kEmpty);
    }
    else {
      row.push_back(State::kObstacle);
    }
  }
  return row;
}

vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile(path);
  vector<vector<State>> board{};

  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

// Write function to compare the f-value of two nodes here
// Note: f_value = g + h (sum of cost and heuristic)
bool Compare(vector<int> a, vector<int> b) {
  int f1 = a[2] + a[3];
  int f2 = b[2] + b[3];

  return f1 > f2;
}

// Heuristic function to guide the A* search
// Calculate the Manhattan Distance from one coordinate to the other
int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

// Add node to open vector
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &board) {
  open_nodes.push_back(vector<int>{x, y, g, h});
  board[x][y] = State::kClosed;
}

// Search function stub.
vector<vector<State>> Search(vector<vector<State>> board, int start[2], int goal[2]) {
  // Init the open nodes vector
  vector<vector<int>> open {};

  // Init the starting node
  int x = start[0];
  int y = start[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);

  // Add the starting node to the open vector
  AddToOpen(x, y, g, h, open, board);

  cout << "No path found!\n";
  return vector<vector<State>>{};
}

string CellString(State cell) {
  switch (cell) {
  case State::kObstacle:
    return "⛰️   ";
  default:
    return "0   ";
  }
}

void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

int main() {
  int start[2]{0, 0};
  int goal[2]{4, 5};

  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, start, goal);
  PrintBoard(solution);
}
