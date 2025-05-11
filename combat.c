#include "cy_fighters.h"

//Allows the player to choose a live target from the opposing team
int choose_target(Team *opponent) {
    printf("Choose a target:\n\n");

    // Simple graphical display of fighters
    for (int i = 0; i < opponent->member_count; i++) {
        Fighter *f = &opponent->members[i];
        if (f->hp > 0) {
            printf("  %d) %s (%d/%d HP)\n", i + 1, f->name, f->hp, f->max_hp);
            printf("     o\n");
            printf("    /|\\\n");
            printf("    / \\\n\n");
        }
    }

    // Get valid target choice from user
    int choice;
    do {
        printf("> ");
        choice = read_int();
        if (choice < 1 || choice > opponent->member_count || opponent->members[choice - 1].hp <= 0) {
            printf("Invalid choice. Please select a valid target.\n");
        }
    } while (choice < 1 || choice > opponent->member_count || opponent->members[choice - 1].hp <= 0);

    return choice - 1; // Return target index
}

// Action of a human player
void fighter_action(Fighter *player, Team *opponent) {
    // Skip turn if fighter is KO
    if (player->hp <= 0) return;

    // Display available actions
    printf("Turn of %s (HP: %d)\n", player->name, player->hp);
    printf("1. Basic Attack\n");
    for (int i = 0; i < MAX_TECH; i++) {
        printf("%d. %s [Cooldown: %d turns]\n", i + 2, player->tech[i].name, player->tech[i].cooldown_remaining);
    }

    // Get valid action choice from user
    int choice;
    do {
        printf("Choice: ");
        choice = read_int();
        if (choice < 1 || choice > MAX_TECH + 1) {
            printf("Invalid choice. Please select a valid action (1-%d).\n", MAX_TECH + 1);
        }
    } while (choice < 1 || choice > MAX_TECH + 1);

    // Check if there is at least one living fighter in the opposing team
    int has_valid_target = 0;
    for (int i = 0; i < opponent->member_count; i++) {
        if (opponent->members[i].hp > 0) {
            has_valid_target = 1;
            break;
        }
    }
    
    // Skip action if no valid targets available
    if (!has_valid_target) {
        printf("No valid targets available!\n");
        return;
    }

    // Get target and process action
    int target = choose_target(opponent);
    Fighter *target_fighter = &opponent->members[target];

    if (choice == 1) { // Basic attack
        // Calculate damage based on attacker's attack and defender's defense
        int damage = player->attack - (target_fighter->defense / 2);
        
        // Dodge mechanic: check if target can dodge based on speed
        int dodge = rand() % 10;
        if (dodge <= target_fighter->speed) {  // Dodge chance based on speed
            damage = 0;
            printf("\u2192 %s dodged the attack!\n", target_fighter->name);
        } else {
            // Ensure damage is never negative
            if (damage < 0) damage = 0;
            
            // Apply damage and ensure HP doesn't go below 0
            target_fighter->hp -= damage;
            if (target_fighter->hp < 0) target_fighter->hp = 0;
            
            // Display attack result
            printf("\u2192 %s attacks %s and deals %d damage! (%d HP left)\n", 
                   player->name, target_fighter->name, damage, target_fighter->hp);
        }
    } else if (choice == 2 || choice == 3) { // Technique usage
        int idx = choice - 2;
        Technique *t = &player->tech[idx];
        
        // Check if technique is on cooldown
        if (t->cooldown_remaining > 0) {
            printf("\u2192 Technique on cooldown! Action lost...\n");
        } else {
            // Process different technique effects
            if (strcmp(t->effect, "attack") == 0) {
                // Apply damage technique (ignores defense)
                target_fighter->hp -= t->value;
                if (target_fighter->hp < 0) target_fighter->hp = 0;
                printf("\u2192 %s uses %s on %s: %d damage! (%d HP left)\n", 
                       player->name, t->name, target_fighter->name, t->value, target_fighter->hp);
            } else if (strcmp(t->effect, "heal") == 0) {
                // Apply healing technique
                player->hp += t->value;
                if (player->hp > player->max_hp) player->hp = player->max_hp;
                printf("\u2192 %s heals with %s: +%d HP (%d/%d)\n", 
                       player->name, t->name, t->value, player->hp, player->max_hp);
            }
            // Reset technique cooldown
            t->cooldown_remaining = t->cooldown;
        }
    }

    // Update all cooldowns at the end of turn
    for (int i = 0; i < MAX_TECH; i++) {
        if (player->tech[i].cooldown_remaining > 0) player->tech[i].cooldown_remaining--;
    }
}

// Action of an AI fighter
void fighter_action_ai(Fighter *ai, Team *opponent) {
    // Skip turn if fighter is KO
    if (ai->hp <= 0) return;
    
    // Check for valid targets
    int valid_targets = 0;
    for (int i = 0; i < opponent->member_count; i++) {
        if (opponent->members[i].hp > 0) {
            valid_targets++;
        }
    }
    
    // Skip turn if no valid targets
    if (valid_targets == 0) return;
    
    // Randomly select an action (0 = basic attack, 1,2 = techniques)
    int action = rand() % (MAX_TECH + 1);

    // Randomly select a target from the opposing team
    int target = rand() % opponent->member_count;
    int attempts = 0;
    
    // Keep trying to find a living target (avoid infinite loop)
    while (opponent->members[target].hp <= 0 && attempts < opponent->member_count * 2) {
        target = rand() % opponent->member_count;
        attempts++;
    }
    
    // Skip turn if no valid target found after multiple attempts
    if (opponent->members[target].hp <= 0) return;

    Fighter *target_fighter = &opponent->members[target];

    if (action == 0) { // Basic attack
        // Calculate damage based on attacker's attack and defender's defense
        int damage = ai->attack - (target_fighter->defense / 2);
        
        // Dodge mechanic for AI attacks too
        int dodge = rand() % 10;
        if (dodge <= target_fighter->speed) {
            damage = 0;
            printf("\u2192 %s dodged the attack from %s (AI)!\n", 
                   target_fighter->name, ai->name);
        } else {
            // Ensure damage is never negative
            if (damage < 0) damage = 0;
            
            // Apply damage and ensure HP doesn't go below 0
            target_fighter->hp -= damage;
            if (target_fighter->hp < 0) target_fighter->hp = 0;
            
            // Display attack result
            printf("\u2192 %s (AI) attacks %s and deals %d damage! (%d HP left)\n", 
                   ai->name, target_fighter->name, damage, target_fighter->hp);
        }
    } else { // Technique usage
        int idx = action - 1;
        Technique *t = &ai->tech[idx];
        
        // Check if technique is available (not on cooldown)
        if (t->cooldown_remaining == 0) {
            // Process different technique effects
            if (strcmp(t->effect, "attack") == 0) {
                // Apply damage technique (ignores defense and dodge)
                target_fighter->hp -= t->value;
                if (target_fighter->hp < 0) target_fighter->hp = 0;
                printf("\u2192 %s (AI) uses %s on %s: %d damage! (%d HP left)\n", 
                       ai->name, t->name, target_fighter->name, t->value, target_fighter->hp);
            } else if (strcmp(t->effect, "heal") == 0) {
                // Apply healing technique
                ai->hp += t->value;
                if (ai->hp > ai->max_hp) ai->hp = ai->max_hp;
                printf("\u2192 %s (AI) heals with %s: +%d HP (%d/%d)\n", 
                       ai->name, t->name, t->value, ai->hp, ai->max_hp);
            }
            // Reset technique cooldown
            t->cooldown_remaining = t->cooldown;
        } else {
            // If technique on cooldown, use basic attack instead (avoids stack overflow from recursion)
            int damage = ai->attack - (target_fighter->defense / 2);
            
            // Apply dodge mechanic for fallback attack too
            int dodge = rand() % 10;
            if (dodge <= target_fighter->speed / 10) {
                damage = 0;
                printf("\u2192 %s dodged the attack from %s (AI)!\n", 
                       target_fighter->name, ai->name);
            } else {
                // Ensure damage is never negative
                if (damage < 0) damage = 0;
                
                // Apply damage and ensure HP doesn't go below 0
                target_fighter->hp -= damage;
                if (target_fighter->hp < 0) target_fighter->hp = 0;
                
                // Display attack result
                printf("\u2192 %s (AI) attacks %s and deals %d damage! (%d HP left)\n", 
                       ai->name, target_fighter->name, damage, target_fighter->hp);
            }
        }
    }

    // Update all cooldowns at the end of turn
    for (int i = 0; i < MAX_TECH; i++) {
        if (ai->tech[i].cooldown_remaining > 0) ai->tech[i].cooldown_remaining--;
    }
}

// Complete tour of a team
void team_turn(Team *player, Team *opponent, int ai_control) {
    // Process turn for each team member in order
    for (int i = 0; i < player->member_count; i++) {
        // End turn early if all opponents are defeated
        if (is_team_KO(*opponent)) return;
        
        // Skip KO fighters
        if (player->members[i].hp <= 0) continue;
        
        // Process action based on control type
        if (ai_control) {
            fighter_action_ai(&player->members[i], opponent);
        } else {
            fighter_action(&player->members[i], opponent);
        }
    }
}