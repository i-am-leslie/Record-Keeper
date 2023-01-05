#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define MAX_TEXT 512
#include <sys/msg.h>
#include "Struct.h"
#include <time.h>
#include <sys/time.h>
#define MICRO_SEC_IN_SEC 1000000
int main(){

	int running = 1;
	int msgid; //holds user message id
	int msgid1;//holds record kepper message id
	struct command_word some_data;
	struct my_msg_st data[10];
	int datastored=0;
	char deleterecord[5];
	char getProgramaverage[3];
	long int msg_to_receive = 0;
	int commandWord;
	int clientid=createuserid();
	int recordKepperid=createRecordKepper();
	struct timeval start,end;
	struct command_word capcommand;// captures the command
	
    while(running){
    
    	
    	if (msgrcv(clientid, (void *)&capcommand, BUFSIZ,msg_to_receive, 0) == -1) {
		fprintf(stderr, "msgrcv failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
			
		}
	printf("You wrote: %s", capcommand.command);
/********This is the command that runs when you want to create a record for student ********/
	gettimeofday(&start,NULL);	
	if(strncmp(capcommand.command,CREATE,6)==0 && datastored!=11){
		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(data[datastored].name,some_data.command);
		printf("%s\n",data[datastored].name);
		fflush(stdout);
		
		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(data[datastored].program_name,some_data.command);
		printf("%s\n",data[datastored].program_name);
		fflush(stdout);
		
		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(data[datastored].student_number,some_data.command);
		printf("%s\n",data[datastored].student_number);
		fflush(stdout);
		
		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(data[datastored].GPA,some_data.command);
		printf("%s\n",data[datastored].GPA);
		datastored++;
		fflush(stdout);


    	
       
        
				
    }
    gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
   
    
    fflush(stdout);
    if (strncmp(capcommand.command,CREATE,6)==0 && datastored==11){// checks if the array is full
			printf("Reached limit for storing\n");
			fflush(stdout);
			continue;	
				
		}
/********			end of command 					       ********/






    gettimeofday(&start,NULL);
    if(strncmp(capcommand.command,DELETE,6)==0 ){
    		
    		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(deleterecord,some_data.command);
		for(int i=0;i<datastored;i++){
			if(strncmp(data[i].student_number,deleterecord,5)==0){
				printf("You just deleted %s\n",data[i].name);
				struct my_msg_st empty;
				data[i]= empty;
				fflush(stdout);
				
			}
		}
     gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
    }
    
     gettimeofday(&start,NULL);    
     if(strncmp(capcommand.command,CHECK_GPA,9)==0 ){
    		
    		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(deleterecord,some_data.command);
		printf("You want the gpa ");
		for(int i=0;i<datastored;i++){
			if(strncmp(data[i].student_number,deleterecord,3)==0){
				strcpy(some_data.command,data[i].GPA);
				some_data.my_msg_type=1;
		  	 if (msgsnd(recordKepperid, (void *)&some_data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
				printf("%s\n",data[i].GPA);
				fflush(stdout);
				
			}
		}
    
    }
    gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
    
     gettimeofday(&start,NULL);
    if(strncmp(capcommand.command,PROGRAM_STUDENTS,8)==0 ){
    		
    		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(deleterecord,some_data.command);
		printf("You want the students in  %s\n",some_data.command);
		for(int i=0;i<datastored;i++){
			if((strncmp(some_data.command,data[i].program_name,3)==0)|| (strncmp(some_data.command,data[i].program_name,2)==0)|| (strncmp(some_data.command,data[i].program_name,4)==0)){
				strcpy(some_data.command,data[i].student_number);
		  	 
				printf("%s\n",data[i].student_number);
				fflush(stdout);
				
			}
		}
    
    }
    gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
    
     gettimeofday(&start,NULL);
    if(strncmp(capcommand.command,CHECK_NAME,10)==0 ){
    		
    		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(deleterecord,some_data.command);
		printf("You want to get studnets name ");
		for(int i=0;i<datastored;i++){
			if(strncmp(data[i].student_number,deleterecord,2)==0){
				strcpy(some_data.command,data[i].name);
				some_data.my_msg_type=1;
		  	 if (msgsnd(recordKepperid, (void *)&some_data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
				printf("%s\n",data[i].name);
				fflush(stdout);
				
			}
		}
    
    }
    gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
    
    /*Getting average*/
    gettimeofday(&start,NULL);
    if(strncmp(capcommand.command,AVERAGE,7)==0 ){
    		
    		if (msgrcv(clientid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

		}
		strcpy(getProgramaverage,some_data.command);
		int total=0;
		for(int i=0;i<datastored;i++){
			if(strncmp(data[i].program_name,getProgramaverage,3)==0|| strncmp(data[i].program_name,getProgramaverage,2)==0||strncmp(data[i].program_name,getProgramaverage,4)==0){
				
				total+=atoi(data[i].GPA);
				
			}
			
		}
		printf("You just trying to get average %s\n",getProgramaverage);
		total=total/datastored;
		printf("total %d\n",total);
    
    }
    gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
    /*Getting average*/
    
    gettimeofday(&start,NULL);
    if (strncmp(capcommand.command, END, 3) == 0) {
			running = 0;
		}
     gettimeofday(&end,NULL);
    printf("Time taken:%ld seconds\n",(end.tv_sec-start.tv_sec));
	
}
	if (msgctl(clientid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
	exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
