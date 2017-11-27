#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include  <netinet/ip.h> 
#include <sqlite3.h>
#include <signal.h>

#include "protocal.h"

int add_friend_handler(struct tianjiahaoyou_st *h)
{
	sqlite3 *db;
	char sql1[256];
	int ret;
	char *sql;
	sqlite3_stmt *stmt;

	ret = sqlite3_open("./nettalk.sqlite", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	// tianjiahaoyou	
	sql = "select * from dizhi where count=?";	
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}

	sqlite3_bind_text(stmt, 1, h->dst_chount, -1, NULL);	
	
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW) {
		goto step_error;
	}

	sqlite3_finalize(stmt);	

	//先判断你要添加的帐号是否已经是好友
	sprintf(sql1, "select * from %s where count='%s'", h->src_count, h->dst_chount);
	ret = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}
	
	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW) {
		//本来就是好友
		sqlite3_finalize(stmt);	
		sqlite3_close(db);	
		return 1;
	} 

	//把好友添加到用户好友表中
	//src_count 表名
	//dst_count
	sprintf(sql1, "insert into %s(count) values('%s')", h->src_count, h->dst_chount);
	ret = sqlite3_exec(db, sql1, NULL, NULL, NULL);
	if (ret != SQLITE_OK) {
		goto step_error;
	}

	sqlite3_finalize(stmt);	
	sqlite3_close(db);	

	return 0;
step_error:
	sqlite3_finalize(stmt);	
prepare_error:
	sqlite3_close(db);
	return -1;
}

int main(void)
{
	int sd;
	int ret;
	pid_t pid;
	struct tianjiahaoyou_st tianjiahaoyou;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(server_addr);
	char *sql;
	char *errmsg;
	struct sigaction action;
	sqlite3 *db;

	action.sa_handler = SIG_IGN;
	action.sa_flags = SA_NOCLDWAIT;
	//信号
	sigaction(SIGCHLD, &action, NULL);	

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(TIANJIAHAOYOU_SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sd, (void *)&server_addr, sizeof(struct sockaddr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, &tianjiahaoyou, sizeof(tianjiahaoyou), 0, (void *)&client_addr, &addr_len);
		if (ret < 0) {
			continue;
		}
		pid = fork();
		if (pid == 0) {
			//处理登录
			ret = add_friend_handler(&tianjiahaoyou);
			if (ret == 0) {
				tianjiahaoyou.status = TIANJIAHAOYOU_STATUS_OK;
				tianjiahaoyou.flag = TIANJIAHAOYOU_FLAG_NO;
			} else if (ret == 1) {
				tianjiahaoyou.status = TIANJIAHAOYOU_STATUS_OK;
				tianjiahaoyou.flag = TIANJIAHAOYOU_FLAG_OK;
			} else {
				tianjiahaoyou.status = TIANJIAHAOYOU_STATUS_ERROR;
			}
			sendto(sd, &tianjiahaoyou, sizeof(tianjiahaoyou), 0, (void *)&client_addr, sizeof(client_addr));
			exit(0);
		}
	}

	return 0;
}





