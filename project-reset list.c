#include "shoro.h"

void reset_file_student(void) {
    FILE* fp = fopen("student.csv", "w");
    if (fp == NULL) return;
    Student* ptr = headStudent;

    while (ptr != NULL) {
        /* |name |lastname |id |password| kodemeli |reshte |year |maghta |ostadrahnama |department| answer1 | answer2 | answer3 | active| */
        fprintf(fp, "|%s |%s |%lld |%s| %lld |%s |%lld |%s |%s |%s| %s | %s | %s | %d|\n",
            ptr->name, ptr->lastname, ptr->id, ptr->password, ptr->kodemeli, ptr->reshte,
            ptr->year, ptr->maghta, ptr->ostadrahnama, ptr->department,
            ptr->answer1, ptr->answer2, ptr->answer3, ptr->active);

        fprintf(fp, "enrolled_offerings: {\n");
        Term_student* tr = ptr->head_term;
        while (tr != NULL) {
            fprintf(fp, "\t\"%lld\": {\n", tr->id);
            Course_student* cr = tr->head_course;
            while (cr != NULL) {
                fprintf(fp, "\t\t\"%s\": %.2f%s\n", cr->id, cr->score, (cr->next == NULL) ? "" : ",");
                cr = cr->next;
            }
            fprintf(fp, "\t}%s\n", (tr->next == NULL) ? "" : ",");
            tr = tr->next;
        }
        fprintf(fp, "}\n");

        ptr = ptr->next;
    }

    fclose(fp);
}

void reset_file_faculty(void) {
    FILE* fp = fopen("faculty.csv", "w");
    if (fp == NULL) return;
    Faculty* ptr = headFaculty;

    while (ptr != NULL) {
        /* |name |lastname |username |password| kodmeli |reshte |akharinmadrak |department | active| */
        fprintf(fp, "|%s |%s |%s |%s| %lld |%s |%s |%s | %d|\n",
            ptr->name, ptr->lastname, ptr->username, ptr->password, ptr->kodmeli,
            ptr->reshte, ptr->akharinmadrak, ptr->department, ptr->active);
        ptr = ptr->next;
    }

    fclose(fp);
}
