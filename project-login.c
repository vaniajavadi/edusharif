#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//#include <cstdlib>
//#include <bits/stdc++.h>
//#include <iostream>
//fgets(line2, 2000, stdin);
//int size_line1 = strlen(line1) - 1; 
typedef long long ll;

//using namespace std;

////////////////////////////////////////////////////////////LOGIN
ll get_username(){
    printf("Enter your username: ");
    ll username = 0;
    scanf("%lld%*c", &username);
    return username;
}


void to_lowercase(char* s){
    for(int i = 0; s[i] != '\0'; i++){
        s[i] = tolower((unsigned char)s[i]);
    }
}

char* get_paswword(){
    printf("Enter your password: ")

    char* password = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    line[strscpn(line, "\n")] = '\0';

    return password;
}

void wrong_password(){
    printf("Incorrect password.");
}



void login_studentOfaculity(int t){
    int option = 0;
    int username = get_username();
    Student* st = NULL;
    Faculty* fac = NULL;
    if(!t){
        st = search_student(headStudent, create_student(NULL, NULL, NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 NULL, NULL, NULL,
                                                 0.0, username, 0, 0, 
                                                 NULL, NULL, NULL));
    }
    else{
        fac = search_faculty(headFaculty, creat_faculty(NULL, NULL, NULL, NULL, NULL,
                                                         username, 0, NULL, NULL, NULL));
    }

    if(st == NULL && fac == NULL){
        option = wrong_username();
        if(!option){    
            login_studentOfaculity(t);
            return;
        }
        return;
    }

    char* password = to_lowercase(get_password());
    if(!t && strcmp(st->password, password) == 0){
        dashboard_student();
        return;
    }
    else if(t && strcmp(fac->password, password) == 0){
        dashboard_faculity();
        return;
    }

    wrong_password();
    login_studentOfaculity();
}

void login_admin(){
    int option = 0;
    printf("Enter your username: ");


    char* username = NULL;
    size_t bufferSize = 0;
    getline(&username, &bufferSize, stdin);
    line[strscpn(username, "\n")] = '\0';

    if(strcmp(username, admin->username) != 0){

        option = wrong_username();
        if(!option){
            login_admin();
            return;
        }
        return;
    }

    char* password = to_lowercase(get_password());
    if(strcmp(admin->password, password) == 0){
        dashboard_admin();
        return;
    }


    wrong_password();
    login_admin();
    return;
}


void login_menu(){
    int option = 0;

    printf("login as\n
        1-student\n
        2-faculity\n
        3-admin\n
        4-forgot password\n
        5-Exit\n
        Enter your option");

    scanf("%d%*c" &option);

    if(option <= 2){
        login_studentOfaculity(--option);
    }
    else if(option == 3){
        login_admin();
    }
    else if(option == 4){
        fotgot_password();
    }
    else return;


}
