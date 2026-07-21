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

///////////////////////////////////////////////////////////SEARCH
Student* search_student(student* ptr, Student* st){
    if(ptr == NULL)    return NULL;

    if(st->name != NULL){
        if(ptr->name == st->name)   return ptr;
    }
    else if(st->lastname != NULL){
        if(ptr->lastname == st->lastname)   return ptr;
    }
    else{
        if(ptr->id == st->id) return ptr;
    }
    return search_student(ptr->next, st);
}

//////////////////////////////////////////////////////////////////////
Request* search_request(int no, int cur, Request* ptr){
    if(no < 1 || ptr == NULL){
        return NULL;
    }

    if(no == cur){
        return ptr;
    }
    return search_request(no, cur++, ptr->next);
}
/////////////////////////////////////////////////////////////////////

