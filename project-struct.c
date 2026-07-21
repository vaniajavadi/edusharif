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

////////////////////////////////STRUCT

typedef struct term{
    int state[4] = 0;
    long long id;
}Term;

typedef struct admin{
    // hard code
    char* username;
    char* password;

}Admin;



typedef struct course_student{
    char* id;
    float score;
    struct course_student* next;
    struct course_student* prev;
}Course_student;


typedef struct term_student{
    ll id;
    Course_student* head;
    struct term_student* next;
    struct term_student* prev;

}Term_student;

typedef struct student{
    char* name;
    char* lastname;
    char* password;
    char* reshte;
    char* maghta;
    char* ostadrahnama;
    char* department;
    char* answer1;
    char* answer2;
    char* answer3;
    float gpa;
    ll id, kodemeli, year;
    Term_student* head;
    struct student* next;
    struct student* prev;
}Student;

typedef struct faculty{
    char* name;
    char* lastname;
    char* reshte;
    char* akharinmadrak;
    char* department;
    char* id;
    ll  kodmeli;
    char* password;
    struct faculty* next;
    struct faculty* prev;
}Faculty;

typedef struct course{
    char* name;
    char* maghta;
    char* reshte;
    char* daneshkade;
    char* id;
    char* phishniaz;
    int tedad_vahed;
    struct course* next;
    struct course* prev;
}Course;

typedef struct offer{
    Course* course;
    char* department;
    char* address;
    Faculty* faculty;
    int termId, enrollment, zarfiyat;
    Student* head;
    struct offer* next;
    struct offer* prev;
}Offer;

typedef struct request{
    int type, enroll;
    Faculty* faculty;
    Course* course;
    Offer* offer;
    char* address;
    struct request* next;
    struct request* prev;
}Request;
