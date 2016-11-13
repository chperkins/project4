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
struct CPLIST* lookupCP(char Course[], char Prerequisite[]);//lookup prerequisites for course

int hc(char* x);
int hc(char* x) {
	int l=0;
	for(int i=0; i<strlen(x); i++) {
		l+=x[i];
	}
	return l%B;


}


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

void insertCR(struct CR* cr){
	int hash = hc(cr->Course);//assume that each course only meets in one place
	printf("hash is %d\n\n", hash);
	HASHTABLE_CR[hash].head = cr;
}


struct CRLIST* lookupCR(char* Course, char* Room);
struct CRLIST* lookupCR(char* Course, char* Room){
	struct CRLIST* crlist = (struct CRLIST*) malloc(sizeof(struct CRLIST));

	if(*Course == '*' && *Room != '*') {
		crlist->head = NULL;
		struct CR* temp;
		for(int i=0; i<B; i++) {
			struct CR* temp1 = HASHTABLE_CR[i].head;
			while(temp1!=NULL) {
				if(temp1->Room == Room) {
					struct CR* temp2 = createCR(temp1->Course, temp1->Room);
					temp2->next = crlist->head;
					crlist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
		return crlist;
	}

	else{
		int hash = h(*Course);
		return &HASHTABLE_CR[hash];
	}
	
	
}

void deleteCR(struct CR* cr){
	int hash = hc(cr->Course);
	printf("%s deleting\n\n", cr->Course);
	HASHTABLE_CR[hash].head = NULL;
	//printf("\n\nhakfhiaekgjaefij %p\n\n",HASHTABLE_CR[hash].head);
	//printf("\n %s \n",lookupCR("CS202", "*")->head);
}

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
	int hash = hc(cdh->Course);



	if (HASHTABLE_CDH[hash].head != NULL) {

		struct CDH* temp_CDH = HASHTABLE_CDH[hash].head;
		HASHTABLE_CDH[hash].head = cdh;
		cdh->next = temp_CDH;
		//printf("%s 12 \n", HASHTABLE_CDH[hash].head->Day);
		//printf("%s 123 \n", HASHTABLE_CDH[hash].head->next->Day);
	}

	else {
		HASHTABLE_CDH[hash].head = cdh;
	}
}
struct CDHLIST* lookupCDH(char Course[], char Day[], char Hour[]);
struct CDHLIST* lookupCDH(char Course[], char Day[], char Hour[]) {
	struct CDHLIST* cdhlist = (struct CDHLIST*) malloc(sizeof(struct CDHLIST));
		cdhlist->head = NULL;
		struct CDH* temp;
		for(int i=0; i<B; i++) {
			struct CDH* temp1 = HASHTABLE_CDH[i].head;
			while(temp1!=NULL) {
				if((temp1->Course == Course || *temp1->Course == '*') && (temp1->Day == Day || *Day == '*') && (temp1->Hour == Hour || *Hour == '*')) {
					struct CDH* temp2 = createCDH(temp1->Course, temp1->Day, temp1->Hour);
					temp2->next = cdhlist->head;
					cdhlist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
		return cdhlist;

	
}
void deleteCDH(struct CDH* cdh){
	int hash = hc(cdh->Course);
	struct CDH* temp_cdh = HASHTABLE_CDH[hash].head;
	if (*cdh->Day == *temp_cdh->Day && *cdh->Hour == *temp_cdh->Hour){//delete the head
		HASHTABLE_CDH[hash].head = HASHTABLE_CDH[hash].head->next;
	}
	else{
		struct CDH* prev = temp_cdh;
		while(temp_cdh->next != NULL){//not the head
			temp_cdh = temp_cdh->next;
			if (*temp_cdh->Day == *cdh->Day && *temp_cdh->Hour == *cdh->Hour){
				prev->next = temp_cdh->next;
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
	int hash = hc(cp->Course);
	if (HASHTABLE_CP[hash].head != NULL) {
		struct CP* temp_CP = HASHTABLE_CP[hash].head;
		HASHTABLE_CP[hash].head = cp;
		cp->next = temp_CP;
	}
	else {
		HASHTABLE_CP[hash].head = cp;
		HASHTABLE_CP[hash].head->next = NULL;
	}
}
struct CPLIST* lookupCP(char Course[], char Prerequisite[]){//lookup prerequisites for course
	/*int hash = hc(Course );
	return &HASHTABLE_CP[hash];*/
	//////////////

	struct CPLIST* cplist = (struct CPLIST*) malloc(sizeof(struct CPLIST));
		cplist->head = NULL;
		struct CP* temp;
		for(int i=0; i<B; i++) {
			struct CP* temp1 = HASHTABLE_CP[i].head;
			while(temp1!=NULL) {
				if((temp1->Course == Course || *Course == '*') && (temp1->Prerequisite == Prerequisite || *Prerequisite == '*') ) {
					struct CP* temp2 = createCP(temp1->Course, temp1->Prerequisite);
					temp2->next = cplist->head;
					cplist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
		return cplist;

	/////
}
void deleteCP(struct CP* cp){
	/*int hash = hc(cp->Course );
	if (HASHTABLE_CP[hash].head != NULL){
		//HASHTABLE_CP[hash].head = NULL;
		struct CP* prev;
		struct CP* temp_cp = HASHTABLE_CP[hash].head;
		while(temp_cp ->Course != cp->Course && temp_cp->Prerequisite != cp->Prerequisite){
			prev = temp_cp;
			temp_cp = temp_cp->next;

		}
		prev->next = temp_cp;

	}


*/
	int hash = hc(cp->Course);
	struct CP* temp_cp = HASHTABLE_CP[hash].head;
	if (cp->Course == temp_cp->Course && cp->Prerequisite == temp_cp->Prerequisite){//delete the head
		//printf("Deleting head Course: %s Prereq:%s\n\n", temp_cp->Course, temp_cp->Prerequisite);
		 printf(" %s == %s\n", cp->Prerequisite, temp_cp->Prerequisite);
		 printf("%d, %d", *cp->Course == *temp_cp->Course, *cp->Prerequisite == *temp_cp->Prerequisite);
		HASHTABLE_CP[hash].head = HASHTABLE_CP[hash].head->next;
		printf("%p\n", HASHTABLE_CP[hash].head->next->next);
	}
	else{
		struct CP* prev = temp_cp;
		while(temp_cp->next != NULL){//not the head
			temp_cp = temp_cp->next;
			if (*temp_cp->Course == *cp->Course && *temp_cp->Prerequisite == *cp->Prerequisite){
				printf("PRev is %s\n", prev->Course);
				prev->next = temp_cp->next;
				break;
			}
		}
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
//----------------------///
					//CSGs
//----------------------///
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
	fprintf(database, "Course Day Hour\n");
	for(int i=0; i<B; i++) {
		struct CDH* new_CDH = HASHTABLE_CDH[i].head;
		while(new_CDH != NULL) {
			fprintf(database, "%s %s %s\n", new_CDH->Course, new_CDH->Day, new_CDH->Hour);
			new_CDH = new_CDH->next;
		}
	}
	fprintf(database,"\n");
   	fclose(database);
}





//struct cDatabase {
//	CDHLIST HASHTABLE_CDH[B];
//};

void file_read();
void file_read() {
	int lol = true;
	char* course[1000];
	char* day[1000];
	char* hour[1000];

	int i=0;

	FILE* database = fopen("program.txt", "r");

	while(lol) {
		course[i]=malloc(1000 * sizeof(char *));
		day[i]=malloc(1000 * sizeof(char *));
		hour[i]=malloc(1000 * sizeof(char *));

		lol = (fscanf(database, "%s %s %s\n", course[i], day[i], hour[i])!=EOF);

		printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		insertCDH(createCDH(course[i], day[i], hour[i]));
		printf("tootoo\n");
		i++;

	}

   	fclose(database);
}

int main() {
	for(int i=0; i<B; i++) {
		HASHTABLE_CDH[i].head=NULL;
	}
	/*struct CDH* cdh = createCDH("CS171", "M", "1AM");
	insertCDH(cdh);
	struct CDH* cdh2 = createCDH("CS171", "T", "2AM");
	insertCDH(cdh2);
	struct CDH* cdh3 = createCDH("CS173", "W", "3AM");
	insertCDH(cdh3);
	struct CDH* cdh4 = createCDH("CS173", "TH", "4AM");
	insertCDH(cdh4);
	struct CDH* cdh5 = createCDH("CS163", "FI", "78AM");
	insertCDH(cdh5);
	printf("%s\n", lookupCDH("CS173", "TH", "*")->head->Hour);
	deleteCDH(cdh5);
	printf("%p\n", lookupCDH("163", "FI", "*")->head);
	deleteCDH(cdh3);
		printf("%s\n", lookupCDH("CS173", "*", "*")->head->Hour);

*/
	
	struct CP* cp = createCP("CS101", "CS100");
	insertCP(cp);
	struct CP* cp2 = createCP("CS101", "CS102");
	insertCP(cp2);
	struct CP* cp3 = createCP("CS101", "CS99");
	insertCP(cp3);

	//insertCP(cp4);
	int hash = hc("CS101");
	printf("CS102 is %s\n", HASHTABLE_CP[hash].head->next->Prerequisite);
	printf("helo%s\n", lookupCP("CS101", "*")->head->next->Prerequisite);
	deleteCP(cp2);
	printf("somthaf\n");
	deleteCP(cp3);
	//printf("%s\n", lookupCP("*", "CS100")->head->Prerequisite);
	//printf("CS102 is %s\n", HASHTABLE_CP[hash].head->next->Prerequisite);

	//hash = hc("CS101");

	/*struct CDH* cdh = createCDH("CS171", "M", "1AM");
	insertCDH(cdh);
	struct CDH* cdh2 = createCDH("CS171", "T", "2AM");
	insertCDH(cdh2);
	struct CDH* cdh3 = createCDH("CS173", "W", "3AM");
	insertCDH(cdh3);
	struct CDH* cdh4 = createCDH("CS173", "TH", "4AM");
	insertCDH(cdh4);
	struct CDH* cdh5 = createCDH("CS163", "FI", "78AM");
	insertCDH(cdh5);
	//struct CDH* test = lookupCDH("CSC171")->head->next;
	//printf(" NOW NOW %s \n", HASHTABLE_CDH[h(*"CSC172")].head->next->next->Course);
	//printf("%s\n", test->next->Day);
	file_make();
	file_read();
	file_make();
	printf("Finally %s \n", HASHTABLE_CDH[hc("CS171")].head->next->Course);
	struct CDH* cdh6 = createCDH("CS162", "FadI", "78safdAM");
	insertCDH(cdh6);
	file_make();*/

	return 0;

}