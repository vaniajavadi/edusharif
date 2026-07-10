


void read_student();
Request* creat_request(int type, int enroll, Faculty* faculty, Course* course,
                        Offer* offer, Request* next, Request* prev)

Offer* creat_offer(Course* course, char* id, char* department, char* address,
                    Faculty* faculty, int termId, int enrollment, int zarfiyat,
                    Student* head, Offer* next, Offer* prev)


Course* creat_course(char* name, char* maghta, char* reshte, char* daneshkade,
                      char* id, char* phishniaz, int tedad_vahed,
                      Course* next, Course* prev)

Faculty* creat_faculty(char* name, char* lastname, char* reshte, char* akharinmadrak,
                        char* department, ll id, ll kodmeli, char* password,
                        Faculty* next, Faculty* prev)

Student* creat_student(char* name, char* lastname, char* password, char* reshte, char* maghta,
                        char* ostadrahnama, char* department,
                        char* answer1, char* answer2, char* answer3,
                        float gpa, ll id, ll kodemeli, ll year,
                        Term_student* head, Student* next, Student* prev)
Term_student* creat_term_student(ll id, Course_student* head, Term_student* next,
                                 Term_student* prev)

Course_student* creat_course_student(char* id, float score, Course_student* next, Course_student* prev){

Student* search_student(*student ptr, *Student st);
void search_student_menu()

void login_menu();
void login_studentOfaculity(int t)
void login_admin()
void dashboard_student()
void dashboard_faculity(Faculty* me)
void dashboard_admin()

ll get_username()
void wrong_username();
void to_lowercase(char* s);

scanf("%d%*c" &option);

push_course_student(head, cr);
push_term_student(head, tr);
push_student(st, head_student);
search_faculity();


char* calendar_message(int state);
void admin_calendar();
void student_list();
void print_student(Student* ptr);
void print_student_list(Student* ptr);




////////////////////
TEMP
strcmp(st->password, password) == 0
create_student(NULL, NULL, NULL, NULL, NULL,
                                                 NULL, NULL,
                                                 NULL, NULL, NULL,
                                                 0.0, username, 0, 0, 
                                                 NULL, NULL, NULL);
creat_faculty(NULL, NULL, NULL, NULL, NULL,
                                                 username, 0, NULL, NULL, NULL)

 char* line = NULL;
    size_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    line[strscpn(line, "\n")] = '\0';




    ///////////////////
    open:
    main->login menue-> login_student->
    main-> 
    	read->
    	login menue->
    		login_studentOfaculity
    			student_dashboard->
    			search_faculity->
    			factulity_dashboard->
    		login_admin-> admin_dashboard->

