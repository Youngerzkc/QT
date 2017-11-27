#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include  <netinet/ip.h> 
#include <sqlite3.h>
#include <unistd.h>
#include <signal.h>

#include "protocal.h"

int main(void)
{
	int ret;
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		execl("/var/ftp/opt/code/project/Server/zhuce", "zhuce", NULL);
		exit(1);
	}
	printf("zhuce start ok\n");


	sleep(1);

	pid = fork();
	if (pid == 0) {
		execl("/var/ftp/opt/code/project/Server/denglu", "denglu", NULL);
		exit(1);
	}
	printf("denglu start ok\n");

	sleep(1);

	pid = fork();
	if (pid == 0) {
		execl("/var/ftp/opt/code/project/Server/jizhudizhi", "jizhudizhi", NULL);
		exit(1);
	}
	printf("jizhudizhi start ok\n");

	pid = fork();
	if (pid == 0) {
		execl("/var/ftp/opt/code/project/Server/tianjiahaoyou", "tianjiahaoyou", NULL);
		exit(1);
	}
	printf("tianjiahaoyou start ok\n");

	while (1) {
		errno = 0;
		ret = wait(NULL);
		if (ret < 0 && errno == ECHILD) {
			break;
		}
	}

	return 0;
}





