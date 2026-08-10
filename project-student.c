#include "shoro.h"

static void print_offering_student(Offer* ptr, int no, ll termId) {
   // printf("%lld", termId);
    if (ptr == NULL){
        printf("%d", no);
        return;
    }
    printf("%lld", ptr->termId);
    if (ptr->termId == termId) {
        printf("| %d | %s | %s | %s | %lld | %d | %d | %s | %s |\n",
            no, ptr->course->name, ptr->course->id, ptr->faculty->name,
            ptr->termId, ptr->zarfiyat, ptr->enrollment, ptr->department, ptr->address);
        no++;
    }
    print_offering_student(ptr->next, no, termId);
}

static Offer* find_offering_by_number(Offer* ptr, int num, ll termId) {
    int cur = 0;
    while (ptr != NULL) {
        if (ptr->termId == termId) {
            cur++;
            if (cur == num) return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

static int student_passed_course(Student* me, const char* courseId) {
    Term_student* tr = me->head_term;
    while (tr != NULL) {
        Course_student* cr = tr->head_course;
        while (cr != NULL) {
            if (strcmp(cr->id, courseId) == 0 && cr->score >= 10.0f) return 1;
            cr = cr->next;
        }
        tr = tr->next;
    }
    return 0;
}

static int has_passed_prerequisites(Student* me, Course* course) {
    if (course->phishniaz == NULL || course->phishniaz[0] == '\0'
        || strcmp(course->phishniaz, "-") == 0) return 1;
    char buf[256];
    strncpy(buf, course->phishniaz, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char* saveptr;
    char* tok = strtok_r(buf, ",", &saveptr);
    while (tok != NULL) {
        trim(tok);
        if (tok[0] != '\0' && !student_passed_course(me, tok)) return 0;
        tok = strtok_r(NULL, ",", &saveptr);
    }
    return 1;
}

static void idk(Student* me, ll termId, int option){
    if (option == 1) {
        printf("Enter course id to search: ");
        char id[64]; scanf("%63s%*c", id);
        Offer* ptr = headOffer;
        int found = 0;
        while (ptr != NULL) {
            if (ptr->termId == termId && strcmp(ptr->course->id, id) == 0) {
                printf("| %s | %s | %s | %lld | %d | %d | %s | %s |\n",
                    ptr->course->name, ptr->course->id, ptr->faculty->name,
                    ptr->termId, ptr->zarfiyat, ptr->enrollment, ptr->department, ptr->address);
                found = 1;
                break;
            }
            ptr = ptr->next;
        }
        if (!found) printf("No offering found for that course this semester.\n");
    }
    else if (option == 2 || option == 3) {
        if(termId != term.id){
            printf("NOT POSSIBLE! The term has been ended.");
            return;
        }
        if (term.state[1] != 1) {
            printf("NOT POSSIBLE! Course selection is not open right now.\n");
            return;
        }
        printf("Enter offering number: ");
        int num; scanf("%d%*c", &num);
        Offer* offer = find_offering_by_number(headOffer, num, termId);
        if (offer == NULL) { printf("Offering not found.\n"); }
        else if (option == 2) {
            if (!has_passed_prerequisites(me, offer->course)) {
                printf("NOT POSSIBLE! You have not passed the prerequisites for this course .\n");
                return;
            }
            Term_student* tr = me->head_term;
            while (tr != NULL && tr->id != offer->termId) tr = tr->next;
            if (tr == NULL) {
                tr = creat_term_student(offer->termId, NULL, me->head_term, NULL);
                if (me->head_term != NULL) me->head_term->prev = tr;
                me->head_term = tr;
            }
            Course_student* dup = tr->head_course;
            while(dup != NULL){
                if(strcmp(dup->id, offer->course->id) == 0 ){
                    printf("You are already enrolled in this course.\n");
                    return;
                }
                dup = dup->next;
            }
            if (offer->enrollment >= offer->zarfiyat) {
                printf("NOT POSSIBLE! Class is full.\n");
            }
            else{
                Course_student* cr = creat_course_student(offer->course->id, -1.0f, tr->head_course, NULL);
                if (tr->head_course != NULL) tr->head_course->prev = cr;
                tr->head_course = cr;
                offer->enrollment++;
                recompute_student_gpa(me);
                reset_file_student();
                reset_file_offer();
                printf("Enrolled successfully.\n");
            }
        }
        else { 
            Term_student* tr = me->head_term;
            while (tr != NULL && tr->id != offer->termId) tr = tr->next;
            Course_student* cr = (tr != NULL) ? tr->head_course : NULL;
            while (cr != NULL && strcmp(cr->id, offer->course->id) != 0) cr = cr->next;
            if (cr == NULL) { printf("You are not enrolled in this course.\n"); }
            else {
                if (cr->prev != NULL) cr->prev->next = cr->next; else tr->head_course = cr->next;
                if (cr->next != NULL) cr->next->prev = cr->prev;
                free(cr->id); free(cr);
                offer->enrollment--;
                recompute_student_gpa(me);
                reset_file_student();
                reset_file_offer();
                printf("Withdrawn successfully.\n");
            }
        }
    }
}
static void student_offerings(Student* me) {
    printf("Enter semester number: ");
    ll termId; scanf("%lld%*c", &termId);

    printf("List of offerings - %lld\n", termId);
    printf("| number | course name | course id | faculty name | semester | capacity | no. enrollments | department | place |\n");
    printf("|--------|-------------|-----------|--------------|----------|----------|-----------------|------------|-------|\n");
    print_offering_student(headOffer, 1, termId);

    while(1){
        printf("1. Search\n2. Enroll in course\n3. Withdraw course\n4. Go back\nEnter an option: ");
        int option; scanf("%d%*c", &option);
        if (option == 4) return;
        idk(me, termId, option);
    }

}

static void report_card_semester(Student* me) {
    printf("Enter semester number: ");
    ll termId; scanf("%lld%*c", &termId);

    Term_student* tr = me->head_term;
    while (tr != NULL && tr->id != termId) tr = tr->next;

    printf("Report card - %s %s - %lld\n", me->name, me->lastname, termId);
    if (tr == NULL) {
        printf("Such term doesn't exist.\n");
        return;
    }

    printf("| course name | grade | instructor's name |\n|-------------|-------|--------------------|\n");
    int enrolled = 0, graded = 0, passed = 0;
    Course_student* cr = tr->head_course;
    while (cr != NULL) {
       
        Offer* off = headOffer;
        while (off != NULL && !(off->termId == termId && strcmp(off->course->id, cr->id) == 0)) off = off->next;
        const char* courseName = (off != NULL) ? off->course->name : cr->id;
        const char* instructor = (off != NULL) ? off->faculty->name : "-";

        enrolled++;
        if (cr->score < 0.0f) {
            printf("| %s | not graded yet | %s |\n", courseName, instructor);
        } else {
            printf("| %s | %.2f | %s |\n", courseName, cr->score, instructor);
            graded++;
            if (cr->score >= 10.0f) passed++;
        }
        cr = cr->next;
    }
    printf("Enrolled courses: %d\nPassed courses: %d\nFailed courses: %d\n",
        enrolled, passed, graded - passed);
    printf("Term GPA: %.2f\n", tr->GPA);
}

static void print_field(const char* label, const char* value) {
    printf("|%s", label);
    print_space(20 - (int)strlen(label));
    printf("|%s", value);
    print_space(20 - (int)strlen(value));
    printf("|\n");
}

static void report_card(Student* me) {
    char buf[64];
    printf("Student: Report Card\n");

    snprintf(buf, sizeof(buf), "%lld", me->id);       print_field("student id", buf);
    print_field("first name", me->name);
    print_field("last name", me->lastname);
    snprintf(buf, sizeof(buf), "%lld", me->kodemeli);  print_field("national code", buf);
    print_field("field", me->reshte);
    snprintf(buf, sizeof(buf), "%lld", me->year);      print_field("entrance year", buf);
    print_field("section", me->maghta);
    print_field("mentor", me->ostadrahnama);
    print_field("department", me->department);
    snprintf(buf, sizeof(buf), "%.2f", me->gpa);       print_field("GPA", buf);

    printf("1. Go to semester\n2. Go back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 1) {
        report_card_semester(me);
        report_card(me);
    }
}

static void student_courses(Student* me) {
    printf("List of courses\nenter semester number:");
    int idd ; scanf("%d%*c", &idd);
    printf("| no | course id |\n");
    printf("|----|-------------|\n");
    Term_student* tr = me->head_term;
    
    while(tr != NULL){
        if(tr->id == idd){
            int num = 0;
            Course_student* cr = tr->head_course;
            while(cr != NULL){
                printf("| %d | %s |\n", ++num, cr->id);
                cr = cr->next;
            }
            
            break;
        }
        tr = tr->next;
    }
    while(1){
        int option = 0;
    
        printf("1.search 2. back\n enter ur option:");
        scanf("%d%*c", &option);
        if(option == 2) return;
        printf("Enter course id: ");
        char id[64]; scanf("%63s%*c", id);
        if(tr != NULL){
            int num = 0;
            Course_student* cr = tr->head_course;
            bool flag = 0;
            while(cr != NULL){
                if(strcmp(id, cr->id) == 0){
                    printf("| %s |\n", cr->id);
                    flag = 1;
                    break;
                }
                
                cr = cr->next;
            }
            if(!flag){
                printf("there is no course with this id\n");
            }
        }
    }
    

}

static void nazarsanji(Student* me) {
    Term_student* tr = me->head_term;
    while (tr != NULL && tr->id != term.id) tr = tr->next;
    if (tr == NULL) { printf("You have no courses this term to rate.\n"); return; }

    Course_student* cr = tr->head_course;
    while (cr != NULL) {
        Offer* off = headOffer;
        while (off != NULL && !(off->termId == term.id && strcmp(off->course->id, cr->id) == 0)) off = off->next;
        if (off != NULL) {
            printf("Rate %s (1-10): ", off->course->name);
            int rating; scanf("%d%*c", &rating);
            if (rating < 1) rating = 1;
            if (rating > 10) rating = 10;
            off->rating_sum += rating;
            off->rating_count++;
        }
        cr = cr->next;
    }
    reset_file_offer();
    printf("Thanks for your feedback.\n");
}

void dashboard_student(Student* me) {
    int surveyOpen = (term.state[2] == 2);
    printf("Student\nWelcome %s %s\n1. Offerings\n2. Courses\n3. Report card\n", me->name, me->lastname);
    if (surveyOpen) printf("4. Course evaluation\n5. Log out\nEnter an option: ");
    else printf("4. Log out\nEnter an option: ");

    int option; scanf("%d%*c", &option);
    if (option == 1) student_offerings(me);
    else if (option == 2) student_courses(me);
    else if (option == 3) report_card(me);
    else if (surveyOpen && option == 4) nazarsanji(me);
    else if ((surveyOpen && option == 5) || (!surveyOpen && option == 4)) return;

    dashboard_student(me);
}
