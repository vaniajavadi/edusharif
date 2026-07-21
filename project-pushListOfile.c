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

void rtrim(char* str){
	int start = 0;
	int end = strlen(str) - 1;
	if(str[start] == ' ')
		stat++;
	if(str[end] == ' ')
		end--;


	int index = 0;
	int i = start;
	while(i <= end){
		str[inedx] = str[i];
		i++;
		index++;
	}

	str[index] = '\0';
	return;
}
void push_student(st, ptr){
	if(headStudent == NULL){
		headStudent = st;
		return;
	}

	if(ptr->next == NULL){
		st->prev = ptr;
		ptr->next = st;
		return;
	}

	push_student(st, ptr->next);
	return;
}


void push_file_student(line){
	FILE *fp = fopen("student.csv", "a");
	fprinf(fp, "%s", line);
	fprinf(fp, "enrolled_offerings: {\n}\n");
	fclose(fp);
	return;

}

void add_student(char* line){
	//|first name |last name |student id |password| national code |field |entrance year |section |mentor |department| answer 1 | answer 2 | answer 3|
	char* tmp = line;
	line[strscpn(line, "\n")] = '0';

	char* token;

	Student* st = (student*)malloc(sizeof(student));


	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->name, token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->lastname, token);

	token = strtok(line, "|");
	trim(token);
	st->id = atoi(token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->password, token);

	token = strtok(line, "|");
	trim(token);
	st->kodemeli = atoi(token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->reshte, token);

	token = strtok(line, "|");
	trim(token);
	st->year = atoi(token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->maghta, token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->ostadrahnama, token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->department, token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->answer1, token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->answer2, token);

	token = strtok(line, "|");
	rtrim(token);
	strcpy(st->answer3, token);

	st->gpa = 0;
	st->head = NULL;
	st->next = NULL;
	st->prev = NULL;
	push_student(st, headStudent);
	push_file_student(tmp);
}
///////////////////////////////////////////////////////////