#include "shoro.h"


void remove_student(Student* st) {
    if (st == NULL) return;
    st->active = 0;
    reset_file_student();
}


void remove_faculty(Faculty* fc) {
    if (fc == NULL) return;
    fc->active = 0;
    reset_file_faculty();
}

void remove_request(Request* rqst) {
    if (rqst == NULL) return;

    if (rqst == headRequest) {
        headRequest = rqst->next;
        if (headRequest != NULL) headRequest->prev = NULL;
        free(rqst->address);
        free(rqst);
        return;
    }

    if (rqst->prev != NULL) rqst->prev->next = rqst->next;
    if (rqst->next != NULL) rqst->next->prev = rqst->prev;
    free(rqst->address);
    free(rqst);
}
