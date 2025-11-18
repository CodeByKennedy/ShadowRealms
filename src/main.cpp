#include <ctime>
#include <iostream>
#include <limits>

#include "Character.h"
#include "DungeonManager.h"
#include "Monster.h"

int readInt() {
    int v;
    while (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a number: ";
    }
    return v;
}

void showIntro() {
    std::cout << "=== ShadowRealms (Demo) ===\n\n";
    std::cout << "Choose your hero:\n";
}

Character chooseCharacter() {
    showIntro();
    std::cout << "1. Lyra Windstrider (Ranger) - Weapon: Bow\n";
    std::cout << "   Agile marksman. Lower HP, higher ranged damage. "
                 "Specializes at level 5 (Piercing Volley).\n\n";

    std::cout << "2. Serenya Vale (Mage) - Weapon: Staff\n";
    std::cout << "   Arcane caster. Low HP, high burst. "
                 "Specializes at level 5 (Arcane Surge).\n\n";

    std::cout << "3. Tharok Ironshield (Paladin) - Weapon: Sword\n";
    std::cout << "   Bulwark fighter. High HP, defensive. "
                 "Specializes at level 5 (Bulwark Strike).\n\n";

    std::cout << "4. Kael Blackthorn (Mercenary) - Weapon: Dual Daggers\n";
    std::cout << "   Versatile melee. Medium HP, strong single-target. "
                 "Specializes at level 5 (Frenzy).\n\n";

    int choice = 0;
    while (choice < 1 || choice > 4) {
        std::cout << "Enter 1-4: ";
        choice = readInt();
    }

    switch (choice) {
        case 1:
            return Character("Lyra Windstrider", "Ranger", "Bow", 1, 90, 20, 10);
        case 2:
            return Character("Serenya Vale", "Mage", "Staff", 1, 80, 25, 10);
        case 3:
            return Character("Tharok Ironshield", "Paladin", "Sword", 1, 120, 15, 10);
        default:
            return Character("Kael Blackthorn", "Mercenary", "Dual Daggers", 1, 85, 22, 10);
    }
}

bool combatLoop(Character& player, Monster& monster) {
    std::cout << "\n--- Combat: " << monster.getName() << " ---\n";

    while (player.isAlive() && monster.isAlive()) {
        std::cout << player.shortStatus() << "\n";
        std::cout << monster.shortStatus() << "\n";
        std::cout << "Choices: 1) Attack  2) Special (if unlocked)  3) Defend  4) Flee (50%)\n";

        int c = readInt();

        if (c == 4) {
            if (std::rand() % 100 < 50) {
                std::cout << "You fled the fight.\n";
                return true;
            }
            std::cout << "Flee failed.\n";
        }

        if (c == 3) {
            int dmg = monster.getDamage() / 2;
            player.takeDamage(dmg);
            std::cout << "You brace and take " << dmg << " damage.\n";
        } else {
            bool useSpecial = (c == 2);
            int dmgToMonster = player.attack(useSpecial);
            monster.takeDamage(dmgToMonster);
            std::cout << "You deal " << dmgToMonster << " damage.\n";

            if (!monster.isAlive()) {
                break;
            }

            int dmgToPlayer = monster.getDamage();
            player.takeDamage(dmgToPlayer);
            std::cout << monster.getName() << " hits you for "
                      << dmgToPlayer << " damage.\n";
        }
    }

    if (!player.isAlive()) {
        std::cout << "You were slain.\n";
        return false;
    }

    if (!monster.isAlive()) {
        std::cout << "Victory! You killed " << monster.getName() << ".\n";
        player.addGold(monster.getGoldReward());
        player.gainXP(monster.getXpReward());
        std::cout << "Gained " << monster.getGoldReward()
                  << " gold and " << monster.getXpReward() << " XP.\n";
    }

    return true;
}

void campfireMenu(Character& player) {
    bool upgradedThisCamp = false;
    bool active = true;

    while (active) {
        std::cout << "\n--- Campfire ---\n";
        std::cout << "1) Rest (Full heal)\n";
        std::cout << "2) Upgrade Weapon " << (upgradedThisCamp ? "(used)" : "") << "\n";
        std::cout << "3) Upgrade Skill (cost 75 gold)\n";
        std::cout << "4) Leave\n";

        int c = readInt();

        switch (c) {
            case 1:
                player.healToFull();
                std::cout << "You rest and heal.\n";
                break;
            case 2:
                if (!upgradedThisCamp) {
                    player.upgradeWeapon();
                    upgradedThisCamp = true;
                } else {
                    std::cout << "Weapon upgrade already used this camp.\n";
                }
                break;
            case 3:
                player.upgradeSkill();
                break;
            case 4:
                active = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }

    std::cout << "Leaving camp...\n";
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Character player = chooseCharacter();
    std::cout << "\nStarting as:\n" << player.longDescription() << "\n";

    DungeonManager dm;
    const int regularRooms = 12;
    dm.generateDungeon(regularRooms);
    const auto& rooms = dm.getRooms();

    std::cout << "Dungeon generated. Camp interval: "
              << dm.getCampInterval() << " rooms.\n";

    int roomNo = 0;
    for (const Room& r : rooms) {
        ++roomNo;

        std::cout << "\n--- Room " << roomNo << " ---\n";
        std::cout << r.desc << "\n";

        if (r.hasCampfire) {
            std::cout << "You find a warm campfire.\n";
            campfireMenu(player);

            if (!player.isAlive()) {
                std::cout << "You died while resting. Game over.\n";
                return 0;
            }
        }

        Monster monster = r.monster;
        std::cout << "A " << monster.getName() << " approaches!\n";

        bool survived = combatLoop(player, monster);
        if (!survived) {
            std::cout << "You died in room " << roomNo << ".\n";
            return 0;
        }

        std::cout << "--- End of room " << roomNo << " ---\n";
    }

    std::cout << "\nYou survived the dungeon! Final status:\n"
              << player.shortStatus() << "\n";
    std::cout << "Thanks for playing the demo.\n";

    return 0;
}
