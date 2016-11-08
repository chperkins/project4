
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>

#define B 1009

int main() {



}

typedef struct TUPLE *TUPLELIST;
struct TUPLE {
	int StudentId;
	char Name[30];
	char Address[50];
	char Phone[8];
	TUPLELIST next;
};

typedef TUPLELIST HASHTABLE[B];

int h(int x) {

	return x % B;
}