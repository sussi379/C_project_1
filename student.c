
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

void main_menu();
void choice();
int add_stu();
void view_stu();
void search_stu();
void search_ID_toEdit();
int edit_stu(int ID);

//file saving functions
void check_and_create_file();
void save_to_file();
void load_from_file(); // text prasing
int StudentCount = 0;

struct Student {
    int ID;
    char *name;
    int gender;
    int year_of_birth;
    int day_of_birth;
    int month_of_birth;
    char *father_name;
    char *mother_name;
    char class;
};
struct Student *students = NULL;

int main() {
    system("clear");
    check_and_create_file();
    load_from_file();
    sleep(1);
    choice();
    free(students);
    students = NULL;
    system("clear");
    return 0;
}

void check_and_create_file() {
    system("clear");
    FILE *pFile = fopen("students.csv", "r");

    if(pFile == NULL) {
        // check if file exist or not
        printf("No save file found. Creating new one ...\n");

        pFile = fopen("students.csv", "w");
        if(pFile == NULL) {
            printf("ERROR: Could not create file\n");
            return;
        }
        fclose(pFile);
    } else {
        printf("File found! Loading data...\n");
        fclose(pFile);
    }
}
void save_to_file() {
    FILE *pFile = fopen("students.csv", "w");

    if(pFile == NULL) {
        printf("ERROR: Could not save file!\n");
        return;
    }

    for(int i = 0; i < StudentCount; i++) {
        fprintf(pFile, "%d|%s|%d|%d|%d|%d|%s|%s|%c\n",
            students[i].ID,
            students[i].name,
            students[i].gender,
            students[i].day_of_birth,
            students[i].month_of_birth,
            students[i].year_of_birth,
            students[i].father_name,
            students[i].mother_name,
            students[i].class);
    }
    fclose(pFile);
    //printf("\nData saved!! There are %d students\n", StudentCount);
}
void load_from_file() {
    FILE *pFile = fopen("students.csv", "r");

    if(pFile == NULL) {
        printf("ERROR: Could not load file!\n");
        return;
    }

    char line[500];
    int count = 0;

    while(fgets(line, sizeof(line), pFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        count ++;
        StudentCount = count;
        students = realloc(students, count * sizeof(struct Student));
        int index = count - 1;

        char *token = strtok(line, "|");
        int field = 0;

        while(token != NULL) {
            switch(field) {
                case 0:
                    students[index].ID = atoi(token);
                    break;
                case 1:
                    students[index].name = malloc(strlen(token) + 1);
                    strcpy(students[index].name, token);
                    break;
                case 2:
                    students[index].gender = atoi(token);
                    break;
                case 3:
                    students[index].day_of_birth = atoi(token);
                    break;
                case 4:
                    students[index].month_of_birth = atoi(token);
                    break;
                case 5:
                    students[index].year_of_birth = atoi(token);
                    break;
                case 6:
                    students[index].father_name = malloc(strlen(token) + 1);
                    strcpy(students[index].father_name, token);
                    break;
                case 7:
                    students[index].mother_name = malloc(strlen(token) + 1);
                    strcpy(students[index].mother_name, token);
                    break;
                case 8:
                    students[index].class = token[0];
                    break;
            }
            field++;
            token = strtok(NULL, "|");
        }

    }
     fclose(pFile);

}

void main_menu() {
    printf("***Student list***\n\n");
    printf("1. Add student\n");
    printf("2. View all students\n");
    printf("3. Search student\n");
    printf("4. Edit Student data\n");
    printf("5. Exit\n\n");
    printf("\n%d Students are in the data base\n\n", StudentCount);
    printf("Enter your option (1-5) : ");
}
void choice() {
    system("clear");
    bool isRunning = true;
    while(isRunning) {
        system("clear");
        main_menu();
        char input[10];
        int choice = 0;

        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1 ] = '\0';

        int result = sscanf(input, "%d", &choice);

        if(result == 0 ||choice > 5 || choice <= 0) {
            printf("\nOption not valid!\n");
            sleep(1);
            system("clear");
        }

        switch (choice) {
            case 1:
                add_stu();
                break;
            case 2:
                view_stu();
                break;
            case 3:
                search_stu();
                break;
            case 4:
                search_ID_toEdit();
                break;
            case 5:
                isRunning = false;
                break;
        }
    }
}
int add_stu() {

    system("clear");
    int count = 0;
    bool isRunning = true;


    while(isRunning) {
        system("clear");
        StudentCount ++;
        students = realloc(students, StudentCount * sizeof(struct Student));

        //name input
        students[StudentCount - 1].ID = 100+StudentCount;
        int id = students[StudentCount - 1].ID;
        printf("Enter the informations below\n\n");
        printf("Student ID : %d\n\n", id);

        char temp[100];
        printf("Enter student name\n\n>> ");
        fgets(temp, sizeof(temp), stdin);
        temp[strlen(temp) - 1 ] = '\0';
        if(strcmp(temp, "quit") == 0) {
            printf("Stopping....\n");
            StudentCount --;
            isRunning = false;
        }
        system("clear");
        students[StudentCount - 1].name = malloc(strlen(temp) + 1);
        strcpy(students[StudentCount - 1].name, temp);
        strcpy(temp, ""); // removing the temp name for new input
        //name input

        do{
            printf("Enter the informations below\n\n");
            printf("Student ID %d\n\n", id);
            printf("Male or Female? ( 1 or 2)\n\n>> ");
            scanf("%d", &students[StudentCount - 1 ].gender);
            while(getchar() != '\n');

            if(students[StudentCount - 1 ].gender < 1 ||students[StudentCount - 1 ].gender > 2) {
                system("clear");
                printf("*** INVALID GENDER! ***\n");
            }
        }while(students[StudentCount - 1 ].gender < 1 ||students[StudentCount - 1 ].gender > 2);
        system("clear");

        do{
            printf("Enter the informations below\n\n");
            printf("Student ID %d\n\n", id);
            printf("Enter the date of birth\n\n>> ");
            scanf("%d", &students[StudentCount - 1 ].day_of_birth);
            while(getchar() != '\n');

            if(students[StudentCount - 1 ].day_of_birth < 0 ||students[StudentCount - 1 ].day_of_birth > 31) {
                system("clear");
                printf("*** INVALID DATE! ***\n");
            }
        }while(students[StudentCount - 1 ].day_of_birth < 0 ||students[StudentCount - 1 ].day_of_birth > 31);
        system("clear");

        do {
            printf("Enter the informations below\n\n");
            printf("Student ID %d\n\n", id);
            printf("Enter the month of birth\n\n>> ");
            scanf("%d", &students[StudentCount - 1 ].month_of_birth);
            while(getchar() != '\n');

            if(students[StudentCount - 1 ].month_of_birth< 0 ||students[StudentCount - 1 ].month_of_birth > 12) {
                system("clear");
                printf("*** INVALID MONTH! ***\n\n");
            }
        }while(students[StudentCount - 1 ].month_of_birth< 0 ||students[StudentCount - 1 ].month_of_birth > 12);
        system("clear");

        printf("Enter the informations below\n\n");
        printf("Student ID %d\n\n", id);
        printf("Enter the year of birth\n\n>>  ");
        scanf("%d", &students[StudentCount - 1 ].year_of_birth);
        while(getchar() != '\n');
        system("clear");

        // father name input
        printf("Enter the informations below\n\n");
        printf("Student ID %d\n\n", id);
        printf("Enter father's name\n\n>> ");
        fgets(temp, sizeof(temp), stdin);
        temp[strlen(temp) - 1 ] = '\0';
        system("clear");

        students[StudentCount - 1].father_name = malloc(strlen(temp) + 1);
        strcpy(students[StudentCount -1].father_name, temp);
        strcpy(temp, ""); // removing the temp name for new input
        system("clear");
        // father name input

        // mother name input
        printf("Enter the informations below\n\n");
        printf("Student ID %d\n\n", id);
        printf("Enter mother's name\n\n>> ");
        fgets(temp, sizeof(temp), stdin);
        temp[strlen(temp) - 1 ] = '\0';

        students[StudentCount - 1].mother_name = malloc(strlen(temp) + 1);
        strcpy(students[StudentCount -1].mother_name, temp);
        strcpy(temp, ""); // removing the temp name for new input
        system("clear");
        // mother name input

        printf("Enter the informations below\n\n");
        printf("Student ID %d\n\n", id);
        printf("Enter the class (A-D)\n\n>> ");
        scanf(" %c", &students[StudentCount - 1].class);
        while(getchar() != '\n');
        system("clear");
        save_to_file();

        printf("ID : %d\n", students[StudentCount - 1].ID);
        printf("Name : %s\n", students[StudentCount - 1].name);

        if(students[StudentCount - 1].gender == 1) {
            printf("Gender : Male\n");
        }else {
            printf("Gender : Female\n");
        }
        printf("Date of birth : %d,%d,%d\n",
            students[StudentCount - 1].day_of_birth,
            students[StudentCount - 1].month_of_birth,
            students[StudentCount - 1].year_of_birth);
        printf("Father name : %s\n", students[StudentCount -1].father_name);
        printf("Mother name : %s\n", students[StudentCount- 1].mother_name);
        printf("Class : %c\n", students[StudentCount -1].class);


        printf("\nAdd another student? y/n : ");
        char input = '\0';
        scanf(" %c", &input);
        while(getchar() != '\n');
        if(input == 'n') {
            isRunning = false;
        }

    }
    system("clear");
    printf("Press any key to return....");
    getchar();
    return 0;
}
void view_stu() {


    system("clear");
    printf("___Student list___\n\n");
    for(int i = 0; i < StudentCount; i++) {

        printf("ID : %d\n", students[i].ID);
        printf("Name : %s\n", students[i].name);
        if(students[i].gender == 1) {
            printf("Gender : Male\n");
        }else {
            printf("Gender : Female\n");
        }
        printf("Date of birth : %d,%d,%d\n", students[i].day_of_birth, students[i].month_of_birth, students[i].year_of_birth);
        printf("Father name : %s\n", students[i].father_name);
        printf("Mother name : %s\n", students[i].mother_name);
        printf("Class : %c\n\n", students[i].class);
    }
    printf("\nPress any key to return...");
    getchar();
    return;
}
void search_stu() {
    system("clear");
    int input = 0;
    bool Return = true;
    bool isRunning = true;
    char quit = 'n';

    while(isRunning) {
        system("clear");
        printf("Enter student ID to search : ");
        scanf("%d", &input);
        while(getchar() != '\n');

        for(int i = 0; i < StudentCount; i++) {
            if(students[i].ID == input) {
                Return = true;
                break;
            } else {
                Return = false;
            }
        }

        if(Return) {
            system("clear");
            printf("Student found!!\n\n");
            printf("ID : %d\n", students[input - 101].ID);
            printf("Name : %s\n", students[input - 101].name);
            if(students[input - 101].gender == 1) {
                printf("Gender : Male\n");
            }else {
                printf("Gender : Female\n");
            }
            printf("Date of birth : %d,%d,%d\n", students[input - 101].day_of_birth, students[input - 101].month_of_birth, students[input - 101].year_of_birth);
            printf("Father name : %s\n", students[input - 101].father_name);
            printf("Mother name : %s\n", students[input - 101].mother_name);
            printf("Class : %c\n\n", students[input - 101].class);
            printf("Press any key to return....");
            getchar();

        } else if(Return == false) {
            system("clear");
            printf("Student NOT found!!!\n\n");
            printf("Press any key to return....");
            getchar();
        }
        system("clear");
        printf("Continue search or return to main menu? (y/n) : ");
        scanf(" %c", &quit);
        while(getchar() != '\n');
        if(quit == 'n') {
            return;
        }
    }

}
void search_ID_toEdit() {
    system("clear");
    bool isRunning = true;
    bool Return = true;
    int input = 0;
    while(isRunning) {
        system("clear");
        printf("Enter student ID to search (Enter 0 to quit): ");
        scanf("%d", &input);
        while(getchar() != '\n');
        if(input == 0) {return;}
        for(int i = 0; i < StudentCount; i++) {
            if(students[i].ID == input) {
                Return = true;
                break;
            } else {
                Return = false;
            }
        }

        if(Return) {
            system("clear");
            printf("Student found!!\n\n");
            printf("ID : %d\n", students[input - 101].ID);
            printf("Name : %s\n", students[input - 101].name);
            if(students[input - 101].gender == 1) {
                printf("Gender : Male\n");
            }else {
                printf("Gender : Female\n");
            }
            printf("Date of birth : %d,%d,%d\n", students[input - 101].day_of_birth, students[input - 101].month_of_birth, students[input - 101].year_of_birth);
            printf("Father name : %s\n", students[input - 101].father_name);
            printf("Mother name : %s\n", students[input - 101].mother_name);
            printf("Class : %c\n\n", students[input - 101].class);

            char Input = '\0';
            printf("Do you wanna edit this student? (y/n) : ");
            scanf(" %c", &Input);
            while(getchar() != '\n');
            if(Input == 'y') {
                edit_stu(input);
                return;
            }


        }
        else if(Return == false) {
            system("clear");
            printf("Student NOT found!!!\n\n");
            printf("Press any key to return....");
            getchar();
        }

    }
}
int edit_stu(int ID) {
    int index = ID - 101;
    system("clear");
    bool isRunning = true;
    char temp[100];
    int Edited = 0;
    while(isRunning) {

        char input[10];
        int choice = 0;
        system("clear");

        printf("What do you wanna edit?\n\n");
        printf("1. Name\n");
        printf("2. Gender\n");
        printf("3. Date of birth\n");
        printf("4. Month of birth\n");
        printf("5. Year of birth\n");
        printf("6. Father name\n");
        printf("7. Mother name\n");
        printf("8. Class\n");
        printf("9. Exit\n\n");

        printf("Enter your option (1-9) : ");

        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1 ] = '\0';

        int result = sscanf(input, "%d", &choice);

        if(result == 0 ||choice > 9 || choice <= 0) {
            printf("\nOption not valid!\n");
            sleep(1);
            system("clear");
        }

        switch (choice) {
            case 1: // ReEdit the name
                free(students[index].name);
                system("clear");
                printf("Enter the new name\n\n>> ");
                fgets(temp, sizeof(temp), stdin);
                temp[strlen(temp) - 1 ] = '\0';
                system("clear");
                students[index].name = malloc(strlen(temp) + 1);
                strcpy(students[index].name, temp);
                strcpy(temp, "");
                Edited = 1;
                system("clear");
                printf("Name changed successfully! Press any key to return....");
                getchar();
                break;
            case 2: // gender
                system("clear");
                printf("Male or Female? (1 or 2)\n\n>> ");
                scanf("%d", &students[index].gender);
                while(getchar() != '\n');
                Edited = 2;
                system("clear");
                printf("Gender changed successfully! Press any key to return....");
                getchar();
                break;
            case 3: // date
                system("clear");
                printf("Enter the new date\n\n>> ");
                scanf("%d", &students[index].day_of_birth);
                while(getchar() != '\n');
                Edited = 3;
                system("clear");
                printf("Day of birth changed successfully! Press any key to return....");
                getchar();
                break;
            case 4: // month
                system("clear");
                printf("Enter the new month\n\n>> ");
                scanf("%d", &students[index].month_of_birth);
                while(getchar() != '\n');
                Edited = 4;
                system("clear");
                printf("Month of birth changed successfully! Press any key to return....");
                getchar();
                break;
            case 5: // year
                system("clear");
                printf("Enter the new year\n\n>> ");
                scanf("%d", &students[index].year_of_birth);
                while(getchar() != '\n');
                Edited = 5;
                system("clear");
                printf("Year of birth changed successfully! Press any key to return....");
                getchar();
                break;
            case 6: // father name
                free(students[index].father_name);
                system("clear");
                printf("Enter the new father name\n\n>> ");
                fgets(temp, sizeof(temp), stdin);
                temp[strlen(temp) - 1 ] = '\0';
                system("clear");
                students[index].father_name = malloc(strlen(temp) + 1);
                strcpy(students[index].father_name, temp);
                strcpy(temp, "");
                Edited = 6;
                system("clear");
                printf("Father name changed successfully! Press any key to return....");
                getchar();
                break;
            case 7: // mother name
                free(students[index].mother_name);
                system("clear");
                printf("Enter the new mother name\n\n>> ");
                fgets(temp, sizeof(temp), stdin);
                temp[strlen(temp) - 1 ] = '\0';
                system("clear");
                students[index].mother_name = malloc(strlen(temp) + 1);
                strcpy(students[index].mother_name, temp);
                strcpy(temp, "");
                Edited = 7;
                system("clear");
                printf("Mother name changed successfully! Press any key to return....");
                getchar();
                break;
            case 8: // class
                system("clear");
                printf("Enter the class (A-D)\n\n>> ");
                scanf(" %c", &students[index].class);
                while(getchar() != '\n');
                Edited = 8;
                system("clear");
                printf("Class changed successfully! Press any key to return....");
                getchar();
                break;
            case 9: // quit
                isRunning = false;
                break;
        }

        if(Edited != 0 && choice == 9) {
            system("clear");
            char Input = '\0';
            do {
                printf("\nDo you actually wanna change the informations? (y/n) : ");
                scanf(" %c", &Input);
                while(getchar() != '\n');
                printf("\nData successfully updated!!\n\n");
                printf("Press any key to return...");
                getchar();
                break;
                return 0;

            }while(Input != 'n' && Input !='y');

            if(Input == 'y') {
                save_to_file();
            } else {

                for(int i = 0; i < StudentCount; i++) {
                    free(students[i].name);
                    free(students[i].father_name);
                    free(students[i].mother_name);
                }
                free(students);
                students = NULL;
                StudentCount = 0;
                load_from_file();
                break;
            }
        }

    }
    return 0;
}
