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


// ////////////////////////////////////////////////////////student
void remove_student(Student* st){
	if(st == headStudent){
		headStudent = st->next;
		if(headStudent != NULL) 	headStudent->prev = NULL;
		return;
	}

	if(st->prev != NULL){
		st->prev->next = st->next;
	}
	if(st->next != NULL){
		st->next->prev = st->prev;
	}
	free(st);
	return;
}
///////////////////////////////////////////////////////////request
void remove_request(Request* rqst){
	if(rqst == headRequest){
		headRequest = rqst->next;
		if(headRequest != NULL) 	headRequest->prev = NULL;
		return;
	}

	if(rqst->prev != NULL){
		rqst->prev->next = rqst->next;
	}
	if(rqst->next != NULL){
		rqst->next->prev = rqst->prev;
	}
	free(rqst);
	return;
}