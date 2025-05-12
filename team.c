#include "cy_fighters.h"

// Check if a team is still alive
int is_team_KO(Team t) {
    for (int i = 0; i < t.member_count; i++) {
        if (t.members[i].hp > 0) { // If at least 1 alive
            return 0; 
        }
    }
    return 1; 
}


void display_team(Team t) {            //Displays team members and their health status
    printf("\nTEAM: %s\n", t.name);
    for (int i = 0; i < t.member_count; i++) {
        Fighter f = t.members[i];
        printf(" - %d) %s : %d/%d HP\n", i + 1, f.name, f.hp, f.max_hp);
    }
}


void configure_team(Team *team, int team_size, const char *player_name) {  // Team Configuration
    printf("\n%s, enter your team name:\n> ", player_name);
    
    
    clear_input_buffer();            // Flush the input buffer
    
    
    read_string(team->name, MAX_NAME_LENGTH);   // Read the team name
    team->member_count = team_size;

    for (int i = 0; i < team_size; i++) {
        display_fighter_list();
        int choice;
        do {
            printf("Choose fighter %d (1-%d):\n> ", i + 1, total_fighters);
            choice = read_int();
            if (choice < 1 || choice > total_fighters) {
                printf("Invalid choice. Please select a valid fighter (1-%d).\n", total_fighters);
            }
        } while (choice < 1 || choice > total_fighters);         //choice of fighters
        
        team->members[i] = available_fighters[choice - 1];
    }
}
