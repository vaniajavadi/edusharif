#include "shoro.h"


Student* search_student(Student* ptr, Student* st) {
    if (ptr == NULL) return NULL;

    if (st->name != NULL && st->name[0] != '\0') {
        if (strcmp(ptr->name, st->name) == 0) return ptr;
    }
    else if (st->lastname != NULL && st->lastname[0] != '\0') {
        if (strcmp(ptr->lastname, st->lastname) == 0) return ptr;
    }
    else {
        if (ptr->id == st->id) return ptr;
    }
    return search_student(ptr->next, st);
}

Faculty* search_faculty(Faculty* ptr, Faculty* fc) {
    if (ptr == NULL) return NULL;

    if (fc->name != NULL && fc->name[0] != '\0') {
        if (strcmp(ptr->name, fc->name) == 0) return ptr;
    }
    else if (fc->lastname != NULL && fc->lastname[0] != '\0') {
        if (strcmp(ptr->lastname, fc->lastname) == 0) return ptr;
    }
    else {
        if (strcmp(ptr->username, fc->username) == 0) return ptr;
    }
    return search_faculty(ptr->next, fc);
}

Request* search_request(int no, int cur, Request* ptr) {
    if (no < 1 || ptr == NULL) return NULL;
    if (no == cur) return ptr;
    return search_request(no, cur + 1, ptr->next);
}
