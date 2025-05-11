#include "cy_fighters.h"


int main() {                  // Main function of the game
    srand(time(NULL)); 

    printf("========================================\n");
    printf("           \U0001F4A5 CY-FIGHTERS \U0001F4A5\n");
    printf("========================================\n\n");

    int num_players;
    do {
        printf("Number of players (1 or 2):\n> ");
        num_players = read_int();
        if (num_players != 1 && num_players != 2) {
            printf("Invalid input. Please enter 1 or 2.\n");
        }
    } while (num_players != 1 && num_players != 2);        //Choice of the number of players

    int team_size;
    do {
        printf("\nTeam size (number of fighters, 1-%d):\n> ", MAX_COMBATTANTS);
        team_size = read_int();
        if (team_size < 1 || team_size > MAX_COMBATTANTS) {
            printf("Invalid team size. Please enter a number between 1 and %d.\n", MAX_COMBATTANTS);
        }
    } while (team_size < 1 || team_size > MAX_COMBATTANTS);    //Choice of the number of fighters

    Team team1, team2;
    configure_team(&team1, team_size, "Player 1");            //Choice of fighters for team 1

    int ai_control = 0;
    if (num_players == 2) {
        configure_team(&team2, team_size, "Player 2");        //Choice of fighters for team 2
    } else {
        strcpy(team2.name, "AI");
        team2.member_count = team_size;
        for (int i = 0; i < team_size; i++) {
            team2.members[i] = available_fighters[rand() % total_fighters];    //Choice of fighters for AI team 
        }
        ai_control = 1;
    }

    printf("\n=== Battle Start ===\n");
    while (!is_team_KO(team1) && !is_team_KO(team2)) {
        display_team(team1);
        display_team(team2);
        printf("\n--- Turn of team %s ---\n", team1.name);
        team_turn(&team1, &team2, 0);
        if (is_team_KO(team2)) break;
        printf("\n--- Turn of team %s ---\n", team2.name);
        team_turn(&team2, &team1, ai_control);
    }                                                    //functions to make the fight

    printf("\n=== End of Battle ===\n");
    if (is_team_KO(team1)) printf("%s wins!\n", team2.name);
    else printf("%s wins!\n", team1.name);              //end of the figth 

    return 0;
}
