#include "shoro.h"


static void push_offer(Offer* off, Offer* ptr) {
    if (headOffer == NULL) { off->next = NULL; off->prev = NULL; headOffer = off; return; }
    if (ptr->next == NULL) { off->next = NULL; off->prev = ptr; ptr->next = off; return; }
    push_offer(off, ptr->next);
}

void reset_file_offer(void) {
    FILE* fp = fopen("offerings.csv", "w");
    if (fp == NULL) return;
    Offer* ptr = headOffer;
    while (ptr != NULL) {
        /* |course id|department|address|faculty username|term id|enrollment|capacity|rating sum|rating count| */
        fprintf(fp, "|%s|%s|%s|%s|%lld|%d|%d|%d|%d|\n",
            ptr->course->id, ptr->department, ptr->address, ptr->faculty->username,
            ptr->termId, ptr->enrollment, ptr->zarfiyat, ptr->rating_sum, ptr->rating_count);
        ptr = ptr->next;
    }
    fclose(fp);
}

static Course* find_course_by_id(const char* id) {
    Course* c = headCourse;
    while (c != NULL) { if (strcmp(c->id, id) == 0) return c; c = c->next; }
    return NULL;
}

static Faculty* find_faculty_by_username(const char* username) {
    Faculty* f = headFaculty;
  
    
    while (f != NULL) { if (strcmp(f->username, username) == 0) return f; f = f->next; }
    return NULL;
}

void read_offering(void) {
    char* line = NULL; size_t bufferSize = 0; ssize_t nread;
    FILE* fp = fopen("offerings.csv", "r");
    if (fp == NULL) return;

    while ((nread = getline(&line, &bufferSize, fp)) != -1) {
        if (line[0] != '|') continue;
        char* work = dup_safe(line);
        work[strcspn(work, "\r\n")] = '\0';
        char* saveptr;
        char* token;

        token = strtok_r(work, "|", &saveptr); trim(token); char* courseId = dup_safe(token);
        token = strtok_r(NULL, "|", &saveptr); trim(token); char* department = token;
        token = strtok_r(NULL, "|", &saveptr); trim(token); char* address = token;
        token = strtok_r(NULL, "|", &saveptr); trim(token); char* facultyUsername = token;
        token = strtok_r(NULL, "|", &saveptr); ll termId = safe_atoll(token);
        token = strtok_r(NULL, "|", &saveptr); int enrollment = safe_atoi(token);
        token = strtok_r(NULL, "|", &saveptr); int zarfiyat = safe_atoi(token);
        token = strtok_r(NULL, "|", &saveptr); int ratingSum = token ? safe_atoi(token) : 0;
        token = strtok_r(NULL, "|", &saveptr); int ratingCount = token ? safe_atoi(token) : 0;

        Course* course = find_course_by_id(courseId);
        Faculty* faculty = find_faculty_by_username(facultyUsername);

        if (course == NULL || faculty == NULL) {
        
            printf("Warning: an offering for course '%s' was skipped (course or faculty no longer exists).\n", courseId);
        } else {
            Offer* off = creat_offer(course, department, address, faculty, termId, enrollment, zarfiyat, NULL, NULL, NULL);
            off->rating_sum = ratingSum;
            off->rating_count = ratingCount;
            push_offer(off, headOffer);
        }

        free(courseId);
        free(work);
    }

    free(line);
    fclose(fp);
}

static void print_single_offer(Offer* offer) {
    if (offer == NULL) { printf("Offering doesn't exist.\n"); return; }
    printf("| %s | %s | %s | %lld | %d | %d | %s | %s |\n",
        offer->course->name, offer->course->id, offer->faculty->username,
        offer->termId, offer->zarfiyat, offer->enrollment, offer->department, offer->address);
}

static int print_offering_admin(Offer* ptr, int no, ll termId) {
    if (ptr == NULL) return no;
    if (ptr->termId == termId) {
        printf("| %d | %s | %s | %s | %lld | %d | %d | %s | %s |\n",
            no, ptr->course->name, ptr->course->id, ptr->faculty->username,
            ptr->termId, ptr->zarfiyat, ptr->enrollment, ptr->department, ptr->address);
        no++;
    }
    return print_offering_admin(ptr->next, no, termId);
}

static Offer* search_offer(int num, ll termId, Offer* ptr) {
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

void remove_offer(Offer* off) {
    if (off == NULL) return;
    if (off == headOffer) {
        headOffer = off->next;
        if (headOffer != NULL) headOffer->prev = NULL;
    } else {
        if (off->prev != NULL) off->prev->next = off->next;
        if (off->next != NULL) off->next->prev = off->prev;
    }
    free(off->department);
    free(off->address);
    free(off);
}

static void add_st_offer(Offer* offer, Student* st) {
    Term_student* tr = st->head_term;
    while (tr != NULL && tr->id != offer->termId) tr = tr->next;
    if (tr == NULL) {
        tr = creat_term_student(offer->termId, NULL, st->head_term, NULL);
        if (st->head_term != NULL) st->head_term->prev = tr;
        st->head_term = tr;
    }

    Course_student* cr = tr->head_course;
    while (cr != NULL) {
        if (strcmp(cr->id, offer->course->id) == 0) {
            printf("Student is already enrolled in this course.\n");
            return;
        }
        cr = cr->next;
    }

    cr = creat_course_student(offer->course->id, -1.0f, tr->head_course, NULL); 
    if (tr->head_course != NULL) tr->head_course->prev = cr;
    tr->head_course = cr;

    offer->enrollment++;
    recompute_student_gpa(st);
    reset_file_student();
    reset_file_offer();
    printf("Student enrolled successfully.\n");
}

static void remove_st_offer(Offer* offer, Student* st) {
    Term_student* tr = st->head_term;
    while (tr != NULL && tr->id != offer->termId) tr = tr->next;
    if (tr == NULL) { printf("Student is not enrolled this term.\n"); return; }

    Course_student* cr = tr->head_course;
    while (cr != NULL && strcmp(cr->id, offer->course->id) != 0) cr = cr->next;
    if (cr == NULL) { printf("Student is not enrolled in this course.\n"); return; }

    if (cr->prev != NULL) cr->prev->next = cr->next; else tr->head_course = cr->next;
    if (cr->next != NULL) cr->next->prev = cr->prev;
    free(cr->id);
    free(cr);

    offer->enrollment--;
    recompute_student_gpa(st);
    reset_file_student();
    reset_file_offer();
    printf("Student withdrawn successfully.\n");
}

static void add_remove_st(int type, ll termId) {
    printf("Enter student id: ");
    ll studentId; scanf("%lld%*c", &studentId);
    printf("Enter offering number: ");
    int num; scanf("%d%*c", &num);

    Student* key = creat_student(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                  0.0, studentId, 0, 0, 1, NULL, NULL, NULL);
    Student* st = search_student(headStudent, key);
    Offer* offer = search_offer(num, termId, headOffer);

    if (st == NULL) { printf("Student not found.\n"); return; }
    if (offer == NULL) { printf("Offering not found.\n"); return; }

    print_student(st);
    print_single_offer(offer);

    if (type == 1) {
        remove_st_offer(offer, st);
    } else if (offer->enrollment >= offer->zarfiyat) {
        printf("NOT POSSIBLE! Class is full.\n");
    } else {
        add_st_offer(offer, st);
    }
}

void admin_offerings(void) {
    printf("Enter semester number: ");
    ll termId; scanf("%lld%*c", &termId);

    printf("List of offerings - %lld\n", termId);
    printf("| number | course name | course id | faculty id | semester | capacity | no. enrollments | department | place |\n");
    printf("|--------|-------------|-----------|------------|----------|----------|-----------------|------------|-------|\n");
    print_offering_admin(headOffer, 1, termId);

    printf("1. Search\n2. Add student to an offering\n3. Remove student from an offering\n4. Go back\nEnter an option: ");
    int option; scanf("%d%*c", &option);

    if (option == 4) return;
    else if (option == 2) add_remove_st(0, termId);
    else if (option == 3) add_remove_st(1, termId);
    else if (option == 1) {
        printf("Enter course id to search: ");
        char id[64]; scanf("%63s%*c", id);
        Offer* ptr = headOffer;
        while (ptr != NULL) {
            if (ptr->termId == termId && strcmp(ptr->course->id, id) == 0) print_single_offer(ptr);
            ptr = ptr->next;
        }
    }
    admin_offerings();
}



static void unenroll_all_from_offer(Offer* off) {
    Student* st = headStudent;
    while (st != NULL) {
        Term_student* tr = st->head_term;
        while (tr != NULL && tr->id != off->termId) tr = tr->next;
        if (tr != NULL) {
            Course_student* cr = tr->head_course;
            while (cr != NULL) {
                Course_student* next = cr->next;
                if (strcmp(cr->id, off->course->id) == 0) {
                    if (cr->prev != NULL) cr->prev->next = cr->next; else tr->head_course = cr->next;
                    if (cr->next != NULL) cr->next->prev = cr->prev;
                    free(cr->id);
                    free(cr);
                    recompute_student_gpa(st);
                }
                cr = next;
            }
        }
        st = st->next;
    }
    reset_file_student();
}

void accept_request(Request* rqst) {
    if (rqst == NULL) {
        printf("There is no request with that number.\n");
        return;
    }

    if (rqst->type == 0) {            
        if (term.state[1] == 2) {
            printf("NOT POSSIBLE! Course selection period is already over.\n");
        } else {
            Offer* offer = creat_offer(rqst->course, rqst->course->daneshkade, rqst->address,
                                        rqst->faculty, term.id, 0, rqst->enroll,
                                        NULL, headOffer, NULL);
            if (headOffer != NULL) headOffer->prev = offer;
            headOffer = offer;
            reset_file_offer();
            printf("Offering created.\n");
        }
    }
    else if (rqst->type == 1) {           
        if (rqst->offer != NULL) unenroll_all_from_offer(rqst->offer);
        remove_offer(rqst->offer);
        reset_file_offer();
        printf("Offering removed.\n");
    }
    else if (rqst->type == 2) {             
        if (rqst->offer != NULL) rqst->offer->zarfiyat = rqst->enroll;
        reset_file_offer();
        printf("Capacity updated.\n");
    }

    remove_request(rqst);
}

void admin_request(void) {
    printf("List of requests:\n");
    if (headRequest == NULL) printf("(no pending requests)\n");
    print_request_list(1, headRequest);

    printf("1. Accept request\n2. Go back\nEnter an option: ");
    int option; scanf("%d%*c", &option);
    if (option == 2) return;

    printf("Enter request's number: ");
    int number; scanf("%d%*c", &number);
    accept_request(search_request(number, 1, headRequest));

    admin_request();
}
