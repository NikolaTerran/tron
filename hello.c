#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define KEY 66666 //NOT A GOOOD IDEA
#define SEG_SIZE 4


void sighandler(int signo){
	if(SIGINT == signo){
		exit(0);
	}
}

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      new.c_lflag |= ECHO; /* set echo mode */
  } else {
      new.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

/* Let's test it out */


int main(void) {

  struct winsize w;
  struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int i = w.ws_row;
  int k = 5;
  int j = 10;
  int direction = 1;
  
  int apple_x = 10;
  int apple_y = 10;
  
  char * c;
  int shared_mem_id;
	//char * input;

	shared_mem_id = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
  c = shmat(shared_mem_id, 0 , 0);
  
  int f;
  while(1){
  int j_copy = j;
  int apple_x_copy = apple_x;
  	while(i){
  		printf("\n");
  		if(i == k){
  			if(i == apple_y){
  				if(j_copy > apple_x_copy){
  					while(j_copy){
  						if(j_copy == apple_x_copy){
  							printf("A");
  						}else{
  							printf(" ");
  							apple_x_copy--;
  						}
  					}
  					printf("@");
  				}else if(j_copy < apple_x_copy){
  					while(apple_x_copy){
  						if(j_copy == apple_x_copy){
  							printf("@");
  						}else{
  							printf(" ");
  							apple_x_copy--;
  						}
  					}
  					printf("A");  		
  				}else{
  					while(j_copy){
  						printf(" ");
  						j_copy --;
  					}
  					printf("@");
  				}
  			}
  			while(j_copy){
  				printf(" ");
  				j_copy--;
  			}
  			printf("@");
  		}
  		
  		i--;
	  	}
	  i = w.ws_row;

    char string[10];

   // if( poll(&mypoll, 1, 500) )
    //{
   	f = fork();
    if(!f){
    	signal(SIGINT,sighandler);
     	*c = getch();
    }
    //printf("%c",c);
    usleep(100000);
    kill(f,SIGINT);
    //}
	  
	  if(*c == 'w'){
	  	direction = 2;
	  	//printf("ok");
	  }else if(*c == 's' ){
	  	direction = 4;
	  }else if(*c == 'a'){
	  	direction = 3;
	  }else if(*c == 'd'){
	  	direction = 1;
	  }
	  
	  if(direction == 1 && j < (w.ws_col - 1)){
	  	j++;
	  }else if(direction == 2 && k < w.ws_row){
	  	k++;
	  }else if(direction == 3 && j > 0){
	  	j--;
	  }else if(direction ==4 && k > 1){
	  	k--;
	  }

  }
  return 0;
} 
