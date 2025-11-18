#ifndef DUNGEON_MANAGER_H
#define DUNGEON_MANAGER_H

#include <string>
#include <vector>

#include "Monster.h"

struct Room {
    Monster monster;
    std::string desc;
    bool hasCampfire = false;
    bool isBoss = false;
};

class DungeonManager {
public:
    DungeonManager();

    void generateDungeon(int numRooms);
    const std::vector<Room>& getRooms() const;
    int getCampInterval() const;

private:
    std::vector<Room> rooms;
    int campInterval;

    Monster makeRandomMonster(int depth);
    Monster makeBoss();
};

#endif // DUNGEON_MANAGER_H
