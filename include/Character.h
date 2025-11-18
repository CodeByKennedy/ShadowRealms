#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    Character(const std::string& displayName,
              const std::string& className,
              const std::string& weaponName,
              int level,
              int maxHP,
              int baseDamage,
              int stamina);

    std::string getName() const;
    std::string getClassName() const;
    std::string getWeaponName() const;
    int getLevel() const;
    int getHP() const;
    int getMaxHP() const;
    int getBaseDamage() const;
    int getStamina() const;
    int getGold() const;
    bool isSkillUnlocked() const;
    int getWeaponLevel() const;

    bool isAlive() const;
    int attack(bool useSpecial = false);
    void takeDamage(int dmg);
    void healToFull();
    void heal(int amount);

    void addGold(int amount);
    bool spendGold(int amount);

    void gainXP(int xp);
    void levelUp();
    void setNextLevelXP(int xp);

    bool upgradeWeapon();
    bool upgradeSkill();

    std::string shortStatus() const;
    std::string longDescription() const;

private:
    std::string name;
    std::string className;
    std::string weaponName;

    int level;
    int maxHP;
    int currentHP;
    int baseDamage;
    int stamina;

    int gold;

    int xp;
    int nextLevelXP;

    int weaponLevel;
    bool skillUnlocked;
    int specialMultiplier;
    std::string specializationText;

    void applyClassGrowthOnLevel();
    void applySpecializationUnlock();
};

#endif // CHARACTER_H
