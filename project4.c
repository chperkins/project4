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


///**************CDH = Course, Day, Hour *************************//

typedef struct CDH *CDHLIST;
struct CDH{
	char* Course;
	char* Day;
	char* Hour;
	CDHLIST next;
};
struct CDHLIST{
	struct CDH* head;
};
struct CDHLIST HASHTABLE_CDH[B];
struct CDH* createCDH(char* Course, char* Day, char* Hour) {
	struct CDH* x = (struct CDH*) malloc(sizeof(struct CDH));
	x->Course=Course;
	x->Day=Day;
	x->Hour=Hour;
	x->next = NULL;
	return x;
}
void insertCDH(struct CDH* cdh);
void insertCDH(struct CDH* cdh){
	/*int hash = h(*cdh->Course);
	printf("Inserting cdh into %d\n", hash);
	if (HASHTABLE_CDH[hash].head != NULL){
		printf("collision\n\n");
		struct CDH* new_CDH = HASHTABLE_CDH[hash].head;
		//new_CDH = HASHTABLE_CDH[hash].head->next;
		while(new_CDH != NULL){//go through the list to find the next empty bucket
			new_CDH = new_CDH->next;
			printf("New_CDH's course is %s\n", new_CDH->Course);
			if (new_CDH== NULL){//this is the empty bucket
				printf("Pointer is %p\n", new_CDH);
				new_CDH = cdh;
				printf("Now, the pointer is %p\n", new_CDH);
				printf("New course is %s\n", new_CDH->Course);
				printf("New time is %s\n", new_CDH->Hour);
				printf("pointer to next is %p\n", new_CDH->next);
				//HASHTABLE_CDH[hash].head->next = new_CDH;
				new_CDH->next = NULL;
				break;
			}
		}
	}
	else{
		HASHTABLE_CDH[hash].head = cdh;
	}*/
	int hash = h(*cdh->Course );
	if (HASHTABLE_CDH[hash].head != NULL){//if there's a collision
		struct CDH* new_CDH = HASHTABLE_CDH[hash].head;
	//int i = 0;
		while(new_CDH != NULL){//go through the list to find the next empty bucket
			//printf("old cp's prerequisite is %s\n", new_CP->Prerequisite);
			//i++;
			//printf("\ni is %d\n", i);
			struct CDH* prev = new_CDH;
			new_CDH = new_CDH->next;
			//printf("New_CP's course is %s\n", new_CP->Course);
			if (new_CDH == NULL){
				
				new_CDH = cdh;
				prev->next = new_CDH;
				//printf("New_CP's course is %s\n", new_CP->Course);

				new_CDH->next = NULL;
				break;
			}
		}
	}
	else{
		HASHTABLE_CDH[hash].head = cdh;
	}
}
struct CDHLIST* lookupCDH(char Course[]);
struct CDHLIST* lookupCDH(char Course[]){
	int hash = h(*Course);
	printf("Hash is %d\n", hash);
	return &HASHTABLE_CDH[hash];
}
void deleteCDH(struct CDH* cdh){
	int hash = h(*cdh->Course);
	struct CDH* temp_cdh = HASHTABLE_CDH[hash].head;
	if (*cdh->Day == *temp_cdh->Day && *cdh->Hour == *temp_cdh->Hour){
		//HASHTABLE_CDH[hash].head = NULL;
		HASHTABLE_CDH[hash].head = HASHTABLE_CDH[hash].head->next;
	}
	else{
		while(temp_cdh != NULL){
			temp_cdh = temp_cdh->next;
			if (*temp_cdh->Day == *cdh->Day && *temp_cdh->Hour == *cdh->Hour){
				///HASHTABLE_CDH[]
				temp_cdh = NULL;
				break;
			}
		}
	}

}
///**************CP = Course, Prerequisites *************************//

typedef struct CP *CPLIST;
struct CP{//Course, Prerequisite
	char* Course;
	char* Prerequisite;
	CPLIST next;
};
struct CPLIST{
	struct CP* head;
};
struct CPLIST HASHTABLE_CP[B];

struct CP* createCP(char* Course, char* Prerequisite){
	struct CP* x = (struct CP*) malloc(sizeof(struct CP));
	x->Course=Course;
	x->Prerequisite=Prerequisite;
	x->next = NULL;
	return x;
}
void insertCP(struct CP* cp){
	int hash = h(*cp->Course );
	if (HASHTABLE_CP[hash].head != NULL){//if there's a collision
		struct CP* new_CP = HASHTABLE_CP[hash].head;
	int i = 0;
		while(new_CP != NULL){//go through the list to find the next empty bucket
			//printf("old cp's prerequisite is %s\n", new_CP->Prerequisite);
			i++;
			printf("\ni is %d\n", i);
			struct CP* prev = new_CP;
			new_CP = new_CP->next;
			//printf("New_CP's course is %s\n", new_CP->Course);
			if (new_CP == NULL){
				
				new_CP = cp;
				prev->next = new_CP;
				//printf("New_CP's course is %s\n", new_CP->Course);

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
		//HASHTABLE_CP[hash].head = NULL;
		/*struct temp_cp = HASHTABLE_CP[hash].head;
		while(temp_cp ->Course != cp->Course && temp_cp->Prerequisite != cp->Prerequisite){
			struct CP* prev = temp_cp;
			temp_cp = temp_cp->next;

		}*/
	}
}

///**************TUPLE = SNAP *************************//
typedef struct TUPLE *TUPLELIST;//list of tuples
struct TUPLE {//TUPLE = SNAP
	int StudentId;
	char* Name;
	char* Address;
	char* Phone;
	TUPLELIST next;
};
struct TUPLELIST{
	struct TUPLE* head;
};
struct TUPLELIST HASHTABLE[B];


int h(int x) {
	return x % B;
}
struct TUPLE* createTUPLE(int StudentId, char* Name, char* Address, char* Phone){
	struct TUPLE* x = (struct TUPLE*) malloc(sizeof(struct TUPLE));
	x->Name=Name;
	x->Address=Address;
	x->StudentId = StudentId;
	x->Phone=Phone;
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
struct TUPLE* lookupSID(int StudentId){//for snap
	int key = h(StudentId);
	return HASHTABLE[key].head;
}
/*struct TUPLE* lookupName(char Name[]){
}*/
//****************************************///
					//CSGs
//***************************************///
typedef struct CSGLIST *CSGLIST;
struct CSG {
	char* Course;
	int StudentId;
	char* Grade;
	CSGLIST next;
};
struct CSGLIST{
	struct CSG* head;
};
struct CSGLIST HASHTABLE_CSG[B];

struct CSG* createCSG(char* Course, int StudentId, char* Grade){
	struct CSG* x = (struct CSG*) malloc(sizeof(struct CSG));
	x->Course=Course;
	x->Grade=Grade;
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

void file_make();
void file_make() {
	FILE *database;
	database = fopen("program.txt", "w");
	fprintf(database, "Course,Day,Hour\n");
	for(int i=0; i<B; i++) {
		struct CDH* new_CDH = HASHTABLE_CDH[i].head;
		while(new_CDH != NULL) {
			fprintf(database, "%s,%s,%s\n", new_CDH->Course, new_CDH->Day, new_CDH->Hour);
			new_CDH = new_CDH->next;
		}
	}
   	fclose(database);
}


int main() {
	for(int i=0; i<B; i++) {
		HASHTABLE_CDH[i].head=NULL;
	}
	
	struct CP* cp = createCP("CS101", "CS100");
	insertCP(cp);
	struct CP* cp2 = createCP("CS101", "CS102");
	insertCP(cp2);
	struct CP* cp3 = createCP("CS101", "CS99");
	insertCP(cp3);

	int hash = h(*cp->Course );

	printf("%s\n", lookupCP("CS101")->head->next->Prerequisite);
	struct CDH* cdh = createCDH("CS171", "M", "9AM");
	insertCDH(cdh);
	struct CDH* cdh2 = createCDH("CS171", "T", "17AM");
	insertCDH(cdh2);
		struct CDH* cdh3 = createCDH("CS171", "W", "17AM");
	insertCDH(cdh3);
	struct CDH* test = lookupCDH("CSC171")->head->next;
	printf("%s\n", test->next->Day);
	file_make();

	return 0;

}