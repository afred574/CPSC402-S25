#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "DisjSets.h"

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;

struct Wall {
    int cell1, cell2;
};

int getIndex(int row, int col) {
    return row * WIDTH + col;
}

void printMaze(const vector<bool>& horizontal, const vector<bool>& vertical) {
    // Top border with entrance
    cout << "┌";
    for (int col = 0; col < WIDTH; ++col) {
        if (col == 0)
            cout << "   "; // entrance
        else
            cout << "───";
        cout << (col == WIDTH - 1 ? "┐\n" : "┬");
    }

    for (int row = 0; row < HEIGHT; ++row) {
        // Cell content and vertical walls
        for (int col = 0; col < WIDTH; ++col) {
            int index = getIndex(row, col);
            if (col == 0)
                cout << "│";

            if (index == 0)
                cout << " S ";
            else if (index == WIDTH * HEIGHT - 1)
                cout << " E ";
            else
                cout << "   ";

            cout << (vertical[index] ? "│" : " ");
        }
        cout << "\n";

        // Bottom walls
        if (row == HEIGHT - 1) {
            cout << "└";
            for (int col = 0; col < WIDTH; ++col) {
                int index = getIndex(row, col);
                cout << (horizontal[index] ? "───" : "   ");
                cout << (col == WIDTH - 1 ? "┘\n" : "┴");
            }
        } else {
            cout << "├";
            for (int col = 0; col < WIDTH; ++col) {
                int index = getIndex(row, col);
                cout << (horizontal[index] ? "───" : "   ");
                cout << (col == WIDTH - 1 ? "┤\n" : "┼");
            }
        }
    }
}

int main() {
    int numCells = WIDTH * HEIGHT;
    DisjSets ds(numCells);

    vector<Wall> walls;
    vector<bool> horizontal(numCells, true);
    vector<bool> vertical(numCells, true);

    // Create horizontal and vertical walls
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            int index = getIndex(row, col);
            if (col < WIDTH - 1)
                walls.push_back({index, index + 1});
            if (row < HEIGHT - 1)
                walls.push_back({index, index + WIDTH});
        }
    }

    // Shuffle walls
    random_device rd;
    mt19937 g(rd());
    shuffle(walls.begin(), walls.end(), g);

    // Kruskal's algorithm
    for (const Wall& wall : walls) {
        int root1 = ds.find(wall.cell1);
        int root2 = ds.find(wall.cell2);

        if (root1 != root2) {
            ds.unionSets(root1, root2);
            if (wall.cell2 == wall.cell1 + 1)
                vertical[wall.cell1] = false;
            else if (wall.cell2 == wall.cell1 + WIDTH)
                horizontal[wall.cell1] = false;
        }
    }

    // Entrance and exit
    vertical[0] = false;
    vertical[numCells - 1] = false;

    printMaze(horizontal, vertical);
    return 0;
}
