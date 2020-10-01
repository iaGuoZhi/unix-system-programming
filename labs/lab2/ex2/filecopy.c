#include<stdlib.h>
#include<stdio.h> 
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc ,char *argv[]){
	if(argc!=3){
		fprintf(stderr, "Usage: %s <srcName> <dstName>", argv[0]);
		exit(EXIT_FAILURE);
	}

	char buffer[128];
	int nread=0, nwrite=0;
	int src_fd, dst_fd;
	src_fd = open(argv[1], O_RDONLY, 0);
	if(src_fd == -1){
		fprintf(stderr, "source file not exist\n");
		exit(EXIT_FAILURE);
	}
	dst_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
	if(dst_fd == -1){
		fprintf(stderr, "failed to create dst file\n");
		exit(EXIT_FAILURE);
	}


	do{
		nread=read(src_fd, buffer, 128);
		if(nread<=0)
			break;
		nwrite=write(dst_fd, buffer, nread);
		if(nwrite!=nread){
			fprintf(stderr, "cp Failed\n");
			exit(EXIT_FAILURE);
		}
	}while(1);

	exit(EXIT_SUCCESS);
}
