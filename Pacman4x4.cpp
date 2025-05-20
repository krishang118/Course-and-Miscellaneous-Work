#include <iostream>
#include <vector>
using namespace std;
const int GRID_SIZE = 4;
class Pacman {
    int x, y;
public:
    Pacman() : x(0), y(0) {}
    void move(int dx, int dy) {
        int new_x = x + dx;
        int new_y = y + dy;
        if (new_x >= 0 && new_x < GRID_SIZE) {
            x = new_x;
        } else if (dx == 1) {
            x = 0;
        } else if (dx == -1) {
            x = GRID_SIZE - 1;
        }
        if (new_y >= 0 && new_y < GRID_SIZE) {
            y = new_y;
        } else if (dy == 1) {
            y = 0;
        } else if (dy == -1) {
            y = GRID_SIZE - 1;}}
    int getX() const {
        return x;}
    int getY() const {
        return y;}
};
void initializegrid(vector<vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 1;}}}
void printgrid(const vector<vector<int>>& grid, const Pacman& p) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i == p.getX() && j == p.getY()) {
                cout << "P ";
            } else if (grid[i][j] == 1) {
                cout << ". ";
            } else {
                cout << "  ";
            }}
        cout << endl;}}
int main() {
    cout << "Welcome to Pacman Game! \nYou move up/down/left/right (u/d/l/r) to move and cover the whole 4x4 grid to complete and win the game!" << endl;
    vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE));
    initializegrid(grid);
    Pacman p;
    int score = 0;
    while (true) {
        printgrid(grid, p);
        char dir;
        cout << "Enter direction (u/d/l/r): ";
        cin >> dir;
        int dx = 0, dy = 0;
        switch (dir) {
        case 'u':
            dx = -1;
            break;
        case 'd':
            dx = 1;
            break;
        case 'l':
            dy = -1;
            break;
        case 'r':
            dy = 1;
            break;
        }
        p.move(dx, dy);
        if (grid[p.getX()][p.getY()] == 1) {
            score++;
            grid[p.getX()][p.getY()] = 0;
        }
        if (score == GRID_SIZE * GRID_SIZE) {
            cout << "Ay Congrats! You won with a score of " << score << "." << endl;
            break;}}
    return 0;
}