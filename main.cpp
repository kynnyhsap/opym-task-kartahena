#include <iostream>
#include <map>
#include <vector>
using namespace std;

void countSectors(vector<int> & sectors, map<int, int> & table) {
    for (int & sector : sectors) {
        table[sector]++;
    }
}

int chooseMin(map<int, int> & table) {
    int minSector = 1;
    int minSectorCount = table[1];

    for(auto & [sector, count] : table) {
        if (count < minSectorCount) {
            minSectorCount = count;
            minSector = sector;
        }
    }

    return minSector;
}

class Pirate {
public:
    int  Position;
    int  Sector;
    bool InBoat;

    Pirate() {
        Position = -1;
        Sector = 0;
        InBoat = false;
    }

    void PlaceOn(int position, int sector) {
        Position = position;
        Sector = sector;
    }
};

bool isBusyBy(Pirate * pirate, vector<int> & sectors) {
    return sectors[pirate->Position] == pirate->Sector;
}

int minSteps(vector<int> & sectors, map<int, int> & table) {
    int steps = 0;

    countSectors(sectors, table);
    const int min = chooseMin(table);

    Pirate p1;
    Pirate p2;

    Pirate * currentPirate = &p1;
    Pirate * smokingPirate = &p2;

    while (!currentPirate->InBoat || !smokingPirate->InBoat) {
        bool foundNewPlace = false;

        for (int i = currentPirate->Position + 1; i < sectors.size(); ++i) {
            if (sectors[i] == min) {
                if (isBusyBy(smokingPirate, sectors)) {
                    continue;
                } else {
                    foundNewPlace = true;

                    currentPirate->PlaceOn(i, sectors[i]);

                    if (!smokingPirate->InBoat) {
                        Pirate * temp = currentPirate;
                        currentPirate = smokingPirate;
                        smokingPirate = temp;
                    }

                    steps += 1;
                    break;
                }
            }
        }

        if (!foundNewPlace) {
            currentPirate->InBoat = true;
            steps += 1;

            if (!smokingPirate->InBoat) {
                Pirate *temp = currentPirate;
                currentPirate = smokingPirate;
                smokingPirate = temp;
            }
        }
    }

    cout << "Steps done " << steps << endl;

    return steps;
}

int main() {
    vector<int> sectors = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5};
    map<int, int> sectorsTable = {
            {1, 0},
            {2, 0},
            {3, 0},
            {4, 0},
            {5, 0},
            {6, 0},
    };

    minSteps(sectors, sectorsTable);

    return 0;
}
