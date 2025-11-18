#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
public:
    Monster() = default;
    Monster(const std::string& name,
            int hp,
            int damage,
            int goldReward,
            int xpReward = 30);

    std::string getName() const;
    int getHp() const;
    int getDamage() const;
    int getGoldReward() const;
    int getXpReward() const;

    bool isAlive() const;
    void takeDamage(int d);

    std::string shortStatus() const;

private:
    std::string name;
    int hp = 1;
    int damage = 1;
    int goldReward = 0;
    int xpReward = 0;
};

#endif // MONSTER_H
