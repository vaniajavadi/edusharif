#include "shoro.h"
// /////////////////////////////stu
void print_student(Student* ptr) {
    if (ptr == NULL) {
        printf("Student doesn't exist.\n");
        return;
    }
    printf("|%s |%s |%lld |%lld |%s |%lld |%s |%s |%s| %s | %s | %s|\n",
        ptr->name, ptr->lastname, ptr->id, ptr->kodemeli, ptr->reshte,
        ptr->year, ptr->maghta, ptr->ostadrahnama, ptr->department,
        ptr->answer1, ptr->answer2, ptr->answer3);
}

void print_student_list(Student* ptr) {
    if (ptr == NULL) return;
    print_student(ptr);
    print_student_list(ptr->next);
}

// /////////////////////////////fac
void print_faculty(Faculty* ptr) {
    if (ptr == NULL) {
        printf("Faculty member doesn't exist.\n");
        return;
    }
    printf("|%s |%s |%s |%s |%s |%lld |%s|\n",
        ptr->name, ptr->lastname, ptr->username, ptr->reshte,
        ptr->akharinmadrak, ptr->kodmeli, ptr->department);
}

void print_faculty_list(Faculty* ptr) {
    if (ptr == NULL) return;
    print_faculty(ptr);
    print_faculty_list(ptr->next);
}
// /////////////////////////////request
void print_request_list(int no, Request* ptr) {
    if (ptr == NULL) return;

    if (ptr->type == 0) {
        printf("%d. Course offering\n", no);
    } else if (ptr->type == 1) {
        printf("%d. Course removing\n", no);
    } else {
        printf("%d. Capacity increment\n", no);
    }

    printf("\tCourse: %s\n\tFaculty: %s\n\tDepartment: %s\n\tCapacity: %d\n",
        ptr->course->name, ptr->faculty->name, ptr->course->daneshkade, ptr->offer->zarfiyat);

    if (ptr->type == 2 && ptr->offer != NULL) {
        printf("\tNo. enrollments: %d\n", ptr->enroll);
    }

    print_request_list(no + 1, ptr->next);
}
