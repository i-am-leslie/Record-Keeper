#ifndef STRUCT_H
#define STRUCT_H
#define CREATE  "create"
#define END "end"
#define AVERAGE "average"
#define DELETE "delete"
#define CHECK_GPA "check_gpa"
#define CHECK_NAME "check_name"
#define PROGRAM_STUDENTS "students"

struct my_msg_st {
	long int my_msg_type;
	char name[BUFSIZ];
    	char program_name[BUFSIZ];
    	char student_number[BUFSIZ];
    	char GPA[BUFSIZ];

};
struct command_word{
	long int my_msg_type;
	char command[12];
	
}; 

    
int createRecordKepper(){
	
	int msgid1;//holds record kepper message id
    
     	msgid1 = msgget((key_t)4313, 0666 | IPC_CREAT);// creating user Record kepper message queue
     	if (msgid1 == -1) {//errror checking for msgid1
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	return msgid1;

}
int createuserid(){

	int msgid; //holds user message id
	
     	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);// creating user message queue

    	if (msgid == -1) {//errror checking for msgid
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	return msgid;
	}
#endif
