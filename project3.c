#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void  main()
{
	int children, work;
	int k;
	FILE *fptr; 
	
	fptr = fopen("common.txt", "r+");
	
	//Getting all the numbers from common text file into array for easier manipulation of files
	int num;
	int counter = 0;

	//getting number of children
	printf("Enter the number of children:");
	scanf("%d", &children);
	//printf("%d",children); 
	
	//getting number of work per child
	printf("Enter the number of work per process: ");
	scanf("%d", &work);
	//printf("%d", work);
	
	
	size_t pos = ftell(fptr); //saving initial position in file
	fseek(fptr, pos, SEEK_END); //goign to the end of the file 
	size_t length = ftell(fptr); //getting full length of the list in the file
	fseek(fptr, pos, SEEK_SET); //setting file pointer 
	
	
	for(int i = 0; i < children; i++){
		
		if(fork() == 0){ //entering child process 
			
			printf("Executing from child %d with pid %d and parent: %d\n ", i, getpid(), getppid());
			
			char str[100]; 
			fgets(str, length, fptr);//we are using fgets to display contents of file after changes are made
			//printf("%s\n",str);
			fseek(fptr, pos, SEEK_SET);//reseting file pointer to first byte
			
			int first = 0;
			fscanf(fptr,"%d", &first); //getting the first character
			first++;
			fseek(fptr, pos, SEEK_SET);//reseting file pointer to first byte
			
			for(int j = 0; j < work; j++){ //work will be done as many times as the user specifies
				printf("Work %d for child %d\n", j, i);
				fputc(first, fptr);		
			}
			//printf("child id #%d running from %d\n", getpid(), getppid());
			exit(0);
		}
		fseek(fptr, pos, SEEK_SET);//reseting file pointer to first byte
	}
	wait(NULL);
	
	fscanf(fptr, "%d", &k); 
	
	fclose(fptr);		
}

void read_ints (const char* file_name)
{
  FILE* file = fopen (file_name, "r");
  int i = 0;

  fscanf (file, "%d", &i);    
  while (!feof (file))
    {  
      printf ("%d ", i);
      fscanf (file, "%d", &i);      
    }
  fclose (file);        
}
