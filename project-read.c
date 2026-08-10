#include "shoro.h"

static Student* load_student_line(char* line) {
    char* work = dup_safe(line);
    work[strcspn(work, "\r\n")] = '\0';
    char* token; char* saveptr;

    Student* st = (Student*)malloc(sizeof(Student));
    st->head_term = NULL;
    st->next = NULL;
    st->prev = NULL;
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
    token = strtok_r(NULL, "|", &saveptr);
    st->active = (token != NULL) ? safe_atoi(token) : 1;

    push_student(st, headStudent);
    free(work);
    return st;
}

void read_student(void) {
    char* line = NULL;
    size_t bufferSize = 0;
    ssize_t nread;

    FILE* fp = fopen("student.csv", "r");
    if (fp == NULL) return;

    Student* current = NULL;
    Term_student* currentTerm = NULL;

    while ((nread = getline(&line, &bufferSize, fp)) != -1) {
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;

        if (p[0] == '|') {
            if (current != NULL) recompute_student_gpa(current);
            current = load_student_line(line);
            currentTerm = NULL;
        }
        else if (strncmp(p, "enrolled_offerings", 18) == 0) {
          
            continue;
        }
        else if (p[0] == '"') {
         
            long long termId;
            char courseId[64];
            float score;

            if (sscanf(p, "\"%lld\":", &termId) == 1 && current != NULL) {
                currentTerm = creat_term_student(termId, NULL, current->head_term, NULL);
                if (current->head_term != NULL) current->head_term->prev = currentTerm;
                current->head_term = currentTerm;
            }
            else if (sscanf(p, "\"%63[^\"]\": %f", courseId, &score) == 2 && currentTerm != NULL) {
                Course_student* cr = creat_course_student(courseId, score, currentTerm->head_course, NULL);
                if (currentTerm->head_course != NULL) currentTerm->head_course->prev = cr;
                currentTerm->head_course = cr;
            }
        }
     
    }

    if (current != NULL) recompute_student_gpa(current); 

    free(line);
    fclose(fp);
}

static Faculty* load_faculty_line(char* line) {
    char* work = dup_safe(line);
    work[strcspn(work, "\r\n")] = '\0';
    char* token; char* saveptr;

    Faculty* fc = (Faculty*)malloc(sizeof(Faculty));
    fc->next = NULL;
    fc->prev = NULL;

    token = strtok_r(work, "|", &saveptr); trim(token); fc->name = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->lastname = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->username = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->password = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->kodmeli = safe_atoll(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->reshte = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->akharinmadrak = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); fc->department = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr);
    fc->active = (token != NULL) ? safe_atoi(token) : 1;

    push_faculty(fc, headFaculty);
    free(work);
    return fc;
}

void read_faculty(void) {
    char* line = NULL;
    size_t bufferSize = 0;
    ssize_t nread;

    FILE* fp = fopen("faculty.csv", "r");
    if (fp == NULL) return;

    while ((nread = getline(&line, &bufferSize, fp)) != -1) {
        if (line[0] == '|') load_faculty_line(line);
    }

    free(line);
    fclose(fp);
}
/////////////// baraye offers and courses toye file haye khodeshe
