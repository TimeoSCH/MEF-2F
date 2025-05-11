#ifndef CY_FIGHTERS_H
#define CY_FIGHTERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define MAX_TECH 2            // Maximum number of techniques per fighter
#define MAX_COMBATTANTS 3     // Maximum number of fighters per team
#define MAX_NAME_LENGTH 29    // Maximum length for names (reserving 1 character for \0)
#define BUFFER_SIZE 100       // Buffer size for user inputs

// Data structures
typedef struct {
    char name[30];               // Technique name
    char effect[30];             // Effect: "attack" or "heal"
    int value;                   // Effect value
    int cooldown;                // Cooldown in turns
    int cooldown_remaining;      // Remaining cooldown
} Technique;

typedef struct {
    char name[30];               // Fighter name
    int max_hp;                  // Maximum HP
    int hp;                      // Current HP
    int attack;                  // Attack power
    int defense;                 // Defense
    int speed;                   // Speed
    Technique tech[MAX_TECH];    // Available techniques
} Fighter;

typedef struct {
    char name[30];               // Team name
    Fighter members[MAX_COMBATTANTS]; // Team members
    int member_count;            // Number of members
} Team;

// Utility function declarations
void clear_input_buffer();
int read_int();
void read_string(char *str, int max_length);

// Team management functions
int is_team_KO(Team t);
void display_team(Team t);
void configure_team(Team *team, int team_size, const char *player_name);

// Combat functions
int choose_target(Team *opponent);
void fighter_action(Fighter *player, Team *opponent);
void fighter_action_ai(Fighter *ai, Team *opponent);
void team_turn(Team *player, Team *opponent, int ai_control);

// Display functions
void display_fighter_list();

// Global variable (declared here, defined in fighters.c)
extern Fighter available_fighters[];
extern int total_fighters;

#endif // CY_FIGHTERS_H