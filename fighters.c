#include "cy_fighters.h"

// Definition of available combatants
Fighter available_fighters[] = {
    {"Yassa", 100, 100, 30, 10, 20, { {"Brava - 40 damages", "attack", 40, 2, 0}, {"heal - 20", "heal", 20, 3, 0} } },
    {"Barim", 150, 150, 20, 25, 40, { {"highkick - 30 damages", "attack", 30, 2, 0}, {"heal - 30", "heal", 30, 3, 0} } },
    {"Mit", 120, 120, 25, 20, 40, { {"Flip - 35 damages", "attack", 35, 2, 0}, {"heal - 25", "heal", 25, 3, 0} } },
    {"Sana", 90, 90, 20, 15, 100, { {"head crushing - 55 damages", "attack", 55, 2, 0}, {"heal - 40", "heal", 40, 3, 0} } },
    {"Juwaw", 110, 110, 35, 15, 10, { {"musty - 40 damages", "attack", 40, 2, 0}, {"heal - 25", "heal", 25, 3, 0} } },
    {"resaf", 90, 90, 15, 15, 30, { {"smock - 35 damages", "attack", 35, 2, 0}, {"heal - 25", "heal", 25, 3, 0} } },
};

// Calculation of the total number of combatants
int total_fighters = sizeof(available_fighters) / sizeof(Fighter);

// Displays the list of available fighters
void display_fighter_list() {
    printf("\nAvailable Fighters:\n");
    for (int i = 0; i < total_fighters; i++) {
        printf("  %d) %s (HP: %d, ATK: %d, DEF: %d, SPD: %d)\n", i + 1,
               available_fighters[i].name, available_fighters[i].max_hp,
               available_fighters[i].attack, available_fighters[i].defense,
               available_fighters[i].speed);
    }
}
