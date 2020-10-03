#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<limits.h>

static int ctrl_c_time=0;
static int MAXSTOPS=0;

int convert(char *s){
	char *p;
	int num;
	errno=0;
	
	long conv = strtol(s, &p, 10);

	if(errno != 0 || *p != '\0' || conv > INT_MAX){
		exit(0);
	}
	else{
		num= conv;
	}
	return num;
}

static size_t sio_strlen(char s[]){
	int len=0;
	while(s[len]!='\0'){
		++len;
	}
	return len;
}

static void sio_reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static  void sio_ltoa(long v, char s[], int b)
{
    int c, i = 0;

    do {
        s[i++] = ((c = (v % b)) < 10)  ?  c + '0' : c - 10 + 'a';
    } while ((v /= b) > 0);
    s[i] = '\0';
    sio_reverse(s);
}

//printf 不是异步信号安全的函数,信号处理程序中产生输出唯一安全的方法是使用write
static ssize_t sio_puts(char s[]){
	return write(STDOUT_FILENO, s, sio_strlen(s));
}

static ssize_t sio_putl(long v){
	char s[128];
	sio_ltoa(v, s, 10);
	return sio_puts(s);
}

// secure signal handler
void my_sigint_handler(int sig){
	sio_puts("You've pressed Ctrl-C ");
	sio_putl(++ctrl_c_time);
	sio_puts(" times.  Aren't you getting the message that I'm invulnerable?\n");
}

void my_sigusr1_handler(int sig){
	sio_puts("You've send kill signal to me, Luckily, I forget you\n");
}	

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Usage: ./prog $(MAXSTOPS)");
		exit(0);
	}

	MAXSTOPS=convert(argv[1]);

	if(signal(SIGINT, my_sigint_handler)==SIG_ERR)
		exit(0);
	if(signal(SIGUSR1, my_sigusr1_handler)==SIG_ERR)
		exit(0);

	while(1){
		char buf[200];
                memset(buf, 0,200);

		read(0,buf, 200);
		//printf("%s",buf);
	        if(strcmp(buf,"kill\n")==0){
			printf("equal");
			kill(getpid(), SIGUSR1);	
		}
		if(ctrl_c_time == MAXSTOPS){
			signal(SIGINT, SIG_DFL);
		}
		
	}
}

