#include <stdio.h>
#include <string.h>

#define numOfSubjects 3
#define numOfStudents 5

// Define struct for a student
typedef struct {
    char firstName[30];
    char lastName[30];
    int studentID;
    float subjectMarks[numOfSubjects];
    float aggregateMarks;
    char grade[15];
} student_t;

// Function prototypes
void enrol(student_t students[], int index);
void calcGrade(student_t *stu);
void topStudents(student_t students[], int count);
void searchUpdate(student_t students[], int count);

// --- MAIN ---
int main() {
    student_t students[numOfStudents] = {0};
    int count = 0;
    char choice;

    do {
        printf("\n--- Year 2 Student Records ---\n");
        printf("a) Enrol a new student\n");
        printf("b) Search & update student\n");
        printf("c) Show top student(s)\n");
        printf("d) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        if (choice == 'a' || choice == 'A') {
            if (count < numOfStudents) {
                enrol(students, count);
                count++;
            } else {
                printf("Student list is full!\n");
            }
        }
        else if (choice == 'b' || choice == 'B') {
            searchUpdate(students, count);
        }
        else if (choice == 'c' || choice == 'C') {
            topStudents(students, count);
        }
        else if (choice == 'd' || choice == 'D') {
            printf("Exiting program...\n");
        }
        else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 'd' && choice != 'D');

    return 0;
}

// --- ENROL FUNCTION ---
void enrol(student_t students[], int index) {
    printf("\nEnter First Name: ");
    scanf("%s", students[index].firstName);
    printf("Enter Last Name: ");
    scanf("%s", students[index].lastName);
    printf("Enter Student ID: ");
    scanf("%d", &students[index].studentID);

    int allEntered = 1;
    for (int i = 0; i < numOfSubjects; i++) {
        char ans;
        printf("Do you want to enter mark for Subject %d? (y/n): ", i + 1);
        scanf(" %c", &ans);
        if (ans == 'y' || ans == 'Y') {
            printf("Enter mark: ");
            scanf("%f", &students[index].subjectMarks[i]);
        } else {
            students[index].subjectMarks[i] = -1;
            allEntered = 0;
        }
    }

    if (allEntered)
        calcGrade(&students[index]);
    else {
        students[index].aggregateMarks = -1;
        strcpy(students[index].grade, "undefined");
    }

    printf("Student enrolled successfully!\n");
}

// --- CALCULATE GRADE FUNCTION ---
void calcGrade(student_t *stu) {
    float total = 0;
    for (int i = 0; i < numOfSubjects; i++)
        total += stu->subjectMarks[i];
    stu->aggregateMarks = total / numOfSubjects;

    float mark = stu->aggregateMarks;
    if (mark >= 85) strcpy(stu->grade, "HD");
    else if (mark >= 75) strcpy(stu->grade, "D");
    else if (mark >= 65) strcpy(stu->grade, "C");
    else if (mark >= 50) strcpy(stu->grade, "P");
    else strcpy(stu->grade, "F");
}

// --- TOP STUDENTS FUNCTION ---
void topStudents(student_t students[], int count) {
    if (count == 0) {
        printf("No students enrolled yet.\n");
        return;
    }

    float highest = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].aggregateMarks > highest)
            highest = students[i].aggregateMarks;
    }

    if (highest == -1) {
        printf("No valid aggregate marks to compare.\n");
        return;
    }

    printf("\n--- Top Student(s) ---\n");
    for (int i = 0; i < count; i++) {
        if (students[i].aggregateMarks == highest) {
            printf("Name: %s %s\n", students[i].firstName, students[i].lastName);
            printf("Student ID: %d\n", students[i].studentID);
            printf("Aggregate: %.2f\n", students[i].aggregateMarks);
            printf("Grade: %s\n\n", students[i].grade);
        }
    }
}

// --- SEARCH & UPDATE FUNCTION ---
void searchUpdate(student_t students[], int count) {
    if (count == 0) {
        printf("No students enrolled yet.\n");
        return;
    }

    char choice;
    printf("Search by ID or Last Name? (i/l): ");
    scanf(" %c", &choice);

    int found = 0;

    if (choice == 'i' || choice == 'I') {
        int id;
        printf("Enter Student ID: ");
        scanf("%d", &id);

        for (int i = 0; i < count; i++) {
            if (students[i].studentID == id) {
                found = 1;

                // Display student details
                printf("\nStudent found: %s %s\n", students[i].firstName, students[i].lastName);
                printf("Student ID: %d\n", students[i].studentID);
                printf("Subject Marks:\n");
                for (int j = 0; j < numOfSubjects; j++) {
                    if (students[i].subjectMarks[j] != -1)
                        printf("  Subject %d: %.2f\n", j + 1, students[i].subjectMarks[j]);
                    else
                        printf("  Subject %d: Not entered\n", j + 1);
                }
                if (students[i].aggregateMarks != -1)
                    printf("Final Grade: %s (%.2f)\n", students[i].grade, students[i].aggregateMarks);
                else
                    printf("Final Grade: undefined\n");

                // Update process
                char ans;
                printf("Update First Name? (y/n): ");
                scanf(" %c", &ans);
                if (ans == 'y' || ans == 'Y') scanf("%s", students[i].firstName);

                printf("Update Last Name? (y/n): ");
                scanf(" %c", &ans);
                if (ans == 'y' || ans == 'Y') scanf("%s", students[i].lastName);

                for (int j = 0; j < numOfSubjects; j++) {
                    printf("Update mark for Subject %d? (y/n): ", j + 1);
                    scanf(" %c", &ans);
                    if (ans == 'y' || ans == 'Y') {
                        printf("Enter new mark: ");
                        scanf("%f", &students[i].subjectMarks[j]);
                    }
                }

                // Recalculate grade
                int allEntered = 1;
                for (int j = 0; j < numOfSubjects; j++)
                    if (students[i].subjectMarks[j] == -1) allEntered = 0;

                if (allEntered) calcGrade(&students[i]);
                else {
                    students[i].aggregateMarks = -1;
                    strcpy(students[i].grade, "undefined");
                }

                printf("Student record updated.\n");
                break;
            }
        }
    }
    else if (choice == 'l' || choice == 'L') {
        char lastName[30];
        printf("Enter Last Name: ");
        scanf("%s", lastName);

        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].lastName, lastName) == 0) {
                found = 1;

                // Display student details
                printf("\nStudent found: %s %s\n", students[i].firstName, students[i].lastName);
                printf("Student ID: %d\n", students[i].studentID);
                printf("Subject Marks:\n");
                for (int j = 0; j < numOfSubjects; j++) {
                    if (students[i].subjectMarks[j] != -1)
                        printf("  Subject %d: %.2f\n", j + 1, students[i].subjectMarks[j]);
                    else
                        printf("  Subject %d: Not entered\n", j + 1);
                }
                if (students[i].aggregateMarks != -1)
                    printf("Final Grade: %s (%.2f)\n", students[i].grade, students[i].aggregateMarks);
                else
                    printf("Final Grade: undefined\n");

                // Update process
                char ans;
                printf("Update First Name? (y/n): ");
                scanf(" %c", &ans);
                if (ans == 'y' || ans == 'Y') scanf("%s", students[i].firstName);

                printf("Update Last Name? (y/n): ");
                scanf(" %c", &ans);
                if (ans == 'y' || ans == 'Y') scanf("%s", students[i].lastName);

                for (int j = 0; j < numOfSubjects; j++) {
                    printf("Update mark for Subject %d? (y/n): ", j + 1);
                    scanf(" %c", &ans);
                    if (ans == 'y' || ans == 'Y') {
                        printf("Enter new mark: ");
                        scanf("%f", &students[i].subjectMarks[j]);
                    }
                }

                // Recalculate grade
                int allEntered = 1;
                for (int j = 0; j < numOfSubjects; j++)
                    if (students[i].subjectMarks[j] == -1) allEntered = 0;

                if (allEntered) calcGrade(&students[i]);
                else {
                    students[i].aggregateMarks = -1;
                    strcpy(students[i].grade, "undefined");
                }

                printf("Student record updated.\n");
            }
        }
    }

    if (!found) printf("No student found.\n");
}
