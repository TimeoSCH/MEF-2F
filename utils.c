#include "cy_fighters.h"
 
void clear_input_buffer() {    //clears the input buffe
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int read_int() {              //read an integer with error handling
    char buffer[BUFFER_SIZE];
    int value;
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        return -1;  
    }
    
    if (sscanf(buffer, "%d", &value) != 1) {
        return -1;  
    }
    
    return value;
}

void read_string(char *str, int max_length) {      //read a string with size limit
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        str[0] = '\0';  
        return;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    strncpy(str, buffer, max_length);
    str[max_length] = '\0';  

}