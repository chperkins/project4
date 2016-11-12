
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define B 1009
struct CP* createCP(char Course[], char Prerequisite[]);
struct TUPLE* createTUPLE(int StudentId, char Name[], char Address[], char Phone[]);
struct CSG* createCSG(char Course[], int StudentId, char Grade[]);
void insertCSG(struct CSG* csg);
struct TUPLE* lookup(struct TUPLE* tuple);
struct CSG* lookupCSG(struct CSG* csg);
void deleteCSG(struct CSG* csg);
void insert(struct TUPLE* tuple);
void deleteCP(struct CP* cp);
int h(int x);
struct CPLIST* lookupCP(char Course[]);//lookup prerequisites for course



///**************CP = Course, Prerequisites *************************//

typedef struct CP *CPLIST;
struct CP{//Course, Prerequisite
	char Course[5];
	char Prerequisite[5];
	CPLIST next;
};
struct CPLIST{
	struct CP* head;
};
struct CPLIST HASHTABLE_CP[B];

struct CP* createCP(char Course[], char Prerequisite[]){
	struct CP* x = (struct CP*) malloc(sizeof(struct CP));
	strcpy(x->Course, Course);
	strcpy(x->Prerequisite, Prerequisite);
	x->next = NULL;
	return x;
}
void insertCP(struct CP* cp){
	int hash = h(*cp->Course );
	if (HASHTABLE_CP[hash].head != NULL){//if there's a collision
		struct CP* new_CP = HASHTABLE_CP[hash].head;
		while(new_CP != NULL){//go through the list to find the next empty bucket

			new_CP = HASHTABLE_CP[hash].head->next;
			printf("New_CP's course is %s\n", new_CP->Course);
			if (new_CP == NULL){
				new_CP = cp;
				HASHTABLE_CP[hash].head->next = new_CP;
				new_CP->next = NULL;
				break;
			}
		}
	}
	else{
		HASHTABLE_CP[hash].head = cp;
	}
}
struct CPLIST* lookupCP(char Course[]){//lookup prerequisites for course
	int hash = h(*Course );
	return &HASHTABLE_CP[hash];
}
void deleteCP(struct CP* cp){
	int hash = h(*cp->Course );
	if (HASHTABLE_CP[hash].head != NULL){
		HASHTABLE_CP[hash].head = NULL;
	}
}

///**************TUPLE = SNAP *************************//
typedef struct TUPLE *TUPLELIST;//list of tuples
struct TUPLE {//TUPLE = SNAP
	int StudentId;
	char Name[30];
	char Address[50];
	char Phone[8];
	TUPLELIST next;
};
struct TUPLELIST{
	struct TUPLE* head;
};
struct TUPLELIST HASHTABLE[B];


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
void insertSNAP(struct TUPLE* tuple){
	int hash = h(tuple->StudentId);
	HASHTABLE[hash].head = tuple;//assume there are no collisions because student ids are unique
}
void deleteSNAP(struct TUPLE* tuple){
	int hash = h(tuple->StudentId);
	if (HASHTABLE[hash].head != NULL){
		HASHTABLE[hash].head = NULL;
	}
}
struct TUPLE* lookup(struct TUPLE* tuple){//lookup with the tuple
	int key = h(tuple->StudentId);
	return HASHTABLE[key].head;
}
//****************************************///
					//CSGs
//***************************************///
typedef struct CSGLIST *CSGLIST;
struct CSG {
	char Course[5];
	int StudentId;
	char Grade[2];
	CSGLIST next;
};
struct CSGLIST{
	struct CSG* head;
};
struct CSGLIST HASHTABLE_CSG[B];

struct CSG* createCSG(char Course[], int StudentId, char Grade[]){
	struct CSG* x = (struct CSG*) malloc(sizeof(struct CSG));
	strcpy(x->Course, Course);
	strcpy(x->Grade, Grade);
	x->StudentId = StudentId;
	x->next = NULL;
	return x;
}

void insertCSG(struct CSG* csg){//use STUDENT ID as the hashtable
	int hash = h(csg->StudentId);
	HASHTABLE_CSG[hash].head = csg;
}
void deleteCSG(struct CSG* csg){
	int hash = h(csg->StudentId);
	if (HASHTABLE_CSG[hash].head != NULL){
		HASHTABLE_CSG[hash].head = NULL;
	}
}
struct CSG* lookupCSG(struct CSG* csg){//lookup with the tuple
	int key = h(csg->StudentId);
	return HASHTABLE_CSG[key].head;
}


int main() {
	struct CP* cp = createCP("CS101", "CS100");
	insertCP(cp);
	struct CP* cp2 = createCP("CS101", "CS102");
	insertCP(cp2);
	int hash = h(*cp->Course );

	printf("%s\n", lookupCP("CS101")->head->next->Prerequisite);
	return 0;

}