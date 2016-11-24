#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "make_log.h"
//demaxiya
int main(int argc,char*argv[])
{
	if(argc<2)
	{
		perror("参数不够");
		exit(1);
	}
	pid_t pid;
	int fd[2],ret;
    char buf[1024] = {0};
	
	ret = pipe(fd);
	if(ret == -1)
	{
		perror("pipe");
		exit(1);
	}

	pid = fork();

	if(pid == 0)
	{
		sleep(1);
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		//子进程;
		execl("/usr/bin/fdfs_upload_file","/usr/bin/fdfs_upload_file","./conf/client.conf",argv[1],NULL);	
		printf("execl error");	
	}
	else
	{
		//父进程；
		close(fd[1]);
		ret = read(fd[0],buf,1024);
		if(ret <0)
		{
			perror("read");
			exit(1);
		}
		LOG("file","file2","fileid = %s",buf);


	}

	return 0 ;
}
