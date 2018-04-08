#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

int read(char str[])
{
	int Number = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++) Number = Number * 10 + str[i] - '0';
	return Number;
}

