#include "Monster.h"

#include <sstream>

Monster::Monster(const std::string& name_,
                 int hp_,
                 int damage_,
                 int goldReward_,
                 int xpReward_)
    : name(name_),
      hp(hp_),
      damage(damage_),
      goldReward(goldReward_),
      xpReward(xpReward_) {}

std::string Monster::getName() const { return name; }
int Monster::getHp() const { return hp; }
int Monster::getDamage() const { return damage; }
int Monster::getGoldReward() const { return goldReward; }
int Monster::getXpReward() const { return xpReward; }

bool Monster::isAlive() const {
    return hp > 0;
}

void Monster::takeDamage(int d) {
    hp -= d;
    if (hp < 0) {
        hp = 0;
    }
}

std::string Monster::shortStatus() const {
    std::ostringstream ss;
    ss << name << " | HP: " << hp
       << " | Atk: " << damage
       << " | Gold: " << goldReward;
    return ss.str();
}
