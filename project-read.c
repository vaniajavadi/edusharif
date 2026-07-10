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

///////////////////////////////////////////////////////// READ:


void read_student(){
    char* line = NULL;
    size_t bufferSize = 0;
    ssize_t read = 0;
    FILE* fp = fopen("student.crv", "r");
    read = get_line(&line, &bufferSize, fp);
    while(read != -1){







        read = get_line(&line, &bufferSize, fp);

    }
}

