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
#include <sys/wait.h> 
#include <time.h>

#define KEY 66666 //NOT A GOOOD IDEA
#define SEG_SIZE 4


void sighandler(int signo){
	if(SIGINT == signo){
		exit(0);
	}
}

void sighandler2(int signo){
	if(SIGINT == signo){
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


void pop_grid(int x, int y){

}

int main(void) {
	signal(SIGINT, sighandler2);

  struct winsize w;
  struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int i = w.ws_row;
  int k = 5;
  int j = 10;
  int direction = 1;
  
  int col = w.ws_col;
  int rol = w.ws_row;
  
  srand(time(NULL));
  
  int apple_x = rand() % (col - 2) + 2;
  int apple_y = rand() % (rol - 2) + 2;
  
  char * c;
  int shared_mem_id;
	//char * input;

	shared_mem_id = shmget(KEY, SEG_SIZE, IPC_CREAT | 0644);
  c = shmat(shared_mem_id, 0 , 0);
  
  int f;

/*difficulty selection */
  int level;
  system("clear");
  printf("Choose a difficulty:\n");
  printf("1: noob\n");
  printf("2: experienced\n");
  printf("3: debugger\n");
  printf("4: skilled\n");
  printf("5: master\n");
  printf("6: superman\n");
  printf("7: god\n");
  
  while(level < 49 || level > 55){
  	level = getch();
  	//printf("%d\n",level);
  }
  
  switch(level){
  	case 49: level = 1000000;
  	break;
  	case 50: level = 500000;
  	break;
  	case 51: level = 100000;
  	break;
  	case 52: level = 50000;
  	break;
  	case 53: level = 30000;
  	break;
  	case 54: level = 10000;
  	break;
  	case 55: level = 1000;
  
  }
  printf("\ngame ready in 3\n");
  sleep(1);
  printf("\ngame ready in 2\n");
  sleep(1);
  printf("\ngame ready in 1\n");
  sleep(1);
  
  int grid[rol][col];
  
  int rol_c = 0;
  int col_c = 0;
  
  //0 " "
  //1 "@"
  //2 "#"
  //3 "A"
  
  while(rol_c < rol){
  	
		while(col_c < col){
			grid[rol_c][col_c] = 0;
			col_c++;
			//printf("%d",grid[rol][col]);
		}
		//printf("\n");
		col_c = 0;
		rol_c ++;
  }
  
  //sleep(2);
  rol_c = 0;
  
  int length = 0;
  
  apple_x = rand() % (col - 2) + 2;
  apple_y = rand() % (rol - 2) + 2;
  
  int zero = 0;
  
  int dir_ts = 0;
  int dir_te[100000];
  
  int length_c = length;
  
  while(1){
  grid[apple_y][apple_x] = 3; 
  int j_copy = j;
  int apple_x_copy = apple_x;
  
  
  grid[k][j] = 1; 
  
  int lj = j;
  int lk = k;
  
  while(rol_c < rol){
		while(col_c < col){
			col_c++;
			switch(grid[rol_c][col_c]){
				case 0: printf(" "); break;
				case 1: printf("@"); break;
				case 2: printf("#"); break;
				case 3: printf("A"); break;
			}
		}
		printf("\n");
		col_c = 0;
		rol_c ++;
  }
  
  rol_c = 0;

    char string[10];

   // if( poll(&mypoll, 1, 500) )
    //{
    f = fork();
    if(!f){
    	signal(SIGINT,sighandler);
     	*c = getch();
     	exit(0);
    }
    
    //printf("%c",c);
    usleep(level);
    kill(f,SIGINT);
    //}
	  
	  if(*c == 'w' && direction != 2){
	  	direction = 4;
	  	//printf("ok");
	  }else if(*c == 's' && direction != 4){
	  	direction = 2;
	  }else if(*c == 'a' && direction != 1){
	  	direction = 3;
	  }else if(*c == 'd' && direction != 3){
	  	direction = 1;
	  }

//printf("length: %d | c: %d\n",length,length_c);
//sleep(2);

	grid[k][j] = 0;
	  if(direction == 1 && j < (col - 1)){
	  	if(grid[k][j + 1] == 3){
	  		length++;
	  		length_c = length;
	  		apple_x = rand() % (col - 2) + 2;
  			apple_y = rand() % (rol - 2) + 2;
	  		
	  		j++;
	  		lj = j;
  			lk = k;
	  		dir_ts++;
	  		dir_te[dir_ts] = 1; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		//dir_ts++;
	  		if(dir_ts >= 0){
		  		switch(dir_te[dir_ts]){
		  			    case 1: lj--; break;
	 	  			    case 2: lk--; break;
		  			    case 3: lj++; break;
		  			    case 4: lk++; break;
		  			}
		  			 grid[lk][lj] = 0;
		  	}	
		  		dir_ts = save;
		  		length_c = length;
	  		
	  		
	  	}else if(grid[k][j + 1] == 2){
	  		printf("you die by eating urself\n");
	  		break;
	  	}else{
	  		j++;
	  		lj = j;
  			lk = k;
	  		dir_ts++;
	  		dir_te[dir_ts] = 1; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		if(dir_ts >= 0){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  			} 
	  		
	  		dir_ts = save;
	  		length_c = length;
	  	} 
	  }else if(direction == 2 && k < (rol - 1)){
	 	if(grid[k + 1][j] == 3){
	  		length++;
	  		apple_x = rand() % (col - 2) + 2;
  			apple_y = rand() % (rol - 2) + 2;
	  		
	  		dir_ts++;
	  		k++;
	  		lj = j;
  			lk = k;
	  		dir_te[dir_ts] = 2; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		
	  		if(dir_ts >= 0){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  			}	 
	  		dir_ts = save;
	  		length_c = length;
	  		
	  		
	  	}else if(grid[k + 1][j] == 2){
	  		printf("you die by eating urself\n");
	  		break;
	  	}else{
	  	dir_ts++;
	  		k++;
	  		lj = j;
  			lk = k;
	  		printf("here1\n");
	  		dir_te[dir_ts] = 2; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		
	  		if(dir_ts >= 0){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  		} 
	  			 
	  		dir_ts = save;
	  		length_c = length;
	  	} 
	  }else if(direction == 3 && j > 1){
	  	if(grid[k][j - 1] == 3){
	  		length++;
	  		apple_x = rand() % (col - 2) + 2;
  			apple_y = rand() % (rol - 2) + 2;
	  		
	  		
	  		j--;
	  		lj = j;
  			lk = k;
	  		dir_ts++;
	  		dir_te[dir_ts] = 3; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		
	  		if(dir_ts >= 0){
	  		switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  		} 
	  			 
	  		dir_ts = save;
	  		length_c = length;
	  		
	  		
	  		//ile(length_c < length){
	  			
	  		//}
	  		
	  	}else if(grid[k][j - 1] == 2){
	  		printf("you die by eating urself\n");
	  		break;
	  	}else{
		  	j--;
		  	dir_ts++;
		  	lj = j;
  			lk = k;
		  	dir_te[dir_ts] = 3; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		
	  		if(dir_ts >= 0){
	  		switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  		}
	  			 
	  		dir_ts = save;
	  		length_c = length;
		  } 
	  }else if(direction ==4 && k > 1){
	  	if(grid[k - 1][j] == 3){
	  		length++;
	  		apple_x = rand() % (col - 2) + 2;
  			apple_y = rand() % (rol - 2) + 2;
	  		
	  		dir_ts++;
	  		k--;
	  		lj = j;
  			lk = k;
	  		dir_te[dir_ts] = 4; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		
	  		if(dir_ts >= 0){
	  		switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  		}
	  		dir_ts = save;
	  		length_c = length;
	  		
	  	}else if(grid[k - 1][j] == 2){
	  		printf("you die by eating urself\n");
	  		break;
	  	}else{
		  	k--;
		  	lj = j;
  			lk = k;
		  	dir_ts++;
		  	dir_te[dir_ts] = 4; 
	  		
	  		int save = dir_ts;
	  		
	  		
	  		while(length_c){
	  			switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 2;
	  			 dir_ts--;
	  			 length_c--;
	  		}
	  		
	  		
	  		if(dir_ts >= 0){
	  		switch(dir_te[dir_ts]){
	  			    case 1: lj--; break;
 	  			    case 2: lk--; break;
	  			    case 3: lj++; break;
	  			    case 4: lk++; break;
	  			}
	  			 grid[lk][lj] = 0;
	  			}
	  		dir_ts = save;
	  		length_c = length;
		}
	  }else{
	  	printf("you die by going outside of bound...\n");
	  	break;
	  }

	
		printf("dir: %d | ts: %d |\n",dir_te[dir_ts],dir_ts);

  }
  return 0;
} 
