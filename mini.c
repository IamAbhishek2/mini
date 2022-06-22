#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

int main() {
	char cmd[100], buf[20]; 
	char *fileName, *newFileName, *token;
	int pipeBuf[2];
	int pid = 0, fda = 0, wstatus = 0;
		
	printf("> ");
	scanf("%s", cmd);
	
    token = strtok(cmd, "\t");
	
	while(strcmp(token, "exit")) {
		if(!strcmp(token, "mycat"))
			fileName = strtok(NULL, "\t");
		printf("File: %s", fileName);
		
		pid = fork();
		
		if(pid == 0) {
			printf("Token: %s", token);
			if(!strcmp(token, "mycat")) {
				printf("File: %s", fileName);
					
				
				fda = open(fileName, O_RDONLY);
				if(fda != -1) {
					while(read(fda, buf, 10)) {
						printf("%s", buf);
						write(pipeBuf[1], buf, strlen(buf));
					}
					write(pipeBuf[1], "-1", 3);
					close(fda);
				}
			}
			
			if(!strcmp(token, "mymv")) {
				fileName = strtok(NULL, " ");
				newFileName = strtok(NULL, " ");
				rename(fileName, newFileName);
			}
			
			
			exit(0);
		}
		
		while(read(pipeBuf[0], buf, 10) && strcmp(buf, "-1")) {
			printf("P:\n%s", buf);
		}
		
		waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
		
		printf("> ");
		token = strtok(NULL, " ");
		if(token == NULL) {
			scanf("%s", cmd);
			token = strtok(cmd, " ");
		}
	}	
	
	return 0;	
}
	
	
