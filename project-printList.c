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


////////////////////////////////////////////////////////////student
void print_student(Student* ptr){
	if(ptr == NULL){
		printf("student doesnt exist");
		return;
	}
	// char* name, char* lastname, char* password, char* reshte, char* maghta,
    //                     char* ostadrahnama, char* department,
    //                     char* answer1, char* answer2, char* answer3,
    //                     float gpa, ll id, ll kodemeli, ll year,
    //                     Term_student* head, Student* next, Student* prev)
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


/////////////////////////////////////////////////////////request
void print_request_list(int no, Request* ptr){
	if(ptr == NULL) return;
	if(ptr->type == 0){
		printf("%d Course offering\n", no);
	}
	else if(ptr->type == 1){
		printf("%d Course removing\n", no);
	}
	else{
		printf("%d Course increment\n", no);
	
	}

	printf("Course: %s\n Faculity: %s\nDepartment: %s\nCapacity: %d\n", ptr->course->name, ptr->faculty->name, ptr->course->daneshkade, ptr->enroll);
	if(ptr->type == 2)	printf("No. enrollments: %d", ptr->offer->enroll)
	print_request_list(no++, ptr->next);
	return;
}

//////////////////////////////////////////////////////////////