#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
       
    char str[20];
    int i;
    char *arr1[100];
    int items = 0;
   

    //initial message to user for input
  
    do {
    
    printf("\n>");
    fgets(str, 20, stdin);
    str[strcspn(str,"\n")] = 0;
        //else {
        printf("\nThank you, %s\n", str);

        //tokenize string and add to array
        char * pch;
        pch = strtok(str, " \n");

       /*
        size_t ln = strlen(str) - 1;
        while (*str && str[ln] == '\n'){
            str[ln] = '\0';
        }
        */

       

        while (pch != NULL) {
        arr1[items] = pch;
        items++;
        pch = strtok(NULL, " ,.-");
        }
        
        //reset array
        arr1[items] = NULL;
        
        //if last item in array is &, needs to be deleted
        if (strcmp (arr1[items-1], "&") == 0) {
        arr1[items - 1] = NULL;
        }

        //reset items for next input
        items = 0;


        printf("hello world (pid: %d)\n", (int)getpid());

        //fork
        int rc = fork();
    

        //fork failed, exit
        if (rc < 0) 
        {
            fprintf(stderr, "fork failed\n");  
            exit(0);
        }
        
        //child (new process)
        else if (rc == 0) 
        {
            printf("Child (pid: %d)\n", (int) getpid());
            execvp(arr1[0], arr1); 
        }

        //parent goes down this path 
        else 
        {
            //wait for any child to complete
            int wc = wait(NULL); 
            printf("Parent (pid: %d)\n", (int)getpid()); 
        }
       }//end do

while (strcmp(str, "exit") != 0);
    //}

    printf("Thanks for running the program!\n");
   //return 0;

}

char * stripSlashN( char * tok )
{
    int i;
    for (i = 0;;i++)
    {
        if (tok[i] == '\n')
        {
            tok[i] = '\0';
            break;
        }
    }
    return tok;
}
