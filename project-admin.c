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
/////////////////////////////////////////////////////////////////////////////////////////Studentlist


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
	return;

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
    	add_student(line);
    	free(line);
    }
    else{
    	printf("Enter file address");

    	getline(&line, &bufferSize, stdin);
    	line[strscpn(line, "\n")] = '\0';
    	FILE *fp = fopen(line, "r");


    	ssize_t read = getline(&line, &bufferSize, fp);
    	while(read != -1){
    		add_student(line);
    		ssize_t read = getline(&line, &bufferSize, fp);
    	}
    	free(line);
    	fclose(fp);
    }
    register_student_menu();
    return;
}	

////////////////////////////////////////////remove student menu

void remove_student_menu(){
	prinf("1.Remove student\n2.back\nEnter an option:");
	int option;
	scanf("%d%*c", &option);
	if(option == 2)
		return

	printf("Enter student id:")
	ll id;
	scanf("%lld%*c", &id);

	Student* ptr = search_student(headStudent, create_student(NULL, NULL, NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 NULL, NULL, NULL,
                                                 0.0, id, 0, 0, 
                                                 NULL, NULL, NULL));

	if(ptr == NULL){
		printf("student doesnt exist");
		return;
	}

	printf("|%s |%s |%lld |%lld |%s |%lld |%s |%s |%s|\nRemove student? [y/n]",
			ptr->name, ptr->lastname, ptr->id, ptr->kodemeli, ptr->reshte,
			ptr->year, ptr->maghta, ptr->ostadrahnama, ptr->department);

	char ch;
	scanf("%c", &ch);
	if(ch == 'y'){
		remove_student(ptr);
		reset_file_student();
	}
	return;
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
//////////////////////////////////////////////admin_faculty_members

void admin_faculty_members(){

}


////////////////////////////////////////////request

void accept_request(Request* rqst){
	if(rqst == NULL){
		printf("there is no request with that number\n");
		return;
	}
	if(ter[1] == 2){
		printf("NOT POSSIBLE! ENTEKHAB VAHED TAMOM SHODE");

	}

	else if(rqst->type == 0){
		if(term[1] == 2){
			printf("NOT POSSIBLE!");
		}
		else{
			Offer* offer = creat_offer(rqst->course, rqst->course->daneshkade, rqst->address,
                    rqst->faculty, term->id, 0, rqst->enroll,
                    NULL, NULL, NULL);
			push_offer(offer, headOffer);
			push_offer_file(offer);
		}	
	}
	else if(rqst->type == 1){
		remove_offer(rqst->offer);
		reset_offer();
	}
	else if(rqst->type == 2){
		rqst->offer->zarfiyat = rqst->enroll;
		reset_offer();
	}

	remove_request(rqst);
}

void admin_request(){
	printf("List of requests:\n");
	print_request_list(1, headRequest);
	printf("1. accept request\n2. Go back\nEnter an option:");
	int option;	scanf("%d%*c", &option);
	if(option == 2)	return;
	printf("Enter request's number: ");
	scanf("%d%*c", &option);
	accept_request(search_request(option, 1, headRequest));
	admin_request();
	return;

}
////////////////////////////////////////////////////////////offering
void admin_offering(){

}

///////////////////////////////////////////////////////////courses



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
	    admin_request();
	} 
	else if (option == 5) {
	    admin_offerings();
	} 
	else if (option == 6) {
	    admin_courses();
	} 
	else return;
}
