#include "shoro.h"

void push_student(Student* st, Student* ptr) {
    if (headStudent == NULL) {
        st->next = NULL;
        st->prev = NULL;
        headStudent = st;
        return;
    }
    if (ptr->next == NULL) {
        st->next = NULL;
        st->prev = ptr;
        ptr->next = st;
        return;
    }
    push_student(st, ptr->next);
}

void push_faculty(Faculty* fc, Faculty* ptr) {
    if (headFaculty == NULL) {
        fc->next = NULL;
        fc->prev = NULL;
        headFaculty = fc;
        return;
    }
    if (ptr->next == NULL) {
        fc->next = NULL;
        fc->prev = ptr;
        ptr->next = fc;
        return;
    }
    push_faculty(fc, ptr->next);
}

void push_file_student(char* line) {
    reset_file_student();
}

void push_file_faculty(char* line) {
    reset_file_faculty();
}


Student* add_student(char* line) {
    char* tmp = dup_safe(line);      
    char* work = dup_safe(line);
    work[strcspn(work, "\r\n")] = '\0';

    char* token;
    char* saveptr;

    Student* st = (Student*)malloc(sizeof(Student));
    st->head_term = NULL;
    st->next = NULL;
    st->prev = NULL;
    st->active = 1;
    st->gpa = 0.0f;

    token = strtok_r(work, "|", &saveptr); trim(token); st->name = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->lastname = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->id = safe_atoll(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->password = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->kodemeli = safe_atoll(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->reshte = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->year = safe_atoll(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->maghta = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->ostadrahnama = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->department = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->answer1 = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->answer2 = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); st->answer3 = dup_safe(token);

    push_student(st, headStudent);
    push_file_student(tmp);

    free(tmp);
    free(work);
    return st;
}

/* |name|lastname|username|password|national_code|field|last_degree|department| */
Faculty* add_faculty(char* line) {
    char* tmp = dup_safe(line);
    char* work = dup_safe(line);
    work[strcspn(work, "\r\n")] = '\0';

    char* token;
    char* saveptr;

    Faculty* fc = (Faculty*)malloc(sizeof(Faculty));
    fc->next = NULL;
    fc->prev = NULL;
    fc->active = 1;

    token = strtok_r(work, "|", &saveptr); trim(token); fc->name = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->lastname = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->username = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->password = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->kodmeli = safe_atoll(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->reshte = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->akharinmadrak = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->department = dup_safe(token);

    push_faculty(fc, headFaculty);
    push_file_faculty(tmp);

    free(tmp);
    free(work);
    return fc;
}
