#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sysmacros.h>


int main(int argc, char *argv[])
{
	struct stat sb;
	if(argc!=2){
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if(stat(argv[1], &sb)==-1){
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	
	printf("  文件:%s\n", argv[1]);
	printf("  大小:%ld", sb.st_size);
	printf("  块:%ld", sb.st_blocks);
	printf("  IO块:%ld", sb.st_blksize);
	//printf(sb.st_mode);
        switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

	printf("  设备: [%lx,%lx]", (long) major(sb.st_dev), (long) minor(sb.st_dev));
	printf("  Inode: %ld", (long)sb.st_ino);
	printf("  硬连接: %ld\n", (long) sb.st_nlink);

	printf("  权限: %lo (octal)\n", (unsigned long) sb.st_mode);
	printf("  UID: %ld  GID: %ld\n", (long)sb.st_uid, (long)sb.st_gid);

	exit(EXIT_SUCCESS);
}
