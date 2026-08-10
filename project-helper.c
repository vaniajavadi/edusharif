#include "shoro.h"

char* dup_safe(const char* s) {
    if (s == NULL) s = "";
    char* copy = (char*)malloc(strlen(s) + 1);
    strcpy(copy, s);
    return copy;
}

void rtrim(char* str) {
    if (str == NULL) return;
    int end = (int)strlen(str) - 1;
    while (end >= 0 && isspace((unsigned char)str[end])) {
        str[end] = '\0';
        end--;
    }
}

void ltrim(char* str) {
    if (str == NULL) return;
    int start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start])) start++;
    if (start > 0) memmove(str, str + start, strlen(str + start) + 1);
}

void trim(char* str) {
    ltrim(str);
    rtrim(str);
}

long long safe_atoll(const char* s) {
    if (s == NULL) return 0;
    return atoll(s);
}

int safe_atoi(const char* s) {
    if (s == NULL) return 0;
    return atoi(s);
}

static int course_units(const char* courseId) {
    Course* c = headCourse;
    while (c != NULL) {
        if (strcmp(c->id, courseId) == 0) return c->tedad_vahed;
        c = c->next;
    }
    return 1;
}

void recompute_student_gpa(Student* st) {
    float totalPoints = 0.0f;
    int totalUnits = 0;

    Term_student* tr = st->head_term;
    while (tr != NULL) {
        float termPoints = 0.0f;
        int termUnits = 0;

        Course_student* cr = tr->head_course;
        while (cr != NULL) {
            if (cr->score >= 0.0f) {
                int u = course_units(cr->id);
                termPoints += cr->score * (float)u;
                termUnits += u;
            }
            cr = cr->next;
        }

        tr->GPA = (termUnits > 0) ? (termPoints / (float)termUnits) : 0.0f;
        totalPoints += termPoints;
        totalUnits += termUnits;
        tr = tr->next;
    }

    st->gpa = (totalUnits > 0) ? (totalPoints / (float)totalUnits) : 0.0f;
}

void to_lowercase(char* s) {
    if (s == NULL) return;
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

void print_space(int n) {
    if (n <= 0) return;
    printf(" ");
    print_space(n - 1);
}
