#include "shoro.h"

//////////////////////////////////////////////////////////////////////////////////////////////////calendar
char* calendar_message(int state) {
    return (state == 1) ? "enabled" : "disabled";
}

void admin_calendar(void) {
    if (term.id == -1) {
        printf("Enter new term id: ");
        scanf("%lld%*c", &term.id);
    } else {
        printf("Term %lld\n", term.id);
    }

    printf("1. offering: %s\n2. unit selection: %s\n3. class & exams: %s\n4. grade recording: %s\n5. go to main menu\nEnter a time to trigger: ",
        calendar_message(term.state[0]), calendar_message(term.state[1]),
        calendar_message(term.state[2]), calendar_message(term.state[3]));

    int option;
    scanf("%d%*c", &option);
    if (option == 5) return;

    option--; 
    if (option < 0 || option > 3) { printf("Not possible.\n"); admin_calendar(); return; }

    if (term.state[option] == 2) {
        printf("Not possible.\n");
    }
    else if (term.state[option] == 1) {
   
        if (option == 0 || term.state[option - 1] == 2) term.state[option] = 2;
        else printf("Not possible.\n");
    }
    else {
      
        if (option == 0 || term.state[option - 1] != 0) term.state[option] = 1;
        else printf("Not possible.\n");
    }

    admin_calendar();
}

//////////////////////////////////////////////////////////////////////////////////////////////////student

void search_student_menu(void) {
    printf("1. Search by first name\n2. Search by last name\n3. Search by student id\n4. back\nEnter an option: ");
    int option;
    scanf("%d%*c", &option);
    if (option == 4) return;

    Student* key;
    if (option == 3) {
        printf("Enter student id: ");
        ll studentId; scanf("%lld%*c", &studentId);
        key = creat_student(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0.0, studentId, 0, 0, 1, NULL, NULL, NULL);
    } else {
        printf("The phrase to search: ");
        char* line = NULL; size_t bufferSize = 0;
        getline(&line, &bufferSize, stdin);
        line[strcspn(line, "\r\n")] = '\0';
        if (option == 1)
            key = creat_student(line, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0.0, 0, 0, 0, 1, NULL, NULL, NULL);
        else
            key = creat_student(NULL, line, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0.0, 0, 0, 0, 1, NULL, NULL, NULL);
        free(line);
    }

    Student* found = search_student(headStudent, key);
    int count = 0;
    while (found != NULL) {
        print_student(found);
        count++;
        found = search_student(found->next, key);
    }
    if (count == 0) printf("No students found.\n");

    search_student_menu();
}

void student_list(void) {
    printf("Student List\n");
    printf("|first name |last name |student id |national code |field |entrance year |section |mentor |department| answer 1 | answer 2 | answer 3|\n");
    printf("|-----------|----------|-----------|--------------|------|--------------|--------|-------|----------|----------|----------|----------|\n");
    print_student_list(headStudent);

    printf("1. search\n2. go back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 1) search_student_menu();
}
//// name, last name, id, password, kodemeli, reshte, year, maghta, ostadrahnama, department, answer1, answer2, answe3
void register_student_menu(void) {
    printf("Register student(s)\n1. Register one student\n2. Register a group of students (import a file)\n3. back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 3) return;

    if (option == 1) {
        printf("Enter student info: ");
        char* line = NULL; size_t bufferSize = 0;
        getline(&line, &bufferSize, stdin);
        add_student(line);
        free(line);
    }
    else if (option == 2) {
        printf("Enter file name or address: ");
        char filename[256];
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\r\n")] = '\0';

        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Could not open that file.\n");
        } else {
            char* line = NULL; size_t bufferSize = 0; ssize_t nread;
            while ((nread = getline(&line, &bufferSize, fp)) != -1) {
                if (line[0] == '\n' || line[0] == '\0') continue;
                add_student(line);
            }
            free(line);
            fclose(fp);
        }
    }

    register_student_menu();
}

void remove_student_menu(void) {
    printf("Remove student(s)\nEnter student id: ");
    ll id; scanf("%lld%*c", &id);

    Student* key = creat_student(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0.0, id, 0, 0, 1, NULL, NULL, NULL);
    Student* ptr = search_student(headStudent, key);

    if (ptr == NULL) {
        printf("Student doesn't exist.\n");
        return;
    }

    print_student(ptr);
    printf("Remove student? [y/n] ");
    char ch; scanf(" %c%*c", &ch);
    if (ch == 'y' || ch == 'Y') {
        remove_student(ptr);
        printf("Done.\n");
    }
}

void admin_students(void) {
    printf("1. students list\n2. register student(s)\n3. remove student(s)\n4. back to admin dashboard\nEnter an option: ");
    int option; scanf("%d%*c", &option);

    if (option == 1) student_list();
    else if (option == 2) register_student_menu();
    else if (option == 3) remove_student_menu();
    else return;

    admin_students();
}

//////////////////////////////////////////////////////////////////////////////////////////////////faculity
void search_faculty_menu(void) {
    printf("1. Search by first name\n2. Search by last name\n3. Search by username\n4. back\nEnter an option: ");
    int option;
    scanf("%d%*c", &option);
    if (option == 4) return;

    Faculty* key;
    if (option == 3) {
        printf("Enter username: ");
        char* line = NULL; size_t bufferSize = 0;
        getline(&line, &bufferSize, stdin);
        line[strcspn(line, "\r\n")] = '\0';
        key = creat_faculty(NULL, NULL, NULL, NULL, NULL, line, 0, NULL, 1, NULL, NULL);
        free(line);
    } else {
        printf("The phrase to search: ");
        char* line = NULL; size_t bufferSize = 0;
        getline(&line, &bufferSize, stdin);
        line[strcspn(line, "\r\n")] = '\0';
        if (option == 1)
            key = creat_faculty(line, NULL, NULL, NULL, NULL, NULL, 0, NULL, 1, NULL, NULL);
        else
            key = creat_faculty(NULL, line, NULL, NULL, NULL, NULL, 0, NULL, 1, NULL, NULL);
        free(line);
    }

    Faculty* found = search_faculty(headFaculty, key);
    int count = 0;
    while (found != NULL) {
        print_faculty(found);
        count++;
        found = search_faculty(found->next, key);
    }
    if (count == 0) printf("No faculty members found.\n");

    search_faculty_menu();
}

void faculty_list(void) {
    printf("Faculty List\n");
    printf("|first name |last name |username |field |last degree |national code |department|\n");
    printf("|-----------|----------|---------|------|------------|--------------|----------|\n");
    print_faculty_list(headFaculty);

    printf("1. search\n2. go back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 1) search_faculty_menu();
}

void register_faculty_menu(void) {
    printf("Register faculty member(s)\n1. Register one faculty member\n2. Register a group (import a file)\n3. back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 3) return;

    if (option == 1) {
        printf("Enter faculty info: ");
        char* line = NULL; size_t bufferSize = 0;
        getline(&line, &bufferSize, stdin);
        add_faculty(line);
        free(line);
    }
    else if (option == 2) {
        printf("Enter file name or address: ");
        char filename[256];
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\r\n")] = '\0';

        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Could not open that file.\n");
        } else {
            char* line = NULL; size_t bufferSize = 0; ssize_t nread;
            while ((nread = getline(&line, &bufferSize, fp)) != -1) {
                if (line[0] == '\n' || line[0] == '\0') continue;
                add_faculty(line);
            }
            free(line);
            fclose(fp);
        }
    }

    register_faculty_menu();
}

void remove_faculty_menu(void) {
    printf("Remove faculty member(s)\nEnter username: ");
    char* username = NULL; size_t bufferSize = 0;
    getline(&username, &bufferSize, stdin);
    username[strcspn(username, "\r\n")] = '\0';

    Faculty* key = creat_faculty(NULL, NULL, NULL, NULL, NULL, username, 0, NULL, 1, NULL, NULL);
    Faculty* ptr = search_faculty(headFaculty, key);
    free(username);

    if (ptr == NULL) {
        printf("Faculty member doesn't exist.\n");
        return;
    }

    print_faculty(ptr);
    printf("Remove faculty member? [y/n] ");
    char ch; scanf(" %c%*c", &ch);
    if (ch == 'y' || ch == 'Y') {
        remove_faculty(ptr);
        printf("Done\n");
    }
}

void admin_faculty_members(void) {
    printf("1. faculty list\n2. register faculty member(s)\n3. remove faculty member(s)\n4. back to admin dashboard\nEnter an option: ");
    int option; scanf("%d%*c", &option);

    if (option == 1) faculty_list();
    else if (option == 2) register_faculty_menu();
    else if (option == 3) remove_faculty_menu();
    else return;

    admin_faculty_members();
}

//////////////////////////////////////////////////////////////////////////////////////////////////dashboard
void dashboard_admin(void) {
    printf("Admin dashboard:\nWelcome %s\n1. Calendar\n2. Students\n3. Faculty members\n4. Requests\n5. Offerings\n6. Courses\n7. Log out\nEnter an option: ",
        admin.username);

    int option; scanf("%d%*c", &option);
    if (option == 1) admin_calendar();
    else if (option == 2) admin_students();
    else if (option == 3) admin_faculty_members();
    else if (option == 4) admin_request();
    else if (option == 5) admin_offerings();
    else if (option == 6) admin_courses();
    else return;

    dashboard_admin();
}
