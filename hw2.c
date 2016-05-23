#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_LINE 80

//create a double linked list of commands.
struct historylist {
    char *command;
    struct historylist *next;
    struct historylist *previous;
};

struct historylist *currnode = NULL;
struct historylist *head;

void getLatestCommands();
void getRecent();
void add(char *);
struct historylist *create(char *);

int value = 1;

int main(int argc, char*argv[]) {
    char *args[MAX_LINE]; //size of char* values.
    char arr[MAX_LINE/2+1];
    int should_not_run = 1; //value of while loop run.
    char *token; //split string token.
    int index;
    int status;
    head = (struct historylist*) malloc (sizeof (struct historylist));
    //int position = 0; //position in the string array.
    //char *history[1000];
    //char *tokenvalue;
    //int historyvalue = 0;
    //int exitvalue = 0;
    //int historyindex = 0;
    
    //create the pipe.
    //int my_pipe[2];
    //pipe(my_pipe);
    
    pid_t pid; //pid of the fork.
    //size_t size; //size of the input by the user.

    while(should_not_run) { //user types in "exit" which causes the while loop to terminate.
        
        index = 0;
        printf("osh>");
        fflush(stdout);
        
        fgets(arr, sizeof arr, stdin);
        
        arr[strlen(arr)-1] = '\0';
         
        //printf("%s", line);
        
        /* get the first token */
        token = strtok(arr, " ");
    
        //printf("First Token: %s\n", token);
        args[0] = token;
        
        add(args[0]); 
        
        //if(strstr(args[0], "!!") != 0) {
        //}
        //position++;
        //}
        
       //head = args[position];
        
        //get the 10 latest commands if history has been typed.
        if(strcmp(arr, "history") == 0) {
            //add(args[position]);
            getLatestCommands();   
        }
    
        //get the latest command if "!!"" has been typed.
        if(strcmp(arr, "!!") == 0) {
            //add(args[position]);
            getRecent();
        }
        
        //exit the program if the user has typed "exit".
        if(strcmp(arr, "exit") == 0) {
            should_not_run = 0;
        }
        
        /* walk through other tokens */
        while(token != NULL) 
        {
            
            args[index] = strdup(token);
            //printf("args[%d] = %s\n", index, args[index]);
            //head->next = args[index];
            
            index++;
            token = strtok(NULL, " ");
            //printf("Token: %s\n", token);
            
            //if(strstr(token, "-") == 0) {
            //    history[historyindex] = strcat(history[historyindex], tokenvalue);
        //    }
            
         //   args[position] = token;
         //   position++;
        }
        
        //fork a child process.
        pid = fork();
        //a failed fork.
        
        if(pid < 0) {
            printf("The fork is not working. Use a spoon instead.\n");
        }
        //child process.
        else if(pid == 0) {
            //printf("This is the child process.\n");
            
            execvp(args[0], args);
            
            return 0;
        }
        
        //a positive pid value - the parent process.
        else {
            pid = wait(&status);
            //printf("This is the parent process.\n");
            //waitpid(pid, &status, 0);
            
            //if(!strcmp(arr, "exit")) {
            //    should_not_run = 0;
            //}
            
            //return pid;
            
            //if(token != '&') {
            
        //    }
            
        }

    }
    
    return (0);
}

//get the ten latest command calls.
void getLatestCommands() {
    int i;
    struct historylist *temp = NULL;
    temp = currnode;
    
    //nothing within the list has been found.
    if(temp==NULL) {
        printf("No commands in the list.");
    }
    
    //keep iterating through the list while there are no null elements to be found.
    while(temp->next != NULL) {
        value++;
    }
    
    printf("Value: %d", value);
    
    //terminate program if history is called with fewer than 10 commands entered.
    if(value<10) {
        printf("You must have at least 10 commands in order to view the history\n");
        exit(1);
    }
    
    //print out each value of the list and its resulting command.
    for(i = value; i>=value-9; i--) {
        printf("%d %s\n", i, temp->command);
        temp = temp->previous;
    }
}

//get the most recent command call.
void getRecent() {
    struct historylist *temp = NULL;
    temp = currnode;
    
    //nothing to be found in the list.
    if(temp==NULL) {
        printf("No commands in the list.");
    }
    
    //keep iterating through the list while more elements exist.
    while(temp->next != NULL) {
        value++;
    }
    
    //print out specific linked list value and command.
    printf("%d %s", value, temp->command);
    printf("\n");
}

//add a command to the list.
void add(char* commandprompt) {
    struct historylist *pnode = NULL;
    pnode = create(commandprompt);
    
    //first element in the list is null, add element in the first position.
    if(head==NULL) {
        head = pnode;
    }
    
    //next element in the list is null.
    if(head->next == NULL) {
        head->next = pnode;
        pnode->previous = head;
        currnode = pnode;
    }
    
    //add element in next available position.
    else {
        currnode->next = pnode;
        pnode->previous = currnode;
        currnode = currnode->next;
    }
}

//create a new entry into the historylist.
struct historylist *create(char* commandprompt) {
    struct historylist *newnode = (struct historylist*) malloc (sizeof (struct historylist));
    newnode->command = commandprompt;
    newnode->next = NULL;
    newnode->previous = NULL;
    return newnode;
}
