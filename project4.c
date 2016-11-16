#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define B 1009

int h(int x);
int h(int x) {
	return x % B;
}

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
struct CRLIST {
	struct CR* head;
};

struct CR* createCR(char* Course, char* Room);
struct CR* createCR(char* Course, char* Room){
	struct CR* x = (struct CR*) malloc(sizeof(struct CR));
	x->Course = Course;
	x->Room = Room;
	x->next = NULL;
	return x;
}

struct CRLIST* lookupCR(char* Course, char* Room, struct CRLIST HASHTABLE_CR[]);
struct CRLIST* lookupCR(char* Course, char* Room, struct CRLIST HASHTABLE_CR[]) {


	struct CRLIST* crlist = (struct CRLIST*) malloc(sizeof(struct CRLIST));
		crlist->head = NULL;
		struct CR* temp;
		for(int i=0; i<B; i++) {
			struct CR* temp1 = HASHTABLE_CR[i].head;
			while(temp1!=NULL) {
				if((strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) && (strcmp(temp1->Room,Room)==0 || strcmp(Room,"*")==0) ) {
					struct CR* temp2 = createCR(temp1->Course, temp1->Room);
					temp2->next = crlist->head;
					crlist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
	return crlist;

	/////
}

void insertCR(struct CR* cr, struct CRLIST HASHTABLE_CR[]);
void insertCR(struct CR* cr, struct CRLIST HASHTABLE_CR[]){

	if(lookupCR(cr->Course, cr->Room, HASHTABLE_CR)->head==NULL) {

		int hash = hc(cr->Course);
		if (HASHTABLE_CR[hash].head != NULL) {
			struct CR* temp_cr = HASHTABLE_CR[hash].head;
			HASHTABLE_CR[hash].head = cr;
			cr->next = temp_cr;
		}
		else {
			HASHTABLE_CR[hash].head = cr;
			HASHTABLE_CR[hash].head->next = NULL;
		}
	}
}


void deleteCR(struct CR* cr, struct CRLIST HASHTABLE_CR[]){
	int hash = hc(cr->Course);
	printf("%s deleting\n\n", cr->Course);
	HASHTABLE_CR[hash].head = NULL;
	//printf("\n\nhakfhiaekgjaefij %p\n\n",HASHTABLE_CR[hash].head);
	//printf("\n %s \n",lookupCR("CS202", "*")->head);
}

///-------------CDH = Course, Day, Hour ----------------//

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


struct CDH* createCDH(char* Course, char* Day, char* Hour) {
	struct CDH* x = (struct CDH*) malloc(sizeof(struct CDH));
	x->Course=Course;
	x->Day=Day;
	x->Hour=Hour;
	x->next = NULL;
	return x;
}

struct CDHLIST* lookupCDH(char Course[], char Day[], char Hour[], struct CDHLIST HASHTABLE_CDH[]);
struct CDHLIST* lookupCDH(char Course[], char Day[], char Hour[], struct CDHLIST HASHTABLE_CDH[]) {
	struct CDHLIST* cdhlist = (struct CDHLIST*) malloc(sizeof(struct CDHLIST));
		cdhlist->head = NULL;
		struct CDH* temp;
		for(int i=0; i<B; i++) {
			struct CDH* temp1 = HASHTABLE_CDH[i].head;
			while(temp1!=NULL) {
				printf("temp1 course %s %s %s  \n", temp1->Course, temp1->Day, temp1->Hour);
				if((strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) && (strcmp(temp1->Day,Day)==0 || strcmp(Day,"*")==0) && (strcmp(temp1->Hour,Hour)==0 || strcmp(Hour,"*")==0)) {
					printf("got here \n");
					struct CDH* temp2 = createCDH(temp1->Course, temp1->Day, temp1->Hour);
					temp2->next = cdhlist->head;
					cdhlist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
		return cdhlist;

	
}

void insertCDH(struct CDH* cdh, struct CDHLIST HASHTABLE_CDH[]);
void insertCDH(struct CDH* cdh, struct CDHLIST HASHTABLE_CDH[]){
	int hash = hc(cdh->Course);

	if(lookupCDH(cdh->Course, cdh->Day, cdh->Hour, HASHTABLE_CDH)->head==NULL) {

		/*printf("not in yet true? |%d| |%p| |%s| |%s| |%s| \n", lookupCDH(cdh->Course, cdh->Day, cdh->Hour)->head==NULL, 
			lookupCDH(cdh->Course, cdh->Day, cdh->Hour)->head,
			cdh->Course, cdh->Day, cdh->Hour);*/
		/*printf("booleans %d %d %d %d %d\n", strcmp(cdh->Course, "CS173"),strcmp(cdh->Day, "W"),strcmp(cdh->Hour, "3AM"), 
			lookupCDH("CS173", "*","*")->head==NULL,
			lookupCDH(cdh->Course, "*","*")->head==NULL);*/

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
	else {
		/*printf("already in \n");
		printf("not in yet true? |%d| |%p| |%s| |%s| |%s| \n", lookupCDH(cdh->Course, cdh->Day, cdh->Hour)->head==NULL, 
			lookupCDH(cdh->Course, cdh->Day, cdh->Hour)->head,
			cdh->Course, cdh->Day, cdh->Hour);*/
	}

}
void deleteCDH(struct CDH* cdh, struct CDHLIST HASHTABLE_CDH[]);
void deleteCDH(struct CDH* cdh, struct CDHLIST HASHTABLE_CDH[]){

	int hash = hc(cdh->Course);
	int match = 0;
	struct CDH* temp_cdh = HASHTABLE_CDH[hash].head;
	struct CDH* temp_cdh_next = temp_cdh->next;

	if(strcmp(cdh->Course,temp_cdh->Course)==0 && strcmp(cdh->Day,temp_cdh->Day)==0 && strcmp(cdh->Hour,temp_cdh->Hour)==0) {
		HASHTABLE_CDH[hash].head = HASHTABLE_CDH[hash].head->next;
		match=1;
	}
	while(temp_cdh_next!=NULL && match == 0) {
		if (strcmp(temp_cdh_next->Course,cdh->Course)==0 && strcmp(temp_cdh_next->Day,cdh->Day)==0 && strcmp(temp_cdh_next->Hour,cdh->Hour)==0) {
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
///-----------CP = Course, Prerequisites---------------//

typedef struct CP *CPLIST;
struct CP{//Course, Prerequisite
	char* Course;
	char* Prerequisite;
	CPLIST next;
};
struct CPLIST{
	struct CP* head;
};

struct CP* createCP(char Course[], char Prerequisite[]);
struct CP* createCP(char* Course, char* Prerequisite){
	struct CP* x = (struct CP*) malloc(sizeof(struct CP));
	x->Course=Course;
	x->Prerequisite=Prerequisite;
	x->next = NULL;
	return x;
}
struct CPLIST* lookupCP(char Course[], char Prerequisite[], struct CPLIST HASHTABLE_CP[]);//lookup prerequisites for course
struct CPLIST* lookupCP(char* Course, char* Prerequisite, struct CPLIST HASHTABLE_CP[]){//lookup prerequisites for course
	/*int hash = hc(Course );
	return &HASHTABLE_CP[hash];*/
	//////////////

	struct CPLIST* cplist = (struct CPLIST*) malloc(sizeof(struct CPLIST));
		cplist->head = NULL;
		struct CP* temp;
		for(int i=0; i<B; i++) {
			struct CP* temp1 = HASHTABLE_CP[i].head;
			while(temp1!=NULL) {
				if((strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) && (strcmp(temp1->Prerequisite,Prerequisite)==0 || strcmp(Prerequisite,"*")==0) ) {
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

void insertCP(struct CP* cp, struct CPLIST HASHTABLE_CP[]);
void insertCP(struct CP* cp, struct CPLIST HASHTABLE_CP[]) {

	if(lookupCP(cp->Course, cp->Prerequisite, HASHTABLE_CP)->head==NULL) {

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
}

void deleteCP(struct CP* cp, struct CPLIST HASHTABLE_CP[]);
void deleteCP(struct CP* cp, struct CPLIST HASHTABLE_CP[]){

	int hash = hc(cp->Course);
	int match = 0;
	struct CP* temp_cp = HASHTABLE_CP[hash].head;
	struct CP* temp_cp_next = temp_cp->next;

	if(strcmp(cp->Course,temp_cp->Course)==0 && strcmp(cp->Prerequisite,temp_cp->Prerequisite)==0) {
		HASHTABLE_CP[hash].head = HASHTABLE_CP[hash].head->next;
		match=1;
	}
	while(temp_cp_next!=NULL && match == 0) {
		if (strcmp(temp_cp_next->Course,cp->Course)==0 && strcmp(temp_cp_next->Prerequisite,cp->Prerequisite)==0) {
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

///-------------SNAP = SNAP------------------------//
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

struct SNAP* createSNAP(char* StudentId, char Name[], char Address[], char Phone[]);
struct SNAP* createSNAP(char* StudentId, char* Name, char* Address, char* Phone){
	struct SNAP* x = (struct SNAP*) malloc(sizeof(struct SNAP));
	x->Name=Name;
	x->Address=Address;
	x->StudentId = StudentId;
	x->Phone=Phone;
	x->next = NULL;
	return x;
}

void deleteSNAP(struct SNAP* snap, struct SNAPLIST HASHTABLE_SNAP[]);
void deleteSNAP(struct SNAP* snap, struct SNAPLIST HASHTABLE_SNAP[]){

	int hash = hc(snap->StudentId);
	int match = 0;
	struct SNAP* temp_snap = HASHTABLE_SNAP[hash].head;
	struct SNAP* temp_snap_next = temp_snap->next;

	if(strcmp(snap->StudentId,temp_snap->StudentId)==0 &&
		 strcmp(snap->Name,temp_snap->Name)==0 &&
		 strcmp(snap->Address,temp_snap->Address)==0 &&
		 strcmp(snap->Phone,temp_snap->Phone)==0) {

		HASHTABLE_SNAP[hash].head = HASHTABLE_SNAP[hash].head->next;
		match=1;
	}
	while(temp_snap_next!=NULL && match == 0) {
		if(strcmp(snap->StudentId,temp_snap_next->StudentId)==0 &&
		 	strcmp(snap->Name,temp_snap_next->Name)==0 &&
		 	strcmp(snap->Address,temp_snap_next->Address)==0 &&
		 	strcmp(snap->Phone,temp_snap_next->Phone)==0) {
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

struct SNAPLIST* lookupSNAP(char* StudentId, char* Name, char* Address, char* Phone, struct SNAPLIST HASHTABLE_SNAP[]);
struct SNAPLIST* lookupSNAP(char* StudentId, char* Name, char* Address, char* Phone, struct SNAPLIST HASHTABLE_SNAP[]){//lookup with the SNAP
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
				if((strcmp(temp1->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0) &&
				 (strcmp(temp1->Name,Name)==0 || strcmp(Name,"*")==0) &&
				 (strcmp(temp1->Address,Address)==0 || strcmp(Address,"*")==0) &&
				 (strcmp(temp1->Phone,Phone)==0 || strcmp(Phone,"*")==0)) {

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
void insertSNAP(struct SNAP* snap, struct SNAPLIST HASHTABLE_SNAP[]);
void insertSNAP(struct SNAP* snap, struct SNAPLIST HASHTABLE_SNAP[]) {

	if(lookupSNAP(snap->StudentId, snap->Name, snap->Address, snap->Phone, HASHTABLE_SNAP)->head==NULL) {

		int hash = hc(snap->StudentId);
		if (HASHTABLE_SNAP[hash].head != NULL) {
			struct SNAP* temp_snap = HASHTABLE_SNAP[hash].head;
			HASHTABLE_SNAP[hash].head = snap;
			snap->next = temp_snap;
		}
		else {
			HASHTABLE_SNAP[hash].head = snap;
			HASHTABLE_SNAP[hash].head->next = NULL;
		}
	}
}
//----------------------///
					//CSGs
//----------------------///
typedef struct CSG *CSGLIST;
struct CSG{
	char* Course;
	char* StudentId;
	char* Grade;
	CSGLIST next;
};
struct CSGLIST{
	struct CSG* head;
};

struct CSG* createCSG(char Course[], char* StudentId, char Grade[]);
struct CSG* createCSG(char* Course, char* StudentId, char* Grade) {
	struct CSG* x = (struct CSG*) malloc(sizeof(struct CSG));
	x->Course=Course;
	x->StudentId=StudentId;
	x->Grade=Grade;
	x->next = NULL;
	return x;
}

void deleteCSG(struct CSG* csg, struct CSGLIST HASHTABLE_CSG[B]);
void deleteCSG(struct CSG* csg, struct CSGLIST HASHTABLE_CSG[B]){

	int hash = hc(csg->Course);

	int match = 0;
	struct CSG* temp_csg = HASHTABLE_CSG[hash].head;
	struct CSG* temp_csg_next = temp_csg->next;

	if(strcmp(csg->Course,temp_csg->Course)==0 &&
		 strcmp(csg->StudentId,temp_csg->StudentId)==0 &&
		 strcmp(csg->Grade,temp_csg->Grade)==0) {

		HASHTABLE_CSG[hash].head = HASHTABLE_CSG[hash].head->next;
		match=1;
	}
	while(temp_csg_next!=NULL && match == 0) {
		if (strcmp(csg->Course,temp_csg_next->Course)==0 &&
		 strcmp(csg->StudentId,temp_csg_next->StudentId)==0 &&
		 strcmp(csg->Grade,temp_csg_next->Grade)==0) {
			//printf("cdh->course %s, cp->pre %s\n", cdh->Course, cdh->Hour);
			//printf("temp_cdh_next %s %s\n", temp_cdh_next->Course, temp_cdh_next->Hour);
			//printf("temp_cdh is %s, temp_cdh_next is %s\n", temp_cdh->Hour, temp_cdh_next->Hour);
			temp_csg->next = temp_csg_next->next;
			match=1;
		}
		else {
			temp_csg = temp_csg->next;
			temp_csg_next = temp_csg_next->next;
		}
	}

}
struct CSGLIST* lookupCSG(char* Course, char* StudentId, char* Grade, struct CSGLIST HASHTABLE_CSG[B]);
struct CSGLIST* lookupCSG(char* Course, char* StudentId, char* Grade, struct CSGLIST HASHTABLE_CSG[B]){//lookup with the SNAP

	struct CSGLIST* CSGlist = (struct CSGLIST*) malloc(sizeof(struct CSGLIST));

		CSGlist->head = NULL;
		struct CSG* temp;
		for(int i=0; i<B; i++) {
			struct CSG* temp1 = HASHTABLE_CSG[i].head;
			while(temp1!=NULL) {
				if((strcmp(temp1->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0) &&
				 (strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) &&
				 (strcmp(temp1->Grade,Grade)==0 || strcmp(Grade,"*")==0)) {

					struct CSG* temp2 = createCSG(temp1->Course, temp1->StudentId, temp1->Grade);
					temp2->next = CSGlist->head;
					CSGlist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
	return CSGlist;
}

void insertCSG(struct CSG* csg, struct CSGLIST HASHTABLE_CSG[B]);
void insertCSG(struct CSG* csg, struct CSGLIST HASHTABLE_CSG[B]) {//use STUDENT ID as the hashtable

	if(lookupCSG(csg->Course, csg->StudentId, csg->Grade, HASHTABLE_CSG)->head==NULL) {

		int hash = hc(csg->Course);

		if (HASHTABLE_CSG[hash].head != NULL) {

			struct CSG* temp_CSG= HASHTABLE_CSG[hash].head;
			HASHTABLE_CSG[hash].head = csg;
			csg->next = temp_CSG;
			//printf("%s 12 \n", HASHTABLE_CDH[hash].head->Day);
			//printf("%s 123 \n", HASHTABLE_CDH[hash].head->next->Day);
		}

		else {
			HASHTABLE_CSG[hash].head = csg;
		}
	}

}


//---------------FILE MAKERS--------------------//

void file_make_CR(struct CRLIST HASHTABLE_CR[]);
void file_make_CR(struct CRLIST HASHTABLE_CR[]) {
	FILE *database;
	database = fopen("CR_table.txt", "w");
	fprintf(database, "Course Room\n");
	for(int i=0; i<B; i++) {
		struct CR* new_CR = HASHTABLE_CR[i].head;
		while(new_CR != NULL) {
			fprintf(database, "%s %s\n", new_CR->Course, new_CR->Room);
			new_CR = new_CR->next;
		}
	}
   	fclose(database);
}

void file_make_CDH(struct CDHLIST HASHTABLE_CDH[]);
void file_make_CDH(struct CDHLIST HASHTABLE_CDH[]) {
	FILE *database;
	database = fopen("CDH_table.txt", "w");
	fprintf(database, "Course Day Hour\n");
	for(int i=0; i<B; i++) {
		struct CDH* new_CDH = HASHTABLE_CDH[i].head;
		while(new_CDH != NULL) {
			fprintf(database, "%s %s %s\n", new_CDH->Course, new_CDH->Day, new_CDH->Hour);
			new_CDH = new_CDH->next;
		}
	}
   	fclose(database);
}


void file_make_CP(struct CPLIST HASHTABLE_CP[]);
void file_make_CP(struct CPLIST HASHTABLE_CP[]) {

	FILE *database;
	database = fopen("CP_table.txt", "w");
	fprintf(database, "Course Prerequisite\n");
	for(int i=0; i<B; i++) {
		struct CP* new_CP = HASHTABLE_CP[i].head;
		while(new_CP != NULL) {
			fprintf(database, "%s %s\n", new_CP->Course, new_CP->Prerequisite);
			new_CP = new_CP->next;
		}
	}
   	fclose(database);	
}

void file_make_SNAP(struct SNAPLIST HASHTABLE_SNAP[]);
void file_make_SNAP(struct SNAPLIST HASHTABLE_SNAP[]) {
	FILE *database;
	database = fopen("SNAP_table.txt", "w");
	fprintf(database, "StudentId Name Address Phone\n");
	for(int i=0; i<B; i++) {
		struct SNAP* new_SNAP = HASHTABLE_SNAP[i].head;
		while(new_SNAP != NULL) {
			fprintf(database, "%s %s %s %s\n", new_SNAP->StudentId, new_SNAP->Name, new_SNAP->Address, new_SNAP->Phone);
			new_SNAP = new_SNAP->next;
		}
	}
   	fclose(database);	
}

void file_make_CSG(struct CSGLIST HASHTABLE_CSG[]);
void file_make_CSG(struct CSGLIST HASHTABLE_CSG[]) {

	FILE *database;
	database = fopen("CSG_table.txt", "w");
	fprintf(database, "Course Student Grade\n");
	for(int i=0; i<B; i++) {
		struct CSG* new_CSG = HASHTABLE_CSG[i].head;
		while(new_CSG != NULL) {
			fprintf(database, "%s %s %s\n", new_CSG->Course, new_CSG->StudentId, new_CSG->Grade);
			new_CSG = new_CSG->next;
		}
	}
   	fclose(database);		
}


//-----------------FILE READERS------------------//

void file_read_CDH(struct CDHLIST HASHTABLE_CDH[]);
void file_read_CDH(struct CDHLIST HASHTABLE_CDH[]) {
	int lol = true;
	char* course[1000];
	char* day[1000];
	char* hour[1000];

	int i=0;

	FILE* database = fopen("CDH_table.txt", "r");

	while(lol) {
		course[i]=malloc(1000 * sizeof(char *));
		day[i]=malloc(1000 * sizeof(char *));
		hour[i]=malloc(1000 * sizeof(char *));

		lol = (fscanf(database, "%s %s %s\n", course[i], day[i], hour[i])!=EOF);

		if(strcmp(course[i],"Course")!=0 && strcmp(course[i],"")!=0) {
			insertCDH(createCDH(course[i], day[i], hour[i]), HASHTABLE_CDH);
		}
		//printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		//printf("tootoo\n");
		i++;

	}

   	fclose(database);
}

void file_read_CR(struct CRLIST HASHTABLE_CR[]);
void file_read_CR(struct CRLIST HASHTABLE_CR[]) {
	int lol = true;
	char* course[1000];
	char* room[1000];

	int i=0;

	FILE* database = fopen("CR_table.txt", "r");

	while(lol) {
		course[i]=malloc(1000 * sizeof(char *));
		room[i]=malloc(1000 * sizeof(char *));

		lol = (fscanf(database, "%s %s\n", course[i], room[i])!=EOF);

		//printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		if(strcmp(course[i],"Course")!=0 && strcmp(course[i],"")!=0) {
			insertCR(createCR(course[i], room[i]),HASHTABLE_CR);
		}
		//printf("tootoo\n");
		i++;

	}

   	fclose(database);
}

void file_read_CP(struct CPLIST HASHTABLE_CP[]);
void file_read_CP(struct CPLIST HASHTABLE_CP[]) {

	int lol = true;
	char* course[1000];
	char* prereq[1000];

	int i=0;

	FILE* database = fopen("CP_table.txt", "r");

	while(lol) {
		course[i]=malloc(1000 * sizeof(char *));
		prereq[i]=malloc(1000 * sizeof(char *));

		lol = (fscanf(database, "%s %s\n", course[i], prereq[i])!=EOF);

		//printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		if(strcmp(course[i],"Course")!=0 && strcmp(course[i],"")!=0) {
			insertCP(createCP(course[i], prereq[i]), HASHTABLE_CP);
		}
		//printf("tootoo\n");
		i++;

	}

   	fclose(database);
}

void file_read_SNAP(struct SNAPLIST HASHTABLE_SNAP[]);
void file_read_SNAP(struct SNAPLIST HASHTABLE_SNAP[]) {

	int lol = true;
	char* sid[1000];
	char* name[1000];
	char* address[1000];
	char* phone[1000];

	int i=0;

	FILE* database = fopen("SNAP_table.txt", "r");

	while(lol) {
		sid[i]=malloc(1000 * sizeof(char *));
		name[i]=malloc(1000 * sizeof(char *));
		address[i]=malloc(1000 * sizeof(char *));
		phone[i]=malloc(1000 * sizeof(char *));

		lol = (fscanf(database, "%s %s %s %s\n", sid[i], name[i], address[i], phone[i])!=EOF);

		//printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		if(strcmp(sid[i],"StudentId")!=0 && strcmp(sid[i],"")!=0) {
			insertSNAP(createSNAP(sid[i], name[i], address[i], phone[i]), HASHTABLE_SNAP);
		}
		//printf("tootoo\n");
		i++;

	}

   	fclose(database);	
}

void file_read_CSG(struct CSGLIST HASHTABLE_CSG[]);
void file_read_CSG(struct CSGLIST HASHTABLE_CSG[]) {

	int lol = true;
	char* course[1000];
	char* sid[1000];
	char* grade[1000];

	int i=0;

	FILE* database = fopen("CSG_table.txt", "r");

	while(lol) {
		course[i]=malloc(1000 * sizeof(char *));
		sid[i]=malloc(1000 * sizeof(char *));
		grade[i]=malloc(1000 * sizeof(char *));

		lol = (fscanf(database, "%s %s %s\n", course[i],sid[i], grade[i])!=EOF);

		//printf("this should be in it %s %s %s \n", course[i], day[i], hour[i]);
		if(strcmp(course[i],"Course")!=0 && strcmp(course[i],"")!=0) {
			insertCSG(createCSG(course[i], sid[i], grade[i]), HASHTABLE_CSG);
		}
		//printf("tootoo\n");
		i++;

	}

   	fclose(database);	
}

void grade_lookup(char* name, char* course, struct SNAPLIST HASHTABLE_SNAP[], struct CSGLIST HASHTABLE_CSG[]);
void grade_lookup(char* name, char* course, struct SNAPLIST HASHTABLE_SNAP[], struct CSGLIST HASHTABLE_CSG[]) {
	
	struct SNAPLIST* namesearch = lookupSNAP("*",name,"*","*",HASHTABLE_SNAP);
	struct SNAP* iterator_snap = namesearch->head;
	while(iterator_snap!=NULL) {
		char* i = iterator_snap->StudentId;
		struct CSGLIST* temp_grades = lookupCSG(course,i,"*", HASHTABLE_CSG);
		struct CSG* iterator_csg = temp_grades->head;
		while(iterator_csg!=NULL) {
			printf("%s got the grade %s in %s.\n", name, iterator_csg->Grade, course);
			iterator_csg = iterator_csg->next;
		}
		iterator_snap = iterator_snap->next;
	}
}

void location_lookup(char* name, char* hour, char* day, struct SNAPLIST HASHTABLE_SNAP[], struct CSGLIST HASHTABLE_CSG[], struct CDHLIST HASHTABLE_CDH[], struct CRLIST HASHTABLE_CR[]);
void location_lookup(char* name, char* hour, char* day, struct SNAPLIST HASHTABLE_SNAP[], struct CSGLIST HASHTABLE_CSG[], struct CDHLIST HASHTABLE_CDH[], struct CRLIST HASHTABLE_CR[]) {
	
	struct SNAPLIST* namesearch = lookupSNAP("*",name,"*","*",HASHTABLE_SNAP);
	struct SNAP* iterator_snap = namesearch->head;
	while(iterator_snap!=NULL) {
		char* i = iterator_snap->StudentId;
		struct CSGLIST* temp_courses = lookupCSG("*",i,"*", HASHTABLE_CSG);
		struct CSG* iterator_csg = temp_courses->head;
		while(iterator_csg!=NULL) {
			char* j = iterator_csg->Course;
			struct CDHLIST* temp_times = lookupCDH(j,day,hour, HASHTABLE_CDH);
			struct CDH* iterator_cdh = temp_times->head;
			while(iterator_cdh!=NULL) {
				struct CRLIST* temp_rooms = lookupCR(iterator_cdh->Course, "*", HASHTABLE_CR);
				struct CR* iterator_cr = temp_rooms->head;
				//printf("woah5 %s \n", iterator_cr->Course);
				while(iterator_cr!=NULL) {
					printf("%s is in the room %s.\n", name, iterator_cr->Room);
					iterator_cr = iterator_cr->next;
				}
				iterator_cdh = iterator_cdh->next;
			}
			iterator_csg = iterator_csg->next;
		}
		iterator_snap = iterator_snap->next;
	}


}
//-----------MAIN METHOD IMPLEMENTATION---------------//


int main() {

	struct CRLIST hash_cr[B];
	struct CDHLIST hash_cdh[B];
	struct CPLIST hash_cp[B];
	struct SNAPLIST hash_snap[B];
	struct CSGLIST hash_csg[B];

	for(int i=0; i<B; i++) {
		hash_cdh[i].head=NULL;
		hash_cr[i].head=NULL;
		hash_cp[i].head=NULL;
		hash_snap[i].head=NULL;
		hash_csg[i].head=NULL;
	}

	struct CSG* csg1 = createCSG("CS101", "12345", "A");
	struct CSG* csg2 = createCSG("CS101", "67890", "B");
	struct CSG* csg3 = createCSG("EE200", "12345", "C");
	struct CSG* csg4 = createCSG("EE200", "22222", "B+");
	struct CSG* csg5 = createCSG("CS101", "33333", "A-");
	struct CSG* csg6 = createCSG("PH100", "67890", "C+");


	insertCSG(csg1, hash_csg);
	insertCSG(csg2, hash_csg);
	insertCSG(csg3, hash_csg);
	insertCSG(csg4, hash_csg);
	insertCSG(csg5, hash_csg);
	insertCSG(csg6, hash_csg);

	file_make_CSG(hash_csg);

	struct SNAP* snap1 = createSNAP("12345", "C_Brown", "12_Apple_St", "555-1234");
	struct SNAP* snap2 = createSNAP("67890", "L_Van_Pelt", "34_Pear_Ave", "555-5678");
	struct SNAP* snap3 = createSNAP("22222", "P_Patty", "56_Grape_Blvd", "555-9999");

	insertSNAP(snap1, hash_snap);
	insertSNAP(snap2, hash_snap);
	insertSNAP(snap3, hash_snap);

	file_make_SNAP(hash_snap);

	struct CP* cp1 = createCP("CS101", "CS100");
	struct CP* cp2 = createCP("EE200", "EE005");
	struct CP* cp3 = createCP("EE200", "CS100");
	struct CP* cp4 = createCP("CS120", "CS101");
	struct CP* cp5 = createCP("CS121", "CS120");
	struct CP* cp6 = createCP("CS205", "CS101");
	struct CP* cp7 = createCP("CS206", "CS121");
	struct CP* cp8 = createCP("CS206", "CS205");

	insertCP(cp1, hash_cp);
	insertCP(cp2, hash_cp);
	insertCP(cp3, hash_cp);
	insertCP(cp4, hash_cp);
	insertCP(cp5, hash_cp);
	insertCP(cp6, hash_cp);
	insertCP(cp7, hash_cp);
	insertCP(cp8, hash_cp);

	file_make_CP(hash_cp);

	struct CDH* cdh1 = createCDH("CS101", "M", "9AM");
	struct CDH* cdh2 = createCDH("CS101", "W", "9AM");
	struct CDH* cdh3 = createCDH("CS101", "F", "9AM");
	struct CDH* cdh4 = createCDH("EE200", "Tu", "10AM");
	struct CDH* cdh5 = createCDH("EE200", "W", "1PM");
	struct CDH* cdh6 = createCDH("EE200", "Th", "10AM");

	insertCDH(cdh1, hash_cdh);
	insertCDH(cdh2, hash_cdh);
	insertCDH(cdh3, hash_cdh);
	insertCDH(cdh4, hash_cdh);
	insertCDH(cdh5, hash_cdh);
	insertCDH(cdh6, hash_cdh);

	lookupCDH("*","W","*", hash_cdh);

	printf("%s %s lookup \n", lookupCDH("*","W","*", hash_cdh)->head->Day, lookupCDH("*","W","*",hash_cdh)->head->next->Day);

	file_make_CDH(hash_cdh);

	struct CR* cr1 = createCR("CS101", "Turing_Aud");
	struct CR* cr2 = createCR("EE200", "25_Ohm_Hall");
	struct CR* cr3 = createCR("PH100", "Newton_Lab");

	insertCR(cr1, hash_cr);
	insertCR(cr2, hash_cr);
	insertCR(cr3, hash_cr);

	file_make_CR(hash_cr);

	grade_lookup("C_Brown", "EE200", hash_snap, hash_csg);
	location_lookup("C_Brown", "9AM", "M", hash_snap, hash_csg, hash_cdh, hash_cr);

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


	//struct CP* cp = createCP("CS101", "CS100");
	//insertCP(cp);
	//struct CP* cp2 = createCP("CS101", "CS102");
	//insertCP(cp2);
	//struct CP* cp3 = createCP("CS101", "CS99");
	//struct CP* cp4 = createCP("CS101", "CS88");
	//insertCP(cp3);
	//insertCP(cp4);

	//insertCP(cp4);
	int hash = hc("CS101");
	//printf("CS102 is %s\n", HASHTABLE_CP[hash].head->next->Prerequisite);
	//printf("helo%s\n", lookupCP("CS101", "*")->head->next->Prerequisite);
	//deleteCP(cp);
	//printf("somthaf\n");
	//deleteCP(cp4);
	//printf("%s %s %sabcd\n", lookupCP("CS101", "*")->head->Prerequisite,
	//	lookupCP("CS101", "*")->head->next->Prerequisite,
	//	lookupCP("CS101", "*")->head->next->next->Prerequisite);
	//printf("%s %s %sxyz\n", HASHTABLE_CP[hash].head->Prerequisite,
	//	HASHTABLE_CP[hash].head->next->Prerequisite,
	//	HASHTABLE_CP[hash].head->next->next->Prerequisite);
	//printf("CS102 is %s\n", HASHTABLE_CP[hash].head->Prerequisite);

	hash = hc("CS173");

	struct CDH* cdh = createCDH("CS171", "M", "1AM");
	insertCDH(cdh, hash_cdh);
	struct CDH* cdh2 = createCDH("CS171", "T", "2AM");
	insertCDH(cdh2, hash_cdh);
	struct CDH* cdh3 = createCDH("CS173", "W", "3AM");
	insertCDH(cdh3, hash_cdh);
	deleteCDH(cdh3, hash_cdh);
	struct CDH* cdh9 = createCDH("CS173", "W", "3AM");
	insertCDH(cdh9, hash_cdh);
	deleteCDH(cdh9, hash_cdh);
	//printf("point is %p \n", lookupCDH("CS173", "W", "3AM")->head);
	//printf("looking up %p", lookupCDH("CS173", "W", "3AM")->head);
	//struct CDH* cdh4 = createCDH("CS173", "TH", "4AM");
	//insertCDH(cdh4);
	//struct CDH* cdh5 = createCDH("CS173", "FI", "78AM");
	//nsertCDH(cdh5);
	//deleteCDH(cdh5);
	insertSNAP(createSNAP("a","b","c","d"), hash_snap);
	//deleteSNAP(createSNAP("a","b","c","d"));
	//printf("ok123\n");
	//printf("first snap %s \n", HASHTABLE_SNAP[hc("a")].head->StudentId);
	//printf("%s %sxyz\n", HASHTABLE_CDH[hash].head->Hour,
	//	HASHTABLE_CDH[hash].head->next->Hour);
	char* abc = "1";
	//printf("is it equal %d %d \n", *abc-'0','*');
	//struct CDH* test = lookupCDH("CSC171")->head->next;
	//printf(" NOW NOW %s \n", HASHTABLE_CDH[h(*"CSC172")].head->next->next->Course);
	//printf("%s\n", test->next->Day);
	//printf("is it in %s\n", lookupCDH("CS173", "W", "3AM")->head->Day);
	printf("here1 \n");
	//file_make_CDH();
	printf("here2 \n");
	//file_read_CDH();
	printf("here3 \n");
	//file_make_CDH();
	//printf("point is %p \n", lookupCDH("CS173", "W", "3AM", hash_cdh)->head->next);
	//printf("Finally %s \n", HASHTABLE_CDH[hc("CS171")].head->next->Course);
	//struct CDH* cdh6 = createCDH("CS162", "FadI", "78safdAM");
	//insertCDH(cdh6);
	//file_read_CDH();
	file_make_CDH(hash_cdh);
	struct CP* cp1 = createCP("CS12","ROOM1020");
	struct CP* cp2 = createCP("CS13","ROOM1011");
	struct CP* cp3 = createCP("CS12","ROOM1010");
	insertCP(cp1,hash_cp);
	insertCP(cp2,hash_cp);
	//deleteCP(cp1,hash_cp);
	insertCP(cp3,hash_cp);
	file_make_CP(hash_cp);
	file_read_CP(hash_cp);
	file_make_CP(hash_cp);*/

	return 0;

}