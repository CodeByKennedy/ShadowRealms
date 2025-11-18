#include "DungeonManager.h"

#include <chrono>
#include <random>

DungeonManager::DungeonManager() : campInterval(5) {}

Monster DungeonManager::makeBoss() {
    return Monster("Dungeon Guardian", 140, 20, 150, 300);
}

Monster DungeonManager::makeRandomMonster(int depth) {
    int baseHp = 12 + depth * 4;
    int baseDmg = 4 + depth;
    int gold = 6 + depth * 2;
    int xp = 20 + depth * 8;

    auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    int t = static_cast<int>((depth + now) % 4);

    switch (t) {
        case 0: return Monster("Goblin", baseHp, baseDmg, gold, xp);
        case 1: return Monster("Skeleton", baseHp + 4, baseDmg + 1, gold + 2, xp + 5);
        case 2: return Monster("Wolf", baseHp - 2, baseDmg + 2, gold, xp + 2);
        default: return Monster("Bandit", baseHp, baseDmg, gold + 1, xp + 3);
    }
}

void DungeonManager::generateDungeon(int numRooms) {
    rooms.clear();

    std::mt19937 rng(static_cast<unsigned>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(5, 6);
    campInterval = dist(rng);

    for (int i = 0; i < numRooms; ++i) {
        Room r;
        r.monster = makeRandomMonster(i / 3);
        r.desc = "A corridor marked with old blood and soot.";
        r.hasCampfire = ((i + 1) % campInterval == 0);
        r.isBoss = false;
        rooms.push_back(r);
    }

    Room boss;
    boss.monster = makeBoss();
    boss.desc = "A great vaulted chamber where the guardian waits.";
    boss.hasCampfire = false;
    boss.isBoss = true;
    rooms.push_back(boss);
}

const std::vector<Room>& DungeonManager::getRooms() const {
    return rooms;
}

int DungeonManager::getCampInterval() const {
    return campInterval;
}
