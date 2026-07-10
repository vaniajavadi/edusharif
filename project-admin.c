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
//////////////////////////////////////////////////////////////calendar
char* calendar_message(int state){
	if(state == 1)	return "enabled";
	else return"disabled";
}

void admin_calendar(){
	if(term->id == -1){
		prinf("Enter new term id:");
		scanf("%d%*c", &term->id);
	}
	else{
		printf("term %d", term->id);
	}

	printf("1.offering: %s\n
		2.unit selection: %s\n
		3. class & exams: %s\n
		4,grade recording: %s\n
		5. go to main menu: %s\n
		Enter a time to trigger:", 
		calendar_message(term->state[0]), 
		calendar_message(term->state[1]),
		calendar_message(term->state[2]),
		calendar_message(term->state[3]));

	int option;	scanf("%d%*c", &option);
	if(option == 5)	return;
	else if(term->state[--option] == 2){
		printf("not possible");
	}
	else if(term->state[option] == 1){
		if(!option || term->state[option - 1] == 2){
			term->state[option] = 2;
		}
		else
			printf("not possible");

	}
	else{
		if(!option || term->state[option - 1])
			term->state[option] = 1;
		else
			printf("not possible");
	}


	admin_calendar();
	return;

}

void print_student(Student* ptr){
	if(ptr == NULL){
		printf("student doesnt exist");
		return;
	}
	char* name, char* lastname, char* password, char* reshte, char* maghta,
                        char* ostadrahnama, char* department,
                        char* answer1, char* answer2, char* answer3,
                        float gpa, ll id, ll kodemeli, ll year,
                        Term_student* head, Student* next, Student* prev)
	printf("|%s |%s |%lld |%lld |%s |%lld |%s |%s |%s| %s | %s | %s|\n",
		ptr->name, ptr->lastname, ptr->id, ptr->kodemeli, ptr->reshte,
		ptr->year, ptr->maghta, ptr->ostadrahnama, ptr->department,
		ptr->answer1, ptr->answer2, ptr->answer3);
	return;

}

void print_student_list(Student* ptr){
	if(ptr == NULL) return;
	print_student(ptr);
	print_student_list(ptr->next);
	return;
}

void search_student_menu(){
	printf("1.search by first name\n
		2. search by lastname\n
		3. search by student id\n
		4.back\n
		........\n
		Enter an option: ");
	int option;
	char* phrase;
	Student* st;
	scanf("%d%*c", &option);

	if(option == 4) return;
	if(option == 3){
		ll studentId;
		scanf("%lld%*c", %studentId);
		st = create_student(NULL, NULL, NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 NULL, NULL, NULL,
                                                 0.0, username, 0, 0, 
                                                 NULL, NULL, NULL);
	}
	else{
		size_t bufferSize = 0;
		getline(&phrase, &bufferSize, stdin);
		phrase[strscpn(line, "\n")] = '\0';

		if(option == 1)
			st = create_student(phrase, NULL, NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 NULL, NULL, NULL,
                                                 0.0, 0, 0, 0, 
                                                 NULL, NULL, NULL);
		else
			st = create_student(NULL, phrase, NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 NULL, NULL, NULL,
                                                 0.0, 0, 0, 0, 
                                                 NULL, NULL, NULL);
	}

	bool flag = 0;
	Student* foundedSt = search_student(headStudent, st);
	print_student(foundedSt);

	while(foundedSt != NULL){
		foundedSt = search_student(foundedSt->next, st);
		print_student(foundedSt);
	}

}


void student_list(){
	printf("STUDENT LIST\n
		|first name |last name |student id |national code |field |entrance year |section |mentor |department| answer 1 | answer 2 | answer 3|\n
		|----------|----------|----------|---------------|------|--------------|-------|------|----------|----------|----------|----------|\n");
	print_student_list(headStudent);
	printf("1.search\n
		2.go back\n
		3.enter an option:");

	int option;
	scanf("%d%*c", option);
	if(option == 1)
		search_student_menu();
	return;
}
///////////////////////////////// register_student_menu
void register_student_menu(){
	prinf("Register student(s)\n
	 1. Register one student\n
	 2. register a group of students (import a file)\n 
	 3. back\n 
	 Enter an option ");
	int option = 0;
	scanf("%d%*c", option);
	if(option == 3)	return;

	char* line = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    line[strscpn(line, "\n")] = '\0';

    if(option == 1){
    	printf("Enter student info");
    	getline(&line, &bufferSize, stdin);
    	add_student();
    	free(line);
    }
    else{
    	printf("Enter file address");

    	char* 
    	getline(&line, &bufferSize, stdin);
    	line[strscpn(line, "\n")] = '\0';

    }


}	

//////////////////////////////////////////// admin_student
void admin_students() {
	int option = 0;
    printf("1. students list\n"
           "2. register student(s)\n"
           "3. remove student(s)\n"
           "4. back to admin dashboard\n"
           "Enter an option: ");
    
    scanf("%d%*c", &option);
    if (option == 1) {
        student_list();
    } 
    else if (option == 2) {
        register_student_menu();
    } 
    else if (option == 3) {
        remove_student_menu();
    } 
    else
        return; 
}
    


////////////////////////////////////////////////////////////dashboard
void dashboard_admin(){
	printf("Welcom %s\n
		1.calendar\n
		2.students\n
		3.faculity members\n
		4.requests\n
		5.offerings\n
		6.courses\n
		7.Log out\n
		Enter an option:", admin->username);

	int option = 0;
	scanf("%d%*c", &option);
	 if (option == 1) {
	    admin_calendar();
	} 
	else if (option == 2) {
	    admin_students();
	} 
	else if (option == 3) {
	    admin_faculty_members();
	} 
	else if (option == 4) {
	    admin_requests();
	} 
	else if (option == 5) {
	    admin_offerings();
	} 
	else if (option == 6) {
	    admin_courses();
	} 
	else return;
}
