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


//----------------CR = Course, Room //----------------

typedef struct CR *CRLIST;
struct CR{
	char* Course;
	char* Room;
	CRLIST next;
};
struct CRLIST{
	struct CR* head;
};
struct CRLIST HASHTABLE_CR[B];
struct CR* createCR(char* Course, char* Room){
	struct CR* x = (struct CR*) malloc(sizeof(struct CR));
	x->Course = Course;
	x->Room = Room;
	x->next = NULL;
	return x;
}
void insertCR(struct CR* cr);
void insertCR(struct CR* cr){
	int hash = h(*cr->Course);//assume that each course only meets in one place
	HASHTABLE_CR[hash].head = cr;
}
void deleteCR(struct CR* cr){
	int hash = h(*cr->Course);
	HASHTABLE_CR[hash].head = NULL;
}
struct CRLIST* crlist;
int j = 0;
struct CR* crs_temp;
void createCRLIST(){
	crlist = (struct CRLIST*) malloc(sizeof(struct CRLIST));
	crs_temp=  (struct CR*) malloc(sizeof(struct CR));
	crlist->head = crs_temp;

}
struct CRLIST* lookupCR(char* Course, char* Room);
struct CRLIST* lookupCR(char* Course, char* Room){
	printf("Loookingup %s\n", Course);
	if (*Course == '*' && *Room != '*'){
		printf("course is *\n\n");
		

		printf("*\n");
		for (int i=0; i<B; i++){
			//printf("*");
			if (HASHTABLE_CR[i].head != NULL && HASHTABLE_CR[i].head->Room == Room){
				if (j==0) {
					j++;
					//printf("nooooooot\n");
					crs_temp = HASHTABLE_CR[i].head;
					printf("temp is %s\n", crs_temp->Room);
					crlist->head = crs_temp;
					crs_temp = crlist->head;
					crs_temp = crs_temp->next;
				}
				else {
					printf("elssseee\n");
					crs_temp->next = HASHTABLE_CR[i].head;
					crs_temp = crs_temp->next;
				}
				//temp->next = HASHTABLE_CR[i].head;//add this to the crlist
				//temp = temp->next;
				//struct CR* cr_temp2 = HASHTABLE_CR[i].head;
				/*while(cr_temp2 != NULL){//iterate through the list in this bucket
					//struct CR* prev = cr_temp2;
					temp->next = cr_temp2;
					temp = temp->next;
					cr_temp2 = cr_temp2->next;
				}*/

			}
		}
		return crlist;
		//lookup method needs to return specific rooms
	}
	else{
		int hash = h(*Course);
		return &HASHTABLE_CR[hash];
	}
	
	
}
//----------------CDH = Course, Day, Hour //----------------

typedef struct CDH *CDHLIST;
struct CDH{
	char Course[5];
	char Day[2];
	char Hour[4];
	CDHLIST next;
};
struct CDHLIST{
	struct CDH* head;
};
struct CDHLIST HASHTABLE_CDH[B];
struct CDH* createCDH(char Course[], char Day[], char Hour[]){
	struct CDH* x = (struct CDH*) malloc(sizeof(struct CDH));
	strcpy(x->Course, Course);
	strcpy(x->Day, Day);
	strcpy(x->Hour, Hour);
	x->next = NULL;
	return x;
}
void insertCDH(struct CDH* cdh);
void insertCDH(struct CDH* cdh){
	
	int hash = h(*cdh->Course );
	if (HASHTABLE_CDH[hash].head != NULL){//if there's a collision
		struct CDH* new_CDH = HASHTABLE_CDH[hash].head;
	//int i = 0;
		while(new_CDH != NULL){//go through the list to find the next empty bucket
			
			struct CDH* prev = new_CDH;
			new_CDH = new_CDH->next;
			if (new_CDH == NULL){
				
				new_CDH = cdh;
				prev->next = new_CDH;

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
		while(temp_cdh->Day != cdh->Day && cdh->Hour != temp_cdh->Hour){
			struct CDH* prev = temp_cdh;
			temp_cdh = temp_cdh->next;
			if (*temp_cdh->Day == *cdh->Day && *temp_cdh->Hour == *cdh->Hour){
				prev->next = temp_cdh->next;
				temp_cdh = NULL;
				break;
			}
		}
	}

}
//----------------CP = Course, Prerequisites //----------------

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
		struct CP* temp_cp = HASHTABLE_CP[hash].head;
		while(temp_cp ->Course != cp->Course && temp_cp->Prerequisite != cp->Prerequisite){
			struct CP* prev = temp_cp;
			temp_cp = temp_cp->next;
			if (temp_cp->Course == cp->Course && temp_cp->Prerequisite == cp->Prerequisite){
				prev->next = temp_cp->next;
				temp_cp = NULL;
				break;
			}

		}
	}
}

//----------------TUPLE = SNAP //----------------
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
struct TUPLE* lookupSID(int StudentId){//for snap
	int key = h(StudentId);
	return HASHTABLE[key].head;
}
/*struct TUPLE* lookupName(char Name[]){
}*/
//----------------
					//CSGs
//----------------
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
	createCRLIST();
	struct CR* cr = createCR("CS201", "Ohm Auditorium");
	insertCR(cr);
	struct CR* cr2 = createCR("CS202", "Ohm Auditorium");

	insertCR(cr2);
	printf("Lloooking up %s\n", lookupCR("*", "Ohm Auditorium")->head->Course);
	printf("hello %p\n",crs_temp);


	//---------------- Test for CP table -----------------//
	/*struct CP* cp = createCP("CS101", "CS100");
	insertCP(cp);
	struct CP* cp2 = createCP("CS101", "CS102");
	insertCP(cp2);
	struct CP* cp3 = createCP("CS101", "CS99");
	insertCP(cp3);

	int hash = h(*cp->Course );

	printf("%s\n", lookupCP("CS101")->head->next->Prerequisite);
	deleteCP(cp2);
	printf("%s\n", lookupCP("CS101")->head->next->Prerequisite);
*/


	//---------------- Test for CDH table -----------------//
/*	struct CDH* cdh = createCDH("CS171", "M", "9AM");
	insertCDH(cdh);
	struct CDH* cdh2 = createCDH("CS171", "T", "17AM");
	insertCDH(cdh2);
		struct CDH* cdh3 = createCDH("CS171", "W", "17AM");
	insertCDH(cdh3);
	struct CDH* test = lookupCDH("CSC171")->head->next;
	printf("%s\n", test->next->Day);
	deleteCDH(cdh2);
	test = lookupCDH("CSC171")->head->next;
	printf("%s\n", test->Day);*/

	return 0;

}