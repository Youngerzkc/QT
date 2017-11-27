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

int register_handler(struct zhuce_st *z)
{
	sqlite3 *db;
	int ret;
	char *sql;
	sqlite3_stmt *stmt;
	char sql1[256];

	ret = sqlite3_open("./nettalk.sqlite", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	sql = "select * from zhuce where count=?";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}

	sqlite3_bind_text(stmt, 1, z->count, -1, NULL);
	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW) {
		goto step_error;
	}

	sqlite3_finalize(stmt);	

	//能够注册
	sql = "insert into zhuce(count, password, sex) values(?, ?, ?)";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}

	sqlite3_bind_text(stmt, 1, z->count, -1, NULL);
	sqlite3_bind_text(stmt, 2, z->passwd, -1, NULL);
	sqlite3_bind_int(stmt, 3, z->sex);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto step_error;
	}

	//创建一张和用户名字一样的表  用来存放该用户的好友
	sprintf(sql1, "create table if not exists %s(no integer primary key autoincrement not null, count)", z->count);
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
	struct zhuce_st zhuce;
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
	//打开数据库 sqlite3 ./nettalk.sqlite
	ret = sqlite3_open("./nettalk.sqlite", &db);	
	if (ret != SQLITE_OK) {
		perror("sqlite3_open");
		exit(1);
	}

	//创建注册表
	sql = "create table if not exists zhuce(no integer primary key autoincrement not null, count text not null, password text, sex integer)";	
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "%s\n", errmsg);
		exit(1);
	}
	//www.embsky.com  sqlite
	//ouremb --->sqlite3 mysql

	sql = "create table if not exists denglu(no integer primary key autoincrement not null, count text not null)";
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "%s\n", errmsg);
		exit(1);
	}

	//.quit
	sqlite3_close(db);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(ZHUCE_SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sd, (void *)&server_addr, sizeof(struct sockaddr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, &zhuce, sizeof(zhuce), 0, (void *)&client_addr, &addr_len);
		if (ret < 0) {
			continue;
		}
		pid = fork();
		if (pid == 0) {
			//处理注册
			ret = register_handler(&zhuce);
			if (ret == 0) {
				zhuce.status = ZHUCE_STATUS_OK;
			} else {
				zhuce.status = ZHUCE_STATUS_ERROR;
			}
			sendto(sd, &zhuce, sizeof(zhuce), 0, (void *)&client_addr, sizeof(struct sockaddr));
			exit(0);
		}
	}
	return 0;
}





