#include "shoro.h"

Course_student* creat_course_student(char* id, float score, Course_student* next, Course_student* prev) {
    Course_student* to_return = (Course_student*)malloc(sizeof(Course_student));
    to_return->id = dup_safe(id);
    to_return->score = score;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Term_student* creat_term_student(ll id, Course_student* head_course, Term_student* next, Term_student* prev) {
    Term_student* to_return = (Term_student*)malloc(sizeof(Term_student));
    to_return->id = id;
    to_return->GPA = 0.0f; 
    to_return->head_course = head_course;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Student* creat_student(char* name, char* lastname, char* password, char* reshte, char* maghta,
                        char* ostadrahnama, char* department,
                        char* answer1, char* answer2, char* answer3,
                        float gpa, ll id, ll kodemeli, ll year, int active,
                        Term_student* head_term, Student* next, Student* prev) {
    Student* to_return = (Student*)malloc(sizeof(Student));
 
    to_return->name = dup_safe(name);
    to_return->lastname = dup_safe(lastname);
    to_return->password = dup_safe(password);
    to_return->reshte = dup_safe(reshte);
    to_return->maghta = dup_safe(maghta);
    to_return->ostadrahnama = dup_safe(ostadrahnama);
    to_return->department = dup_safe(department);
    to_return->answer1 = dup_safe(answer1);
    to_return->answer2 = dup_safe(answer2);
    to_return->answer3 = dup_safe(answer3);
    to_return->gpa = gpa;
    to_return->id = id;
    to_return->kodemeli = kodemeli;
    to_return->year = year;
    to_return->active = active;
    to_return->head_term = head_term;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Faculty* creat_faculty(char* name, char* lastname, char* reshte, char* akharinmadrak,
                        char* department, char* username, ll kodmeli, char* password, int active,
                        Faculty* next, Faculty* prev) {
    Faculty* to_return = (Faculty*)malloc(sizeof(Faculty));
    to_return->name = dup_safe(name);
    to_return->lastname = dup_safe(lastname);
    to_return->reshte = dup_safe(reshte);
    to_return->akharinmadrak = dup_safe(akharinmadrak);
    to_return->department = dup_safe(department);
    to_return->username = dup_safe(username);  
    to_return->kodmeli = kodmeli;
    to_return->password = dup_safe(password);
    to_return->active = active;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Course* creat_course(char* name, char* maghta, char* reshte, char* daneshkade,
                      char* id, char* phishniaz, int tedad_vahed,
                      Course* next, Course* prev) {
    Course* to_return = (Course*)malloc(sizeof(Course));
    to_return->name = dup_safe(name);
    to_return->maghta = dup_safe(maghta);
    to_return->reshte = dup_safe(reshte);
    to_return->daneshkade = dup_safe(daneshkade);
    to_return->id = dup_safe(id);
    to_return->phishniaz = dup_safe(phishniaz);
    to_return->tedad_vahed = tedad_vahed;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Offer* creat_offer(Course* course, char* department, char* address,
                    Faculty* faculty, ll termId, int enrollment, int zarfiyat,
                    Student* head, Offer* next, Offer* prev) {
    Offer* to_return = (Offer*)malloc(sizeof(Offer));
    to_return->course = course;
    to_return->department = dup_safe(department);
    to_return->address = dup_safe(address);
    to_return->faculty = faculty;
    to_return->termId = termId;
    to_return->enrollment = enrollment;
    to_return->zarfiyat = zarfiyat;
    to_return->rating_sum = 0;
    to_return->rating_count = 0;
    to_return->head = head;
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}

Request* creat_request(int type, int enroll, Faculty* faculty, Course* course,
                        Offer* offer, char* address, Request* next, Request* prev) {
    Request* to_return = (Request*)malloc(sizeof(Request));
    to_return->type = type;
    to_return->enroll = enroll;
    to_return->faculty = faculty;
    to_return->course = course;
    to_return->offer = offer;
    to_return->address = dup_safe(address);
    to_return->next = next;
    to_return->prev = prev;
    return to_return;
}
