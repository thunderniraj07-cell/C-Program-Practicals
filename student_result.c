#include <stdio.h>
#include <stdlib.h>

#define MAX 50
#define FILENAME "students.txt"

struct Student
{
    int roll;
    char name[50];
    float marks[3];
    float total, average;
    char grade;
};

/* Reads a number; stops the program if the input is not a number */
float readNumber(void)
{
    float x;
    if (scanf("%f", &x) != 1)
    {
        printf("\nInvalid input. Program closed.\n");
        exit(1);
    }
    return x;
}

void calculateResult(struct Student *s)
{
    int i, pass = 1;
    s->total = 0;
    for (i = 0; i < 3; i++)
    {
        s->total += s->marks[i];
        if (s->marks[i] < 40)
            pass = 0;
    }
    s->average = s->total / 3;

    if (!pass)                    s->grade = 'F';
    else if (s->average >= 75) s->grade = 'A';
    else if (s->average >= 60) s->grade = 'B';
    else if (s->average >= 50) s->grade = 'C';
    else                          s->grade = 'D';
}

struct Student *findStudent(struct Student *s, int n, int roll)
{
    int i;
    for (i = 0; i < n; i++)
        if ((s + i)->roll == roll)
            return s + i;
    return NULL;
}

void addStudent(struct Student *s, int *n)
{
    struct Student *p = s + *n;
    int i, roll;

    if (*n >= MAX)
    {
        printf("Record list is full.\n");
        return;
    }
    printf("Enter roll number: ");
    roll = (int)readNumber();
    if (findStudent(s, *n, roll) != NULL)
    {
        printf("Roll number already exists.\n");
        return;
    }
    p->roll = roll;
    printf("Enter name: ");
    scanf(" %49[^\n]", p->name);
    for (i = 0; i < 3; i++)
    {
        do
        {
            printf("Enter marks of subject %d (0-100): ", i + 1);
            p->marks[i] = readNumber();
        } while (p->marks[i] < 0 || p->marks[i] > 100);
    }
    calculateResult(p);
    (*n)++;
    printf("Record added.\n");
}

void printStudent(const struct Student *s)
{
    printf("%-6d %-20s %6.1f %6.1f %6.1f %7.1f %7.2f %5c\n",
           s->roll, s->name, s->marks[0], s->marks[1], s->marks[2],
           s->total, s->average, s->grade);
}

void printHeader(void)
{
    printf("\n%-6s %-20s %6s %6s %6s %7s %7s %5s\n",
           "Roll", "Name", "Sub1", "Sub2", "Sub3", "Total", "Avg", "Grade");
}

void displayAll(const struct Student *s, int n)
{
    int i;
    if (n == 0)
    {
        printf("No records found.\n");
        return;
    }
    printHeader();
    for (i = 0; i < n; i++)
        printStudent(s + i);
}

void searchStudent(struct Student *s, int n)
{
    struct Student *p;
    printf("Enter roll number to search: ");
    p = findStudent(s, n, (int)readNumber());
    if (p == NULL)
        printf("Student not found.\n");
    else
    {
        printHeader();
        printStudent(p);
    }
}

void showTopper(const struct Student *s, int n)
{
    const struct Student *top = s;
    int i;
    if (n == 0)
    {
        printf("No records found.\n");
        return;
    }
    for (i = 1; i < n; i++)
        if ((s + i)->average > top->average)
            top = s + i;
    printHeader();
    printStudent(top);
}

void saveToFile(const struct Student *s, int n)
{
    int i;
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }
    for (i = 0; i < n; i++)
        fprintf(fp, "%d|%s|%.2f|%.2f|%.2f\n", s[i].roll, s[i].name,
                s[i].marks[0], s[i].marks[1], s[i].marks[2]);
    fclose(fp);
    printf("%d record(s) saved to %s\n", n, FILENAME);
}

void loadFromFile(struct Student *s, int *n)
{
    struct Student t;
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
        return;
    while (*n < MAX && fscanf(fp, "%d|%49[^|]|%f|%f|%f", &t.roll, t.name,
           &t.marks[0], &t.marks[1], &t.marks[2]) == 5)
    {
        calculateResult(&t);
        s[(*n)++] = t;
    }
    fclose(fp);
}

void retrieveFromFile(void)
{
    struct Student temp[MAX];
    int count = 0;
    loadFromFile(temp, &count);
    printf("\nRecords retrieved from %s:\n", FILENAME);
    displayAll(temp, count);
}

int main()
{
    struct Student s[MAX];
    int n = 0, choice;

    loadFromFile(s, &n);

    do
    {
        printf("\n--- Student Record and Result Management ---\n");
        printf("1. Add Student\n2. Display All\n3. Search by Roll Number\n");
        printf("4. Show Topper\n5. Save to File\n6. Retrieve from File and Display\n7. Save and Exit\n");
        printf("Enter choice: ");
        choice = (int)readNumber();

        switch (choice)
        {
        case 1: addStudent(s, &n);    break;
        case 2: displayAll(s, n);     break;
        case 3: searchStudent(s, n);  break;
        case 4: showTopper(s, n);     break;
        case 5: saveToFile(s, n);     break;
        case 6: retrieveFromFile();   break;
        case 7: saveToFile(s, n);     break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}
