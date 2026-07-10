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

/////////////////////////////////////////////////////////////////////// FUNC OF STRUCT


Course_student* creat_course_student(char* id, float score, Course_student* next, Course_student* prev){
    Course_student* to_return = (Course_student*) malloc(sizeof(Course_student));
    to_return->id = strdup(id);
    to_return->score = score;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Term_student* creat_term_student(ll id, Course_student* head, Term_student* next,
                                 Term_student* prev){
    Term_student* to_return = (Term_student*)malloc(sizeof(Term_student));
    to_return->id = id;
    to_return->head = head;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Student* creat_student(char* name, char* lastname, char* password, char* reshte, char* maghta,
                        char* ostadrahnama, char* department,
                        char* answer1, char* answer2, char* answer3,
                        float gpa, ll id, ll kodemeli, ll year,
                        Term_student* head, Student* next, Student* prev){

    Student* to_return = (Student*)malloc(sizeof(Student));
    to_return->name = strdup(name);
    to_return->lastname = strdup(lastname);
    to_return->reshte = strdup(reshte);
    to_return->maghta = strdup(maghta);
    to_return->ostadrahnama = strdup(ostadrahnama);
    to_return->department = strdup(department);
    to_return->answer1 = strdup(answer1);
    to_return->answer2 = strdup(answer2);
    to_return->answer3 = strdup(answer3);
    to_return->gpa = gpa;
    to_return->id = id;
    to_return->kodemeli = kodemeli;
    to_return->year = year;
    to_return->head = head;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Faculty* creat_faculty(char* name, char* lastname, char* reshte, char* akharinmadrak,
                        char* department, ll id, ll kodmeli, char* password,
                        Faculty* next, Faculty* prev){
    Faculty* to_return = (Faculty*) malloc(sizeof(Faculty));
    to_return->name = strdup(name);
    to_return->lastname = strdup(lastname);
    to_return->reshte = strdup(reshte);
    to_return->akharinmadrak = strdup(akharinmadrak);
    to_return->department = strdup(department);
    to_return->id = id;
    to_return->kodmeli = kodmeli;
    to_return->password = strdup(password);
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Course* creat_course(char* name, char* maghta, char* reshte, char* daneshkade,
                      char* id, char* phishniaz, int tedad_vahed,
                      Course* next, Course* prev){
    Course* to_return = (Course*) malloc(sizeof(Course));
    to_return->name = strdup(name);
    to_return->maghta = strdup(maghta);
    to_return->reshte = strdup(reshte);
    to_return->daneshkade = strdup(daneshkade);
    to_return->id = strdup(id);
    to_return->phishniaz = strdup(phishniaz);
    to_return->tedad_vahed = tedad_vahed;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Offer* creat_offer(Course* course, char* id, char* department, char* address,
                    Faculty* faculty, int termId, int enrollment, int zarfiyat,
                    Student* head, Offer* next, Offer* prev){
    Offer* to_return = (Offer*) malloc(sizeof(Offer));
    to_return->course = course;
    to_return->id = strdup(id);
    to_return->department = strdup(department);
    to_return->address = strdup(address);
    to_return->faculty = faculty;
    to_return->termId = termId;
    to_return->enrollment = enrollment;
    to_return->zarfiyat = zarfiyat;
    to_return->head = head;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Request* creat_request(int type, int enroll, Faculty* faculty, Course* course,
                        Offer* offer, Request* next, Request* prev){
    Request* to_return = (Request*) malloc(sizeof(Request));
    to_return->type = type;
    to_return->enroll = enroll;
    to_return->faculty = faculty;
    to_return->course = course;
    to_return->offer = offer;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

