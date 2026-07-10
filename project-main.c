#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
//#include <cstdlib>
//#include <bits/stdc++.h>
//#include <iostream>
//fgets(line2, 2000, stdin);
//int size_line1 = strlen(line1) - 1; 
typedef long long ll;

//using namespace std;

/////////////////////////////////////////////////////////////// GLOBAL FUNC
Admin admin = { "admin", "aaaaa" };
Term term = {{0,0,0,0}, -1};
Student* headStudent = NULL;
Request* headRequest = NULL;
Offer* headOffer = NULL;
Faculty* headFaculty = NULL;


/////////////////////////////////////////////////////////////////main

int main(){
    read_student();
    read_faculty();
    read_course();
    login_menu();

    return 0;
}

