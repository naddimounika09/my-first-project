#include<stdio.h>
#include<stdlib.h>

struct Student
{
    int id;
    char name[50];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.txt", "a");

    printf("\nEnter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n",
            s.id, s.name, s.marks);

    fclose(fp);

    printf("\nStudent Added Successfully\n");
}

void viewStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo records found\n");
        return;
    }

    printf("\n===== STUDENT RECORDS =====\n");

    while(fscanf(fp, "%d %s %f",
          &s.id, s.name, &s.marks) != EOF)
    {
        printf("\nID: %d", s.id);
        printf("\nName: %s", s.name);
        printf("\nMarks: %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    FILE *fp;

    int id;
    int found = 0;

    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo records found\n");
        return;
    }

    while(fscanf(fp, "%d %s %f",
          &s.id, s.name, &s.marks) != EOF)
    {
        if(s.id == id)
        {
            found = 1;

            printf("\n===== STUDENT FOUND =====\n");

            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
        }
    }

    fclose(fp);

    if(found == 0)
    {
        printf("\nStudent Not Found\n");
    }
}

void deleteStudent()
{
    struct Student s;

    FILE *fp, *temp;

    int id;
    int found = 0;

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo records found\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    while(fscanf(fp, "%d %s %f",
          &s.id, s.name, &s.marks) != EOF)
    {
        if(s.id == id)
        {
            found = 1;
        }
        else
        {
            fprintf(temp, "%d %s %.2f\n",
                    s.id, s.name, s.marks);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found == 1)
    {
        printf("\nStudent Deleted Successfully\n");
    }
    else
    {
        printf("\nStudent Not Found\n");
    }
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n");
        printf("===== STUDENT MANAGEMENT SYSTEM =====\n");

        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                printf("\nThank You\n");
                exit(0);

            default:
                printf("\nInvalid Choice\n");
        }
    }

    return 0;
}