#include "Character.h"

#include <algorithm>
#include <iostream>
#include <sstream>

Character::Character(const std::string& displayName,
                     const std::string& className_,
                     const std::string& weaponName_,
                     int level_,
                     int maxHP_,
                     int baseDamage_,
                     int stamina_)
    : name(displayName),
      className(className_),
      weaponName(weaponName_),
      level(level_),
      maxHP(maxHP_),
      currentHP(maxHP_),
      baseDamage(baseDamage_),
      stamina(stamina_),
      gold(0),
      xp(0),
      nextLevelXP(100),
      weaponLevel(0),
      skillUnlocked(false),
      specialMultiplier(2) {

    if (className == "Ranger") {
        specializationText = "Piercing Volley: bow shots pierce and deal extra damage.";
    } else if (className == "Mage") {
        specializationText = "Arcane Surge: special spells deal greatly increased damage.";
    } else if (className == "Paladin") {
        specializationText = "Bulwark Strike: special attacks grant a temporary shield.";
    } else if (className == "Mercenary") {
        specializationText = "Frenzy: special attacks increase attack pressure.";
    } else {
        specializationText = "Specialization: unspecified.";
    }
}

std::string Character::getName() const { return name; }
std::string Character::getClassName() const { return className; }
std::string Character::getWeaponName() const { return weaponName; }
int Character::getLevel() const { return level; }
int Character::getHP() const { return currentHP; }
int Character::getMaxHP() const { return maxHP; }
int Character::getBaseDamage() const { return baseDamage; }
int Character::getStamina() const { return stamina; }
int Character::getGold() const { return gold; }
bool Character::isSkillUnlocked() const { return skillUnlocked; }
int Character::getWeaponLevel() const { return weaponLevel; }

bool Character::isAlive() const {
    return currentHP > 0;
}

int Character::attack(bool useSpecial) {
    int dmg = baseDamage + weaponLevel * 2;

    if (useSpecial && skillUnlocked) {
        if (className == "Ranger") {
            dmg = static_cast<int>(dmg * (specialMultiplier + 0.5));
        } else if (className == "Mage") {
            dmg = static_cast<int>(dmg * (specialMultiplier + 1.0));
        } else if (className == "Paladin") {
            dmg = static_cast<int>(dmg * specialMultiplier);
        } else if (className == "Mercenary") {
            dmg = static_cast<int>(dmg * (specialMultiplier + 0.3));
        } else {
            dmg = static_cast<int>(dmg * specialMultiplier);
        }
    }

    return dmg;
}

void Character::takeDamage(int dmg) {
    currentHP -= dmg;
    if (currentHP < 0) {
        currentHP = 0;
    }
}

void Character::healToFull() {
    currentHP = maxHP;
}

void Character::heal(int amount) {
    if (amount <= 0) return;
    currentHP += amount;
    if (currentHP > maxHP) {
        currentHP = maxHP;
    }
}

void Character::addGold(int amount) {
    if (amount <= 0) return;
    gold += amount;
}

bool Character::spendGold(int amount) {
    if (amount <= 0) return true;
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Character::gainXP(int gained) {
    if (gained <= 0) return;

    xp += gained;
    while (xp >= nextLevelXP) {
        xp -= nextLevelXP;
        levelUp();
        nextLevelXP = static_cast<int>(nextLevelXP * 1.45);
    }
}

void Character::levelUp() {
    applyClassGrowthOnLevel();

    std::cout << "Level up! " << name << " is now level " << level << ".\n";

    if (level >= 5 && !skillUnlocked) {
        applySpecializationUnlock();
    }
}

void Character::setNextLevelXP(int xp_) {
    if (xp_ > 0) {
        nextLevelXP = xp_;
    }
}

bool Character::upgradeWeapon() {
    weaponLevel++;
    std::cout << name << "'s " << weaponName
              << " has been upgraded (weapon level " << weaponLevel << ").\n";
    return true;
}

bool Character::upgradeSkill() {
    const int cost = 75;
    if (!spendGold(cost)) {
        std::cout << "Not enough gold to upgrade skill (cost " << cost << ").\n";
        return false;
    }

    specialMultiplier++;
    skillUnlocked = true;
    std::cout << name << "'s special skill improved. Multiplier now "
              << specialMultiplier << ".\n";
    return true;
}

std::string Character::shortStatus() const {
    std::ostringstream ss;
    ss << name << " (" << className << ") | HP: " << currentHP << "/"
       << maxHP << " | Dmg: " << baseDamage << "+" << (weaponLevel * 2)
       << " | Lv: " << level << " | Gold: " << gold;
    return ss.str();
}

std::string Character::longDescription() const {
    std::ostringstream ss;
    ss << name << " - " << className
       << " - Weapon: " << weaponName << "\n";
    ss << "HP: " << maxHP
       << ", Base Damage: " << baseDamage
       << ", Stamina: " << stamina << "\n";
    ss << "Special: " << specializationText << "\n";
    return ss.str();
}

void Character::applyClassGrowthOnLevel() {
    if (className == "Ranger") {
        maxHP += 6;
        baseDamage += 3;
    } else if (className == "Mage") {
        maxHP += 4;
        baseDamage += 4;
    } else if (className == "Paladin") {
        maxHP += 10;
        baseDamage += 2;
    } else if (className == "Mercenary") {
        maxHP += 5;
        baseDamage += 3;
    } else {
        maxHP += 6;
        baseDamage += 2;
    }

    currentHP = std::min(currentHP + (maxHP / 10), maxHP);
}

void Character::applySpecializationUnlock() {
    skillUnlocked = true;
    specialMultiplier += 1;
    std::cout << "Specialization unlocked for "
              << name << ". " << specializationText << "\n";
}
