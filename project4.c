
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define B 1009

typedef struct TUPLE *TUPLELIST;//list of tuples

struct TUPLE {
	int StudentId;
	char Name[30];
	char Address[50];
	char Phone[8];
	//struct TUPLE next;
	//struct TUPLELIST next;
};
struct TUPLELIST{
	struct TUPLE* head;
};
struct TUPLE* createTUPLE(int StudentId, char Name[], char Address[], char Phone[]);
struct TUPLELIST HASHTABLE[B];
void insert(struct TUPLE* tuple);
int h(int x);
int h(int x) {
	return x % B;
}
struct TUPLE* createTUPLE(int StudentId, char Name[], char Address[], char Phone[]){
	struct TUPLE* x = (struct TUPLE*) malloc(sizeof(struct TUPLE));
	strcpy(x->Name, Name);
	strcpy(x->Address, Address);
	x->StudentId = StudentId;
	strcpy(x->Phone, Phone);
	//x->next = NULL;
	return x;
}
void insert(struct TUPLE* tuple){
	int hash = h(tuple->StudentId);
	printf("%d\n\n", hash);
	if (HASHTABLE[hash].head == NULL){
		HASHTABLE[hash].head = tuple;
	}
	else{
		HASHTABLE[hash].head = tuple;
	}
}

int main() {
	struct TUPLE* x = createTUPLE(000, "Lilian", "1414 woodoak", "213555");
	printf("%s\n", x->Name);
	insert(x);
	printf("%s\n", HASHTABLE[0].head->Phone);
	struct TUPLE* m = createTUPLE(02, "lil", "7 afewf", "3335");
	insert(m);
	int m_hash = h(m->StudentId);
	printf("%s\n", HASHTABLE[m_hash].head->Phone);
	return 0;

}