#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

typedef struct {
    char label[MAX_LENGTH];
    int line_number;
} Label;

void trimming_spaces(char *str) {
    char *start = str;
    while (*start == ' ') start++;

    
    char *comment = strstr(start, "//");  //It will find the "//" string
    if (comment) {
        *comment = '\0';
    }

    memmove(str, start, strlen(start) + 1);  // it will shift the trimmed string to left
}

void replaceLabelWithOffset(char *line, int current_line, Label labels[], int label_count) {
    char opcode[MAX_LENGTH], operand[MAX_LENGTH];

    if (sscanf(line, "%s %s", opcode, operand) == 2) {  //This line checks the wheather the instruction have one operand
        for (int i = 0; i < label_count; i++) {
            if (strcmp(operand, labels[i].label) == 0) {
                int offset = labels[i].line_number - current_line;
                sprintf(line, "%s %d\n", opcode, offset);  // It will replace operand with offset
                return;
            }
        }
    }
}

int readFileAndStoreLabels(const char *filename, Label labels[], int *label_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    char buffer[MAX_LENGTH];
    int line_number = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        trimming_spaces(buffer);
        if (strlen(buffer) == 0) continue;  // This line skip empty lines after trimming

        char *colon = strchr(buffer, ':'); // this line finds the ":" character in string
        if (colon) {
            *colon = '\0';
            strcpy(labels[*label_count].label, buffer);
            labels[*label_count].line_number = line_number;
            (*label_count)++;
        }
        line_number++;
    }

    fclose(file);
    return 0;
}

void removeLabelsAndProcessFile(const char *filename, char *output_buffer, Label labels[], int label_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    char buffer[MAX_LENGTH];
    char temp_buffer[MAX_LENGTH * MAX_LINES] = "";
    int line_number = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        trimming_spaces(buffer);
        if (strlen(buffer) == 0) continue; 
        char *colon = strchr(buffer, ':');
        if (colon) {
            memmove(buffer, colon + 1, strlen(colon + 1) + 1);
            trimming_spaces(buffer);
        }

        replaceLabelWithOffset(buffer, line_number, labels, label_count);
        
        
        if (buffer[strlen(buffer) - 1] != '\n') {
            strcat(buffer, "\n");
        }

        strcat(temp_buffer, buffer);
        line_number++;
    }

    fclose(file);
    strcpy(output_buffer, temp_buffer);
}

int main() {
    const char *input_filename = "input.asm";
    char output_buffer[1024];

    Label labels[MAX_LINES];
    int label_count = 0;

    if (readFileAndStoreLabels(input_filename, labels, &label_count) != 0) {
        return 1;
    }

    removeLabelsAndProcessFile(input_filename, output_buffer, labels, label_count);

    printf("\nModified content (with labels removed and offsets applied):\n");

    FILE *file = fopen("output.asm", "w");  // Opening file in write mode
    if (file == NULL) {
        perror("Error opening file for writing");
        return 0;
    }

    // Writing content to the file
    fprintf(file, "%s", output_buffer);

    // Close the file afer writing
    fclose(file);

    return 0;
}