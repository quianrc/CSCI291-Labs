#include <stdio.h>
#include <ctype.h>
#include <string.h>
// Validate name: printable, non-numeric, non-empty
int isValidName(char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isprint(name[i])) return 0;   // must be printable
        if (isdigit(name[i])) return 0;    // cannot contain digits
    }
    return 1;
}
int main() {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) {
        printf("Error: Could not open file students.txt\n");
        return 1;
    }
    char name[100];
    char markStr[100];
    int validCount = 0, corruptedCount = 0;
    int totalMarks = 0;
    printf("Reading records...\n\n");
    // Read two strings: name and mark candidate
    while (fscanf(fp, "%s %s", name, markStr) != EOF) 
    {
        int mark;
        int markValid = 1;
        
        if (sscanf(markStr, "%d", &mark) != 1) {
            markValid = 0;
        }
        // Validate name and mark
        if (isValidName(name) && markValid) {
            printf("VALID: %-10s %d\n", name, mark);
            validCount++;
            totalMarks += mark;
        } 
        else {
            printf("CORRUPTED: %-10s %-10s\n", name, markStr);
            corruptedCount++;
        }
    }
    printf("\n--- SUMMARY ---\n");
    printf("Valid records: %d\n", validCount);
    printf("Corrupted records: %d\n", corruptedCount);
    if (validCount > 0)
        printf("Average mark: %.2f\n", (float)totalMarks / validCount);
    else
        printf("Average mark: N/A\n");
    fclose(fp);
    return 0;
}
