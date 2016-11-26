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
		if(strcmp(Course, "*")==0) {
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
		}

		else {
			struct CR* iterator_cr = HASHTABLE_CR[hc(Course)].head;
			while(iterator_cr!=NULL) {
				if((strcmp(iterator_cr->Room,Room)==0 || strcmp(Room,"*")==0) &&
					(strcmp(iterator_cr->Course,Course)==0 || strcmp(Course,"*")==0)) {
					struct CR* temp2 = createCR(iterator_cr->Course, iterator_cr->Room);
					temp2->next = crlist->head;
					crlist->head = temp2;
				}
				iterator_cr = iterator_cr->next;
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

void deleteCR(char* Course, char* Room, struct CRLIST HASHTABLE_CR[]);
void deleteCR(char* Course, char* Room, struct CRLIST HASHTABLE_CR[]) {

	int hash = hc(Course);
	int match = 0;

	if(strcmp(Course, "*")==0) {
		for(int i=0; i<B; i++) {
			struct CR* temp_cr = HASHTABLE_CR[i].head;
			int q = 1;
			if(temp_cr!=NULL) {
				struct CR* temp_cr_next = temp_cr->next;
				while(HASHTABLE_CR[i].head!=NULL && q == 1) {
					if((strcmp(Course,temp_cr->Course)==0 || strcmp(Course,"*")==0) && (strcmp(Room,temp_cr->Room)==0 || strcmp(Room, "*")==0)) {
						HASHTABLE_CR[i].head = HASHTABLE_CR[i].head->next;
						temp_cr = HASHTABLE_CR[i].head;
					}
					else {
						q = 0;
					}
				}
				if(temp_cr!=NULL) {
					temp_cr_next = temp_cr->next;
					while(temp_cr_next!=NULL) {
						if((strcmp(temp_cr_next->Course,Course)==0 || strcmp(Course,"*")==0) && (strcmp(temp_cr_next->Room,Room)==0 || strcmp(Room,"*")==0) ) {
							temp_cr->next = temp_cr_next->next;
						}
						if(temp_cr!=NULL) {
							temp_cr = temp_cr->next;
							temp_cr_next = temp_cr_next->next;
						}	
					}				
				}	
			}
		}			
	}

	else {
		struct CR* temp_cr = HASHTABLE_CR[hash].head;
		int q = 1;
		if(temp_cr!=NULL) {
			struct CR* temp_cr_next = temp_cr->next;
			while(HASHTABLE_CR[hash].head!=NULL && q == 1) {
				if((strcmp(Course,temp_cr->Course)==0 || strcmp(Course,"*")==0) && (strcmp(Room,temp_cr->Room)==0 || strcmp(Room, "*")==0)) {
					
					HASHTABLE_CR[hash].head = HASHTABLE_CR[hash].head->next;
					temp_cr = HASHTABLE_CR[hash].head;
				}
				else {
					q = 0;
				}
			}
			if(temp_cr!=NULL) {
				temp_cr_next = temp_cr->next;
				while(temp_cr_next!=NULL) {
					if((strcmp(temp_cr_next->Course,Course)==0 || strcmp(Course,"*")==0) && (strcmp(temp_cr_next->Room,Room)==0 || strcmp(Room,"*")==0) ) {
						temp_cr->next = temp_cr_next->next;
					}
					if(temp_cr!=NULL) {
						temp_cr = temp_cr->next;
						temp_cr_next = temp_cr_next->next;
					}	
				}				
			}	
		}
	}
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
		if(strcmp(Course,"*")==0) {
			for(int i=0; i<B; i++) {
				struct CDH* temp1 = HASHTABLE_CDH[i].head;
				while(temp1!=NULL) {
					if((strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) && (strcmp(temp1->Day,Day)==0 || strcmp(Day,"*")==0) && (strcmp(temp1->Hour,Hour)==0 || strcmp(Hour,"*")==0)) {
						struct CDH* temp2 = createCDH(temp1->Course, temp1->Day, temp1->Hour);
						temp2->next = cdhlist->head;
						cdhlist->head = temp2;
					}
					temp1=temp1->next;
				}
			}
		}

		else {
			struct CDH* iterator_cdh = HASHTABLE_CDH[hc(Course)].head;	
			while(iterator_cdh!=NULL) {
				
				if((strcmp(iterator_cdh->Day,Day)==0 || strcmp(Day,"*")==0)&&
				(strcmp(iterator_cdh->Hour,Hour)==0 || strcmp(Hour,"*")==0)&&
				(strcmp(iterator_cdh->Course,Course)==0|| strcmp(Course,"*")==0)) {
					struct CDH* temp2 = createCDH(iterator_cdh->Course, iterator_cdh->Day, iterator_cdh->Hour);
					temp2->next = cdhlist->head;
					cdhlist->head = temp2;
				}
				iterator_cdh = iterator_cdh->next;
			}
		}
		return cdhlist;

	
}

void insertCDH(struct CDH* cdh, struct CDHLIST HASHTABLE_CDH[]);
void insertCDH(struct CDH* cdh, struct CDHLIST HASHTABLE_CDH[]){
	int hash = hc(cdh->Course);

	if(lookupCDH(cdh->Course, cdh->Day, cdh->Hour, HASHTABLE_CDH)->head==NULL) {

		if (HASHTABLE_CDH[hash].head != NULL) {

			struct CDH* temp_CDH = HASHTABLE_CDH[hash].head;
			HASHTABLE_CDH[hash].head = cdh;
			cdh->next = temp_CDH;
		}

		else {
			HASHTABLE_CDH[hash].head = cdh;
		}
	}

}
void deleteCDH(char* Course, char* Day, char* Hour, struct CDHLIST HASHTABLE_CDH[]);
void deleteCDH(char* Course, char* Day, char* Hour, struct CDHLIST HASHTABLE_CDH[]){

	int hash = hc(Course);
	int match = 0;
	if(strcmp(Course, "*")==0) {
		for(int i=0; i<B; i++) {
			struct CDH* temp_cdh = HASHTABLE_CDH[i].head;
			int q = 1;
			if(temp_cdh!=NULL) {
				struct CDH* temp_cdh_next = temp_cdh->next;
				while(HASHTABLE_CDH[i].head!=NULL && q == 1) {
					if((strcmp(Course,temp_cdh->Course)==0 || strcmp(Course,"*")==0) 
						&& (strcmp(Day,temp_cdh->Day)==0 || strcmp(Day, "*")==0)
						&& (strcmp(Hour, temp_cdh->Hour)==0 || strcmp(Hour, "*")==0)) {
						HASHTABLE_CDH[i].head = HASHTABLE_CDH[i].head->next;
						temp_cdh = HASHTABLE_CDH[i].head;
					}
					else {
						q = 0;
					}
				}
				if(temp_cdh!=NULL) {
					temp_cdh_next = temp_cdh->next;
					while(temp_cdh_next!=NULL) {
						if((strcmp(temp_cdh_next->Course,Course)==0 || strcmp(Course,"*")==0)
						 && (strcmp(temp_cdh_next->Day,Day)==0 || strcmp(Day,"*")==0)
						 && (strcmp(temp_cdh_next->Hour, Hour)==0 || strcmp(Hour, "*")==0) ) {
							temp_cdh->next = temp_cdh_next->next;
						}
						if(temp_cdh!=NULL) {
							temp_cdh = temp_cdh->next;
							temp_cdh_next = temp_cdh_next->next;
						}	
					}				
				}	
			}
		}			
	}

	else {
		struct CDH* temp_cdh = HASHTABLE_CDH[hash].head;
		int q = 1;
		if(temp_cdh!=NULL) {
			//printf("got5\n");
			struct CDH* temp_cdh_next = temp_cdh->next;
				//printf("course room %s %s \n", temp_cdh->Course, temp_cdh->Room);
			while(HASHTABLE_CDH[hash].head!=NULL && q == 1) {
				//printf("1111\n");
				if((strcmp(Course,temp_cdh->Course)==0 || strcmp(Course,"*")==0)
				 && (strcmp(Day,temp_cdh->Day)==0 || strcmp(Day, "*")==0)
				 && (strcmp(Hour, temp_cdh->Hour)==0 || strcmp(Hour, "*")==0)) {
					//printf("22222\n");
					//printf("got1\n");
					//printf("deleting2 %s %s\n", HASHTABLE_CDH[hash].head->Course, HASHTABLE_CDH[hash].head->Room);
					HASHTABLE_CDH[hash].head = HASHTABLE_CDH[hash].head->next;
					temp_cdh = HASHTABLE_CDH[hash].head;
					//printf("got2\n");
				}
				else {
					q = 0;
				}
			}
			if(temp_cdh!=NULL) {
				temp_cdh_next = temp_cdh->next;
				while(temp_cdh_next!=NULL) {
					//printf("got3\n");
					if((strcmp(temp_cdh_next->Course,Course)==0 || strcmp(Course,"*")==0)
					 && (strcmp(temp_cdh_next->Day,Day)==0 || strcmp(Day,"*")==0) 
					 && (strcmp(temp_cdh_next->Hour,Hour)==0 || strcmp(Hour,"*")==0)) {
						//printf("got4\n");
						//printf("deleting1 %s %s\n", temp_cdh_next->Course, temp_cdh_next->Room);
						temp_cdh->next = temp_cdh_next->next;
					}
					if(temp_cdh!=NULL) {
						//printf("got5\n");
						temp_cdh = temp_cdh->next;
						temp_cdh_next = temp_cdh_next->next;
					}	
				}				
			}	
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

	struct CPLIST* cplist = (struct CPLIST*) malloc(sizeof(struct CPLIST));
		cplist->head = NULL;
		struct CP* temp;

	if (strcmp(Course, "*")!=0){
		int hash = hc(Course);

		struct CP* temp1 = HASHTABLE_CP[hash].head;
		while(temp1!=NULL) {
			if((strcmp(temp1->Course,Course)==0 || strcmp(Course, "*")==0) && (strcmp(temp1->Prerequisite,Prerequisite)==0 || strcmp(Prerequisite, "*")==0)) {
				struct CP* temp2 = createCP(temp1->Course, temp1->Prerequisite);
				temp2->next = cplist->head;
				cplist->head = temp2;
			}
			temp1=temp1->next;
		}
	}
	else {
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
	}
	return cplist;
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

void deleteCP(char *Course, char *Prerequisite, struct CPLIST HASHTABLE_CP[]);
void deleteCP(char *Course, char *Prerequisite, struct CPLIST HASHTABLE_CP[]){


	////////--------------------------------------------



	int hash = hc(Course);
	int match = 0;
	if(strcmp(Course, "*")==0) {
		for(int i=0; i<B; i++) {
			struct CP* temp_cp = HASHTABLE_CP[i].head;
			int q = 1;
			if(temp_cp!=NULL) {
				struct CP* temp_cp_next = temp_cp->next;
				while(HASHTABLE_CP[i].head!=NULL && q == 1) {
					if((strcmp(Course,temp_cp->Course)==0 || strcmp(Course,"*")==0) 
						&& (strcmp(Prerequisite,temp_cp->Prerequisite)==0 || strcmp(Prerequisite, "*")==0)) {
						HASHTABLE_CP[i].head = HASHTABLE_CP[i].head->next;
						temp_cp = HASHTABLE_CP[i].head;
					}
					else {
						q = 0;
					}
				}
				if(temp_cp!=NULL) {
					temp_cp_next = temp_cp->next;
					while(temp_cp_next!=NULL) {
						if((strcmp(temp_cp_next->Course,Course)==0 || strcmp(Course,"*")==0)
						 && (strcmp(temp_cp_next->Prerequisite,Prerequisite)==0 || strcmp(Prerequisite,"*")==0) ) {
							temp_cp->next = temp_cp_next->next;
						}
						if(temp_cp!=NULL) {
							temp_cp = temp_cp->next;
							temp_cp_next = temp_cp_next->next;
						}	
					}				
				}	
			}
		}			
	}

	else {
		struct CP* temp_cp = HASHTABLE_CP[hash].head;
		int q = 1;
		if(temp_cp!=NULL) {
			struct CP* temp_cp_next = temp_cp->next;
			while(HASHTABLE_CP[hash].head!=NULL && q == 1) {
				if((strcmp(Course,temp_cp->Course)==0 || strcmp(Course,"*")==0)
				 && (strcmp(Prerequisite,temp_cp->Prerequisite)==0 || strcmp(Prerequisite, "*")==0)) {
					HASHTABLE_CP[hash].head = HASHTABLE_CP[hash].head->next;
					temp_cp = HASHTABLE_CP[hash].head;
				}
				else {
					q = 0;
				}
			}
			if(temp_cp!=NULL) {
				temp_cp_next = temp_cp->next;
				while(temp_cp_next!=NULL) {
					if((strcmp(temp_cp_next->Course,Course)==0 || strcmp(Course,"*")==0)
					 && (strcmp(temp_cp_next->Prerequisite,Prerequisite)==0 || strcmp(Prerequisite,"*")==0)) {
						temp_cp->next = temp_cp_next->next;
					}
					if(temp_cp!=NULL) {
						temp_cp = temp_cp->next;
						temp_cp_next = temp_cp_next->next;
					}	
				}				
			}	
		}
	}
	/////////////---------------------
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

void deleteSNAP( char *StudentId, char *Name, char *Address, char *Phone, struct SNAPLIST HASHTABLE_SNAP[]);
void deleteSNAP( char *StudentId, char *Name, char *Address, char *Phone, struct SNAPLIST HASHTABLE_SNAP[]){
	////---------------------------------------
	
	int hash = hc(StudentId);
	int match = 0;
	if(strcmp(StudentId, "*")==0) {
		for(int i=0; i<B; i++) {
			struct SNAP* temp_snap = HASHTABLE_SNAP[i].head;
			int q = 1;
			if(temp_snap!=NULL) {
				struct SNAP* temp_snap_next = temp_snap->next;
				while(HASHTABLE_SNAP[i].head!=NULL && q == 1) {
					if((strcmp(StudentId,temp_snap->StudentId)==0 || strcmp(StudentId,"*")==0) 
						&& (strcmp(Name,temp_snap->Name)==0 || strcmp(Name, "*")==0)
						&& (strcmp(Address, temp_snap->Address)==0 || strcmp(Address, "*")==0)
						&& (strcmp(Phone, temp_snap->Phone)==0 || strcmp(Phone, "*")==0)) {
						HASHTABLE_SNAP[i].head = HASHTABLE_SNAP[i].head->next;
						temp_snap = HASHTABLE_SNAP[i].head;
					}
					else {
						q = 0;
					}
				}
				if(temp_snap!=NULL) {
					temp_snap_next = temp_snap->next;
					while(temp_snap_next!=NULL) {
						if((strcmp(temp_snap_next->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0)
						 && (strcmp(temp_snap_next->Name,Name)==0 || strcmp(Name,"*")==0)
						 && (strcmp(temp_snap_next->Address, Address)==0 || strcmp(Address, "*")==0) 
						 && (strcmp(temp_snap_next->Phone, Phone)==0 || strcmp(Phone, "*")==0)) {
							temp_snap->next = temp_snap_next->next;
						}
						if(temp_snap!=NULL) {
							temp_snap = temp_snap->next;
							temp_snap_next = temp_snap_next->next;
						}	
					}				
				}	
			}
		}			
	}

	else {
		struct SNAP* temp_snap = HASHTABLE_SNAP[hash].head;
		int q = 1;
		if(temp_snap!=NULL) {
			//printf("got5\n");
			struct SNAP* temp_snap_next = temp_snap->next;
				//printf("course room %s %s \n", temp_cdh->Course, temp_cdh->Room);
			while(HASHTABLE_SNAP[hash].head!=NULL && q == 1) {
				//printf("1111\n");
				if((strcmp(StudentId,temp_snap->StudentId)==0 || strcmp(StudentId,"*")==0)
				 && (strcmp(Name,temp_snap->Name)==0 || strcmp(Name, "*")==0)
				 && (strcmp(Address, temp_snap->Address)==0 || strcmp(Address, "*")==0)
				 && (strcmp(Phone, temp_snap->Phone)==0 || strcmp(Phone, "*")==0)) {
					HASHTABLE_SNAP[hash].head = HASHTABLE_SNAP[hash].head->next;
					temp_snap = HASHTABLE_SNAP[hash].head;
				}
				else {
					q = 0;
				}
			}
			if(temp_snap!=NULL) {
				temp_snap_next = temp_snap->next;
				while(temp_snap_next!=NULL) {
					if((strcmp(temp_snap_next->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0)
					 && (strcmp(temp_snap_next->Name,Name)==0 || strcmp(Name,"*")==0) 
					 && (strcmp(temp_snap_next->Address,Address)==0 || strcmp(Address,"*")==0)
					 && (strcmp(temp_snap_next->Phone, Phone)==0 || strcmp(Phone,"*")==0)) {
						temp_snap->next = temp_snap_next->next;
					}
					if(temp_snap!=NULL) {
						temp_snap = temp_snap->next;
						temp_snap_next = temp_snap_next->next;
					}	
				}				
			}	
		}
	}
		//=------------------------------------
}

struct SNAPLIST* lookupSNAP(char* StudentId, char* Name, char* Address, char* Phone, struct SNAPLIST HASHTABLE_SNAP[]);
struct SNAPLIST* lookupSNAP(char* StudentId, char* Name, char* Address, char* Phone, struct SNAPLIST HASHTABLE_SNAP[]){//lookup with the SNAP

		struct SNAPLIST* snaplist = (struct SNAPLIST*) malloc(sizeof(struct SNAPLIST));
		snaplist->head = NULL;
		struct SNAP* temp;
	if (strcmp(StudentId, "*")!=0){
		int hash = hc(StudentId);

		struct SNAP* temp1 = HASHTABLE_SNAP[hash].head;
		while(temp1!=NULL) {
			if( (strcmp(temp1->Name,Name)==0 || strcmp(Name, "*")==0) && (strcmp(temp1->Phone, Phone)==0 || strcmp(Phone, "*")==0) && (strcmp(temp1->Address, Address)==0 || strcmp(Address, "*")==0)) {
				struct SNAP* temp2 = createSNAP(temp1->StudentId, temp1->Name, temp1->Address, temp1->Phone);
				temp2->next = snaplist->head;
				snaplist->head = temp2;
			}
			temp1=temp1->next;
		}
	}
	else {
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
	}
	return snaplist;

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

void deleteCSG(char* Course, char* StudentId, char* Grade, struct CSGLIST HASHTABLE_CSG[B]);
void deleteCSG(char* Course, char* StudentId, char* Grade, struct CSGLIST HASHTABLE_CSG[B]){

	int hash = hc(Course);
	int match = 0;
	if(strcmp(Course, "*")==0) {
		for(int i=0; i<B; i++) {
			struct CSG* temp_csg = HASHTABLE_CSG[i].head;
			int q = 1;
			if(temp_csg!=NULL) {
				struct CSG* temp_csg_next = temp_csg->next;
				while(HASHTABLE_CSG[i].head!=NULL && q == 1) {
					if((strcmp(Course,temp_csg->Course)==0 || strcmp(Course,"*")==0) 
						&& (strcmp(StudentId,temp_csg->StudentId)==0 || strcmp(StudentId, "*")==0)
						&& (strcmp(Grade, temp_csg->Grade)==0 || strcmp(Grade, "*")==0)) {
						HASHTABLE_CSG[i].head = HASHTABLE_CSG[i].head->next;
						temp_csg= HASHTABLE_CSG[i].head;
					}
					else {
						q = 0;
					}
				}
				if(temp_csg!=NULL) {
					temp_csg_next = temp_csg->next;
					while(temp_csg_next!=NULL) {
						if((strcmp(temp_csg_next->Course,Course)==0 || strcmp(Course,"*")==0)
						 && (strcmp(temp_csg_next->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0)
						 && (strcmp(temp_csg_next->Grade, Grade)==0 || strcmp(Grade, "*")==0) ) {
							temp_csg->next = temp_csg_next->next;
						}
						if(temp_csg!=NULL) {
							temp_csg = temp_csg->next;
							temp_csg_next = temp_csg_next->next;
						}	
					}				
				}	
			}
		}			
	}

	else {
		struct CSG* temp_csg = HASHTABLE_CSG[hash].head;
		int q = 1;
		if(temp_csg!=NULL) {
			struct CSG* temp_csg_next = temp_csg->next;
			while(HASHTABLE_CSG[hash].head!=NULL && q == 1) {
				if((strcmp(Course,temp_csg->Course)==0 || strcmp(Course,"*")==0)
				 && (strcmp(StudentId,temp_csg->StudentId)==0 || strcmp(StudentId, "*")==0)
				 && (strcmp(Grade, temp_csg->Grade)==0 || strcmp(Grade, "*")==0)) {
					HASHTABLE_CSG[hash].head = HASHTABLE_CSG[hash].head->next;
					temp_csg = HASHTABLE_CSG[hash].head;
				}
				else {
					q = 0;
				}
			}
			if(temp_csg!=NULL) {
				temp_csg_next = temp_csg->next;
				while(temp_csg_next!=NULL) {
					if((strcmp(temp_csg_next->Course,Course)==0 || strcmp(Course,"*")==0)
					 && (strcmp(temp_csg_next->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0) 
					 && (strcmp(temp_csg_next->Grade,Grade)==0 || strcmp(Grade,"*")==0)) {
						temp_csg->next = temp_csg_next->next;
					}
					if(temp_csg!=NULL) {
						temp_csg = temp_csg->next;
						temp_csg_next = temp_csg_next->next;
					}	
				}				
			}	
		}
	}

}
struct CSGLIST* lookupCSG(char* Course, char* StudentId, char* Grade, struct CSGLIST HASHTABLE_CSG[B]);
struct CSGLIST* lookupCSG(char* Course, char* StudentId, char* Grade, struct CSGLIST HASHTABLE_CSG[B]){//lookup with the SNAP

		struct CSGLIST* csglist = (struct CSGLIST*) malloc(sizeof(struct CSGLIST));
		csglist->head = NULL;
		struct CSG* temp;
	if (strcmp(Course, "*")!=0){
		int hash = hc(Course);

		struct CSG* temp1 = HASHTABLE_CSG[hash].head;
		while(temp1!=NULL) {
			if( (strcmp(temp1->StudentId,StudentId)==0 || strcmp(StudentId, "*")==0) && (strcmp(temp1->Grade, Grade)==0 || strcmp(Grade, "*")==0)) {
				struct CSG* temp2 = createCSG(temp1->Course, temp1->StudentId, temp1->Grade);
				temp2->next = csglist->head;
				csglist->head = temp2;
			}
			temp1=temp1->next;
		}
	}
	else {
		for(int i=0; i<B; i++) {
			struct CSG* temp1 = HASHTABLE_CSG[i].head;
			while(temp1!=NULL) {
				if((strcmp(temp1->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0) &&
				 (strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) &&
				 (strcmp(temp1->Grade,Grade)==0 || strcmp(Grade,"*")==0)) {

					struct CSG* temp2 = createCSG(temp1->Course, temp1->StudentId, temp1->Grade);
					temp2->next = csglist->head;
					csglist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
	}
	return csglist;
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
	//printf("starting \n");
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
				while(iterator_cr!=NULL) {
					printf("%s is in the room %s at %s on %s.\n", name, iterator_cr->Room, hour, day);
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


void unionize(struct CDHLIST hash1[], struct CDHLIST hash2[], struct CDHLIST hashjoin[]);
void unionize(struct CDHLIST hash1[], struct CDHLIST hash2[], struct CDHLIST hashjoin[]) {

	for(int i=0; i<B; i++) {
		struct CDH* new_CDH = hash1[i].head;
		while(new_CDH != NULL) {
			insertCDH(new_CDH, hashjoin);
			new_CDH = new_CDH->next;
		}
	}
	for(int i=0; i<B; i++) {
		struct CDH* new_CDH = hash2[i].head;
		while(new_CDH != NULL) {
			insertCDH(new_CDH, hashjoin);
			new_CDH = new_CDH->next;
		}
	}	
}

void intersection(struct CDHLIST hash1[], struct CDHLIST hash2[], struct CDHLIST hashjoin[]);
void intersection(struct CDHLIST hash1[], struct CDHLIST hash2[], struct CDHLIST hashjoin[]) {
		for(int i=0; i<B; i++) {
		struct CDH* new_CDH = hash1[i].head;
		while(new_CDH != NULL) {
			if(lookupCDH(new_CDH->Course, new_CDH->Day, new_CDH->Hour, hash2)!=NULL) {
				insertCDH(new_CDH, hashjoin);
			}
			new_CDH = new_CDH->next;
		}
	}
}

void difference(struct CDHLIST hash1[], struct CDHLIST hash2[], struct CDHLIST hashjoin[]);
void difference(struct CDHLIST hash1[], struct CDHLIST hash2[], struct CDHLIST hashjoin[]) {
		for(int i=0; i<B; i++) {
		struct CDH* new_CDH = hash1[i].head;
		while(new_CDH != NULL) {
			if(lookupCDH(new_CDH->Course, new_CDH->Day, new_CDH->Hour, hash2)==NULL) {
				insertCDH(new_CDH, hashjoin);
			}
			new_CDH = new_CDH->next;
		}
	}	
}

void selection(struct CSGLIST hash1[], struct CSGLIST hash2[], char* course, char* studentid, char* grade);
void selection(struct CSGLIST hash1[], struct CSGLIST hash2[], char* course, char* studentid, char* grade) {

	struct CSGLIST* csglist1 = lookupCSG(course, studentid, grade, hash1);
	struct CSG* iterator_csg = csglist1->head;
	while(iterator_csg!=NULL) {
		insertCSG(iterator_csg, hash2);
		iterator_csg = iterator_csg->next;
	}

	printf("SELECTION OF CSG for Course = %s, StudentId = %s, Grade = %s\n", course, studentid, grade);
	printf("Course StudentId Grade\n");
	for(int i=0; i<B; i++) {
		struct CSG* iterator_csg = hash2[i].head;
		while(iterator_csg!=NULL) {
			printf("%s %s %s\n",iterator_csg->Course, iterator_csg->StudentId, iterator_csg->Grade);
			iterator_csg = iterator_csg->next;
		}
	}	
}


typedef struct S *SLIST;
struct S {
	char* StudentId;

	SLIST next;
};
struct SLIST{
	struct S* head;
};

struct S* createS(char* StudentId);
struct S* createS(char* StudentId) {
	struct S* x = (struct S*) malloc(sizeof(struct S));
	x->StudentId=StudentId;
	x->next = NULL;
	return x;
}


struct SLIST* lookupS(char* StudentId, struct SLIST HASHTABLE_S[]);//lookup prerequisites for course
struct SLIST* lookupS(char* StudentId, struct SLIST HASHTABLE_S[]){//lookup prerequisites for course

		struct SLIST* slist = (struct SLIST*) malloc(sizeof(struct SLIST));
		slist->head = NULL;
		struct S* temp;

	if (strcmp(StudentId, "*")!=0){
		int hash = hc(StudentId);

		struct S* temp1 = HASHTABLE_S[hash].head;
		while(temp1!=NULL) {
			if((strcmp(temp1->StudentId,StudentId)==0 || strcmp(StudentId, "*")==0)) {
				struct S* temp2 = createS(temp1->StudentId);
				temp2->next = slist->head;
				slist->head = temp2;
			}
			temp1=temp1->next;
		}
	}
	else {
		for(int i=0; i<B; i++) {
			struct S* temp1 = HASHTABLE_S[i].head;
			while(temp1!=NULL) {
				if((strcmp(temp1->StudentId,StudentId)==0 || strcmp(StudentId,"*")==0) ) {
					struct S* temp2 = createS(temp1->StudentId);
					temp2->next = slist->head;
					slist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
	}
	return slist;
}

void insertS(struct S* s, struct SLIST HASHTABLE_S[]);
void insertS(struct S* s, struct SLIST HASHTABLE_S[]) {

	if(lookupS(s->StudentId, HASHTABLE_S)->head==NULL) {

		int hash = hc(s->StudentId);
		if (HASHTABLE_S[hash].head != NULL) {
			struct S* temp_S = HASHTABLE_S[hash].head;
			HASHTABLE_S[hash].head = s;
			s->next = temp_S;
		}
		else {
			HASHTABLE_S[hash].head = s;
			HASHTABLE_S[hash].head->next = NULL;
		}
	}
}

void projection(struct CSGLIST hashin[], struct SLIST hashout[]);
void projection(struct CSGLIST hashin[], struct SLIST hashout[]) {

	printf("\nPROJECTION OF CSG ONTO CS\n");
	printf("StudentId\n");

	for(int i=0; i<B; i++) {
		struct CSG* iterator_csg = hashin[i].head;
		while(iterator_csg!=NULL) {
			insertS(createS(iterator_csg->StudentId), hashout);
			iterator_csg = iterator_csg->next;
		}
	}

	for(int i=0; i<B; i++) {
		struct S* iterator_s = hashout[i].head;
		while(iterator_s!=NULL) {
			printf("%s\n",iterator_s->StudentId);
			iterator_s = iterator_s->next;
		}
	}
}

typedef struct CRDH *CRDHLIST;
struct CRDH {
	char* Course;
	char* Room;
	char* Day;
	char* Hour;
	CRDHLIST next;
};
struct CRDHLIST{
	struct CRDH* head;
};

struct CRDH* createCRDH(char* Course, char* Room, char* Day, char* Hour);
struct CRDH* createCRDH(char* Course, char* Room, char* Day, char* Hour) {
	struct CRDH* x = (struct CRDH*) malloc(sizeof(struct CRDH));
	x->Course=Course;
	x->Room=Room;
	x->Day=Day;
	x->Hour=Hour;
	x->next = NULL;
	return x;
}


struct CRDHLIST* lookupCRDH(char* Course, char* Room, char* Day, char* Hour, struct CRDHLIST HASHTABLE_CRDH[]);//lookup prerequisites for course
struct CRDHLIST* lookupCRDH(char* Course, char* Room, char* Day, char* Hour, struct CRDHLIST HASHTABLE_CRDH[]) {//lookup prerequisites for course

		struct CRDHLIST* crdhlist = (struct CRDHLIST*) malloc(sizeof(struct CRDHLIST));
		crdhlist->head = NULL;
		struct CRDH* temp;
	if (strcmp(Course, "*")!=0){
		int hash = hc(Course);

		struct CRDH* temp1 = HASHTABLE_CRDH[hash].head;
		while(temp1!=NULL) {
			if( (strcmp(temp1->Room,Room)==0 || strcmp(Room, "*")==0) && (strcmp(temp1->Day, Day)==0 || strcmp(Day, "*")==0) && (strcmp(temp1->Hour, Hour)==0 || strcmp(Hour, "*")==0)) {
				struct CRDH* temp2 = createCRDH(temp1->Course, temp1->Room, temp1->Day, temp1->Hour);
				temp2->next = crdhlist->head;
				crdhlist->head = temp2;
			}
			temp1=temp1->next;
		}
	}
	else {
		for(int i=0; i<B; i++) {
			struct CRDH* temp1 = HASHTABLE_CRDH[i].head;
			while(temp1!=NULL) {
				if((strcmp(temp1->Course,Course)==0 || strcmp(Course,"*")==0) &&
				 (strcmp(temp1->Room,Room)==0 || strcmp(Room,"*")==0) &&
				 (strcmp(temp1->Day,Day)==0 || strcmp(Day,"*")==0) &&
				 (strcmp(temp1->Hour,Hour)==0 || strcmp(Hour,"*")==0)) {

					struct CRDH* temp2 = createCRDH(temp1->Course, temp1->Room, temp1->Day, temp1->Hour);
					temp2->next = crdhlist->head;
					crdhlist->head = temp2;
				}
				temp1=temp1->next;
			}
		}
	}
	return crdhlist;
}

void insertCRDH(struct CRDH* crdh, struct CRDHLIST HASHTABLE_CRDH[]);
void insertCRDH(struct CRDH* crdh, struct CRDHLIST HASHTABLE_CRDH[]) {

	if(lookupCRDH(crdh->Course,crdh->Room, crdh->Day, crdh->Hour, HASHTABLE_CRDH)->head==NULL) {
		printf("success\n");
		int hash = hc(crdh->Course);
		if (HASHTABLE_CRDH[hash].head != NULL) {
			struct CRDH* temp_CRDH = HASHTABLE_CRDH[hash].head;
			HASHTABLE_CRDH[hash].head = crdh;
			crdh->next = temp_CRDH;
		}
		else {
			HASHTABLE_CRDH[hash].head = crdh;
			HASHTABLE_CRDH[hash].head->next = NULL;
		}
	}

	else {
		printf("oops\n");
	}
}

void join(struct CRLIST HASHTABLE_CR[], struct CDHLIST HASHTABLE_CDH[], struct CRDHLIST HASHTABLE_CRDH[]);
void join(struct CRLIST HASHTABLE_CR[], struct CDHLIST HASHTABLE_CDH[], struct CRDHLIST HASHTABLE_CRDH[]) {

	for(int i=0; i<B; i++) {
		struct  CR* iterator_cr = HASHTABLE_CR[i].head;
		while(iterator_cr!=NULL) {
			char* a = iterator_cr->Course;
			struct CDHLIST* cdhlist = lookupCDH(a, "*", "*", HASHTABLE_CDH);
			struct CDH* iterator_cdh = cdhlist->head;
			while(iterator_cdh!=NULL) {
				struct CRDH* tempcrdh = createCRDH(iterator_cr->Course, iterator_cr->Room, iterator_cdh->Day,
				 iterator_cdh->Hour);
				insertCRDH(tempcrdh, HASHTABLE_CRDH);
				iterator_cdh = iterator_cdh->next;
			}
			iterator_cr = iterator_cr->next;
		}
	}

	printf("\nJOINING CR and CDH\n");
	printf("Course Room Day Hour\n");

	for(int i=0; i<B; i++) {
		struct CRDH* iterator_crdh = HASHTABLE_CRDH[i].head;
		while(iterator_crdh!=NULL) {
			printf("%s %s %s %s\n", iterator_crdh->Course, iterator_crdh->Room,
				iterator_crdh->Day, iterator_crdh->Hour);
			iterator_crdh= iterator_crdh->next;
		}
	}
}

typedef struct DH *DHLIST;
struct DH {
	char* Day;
	char* Hour;
	DHLIST next;
};
struct DHLIST {
	struct DH* head;
};

struct DH* createDH(char* Day, char* Hour);
struct DH* createDH(char* Day, char* Hour){
	struct DH* x = (struct DH*) malloc(sizeof(struct DH));
	x->Day = Day;
	x->Hour = Hour;
	x->next = NULL;
	return x;
}

struct DHLIST* lookupDH(char* Day, char* Hour, struct DHLIST HASHTABLE_DH[]);
struct DHLIST* lookupDH(char* Day, char* Hour, struct DHLIST HASHTABLE_DH[]) {
	struct DHLIST* dhlist = (struct DHLIST*) malloc(sizeof(struct DHLIST));
		dhlist->head = NULL;
		if(strcmp(Day, "*")==0) {
			for(int i=0; i<B; i++) {
				struct DH* temp1 = HASHTABLE_DH[i].head;
				while(temp1!=NULL) {
					if((strcmp(temp1->Day,Day)==0 || strcmp(Day,"*")==0) && (strcmp(temp1->Hour,Hour)==0 || strcmp(Hour,"*")==0) ) {
						struct DH* temp2 = createDH(temp1->Day, temp1->Hour);
						temp2->next = dhlist->head;
						dhlist->head = temp2;
					}
					temp1=temp1->next;
				}
			}			
		}

		else {
			struct DH* iterator_dh = HASHTABLE_DH[hc(Day)].head;
			while(iterator_dh!=NULL) {
				if((strcmp(iterator_dh->Day,Day)==0 || strcmp(Day,"*")==0) &&
					(strcmp(iterator_dh->Hour, Hour)==0 || strcmp(Hour,"*")==0)) {
					struct DH* temp2 = createDH(iterator_dh->Day, iterator_dh->Hour);
					temp2->next = dhlist->head;
					dhlist->head = temp2;
				}
				iterator_dh = iterator_dh->next;
			}
		}

	return dhlist;

	/////
}

void insertDH(struct DH* dh, struct DHLIST HASHTABLE_DH[]);
void insertDH(struct DH* dh, struct DHLIST HASHTABLE_DH[]){

	if(lookupDH(dh->Day, dh->Hour, HASHTABLE_DH)->head==NULL) {

		int hash = hc(dh->Day);
		if (HASHTABLE_DH[hash].head != NULL) {
			struct DH* temp_dh = HASHTABLE_DH[hash].head;
			HASHTABLE_DH[hash].head = dh;
			dh->next = temp_dh;
		}
		else {
			HASHTABLE_DH[hash].head = dh;
			HASHTABLE_DH[hash].head->next = NULL;
		}
	}
}

void selectionCRDH(struct CRDHLIST hash1[], struct CRDHLIST hash2[], char* course, char* room, char* day, char* hour);
void selectionCRDH(struct CRDHLIST hash1[], struct CRDHLIST hash2[], char* course, char* room, char* day, char* hour) {

	int v=0;
	struct CRDHLIST* crdhlist1 = lookupCRDH(course, room, day, hour, hash1);
	printf("looking up in selection %p \n", crdhlist1->head->next);
	struct CRDH* iterator_crdh = crdhlist1->head;
	while(iterator_crdh!=NULL) {
		insertCRDH(iterator_crdh, hash2);
		iterator_crdh = iterator_crdh->next;
		printf("\n%p pointer \n", crdhlist1->head->next);
		v++;
		printf("\n %d number of times \n", v);
	}

	printf("SELECTION OF CRDH for Course = %s, Room = %s, Day = %s, Hour = %s\n", course, room, day, hour);
	printf("Course Room Day Hour\n");
	for(int i=0; i<B; i++) {
		struct CRDH* iterator_crdh = hash2[i].head;
		while(iterator_crdh!=NULL) {
			printf("%s %s %s %s\n",iterator_crdh->Course, iterator_crdh->Room, iterator_crdh->Day, iterator_crdh->Hour);
			iterator_crdh = iterator_crdh->next;
		}
	}
}

void projectionDH(struct CRDHLIST hashin[], struct DHLIST hashout[]);
void projectionDH(struct CRDHLIST hashin[], struct DHLIST hashout[]) {

	printf("\nPROJECTION OF CRDH ONTO DH\n");
	printf("Day Hour\n");

	for(int i=0; i<B; i++) {
		struct CRDH* iterator_crdh = hashin[i].head;
		while(iterator_crdh!=NULL) {
			insertDH(createDH(iterator_crdh->Day, iterator_crdh->Hour), hashout);
			iterator_crdh = iterator_crdh->next;
		}
	}

	for(int i=0; i<B; i++) {
		struct DH* iterator_dh = hashout[i].head;
		while(iterator_dh!=NULL) {
			printf("%s %s\n",iterator_dh->Day, iterator_dh->Hour);
			iterator_dh = iterator_dh->next;
		}
	}
}



int main() {

	struct CRLIST hash_cr[B];
	struct CDHLIST hash_cdh[B];
	struct CPLIST hash_cp[B];
	struct SNAPLIST hash_snap[B];
	struct CSGLIST hash_csg[B];
	struct CSGLIST hash_csg_select[B];
	struct SLIST hash_s[B];
	struct CRDHLIST hash_crdh[B];
	struct CRDHLIST hash_crdh_select[B];
	struct DHLIST hash_dh[B];

	struct CDHLIST hash_cdh2[B];
	struct CDHLIST hash_cdh3[B];

	for(int i=0; i<B; i++) {
		hash_cdh[i].head=NULL;
		hash_cr[i].head=NULL;
		hash_cp[i].head=NULL;
		hash_snap[i].head=NULL;
		hash_csg[i].head=NULL;
		hash_cdh2[i].head=NULL;
		hash_cdh3[i].head=NULL;
		hash_csg_select[i].head=NULL;
		hash_s[i].head=NULL;
		hash_crdh[i].head=NULL;
		hash_crdh_select[i].head=NULL;
		hash_dh[i].head=NULL;
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

	selection(hash_csg, hash_csg_select, "CS101", "*", "*");
	projection(hash_csg_select, hash_s);

	file_make_CSG(hash_csg_select);

	struct SNAP* snap1 = createSNAP("12345", "C_Brown", "12_Apple_St", "555-1234");
	struct SNAP* snap2 = createSNAP("67890", "L_Van_Pelt", "34_Pear_Ave", "555-5678");
	struct SNAP* snap3 = createSNAP("22222", "P_Patty", "56_Grape_Blvd", "555-9999");

	insertSNAP(snap1, hash_snap);
	insertSNAP(snap2, hash_snap);
	insertSNAP(snap3, hash_snap);
	deleteSNAP("22222", "*", "*", "*", hash_snap);

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

	printf("this one %s\n", lookupCP("CS101", "*", hash_cp)->head->Prerequisite);

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


	join(hash_cr, hash_cdh, hash_crdh);

	selectionCRDH(hash_crdh, hash_crdh_select, "*", "Turing_Aud", "*", "*");

	return 0;

}