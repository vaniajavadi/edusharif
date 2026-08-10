#include "shoro.h"


ll get_student_username(void) {
    printf("Enter your username: ");
    ll username = 0;
    scanf("%lld%*c", &username);
    return username;
}


char* get_faculty_username(void) {
    printf("Enter your username: ");
    char* line = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    line[strcspn(line, "\r\n")] = '\0';
    return line;
}

char* get_password(void) {
    printf("Enter your password: ");
    char* line = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    line[strcspn(line, "\r\n")] = '\0';
    return line;
}

int wrong_username(void) {
    printf("Username not found.\n1. Retry\n2. Go to login menu\nEnter an option: ");
    int option = 2;
    scanf("%d%*c", &option);
    return option - 1;
}

int wrong_password(void) {
    printf("Incorrect password.\n1. Retry\n2. Go to login menu\nEnter an option: ");
    int option = 2;
    scanf("%d%*c", &option);
    return option - 1;
}


int account_disabled(void) {
    printf("in account hazf shode ast.\n1. Retry\n2. Go to login menu\nEnter an option: ");
    int option = 2;
    scanf("%d%*c", &option);
    return option - 1;
}

void login_student(void) {
    ll username = get_student_username();

    Student* key = creat_student(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                  0.0, username, 0, 0, 1, NULL, NULL, NULL);
    Student* st = search_student(headStudent, key);

    if (st == NULL) {
        if (wrong_username() == 0) login_student();
        return;
    }
    if (!st->active) {
        if (account_disabled() == 0) login_student();
        return;
    }

    while(1){
        char* password = get_password();
        if (strcmp(st->password, password) == 0) {
            free(password);
            dashboard_student(st);
            return;
        }
        free(password);
        if (wrong_password() == 1) return;
    }
   
}

void login_faculty(void) {
    char* username = get_faculty_username();

    Faculty* key = creat_faculty(NULL, NULL, NULL, NULL, NULL, username, 0, NULL, 1, NULL, NULL);
    Faculty* fc = search_faculty(headFaculty, key);
    free(username);

    if (fc == NULL) {
        if (wrong_username() == 0) login_faculty();
        return;
    }
    if (!fc->active) {
        if (account_disabled() == 0) login_faculty();
        return;
    }

    while(1){
        char* password = get_password();
        if (strcmp(fc->password, password) == 0) {
            free(password);
            dashboard_faculity(fc);
            return;
        }
        free(password);
        if (wrong_password() == 1) return;
    }
}


void login_admin(void) {
    printf("Enter your username: ");
    char* username = NULL;
    size_t bufferSize = 0;
    getline(&username, &bufferSize, stdin);
    username[strcspn(username, "\r\n")] = '\0';

    if (strcmp(username, admin.username) != 0) {
        free(username);
        if (wrong_username() == 0) login_admin();
        return;
    }
    free(username);

    while(1){
        char* password = get_password();
        if (strcmp(admin.password, password) == 0) {
            free(password);
            dashboard_admin();
            return;
        }
        free(password);
        if (wrong_password() == 1) return;
    }
}


static char* ask_line(const char* prompt) {
    printf("%s", prompt);
    char* line = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    line[strcspn(line, "\r\n")] = '\0';
    return line;
}

static int forgot_password_wrong_message(void) {
    printf("Incorrect answer.\n1. Retry\n2. Go to login menu\nEnter an option: ");
    int option = 2;
    scanf("%d%*c", &option);
    return option - 1;
}

static int ask_security_question(const char* prompt, const char* expected) {
    while (1) {
        char* answer = ask_line(prompt);
        int ok = (strcmp(answer, expected) == 0);
        free(answer);
        if (ok) return 1;
        if (forgot_password_wrong_message() != 0) return 0;
    }
}

void forgot_password(void) {
    ll username = get_student_username();
    Student* key = creat_student(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                  0.0, username, 0, 0, 1, NULL, NULL, NULL);
    Student* st = search_student(headStudent, key);

    if (st == NULL) {
        if (wrong_username() == 0) forgot_password();
        return;
    }
    if (!st->active) {
        if (account_disabled() == 0) forgot_password();
        return;
    }

    if (!ask_security_question("Where were you born? ", st->answer1)) return;
    if (!ask_security_question("What was the title of the first book you read? ", st->answer2)) return;
    if (!ask_security_question("What was the color of your first bicycle? ", st->answer3)) return;

    printf("Authentication successful.\n");

    while (1) {
        char* password = ask_line("Enter your new password: ");
        char* confirm = ask_line("Confirm your password: ");

        if (strcmp(password, confirm) == 0) {
            free(st->password);
            st->password = password;
            free(confirm);
            reset_file_student();
            printf("Password changed successfully.\nPress any key to go to login menu...");
            int chhhh = _getch();
            if(chhhh == 0 || chhhh == 224){
                _getch();
            }
            return;
        }

        free(password);
        free(confirm);
        printf("Passwords aren't matching.\n1. Retry.\n2. Cancel (go to login menu).\nEnter an option: ");
        int option = 2;
        scanf("%d%*c", &option);
        if (option != 1) return;
    }
}


void login_menu(void) {
    printf("1. Login as student\n2. Login as faculty\n3. Login as admin\n4. Forgot password\n5. Exit\nEnter an option: ");
    int option = 5;
    scanf("%d%*c", &option);

    if (option == 1) login_student();
    else if (option == 2) login_faculty();
    else if (option == 3) login_admin();
    else if (option == 4) forgot_password();
    else return;

    login_menu();
}
