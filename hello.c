#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>


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
  
  char c;
  //printf("(getche example) please type a letter: ");
  while(1){
  int j_copy = j;
  	while(i){
  		printf("\n");
  		if(i == k){
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
    	alarm(0.5);
        c = getch();
        
    //}
	  
	  if(c == 'w' && k < w.ws_row){
	  	direction = 2;
	  	//printf("ok");
	  }else if(c == 's' && k > 1){
	  	direction = 4;
	  }else if(c == 'a'&& j > 0){
	  	direction = 3;
	  }else if(c == 'd'&& j < (w.ws_col - 1)){
	  	direction = 1;
	  }
	  
	  if(direction == 1){
	  	j++;
	  }else if(direction == 2){
	  	k++;
	  }else if(direction == 3){
	  	j--;
	  }else if(direction ==4){
	  	k--;
	  }

  }
  return 0;
} 
