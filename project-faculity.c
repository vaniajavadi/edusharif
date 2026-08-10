#include "shoro.h"

static void print_my_offering(Offer* ptr, int no, Faculty* me) {
    if (ptr == NULL) return;
    if (strcmp(ptr->faculty->username, me->username) == 0) {
        printf("| %d | %s | %s | %s | %lld | %d | %d | %s | %s |\n",
            no, ptr->course->name, ptr->course->id, ptr->faculty->username,
            ptr->termId, ptr->zarfiyat, ptr->enrollment, ptr->department, ptr->address);
        no++;
    }
    print_my_offering(ptr->next, no, me);
}

static Offer* find_my_offering(Offer* ptr, int num, Faculty* me) {
    int cur = 0;
    while (ptr != NULL) {
        if (strcmp(ptr->faculty->username, me->username) == 0) {
            cur++;
            if (cur == num) return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

static void print_single_offering(Offer* off) {
    printf("| %s | %s | %s | %lld | %d | %d | %s | %s |\n",
        off->course->name, off->course->id, off->faculty->username,
        off->termId, off->zarfiyat, off->enrollment, off->department, off->address);
    if (off->rating_count > 0) {
        printf("Course evaluation: average %.1f/10 from %d student(s).\n",
            (float)off->rating_sum / off->rating_count, off->rating_count);
    } else {
        printf("Course evaluation: no ratings submitted yet.\n");
    }
}

static void record_grades(Offer* off) {
    printf("Enter file name or address: \n(\"student id\" : grade;\n \"student id\" : grade;)\n");
    char filename[256];
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\r\n")] = '\0';

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open that file.\n");
    } else {
        char* line = NULL; size_t bufferSize = 0; ssize_t nread;
        while ((nread = getline(&line, &bufferSize, fp)) != -1) {
            char* p = line;
            if(p[0] == '"'){
                long long studentId;
                float score;
                if(sscanf(p, "\"%lld\" : %f;", &studentId, &score) == 2){
                    Student* st = search_student(headStudent, creat_student(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                  0.0, studentId, 0, 0, 1, NULL, NULL, NULL));
                    if(st != NULL){
                        Term_student* tr = st->head_term;
                        while(tr != NULL && tr->id != off->termId)
                            tr = tr->next;
                        if(tr != NULL){
                            Course_student* cr = tr->head_course;
                            while(cr != NULL && strcmp(cr->id, off->course->id) != 0)
                                cr = cr->next;
                            if(cr != NULL){
                                cr->score = score;
                                recompute_student_gpa(st);

                            }
                        }
                    }
                }
            }
        }
        free(line);
        fclose(fp);
    }
   reset_file_student();
    printf("Grades recorded.\n");
}

static void my_offer_menu(Faculty* me) {
    printf("Faculty: My offerings\n");
    printf("| number | course name | course id | faculty id | semester | capacity | no. enrollments | department | place |\n");
    printf("|--------|-------------|-----------|------------|----------|----------|-----------------|------------|-------|\n");
    print_my_offering(headOffer, 1, me);

    printf("1. Go to offering\n2. Search\n3. Go back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 3) return;

    if (option == 2) {
        printf("Enter course id: ");
        char id[64]; scanf("%63s%*c", id);
        Offer* ptr = headOffer;
        int found = 0;
        while (ptr != NULL) {
            if (strcmp(ptr->faculty->username, me->username) == 0 && strcmp(ptr->course->id, id) == 0) {
                print_single_offering(ptr);
                found = 1;
            }
            ptr = ptr->next;
        }
        if (!found) printf("No offering of yours matches that course id.\n");
        my_offer_menu(me);
        return;
    }

    if (option != 1) { my_offer_menu(me); return; }

    printf("Enter offering number: ");
    int num; scanf("%d%*c", &num);
    Offer* off = find_my_offering(headOffer, num, me);
    if (off == NULL) { printf("Offering not found.\n"); my_offer_menu(me); return; }
    print_single_offering(off);

    printf("1. Add capacity\n2. Record grades\n3. Remove offering\n4. Go back\nEnter an option: ");
    int sub; scanf("%d%*c", &sub);

    if (sub == 1) {
        printf("Enter new capacity: ");
        int cap; scanf("%d%*c", &cap);
        Request* rqst = creat_request(2, cap, me, off->course, off, me->department, headRequest, NULL);
        if (headRequest != NULL) headRequest->prev = rqst;
        headRequest = rqst;
        printf("Capacity increase request sent to admin.\n");
    } else if (sub == 2) {
        if (term.state[3] != 1) {
            printf("NOT POSSIBLE! Grade recording is not open right now.\n");
        } else {
            record_grades(off);
        }
    } else if (sub == 3) {
        Request* rqst = creat_request(1, 0, me, off->course, off, me->department, headRequest, NULL);
        if (headRequest != NULL) headRequest->prev = rqst;
        headRequest = rqst;
        printf("Removal request sent to admin.\n");
    }

    my_offer_menu(me);
}

static void print_course_readonly(Course* ptr) {
    if (ptr == NULL) return;
    printf("| %s | %s | %d | %s | %s | %s | %s |\n",
        ptr->name, ptr->id, ptr->tedad_vahed, ptr->phishniaz, ptr->maghta, ptr->reshte, ptr->daneshkade);
    print_course_readonly(ptr->next);
}

static void list_courses_for_faculty(void) {
    printf("List of courses\n");
    printf("| course name | course id | units | prerequisites (separated by comma) | section | field | department |\n");
    printf("|-------------|-----------|-------|------------------------------------|---------|-------|------------|\n");
    print_course_readonly(headCourse);
     printf("1.search\n 2.back\n Enter ur option:");
    int option;
    scanf("%d%*c", &option);
    if(option == 2){
        return;
    }
    printf("Enter course id: ");
    char id[64]; scanf("%63s%*c", id);

    Course* ptr = headCourse;
    while(ptr != NULL){
        if(strcmp(id, ptr->id) == 0){
            printf("| %s | %s | %d | %s | %s | %s | %s |\n",
             ptr->name, ptr->id, ptr->tedad_vahed, ptr->phishniaz, ptr->maghta, ptr->reshte, ptr->daneshkade);
            return;
        }
        ptr = ptr->next;
    }
    printf("No such course was founded");
    
}

static void print_offering_all(Offer* ptr, int no, ll termId) {
    if (ptr == NULL) return;
    if (ptr->termId == termId) {
        printf("| %d | %s | %s | %s | %lld | %d | %d | %s | %s |\n",
            no, ptr->course->name, ptr->course->id, ptr->faculty->username,
            ptr->termId, ptr->zarfiyat, ptr->enrollment, ptr->department, ptr->address);
        no++;
    }
    print_offering_all(ptr->next, no, termId);
}

static void offerings_in_semester(void) {
    printf("Enter semester number: ");
    ll termId; scanf("%lld%*c", &termId);
    printf("| number | course name | course id | faculty id | semester | capacity | no. enrollments | department | place |\n");
    printf("|--------|-------------|-----------|------------|----------|----------|-----------------|------------|-------|\n");
    print_offering_all(headOffer, 1, termId);
    printf("1.search\n 2.back\n Enter ur option:");
    int option;
    scanf("%d%*c", &option);
    if(option == 2){
        return;
    }
    printf("Enter offer num: ");
    scanf("%d%*c", &option);
    int num = 0;
    Offer* ptr = headOffer;
    while(ptr != NULL){
        if (ptr->termId == termId) {
            num++;
            if(num == option){
                printf("| %s | %s | %s | %lld | %d | %d | %s | %s |\n",
                ptr->course->name, ptr->course->id, ptr->faculty->username,
                ptr->termId, ptr->zarfiyat, ptr->enrollment, ptr->department, ptr->address);
                return;
            }
         
        }
        ptr = ptr->next;
    }
    printf("there is no such offer\n");
}

static Course* search_course_by_id_local(Course* ptr, const char* id) {
    if (ptr == NULL) return NULL;
    if (strcmp(ptr->id, id) == 0) return ptr;
    return search_course_by_id_local(ptr->next, id);
}

static Offer* find_existing_offer(const char* courseId) {
    Offer* o = headOffer;
    while (o != NULL) {
        if (o->termId == term.id && strcmp(o->course->id, courseId) == 0) {
            return o;
        }
        o = o->next;
    }
    return NULL;
}

static void offer_a_course(Faculty* me) {
    if (term.state[0] == 0 || term.state[1] == 2) {
        printf("NOT POSSIBLE! Offering period is not open right now.\n");
        return;
    }

    printf("Faculty: Offer a course\nEnter the course id: ");
    char id[64]; scanf("%63s%*c", id);

    if (find_existing_offer(id) != NULL) {
        printf("This course has been offered before.\n");
        return;
    }

    Course* course = search_course_by_id_local(headCourse, id);
    if (course == NULL) { printf("Course not found.\n"); return; }
    printf("| %s | %s | %d | %s | %s | %s | %s |\n",
        course->name, course->id, course->tedad_vahed, course->phishniaz,
        course->maghta, course->reshte, course->daneshkade);

    printf("Enter the capacity: ");
    int capacity; scanf("%d%*c", &capacity);

    Request* rqst = creat_request(0, capacity, me, course, NULL, me->department, headRequest, NULL);
    if (headRequest != NULL) headRequest->prev = rqst;
    headRequest = rqst;

    printf("Sent request to admin.\nPress any key to go to offerings...");
    
    int chhhh = _getch();
    if(chhhh == 0 || chhhh == 224){
        _getch();
    }
}

void dashboard_faculity(Faculty* me) {
    printf("Faculty\nWelcome %s %s\n1. My offerings\n2. List of offerings in semester\n3. List of courses\n4. Offer a course\n5. Log out\nEnter an option: ",
        me->name, me->lastname);

    int option; scanf("%d%*c", &option);
    if (option == 1) my_offer_menu(me);
    else if (option == 2) offerings_in_semester();
    else if (option == 3) list_courses_for_faculty();
    else if (option == 4) offer_a_course(me);
    else if (option == 5) return;

    dashboard_faculity(me);
}
