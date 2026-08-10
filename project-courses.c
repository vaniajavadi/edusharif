#include "shoro.h"

static void push_course(Course* c, Course* ptr) {
    if (headCourse == NULL) { c->next = NULL; c->prev = NULL; headCourse = c; return; }
    if (ptr->next == NULL) { c->next = NULL; c->prev = ptr; ptr->next = c; return; }
    push_course(c, ptr->next);
}

static void print_course(Course* ptr) {
    if (ptr == NULL) { printf("Course doesn't exist.\n"); return; }
    printf("| %s | %s | %d | %s | %s | %s | %s |\n",
        ptr->name, ptr->id, ptr->tedad_vahed, ptr->phishniaz, ptr->maghta, ptr->reshte, ptr->daneshkade);
}

static void print_course_list(Course* ptr) {
    if (ptr == NULL) return;
    print_course(ptr);
    print_course_list(ptr->next);
}

static Course* search_course_by_id(Course* ptr, const char* id) {
    if (ptr == NULL) return NULL;
    if (strcmp(ptr->id, id) == 0) return ptr;
    return search_course_by_id(ptr->next, id);
}

static void reset_file_course(void) {
    FILE* fp = fopen("courses.csv", "w");
    if (fp == NULL) return;
    Course* ptr = headCourse;
    while (ptr != NULL) {
        fprintf(fp, "|%s|%s|%d|%s|%s|%s|%s|\n",
            ptr->name, ptr->id, ptr->tedad_vahed, ptr->phishniaz, ptr->maghta, ptr->reshte, ptr->daneshkade);
        ptr = ptr->next;
    }
    fclose(fp);
}

/* |course name|course id|units|prerequisites|section|field|department| */
static Course* add_course(char* line) {
    char* work = dup_safe(line);
    work[strcspn(work, "\r\n")] = '\0';
    char* token; char* saveptr;

    Course* c = (Course*)malloc(sizeof(Course));
    c->next = NULL;
    c->prev = NULL;

    token = strtok_r(work, "|", &saveptr); trim(token); c->name = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); c->id = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); c->tedad_vahed = safe_atoi(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); c->phishniaz = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); c->maghta = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); c->reshte = dup_safe(token);
    token = strtok_r(NULL, "|", &saveptr); trim(token); c->daneshkade = dup_safe(token);

    push_course(c, headCourse);
    free(work);
    return c;
}

static void remove_course_menu(void) {
    printf("Enter course id: ");
    char id[64];
    scanf("%63s%*c", id);
    Course* c = search_course_by_id(headCourse, id);
    if (c == NULL) { printf("Course doesn't exist.\n"); return; }

   
    Offer* o = headOffer;
    while (o != NULL) {
        if (o->course == c) {
            printf("NOT POSSIBLE!\n");
            return;
        }
        o = o->next;
    }

    print_course(c);
    printf("Remove course? [y/n] ");
    char ch; scanf(" %c%*c", &ch);
    if (ch == 'y' || ch == 'Y') {
        if (c == headCourse) { headCourse = c->next; if (headCourse) headCourse->prev = NULL; }
        else { if (c->prev) c->prev->next = c->next; if (c->next) c->next->prev = c->prev; }
        free(c->name); free(c->maghta); free(c->reshte); free(c->daneshkade);
        free(c->id); free(c->phishniaz); free(c);
        reset_file_course();
        printf("Course removed.\n");
    }
}

static void add_course_menu(void) {
    printf("Enter course info (name|id|units|phishniaz|section|field|department): ");
    char* line = NULL; size_t bufferSize = 0;
    if (getline(&line, &bufferSize, stdin) != -1) {
        add_course(line);
        reset_file_course();
        printf("Course added.\n");
    }
    free(line);
}

void read_course(void) {
    char* line = NULL; size_t bufferSize = 0; ssize_t nread;
    FILE* fp = fopen("courses.csv", "r");
    if (fp == NULL) return;
    while ((nread = getline(&line, &bufferSize, fp)) != -1) {
        if (line[0] == '|') add_course(line);
    }
    free(line);
    fclose(fp);
}

void admin_courses(void) {
    printf("List of courses\n");
    printf("| course name | course id | units | prerequisites (separated by comma) | section | field | department |\n");
    printf("|-------------|-----------|-------|------------------------------------|---------|-------|------------|\n");
    print_course_list(headCourse);
    printf("1. Search\n2. Add a course\n3. Remove a course\n4. Go back\nEnter an option: ");

    int option; scanf("%d%*c", &option);
    if (option == 4) return;
    else if (option == 2) add_course_menu();
    else if (option == 3) remove_course_menu();
    else if (option == 1) {
        printf("Enter course id to search: ");
        char id[64]; scanf("%63s%*c", id);
        print_course(search_course_by_id(headCourse, id));
    }
    admin_courses();
}
