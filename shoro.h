#ifndef SHORO_H
#define SHORO_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef long long ll;

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    static inline int _getch(void) {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#endif
    
typedef struct term {
    int state[4];
    ll id;
} Term;

typedef struct admin {
    char* username;
    char* password;
} Admin;

typedef struct course_student {
    char* id;  
    float score;
    struct course_student* next;
    struct course_student* prev;
} Course_student;

typedef struct term_student {
    ll id;                      
    float GPA;                   
    Course_student* head_course; 
    struct term_student* next;
    struct term_student* prev;
} Term_student;

typedef struct student {
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
    ll id;  
    ll kodemeli;
    ll year;
    int active; 
    Term_student* head_term;
    struct student* next;
    struct student* prev;
} Student;

typedef struct faculty {
    char* name;
    char* lastname;
    char* reshte;
    char* akharinmadrak;
    char* department;
    char* username; 
    ll kodmeli;
    char* password;
    int active;      
    struct faculty* next;
    struct faculty* prev;
} Faculty;

typedef struct course {
    char* name;
    char* maghta;
    char* reshte;
    char* daneshkade;
    char* id;
    char* phishniaz;
    int tedad_vahed;
    struct course* next;
    struct course* prev;
} Course;

typedef struct offer {
    Course* course;
    char* department;
    char* address;
    Faculty* faculty;
    ll termId;
    int enrollment;
    int zarfiyat;
    int rating_sum;  
    int rating_count; 
    Student* head; 
    struct offer* next;
    struct offer* prev;
} Offer;

typedef struct request {
    int type; 
    int enroll;
    Faculty* faculty;
    Course* course;
    Offer* offer;
    char* address;
    struct request* next;
    struct request* prev;
} Request;


extern Admin admin;
extern Term term;
extern Student* headStudent;
extern Faculty* headFaculty;
extern Course* headCourse;
extern Offer* headOffer;
extern Request* headRequest;


Course_student* creat_course_student(char* id, float score, Course_student* next, Course_student* prev);
Term_student* creat_term_student(ll id, Course_student* head_course, Term_student* next, Term_student* prev);
Student* creat_student(char* name, char* lastname, char* password, char* reshte, char* maghta,
                        char* ostadrahnama, char* department,
                        char* answer1, char* answer2, char* answer3,
                        float gpa, ll id, ll kodemeli, ll year, int active,
                        Term_student* head_term, Student* next, Student* prev);
Faculty* creat_faculty(char* name, char* lastname, char* reshte, char* akharinmadrak,
                        char* department, char* username, ll kodmeli, char* password, int active,
                        Faculty* next, Faculty* prev);
Course* creat_course(char* name, char* maghta, char* reshte, char* daneshkade,
                      char* id, char* phishniaz, int tedad_vahed,
                      Course* next, Course* prev);
Offer* creat_offer(Course* course, char* department, char* address,
                    Faculty* faculty, ll termId, int enrollment, int zarfiyat,
                    Student* head, Offer* next, Offer* prev);
Request* creat_request(int type, int enroll, Faculty* faculty, Course* course,
                        Offer* offer, char* address, Request* next, Request* prev);


void rtrim(char* str);
void ltrim(char* str);
void trim(char* str);
void print_space(int n);
char* dup_safe(const char* s);
long long safe_atoll(const char* s);
int safe_atoi(const char* s);
void recompute_student_gpa(Student* st); 

void push_student(Student* st, Student* ptr);
void push_faculty(Faculty* fc, Faculty* ptr);
void push_file_student(char* line);
void push_file_faculty(char* line);
Student* add_student(char* line);
Faculty* add_faculty(char* line);


Student* search_student(Student* ptr, Student* st);
Faculty* search_faculty(Faculty* ptr, Faculty* fc);
Request* search_request(int no, int cur, Request* ptr);


void print_student(Student* ptr);
void print_student_list(Student* ptr);
void print_faculty(Faculty* ptr);
void print_faculty_list(Faculty* ptr);
void print_request_list(int no, Request* ptr);


void remove_student(Student* st);  
void remove_faculty(Faculty* fc); 
void remove_request(Request* rqst); 

void reset_file_student(void);
void reset_file_faculty(void);
void reset_file_offer(void);

void read_student(void);
void read_faculty(void);
void read_course(void);
void read_offering(void);

ll get_student_username(void);
char* get_faculty_username(void);
char* get_password(void);
void to_lowercase(char* s);
int wrong_username(void);
int wrong_password(void);
int account_disabled(void);
void login_student(void);
void login_faculty(void);
void login_admin(void);
void forgot_password(void);
void login_menu(void);


void dashboard_student(Student* me);
void dashboard_faculity(Faculty* me);
void dashboard_admin(void);


char* calendar_message(int state);
void admin_calendar(void);
void search_student_menu(void);
void student_list(void);
void register_student_menu(void);
void remove_student_menu(void);
void admin_students(void);

void search_faculty_menu(void);
void faculty_list(void);
void register_faculty_menu(void);
void remove_faculty_menu(void);
void admin_faculty_members(void);

void admin_request(void);
void accept_request(Request* rqst);

void admin_offerings(void);
void admin_courses(void);

#endif
