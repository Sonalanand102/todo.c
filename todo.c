/*
 	TODOS - todo list in your terminal
	created by MarizMelo (c) 2012
	http://github/jmarizgit/todo.c
	version 1.0.1
*/

//LIBRARIES
#include <stdio.h>
#include <string.h>

//CONSTANTS
#define PATH "./.todo_file" 
#define TEMP "./.todo_tmp"

//TYPEDEFS
typedef enum { false, true } bool;

//FUNCTIONS
void init();
bool fileExists();
void showAll();
void showCompleted();
void showTodos();
void addTodo(char todo[]);
void completeTodo(char todo[]);
void deleteTodo(char todo[]);
void deleteTodos();
void showHelp();
void uninstallTodo();

//MAIN PROGRAM
int main ( int argc, char *argv[] ){
	bool exists = fileExists();
	//if user write an argument on command
	if(argv[1] && exists){
		//if argument is "-" show only completed todos
		if(strcmp(argv[1],"-")==0){
			showCompleted();
		//else argument is "+" show only active todos
		}else if(strcmp(argv[1],"+")==0){
			showTodos();
		//else if second argument is "add" and third argument exists, include new todo
		}else if(strcmp(argv[1],"add")==0  && argv[2]){
			addTodo(argv[2]);
		//else if second argument is "done" and third argument exists, move todo to completed list
		}else if(strcmp(argv[1],"done")==0 && argv[2]){
			completeTodo(argv[2]);
		//else if second argument is "del" and third argument exists, delete corresponding todo
		}else if(strcmp(argv[1],"del")==0 && argv[2]){
			deleteTodo(argv[2]);
		//else if second argument is "clean", remove all todos from list
		}else if(strcmp(argv[1],"clean")==0){
			deleteTodos();
		//else if second argument is "help", display list of available commands
		}else if(strcmp(argv[1],"help")==0){
			showHelp();
		}else if(strcmp(argv[1],"uninstall")==0){
			uninstallTodo();
        //else if second argument is "list", create list with selected name
		}else{
			showAll();
		}//if_else	
	}else if(exists){
		showAll();
	}else if(argv[1] && strcmp(argv[1],"init")==0){
		init();
	}else{
		showHelp();
	}//if_else
	return 0;
}//main

//CREATE TODO FILESYSTEM
void init(){
	FILE* file;
	if ( file = fopen(PATH, "a"))
    {
        fclose(file);
    }
    printf(".todo_file created!\n");
}//init()

//VERIFY IF FILE EXISTS
bool fileExists()
{
	FILE* file;
    if ( file = fopen(PATH, "r"))
    {
        fclose(file);
        return true;
    }else{
    	return false;
    }
}//fileExists()

//DISPLAY ALL TODOS
void showAll(){
	char buf[100];
	strcpy(buf,"cat -n ");
	strcat(buf, PATH);
	system(buf);
	return;
}//showAll()

//DISPLAY ONLY COMPLETED TODOS
void showCompleted(){
	char buf[100];
	strcpy(buf, "cat -n ");
	strcat(buf, PATH);
	strcat(buf, " | awk '/[0-9]\\t\\-/'");
	system(buf);
	return;
}//showCompleted()

//DISPLAY ONLY PENDING TODOS
void showTodos(){
	char buf[100];
        strcpy(buf, "cat -n ");
        strcat(buf, PATH);
        strcat(buf, " | awk '/[0-9]\\t\\+/'");
        system(buf);
	return;
}//showTodos()i

//ADD NEW TODO
void addTodo(char todo[]){
	char buf[400];
	strcpy(buf, "echo \"+ ");
	strcat(buf, todo);
	strcat(buf, "\" > ");
	strcat(buf, TEMP);
	strcat(buf, "; cat ");
	strcat(buf, PATH);
	strcat(buf, " >> ");
	strcat(buf, TEMP);
	strcat(buf, "; cat ");
	strcat(buf, TEMP);
	strcat(buf, " > ");
	strcat(buf, PATH);
	system(buf);
	return;
}//addTodo()

//MARK TODO AS COMPLETED
void completeTodo(char todo[]){
	char buf[200];
	strcpy(buf, "sed -n ");
	strcat(buf, todo);
	strcat(buf, "p ");
	strcat(buf, PATH);
	strcat(buf, " | sed 's/^\\+/\\-/' >> ");
	strcat(buf, PATH);
	strcat(buf, "; sed ");
	strcat(buf, todo);
	strcat(buf, "d ");
	strcat(buf, PATH);
	strcat(buf, " > ");
	strcat(buf, TEMP);
	strcat(buf, "; cat ");
	strcat(buf, TEMP);
	strcat(buf, " > ");
	strcat(buf, PATH);
	system(buf);
	return;	
}//completeTodo()

//REMOVE SPECIFIC TODO
void deleteTodo(char todo[]){
	char buf[200];
	strcpy(buf, "sed -e ");
	strcat(buf, todo);
	strcat(buf, "d ");
	strcat(buf, PATH);
	strcat(buf, " > ");
	strcat(buf, TEMP);
	strcat(buf, "; cat ");
	strcat(buf, TEMP);
	strcat(buf, " > ");
	strcat(buf, PATH);
	system(buf);
	return;	
}//deleteTodo()

//REMOVE ALL TODOS
void deleteTodos(){
	char buf[50];
	strcpy(buf, "> ");
	strcat(buf, PATH);
	system(buf);
	return;
}//deleteTodos()

//SHOW SYSTEM HELP
void showHelp(){
	printf("\n TODO - command line todo list MM (c) 2012\n");
	printf(" --------------------------------------------\n\n");
	printf(" Usage:\ttodo [option] <string>\n");
	printf("\n List of options\n\n");
	printf(" init\tstarts todo list on current folder\n");
	printf(" +\tdisplays only active todos\n");
	printf(" -\tdisplay only completed todos\n");
	printf(" add\tfollowed by QUOTED string (ex.:\"my new todo\") includes a new todo\n");
	printf(" done\tfollowed by todo's ID number, marks todo as completed\n");
	printf(" del\tfollowed by todo's ID number, remove todo from current list\n");
	printf(" clean\tdeletes all list of todos ***USE WITH MODERATION***\n");
	printf(" uninstall\tremove TODO application\n");
	printf(" help\tdisplay a quick command reference for the system\n\n");
	return;
}//showHelp()

//UNINSTALL TODO SYSTEM
void uninstallTodo(){
	system("/usr/local/todo/./uninstall.sh");
	return;
}//uninstallTodo()