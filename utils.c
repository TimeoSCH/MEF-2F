

// Clears the remaining characters in the input buffer (stdin)
void clear_input_buffer() {
    int c;
    // Read characters one by one until a newline or end-of-file is found
    while ((c = getchar()) != '\n' && c != EOF);
}

// Reads an integer from the user with basic error handling
int read_int() {
    char buffer[BUFFER_SIZE];  // Temporary buffer to store user input
    int value;                 // Variable to store the integer value

    // Read a line from stdin into the buffer
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        return -1;  // Return -1 if input reading fails
    }

    // Try to extract an integer from the buffer
    if (sscanf(buffer, "%d", &value) != 1) {
        return -1;  // Return -1 if no valid integer was found
    }

    return value;  // Return the valid integer
}

// Reads a string from the user with a size limit
void read_string(char *str, int max_length) {
    char buffer[BUFFER_SIZE];  // Temporary buffer to store user input

    // Read a line from stdin into the buffer
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        str[0] = '\0';  // If reading fails, set str to an empty string
        return;
    }

    // Remove the newline character from the buffer, if present
    buffer[strcspn(buffer, "\n")] = '\0';

    // Copy up to max_length characters from buffer to str
    strncpy(str, buffer, max_length);

    // Make sure the string is null-terminated
    str[max_length] = '\0';
}
