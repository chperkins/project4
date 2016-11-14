#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define B 1009
struct CP* createCP(char Course[], char Prerequisite[]);
struct SNAP* createSNAP(char* StudentId, char Name[], char Address[], char Phone[]);
struct CSG* createCSG(char Course[], char* StudentId, char Grade[]);
void insertCSG(struct CSG* csg);
struct SNAP* lookup(struct SNAP* SNAP);
struct CSG* lookupCSG(struct CSG* csg);
void deleteCSG(struct CSG* csg);
void insert(struct SNAP* SNAP);
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
struct CRLIST* lookupCR(char* Course, char* Room) {

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
	int match = 0;
	struct CDH* temp_cdh = HASHTABLE_CDH[hash].head;
	struct CDH* temp_cdh_next = temp_cdh->next;

	if(cdh->Course == temp_cdh->Course && cdh->Day == temp_cdh->Day && cdh->Hour == temp_cdh->Hour) {
		HASHTABLE_CDH[hash].head = HASHTABLE_CDH[hash].head->next;
		match=1;
	}
	while(temp_cdh_next!=NULL && match == 0) {
		if (temp_cdh_next->Course == cdh->Course && temp_cdh_next->Day == cdh->Day && temp_cdh_next->Hour == cdh->Hour) {
			//printf("cdh->course %s, cp->pre %s\n", cdh->Course, cdh->Hour);
			//printf("temp_cdh_next %s %s\n", temp_cdh_next->Course, temp_cdh_next->Hour);
			//printf("temp_cdh is %s, temp_cdh_next is %s\n", temp_cdh->Hour, temp_cdh_next->Hour);
			temp_cdh->next = temp_cdh_next->next;
			match=1;
		}
		else {
			temp_cdh = temp_cdh->next;
			temp_cdh_next = temp_cdh_next->next;
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
struct CPLIST* lookupCP(char* Course, char* Prerequisite){//lookup prerequisites for course
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

	int hash = hc(cp->Course);
	int match = 0;
	struct CP* temp_cp = HASHTABLE_CP[hash].head;
	struct CP* temp_cp_next = temp_cp->next;

	if(cp->Course == temp_cp->Course && cp->Prerequisite == temp_cp->Prerequisite) {
		HASHTABLE_CP[hash].head = HASHTABLE_CP[hash].head->next;
		match=1;
	}
	while(temp_cp_next!=NULL && match == 0) {
		if (temp_cp_next->Course == cp->Course && temp_cp_next->Prerequisite == cp->Prerequisite) {
			printf("cp->course %s, cp->pre %s\n", cp->Course, cp->Prerequisite);
			printf("temp_cp_next %s %s\n", temp_cp_next->Course, temp_cp_next->Prerequisite);
			printf("temp_cp is %s, temp_cp_next is %s\n", temp_cp->Prerequisite, temp_cp_next->Prerequisite);
			temp_cp->next = temp_cp_next->next;
			match=1;
		}
		else {
			temp_cp = temp_cp->next;
			temp_cp_next = temp_cp_next->next;
		}
	}
}

///**************SNAP = SNAP *************************//
typedef struct SNAP *SNAPLIST;//list of SNAPs
struct SNAP {//SNAP = SNAP
	char* StudentId;
	char* Name;
	char* Address;
	char* Phone;
	SNAPLIST next;
};
struct SNAPLIST{
	struct SNAP* head;
};
struct SNAPLIST HASHTABLE_SNAP[B];


int h(int x) {
	return x % B;
}
struct SNAP* createSNAP(char* StudentId, char* Name, char* Address, char* Phone){
	struct SNAP* x = (struct SNAP*) malloc(sizeof(struct SNAP));
	x->Name=Name;
	x->Address=Address;
	x->StudentId = StudentId;
	x->Phone=Phone;
	x->next = NULL;
	return x;
}
void insertSNAP(struct SNAP* snap){

	int hash = hc(snap->StudentId);
	if (HASHTABLE_CP[hash].head != NULL) {
		struct SNAP* temp_snap = HASHTABLE_SNAP[hash].head;
		HASHTABLE_SNAP[hash].head = snap;
		snap->next = temp_snap;
	}
	else {
		HASHTABLE_SNAP[hash].head = snap;
		HASHTABLE_SNAP[hash].head->next = NULL;
	}

}
void deleteSNAP(struct SNAP* snap){

	int hash = hc(snap->StudentId);
	int match = 0;
	struct SNAP* temp_snap = HASHTABLE_SNAP[hash].head;
	struct SNAP* temp_snap_next = temp_snap->next;

	if(snap->StudentId == temp_snap->StudentId &&
		 snap->Name == temp_snap->Name &&
		 snap->Address == temp_snap->Address &&
		 snap->Phone == temp_snap->Phone) {

		HASHTABLE_SNAP[hash].head = HASHTABLE_SNAP[hash].head->next;
		match=1;
	}
	while(temp_snap_next!=NULL && match == 0) {
		if(snap->StudentId == temp_snap_next->StudentId &&
		 	snap->Name == temp_snap_next->Name &&
		 	snap->Address == temp_snap_next->Address &&
		 	snap->Phone == temp_snap_next->Phone) {
			//printf("cp->course %s, cp->pre %s\n", cp->Course, cp->Prerequisite);
			//printf("temp_cp_next %s %s\n", temp_cp_next->Course, temp_cp_next->Prerequisite);
			//printf("temp_cp is %s, temp_cp_next is %s\n", temp_cp->Prerequisite, temp_cp_next->Prerequisite);
			temp_snap->next = temp_snap_next->next;
			match=1;
		}
		else {
			temp_snap = temp_snap->next;
			temp_snap_next = temp_snap_next->next;
		}
	}	
}
struct SNAPLIST* lookupSNAP(char* StudentId, char* Name, char* Address, char* Phone){//lookup with the SNAP
	/*int hash = hc(Course );
	return &HASHTABLE_CP[hash];*/
	//////////////

	/*UNTESTED*/

	struct SNAPLIST* snaplist = (struct SNAPLIST*) malloc(sizeof(struct SNAPLIST));
		snaplist->head = NULL;
		struct SNAP* temp;
		for(int i=0; i<B; i++) {
			struct SNAP* temp1 = HASHTABLE_SNAP[i].head;
			while(temp1!=NULL) {
				if((temp1->StudentId == StudentId || *StudentId == '*') &&
				 (temp1->Name == Name || *Name == '*') &&
				 (temp1->Address == Address || *Address == '*') &&
				 (temp1->Phone == Phone || *Phone == '*')) {

					struct SNAP* temp2 = createSNAP(temp1->StudentId, temp1->Name, temp1->Address, temp1->Phone);
					temp2->next = snaplist->head;
					snaplist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
	return snaplist;

	/////

}
//----------------------///
					//CSGs
//----------------------///
typedef struct CSGLIST *CSGLIST;
struct CSG {
	char* Course;
	char* StudentId;
	char* Grade;
	CSGLIST next;
};
struct CSGLIST{
	struct CSG* head;
};
struct CSGLIST HASHTABLE_CSG[B];

struct CSG* createCSG(char* Course, char* StudentId, char* Grade){
	struct CSG* x = (struct CSG*) malloc(sizeof(struct CSG));
	x->Course=Course;
	x->Grade=Grade;
	x->StudentId = StudentId;
	x->next = NULL;
	return x;
}

void insertCSG(struct CSG* csg){//use STUDENT ID as the hashtable
	int hash = hc(csg->StudentId);
	HASHTABLE_CSG[hash].head = csg;
}
void deleteCSG(struct CSG* csg){
	int hash = hc(csg->StudentId);
	if (HASHTABLE_CSG[hash].head != NULL){
		HASHTABLE_CSG[hash].head = NULL;
	}
}
struct CSG* lookupCSG(struct CSG* csg){//lookup with the SNAP
	int key = hc(csg->StudentId);
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

		//printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		insertCDH(createCDH(course[i], day[i], hour[i]));
		//printf("tootoo\n");
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
	struct CP* cp4 = createCP("CS101", "CS88");
	insertCP(cp3);
	insertCP(cp4);

	//insertCP(cp4);
	int hash = hc("CS101");
	//printf("CS102 is %s\n", HASHTABLE_CP[hash].head->next->Prerequisite);
	//printf("helo%s\n", lookupCP("CS101", "*")->head->next->Prerequisite);
	//deleteCP(cp);
	//printf("somthaf\n");
	deleteCP(cp4);
	//printf("%s %s %sabcd\n", lookupCP("CS101", "*")->head->Prerequisite,
	//	lookupCP("CS101", "*")->head->next->Prerequisite,
	//	lookupCP("CS101", "*")->head->next->next->Prerequisite);
	//printf("%s %s %sxyz\n", HASHTABLE_CP[hash].head->Prerequisite,
	//	HASHTABLE_CP[hash].head->next->Prerequisite,
	//	HASHTABLE_CP[hash].head->next->next->Prerequisite);
	//printf("CS102 is %s\n", HASHTABLE_CP[hash].head->Prerequisite);

	hash = hc("CS173");

	//struct CDH* cdh = createCDH("CS171", "M", "1AM");
	//insertCDH(cdh);
	//struct CDH* cdh2 = createCDH("CS171", "T", "2AM");
	//insertCDH(cdh2);
	struct CDH* cdh3 = createCDH("CS173", "W", "3AM");
	insertCDH(cdh3);
	struct CDH* cdh4 = createCDH("CS173", "TH", "4AM");
	insertCDH(cdh4);
	struct CDH* cdh5 = createCDH("CS173", "FI", "78AM");
	insertCDH(cdh5);
	deleteCDH(cdh5);
	insertSNAP(createSNAP("a","b","c","d"));
	//deleteSNAP(createSNAP("a","b","c","d"));
	printf("ok123\n");
	printf("first snap %s \n", HASHTABLE_SNAP[hc("a")].head->StudentId);
	printf("%s %sxyz\n", HASHTABLE_CDH[hash].head->Hour,
		HASHTABLE_CDH[hash].head->next->Hour);
	char* abc = "1";
	printf("is it equal %d %d \n", *abc-'0','*');
	//struct CDH* test = lookupCDH("CSC171")->head->next;
	//printf(" NOW NOW %s \n", HASHTABLE_CDH[h(*"CSC172")].head->next->next->Course);
	//printf("%s\n", test->next->Day);
	file_make();
	file_read();
	file_make();
	//printf("Finally %s \n", HASHTABLE_CDH[hc("CS171")].head->next->Course);
	//struct CDH* cdh6 = createCDH("CS162", "FadI", "78safdAM");
	//insertCDH(cdh6);
	file_make();

	return 0;

}