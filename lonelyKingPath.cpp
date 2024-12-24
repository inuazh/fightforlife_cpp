#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

struct Position {
    int x, y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

struct HashPosition {
    size_t operator()(const Position& pos) const {
        return hash<int>()(pos.x) ^ (hash<int>()(pos.y) << 1);
    }
};

bool hasVisitedTwice(const string& moves) {
    unordered_set<Position, HashPosition> visited;
    Position current = {0, 0};
    visited.insert(current);

    for (char move : moves) {
        switch (move) {
            case 'U': current.y++; break;
            case 'D': current.y--; break;
            case 'L': current.x--; break;
            case 'R': current.x++; break;
            case 'Q': current.x--; current.y++; break;
            case 'E': current.x++; current.y++; break;
            case 'Z': current.x--; current.y--; break;
            case 'C': current.x++; current.y--; break;
        }

        if (visited.count(current)) {
            return true;
        }
        visited.insert(current);
    }

    return false;
}

int main() {
    string moves;
    cout << "Введите последовательность ходов короля (U, D, L, R, Q, E, Z, C): ";
    cin >> moves;

    if (hasVisitedTwice(moves)) {
        cout << "Король побывал дважды на одном и том же поле." << endl;
    } else {
        cout << "Король не побывал дважды на одном и том же поле." << endl;
    }

    return 0;
}