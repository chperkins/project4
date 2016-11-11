
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
	TUPLELIST next;
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
	x->next = NULL;
	return x;
}
void insert(struct TUPLE* tuple){
	int hash = h(tuple->StudentId);
	//printf("%d\n\n", hash);
	if (HASHTABLE[hash].head == NULL){
		HASHTABLE[hash].head = tuple;
	}
	else{
		HASHTABLE[hash].head = tuple;
	}
}
void delete(struct TUPLE* tuple){
	int hash = h(tuple->StudentId);
	if (HASHTABLE[hash].head != NULL){
		HASHTABLE[hash].head = NULL;
	}
}
struct TUPLE* lookup(struct TUPLE* tuple);
struct TUPLE* lookup(struct TUPLE* tuple){//lookup with the tuple
	int key = h(tuple->StudentId);
	return HASHTABLE[key].head;
}
int main() {
	struct TUPLE* x = createTUPLE(000, "Lilian", "1414 woodoak", "213555");
	printf("%s\n", x->Name);
	insert(x);
	printf("%s\n", HASHTABLE[0].head->Phone);
	struct TUPLE* m = createTUPLE(02, "lil", "7 afewf", "3335");
	insert(m);
	struct TUPLE* n = createTUPLE(3, "hay", "93'2", "2423");
	insert(n);
	int m_hash = h(m->StudentId);
	printf("%s\n", HASHTABLE[m_hash].head->Phone);
	delete(m);
	insert(m);
	printf("%p\n", HASHTABLE[m_hash].head);
	printf("%s\n", lookup(x)->Name);

	return 0;

}