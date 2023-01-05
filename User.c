#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>
#include "Struct.h"
#define MAX_TEXT 512
#define CREATE  "create"
#define END "end"
int main(){
	int running = 1;
	long int msg_to_receive = 0;
	struct command_word data;
	struct my_msg_st some_data;
	int clientid=createuserid();
	int recordKepperid=createRecordKepper();
	struct command_word command;
    	while(running){
		printf("This is the user interface enter some command to make use of the record kepper\n");
		printf("Enter key word create to make a record\n");
		printf("Enter delete to remove a record\n");
		printf("Enter average to get The average of all students\n");
		printf("Enter 4 to check student program name\n");
		printf("Enter check_gpa to check student GPA\n");
		printf("Enter end to stop running \n");
		fgets(command.command,12,stdin);// gets user input
		
		
/********This is the command that runs when you want to create a record for student ********/
		if(strncmp(command.command,CREATE,6)==0){
		   command.my_msg_type=1;
		   if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		   data.my_msg_type=1;
		   printf("Enter student name\n");
		   scanf("%s",data.command);
		   
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		   memset(data.command,0,sizeof(data));
		   printf("program name\n");
		   scanf("%s",data.command);
		   if((strncmp(data.command,"CSE",3)!=0)|| (strncmp(data.command,"SE",2)!=0)|| (strncmp(data.command,"ELEC",4)!=0)){ // error checking for program name not complete
		   		printf("Please enter a correct program from this three choices ELEC,CSE,SE\n");
		   		scanf("%s",data.command);
		   }
		   
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		   memset(data.command,0,sizeof(data));
		    
		   printf("Enter student number\n");
		   scanf("%s",data.command);
		   if(atoi(data.command)<0 || atoi(data.command)>100){
		    	 printf("Enter a valid student number between 0 and 100 \n");
		   	 scanf("%s",data.command);
		    }
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		    
		   memset(data.command,0,sizeof(data));
		   printf("Enter student GPA\n");
		   scanf("%s",data.command);
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		    memset(data.command,0,sizeof(data));
		  
		}
/********			end of command 					       ********/


		
		/********This is the command to stop the whole program ********/
		
		if (strncmp(command.command,END,3)==0) {
				running = 0;
				command.my_msg_type=1;
				if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
					fprintf(stderr, "msgsnd failed\n");
					exit(EXIT_FAILURE);
				}
			}
			/********			end of command 					       ********/
			
			
		/********This is the command to delete a student ********/	
		if(strncmp(command.command,DELETE,6)==0){
		   command.my_msg_type=1;
		   if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
					fprintf(stderr, "msgsnd failed\n");
					exit(EXIT_FAILURE);
				
				}
		   data.my_msg_type=1;
		   printf("Enter student number to delete\n");
		   scanf("%s",data.command);
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		    memset(data.command,0,sizeof(data));
		   
		}
		/********			end of command 					       ********/
		
		
		if(strncmp(command.command,AVERAGE,7)==0){
		   command.my_msg_type=1;
		   if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
					fprintf(stderr, "msgsnd failed\n");
					exit(EXIT_FAILURE);
				
				}
		   data.my_msg_type=1;
		   printf("Enter Program to check average \n");
		   scanf("%s",data.command);
		   if(!(strncmp(data.command,"CSE",3)==0)|| !(strncmp(data.command,"SE",2)==0)|| !(strncmp(data.command,"ELEC",4)==0)){ // error checking for program name not complete
		   		printf("Please enter a correct program from this three choices ELEC,CSE,SE\n");
		   		scanf("%s",data.command);
		   }
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		    memset(data.command,0,sizeof(data));
		   
		}
		if(strncmp(command.command,CHECK_GPA,7)==0){
		   command.my_msg_type=1;
		   if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
					fprintf(stderr, "msgsnd failed\n");
					exit(EXIT_FAILURE);
				
				}
		   data.my_msg_type=1;
		   printf("student number to check for GPA \n");
		   scanf("%s",data.command);
		   
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		    if (msgrcv(recordKepperid, (void *)&data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);

			}
		   char gpa[6];
		   strcpy(data.command,gpa);
		   printf("%s\n",gpa);
		   fflush(stdout);
		   
		   
		}
		if(strncmp(command.command,CHECK_NAME,10)==0){
		   command.my_msg_type=1;
		   if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
					fprintf(stderr, "msgsnd failed\n");
					exit(EXIT_FAILURE);
				
				}
		   data.my_msg_type=1;
		   printf("Please enter student number to get student \n");
		   scanf("%s",data.command);
		   
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		}
		if(strncmp(command.command,PROGRAM_STUDENTS,8)==0){
		   command.my_msg_type=1;
		   if (msgsnd(clientid, (void *)&command, MAX_TEXT, 0) == -1) {
					fprintf(stderr, "msgsnd failed\n");
					exit(EXIT_FAILURE);
				
				}
		   data.my_msg_type=1;
		   printf("Please enter a correct program to check for all students \n");
		   scanf("%s",data.command);
		   
		   if (msgsnd(clientid, (void *)&data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
		}
		
		
        
    }
    exit(EXIT_SUCCESS);
}
