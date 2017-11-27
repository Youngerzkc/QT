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

int addr_handler(int sd, struct jizhudizhi_st *j, struct sockaddr_in *addr)
{
	sqlite3 *db;
	int ret;
	char sql1[256];
	char *sql;
	sqlite3_stmt *stmt;
	char *count;
	struct liaotian_st haoyou;

	ret = sqlite3_open("./nettalk.sqlite", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}
	// jizhudizhi	
	sql = "select * from dizhi where count=?";	
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;
	}

	sqlite3_bind_text(stmt, 1, j->count, -1, NULL);	
	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW) {
		//update
		sqlite3_finalize(stmt);	
		sql = "update dizhi set addr=? where count=?";
		ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (ret != SQLITE_OK) {
			goto prepare_error;	
		}
		sqlite3_bind_blob(stmt, 1, addr, sizeof(*addr), NULL);
		sqlite3_bind_text(stmt, 2, j->count, -1, NULL);
		ret = sqlite3_step(stmt);	
		if (ret != SQLITE_DONE) {
			goto step_error;
		}
	} else {
		//insert into
		sqlite3_finalize(stmt);	
		sql = "insert into dizhi(count, addr) values(?, ?)";
		ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (ret != SQLITE_OK) {
			goto prepare_error;	
		}
		sqlite3_bind_text(stmt, 1, j->count, -1, NULL);
		sqlite3_bind_blob(stmt, 2, addr, sizeof(*addr), NULL);
		ret = sqlite3_step(stmt);	
		if (ret != SQLITE_DONE) {
			goto step_error;
		}
	}

	sqlite3_finalize(stmt);	
	
	//查询该用户的好友，然后一个一个发送给用户
	sprintf(sql1, "select * from %s", j->count);
	ret = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto prepare_error;	
	}
	
	while (1) {
		// no count
		ret = sqlite3_step(stmt);	
		if (ret != SQLITE_ROW) {
			goto step_error;
		}
		count = (void *)sqlite3_column_text(stmt, 1);	
		sprintf(haoyou.dst_count, "%s", count);
		haoyou.status = HAOYOU_ITEM;
		sendto(sd, &haoyou, sizeof(haoyou), 0, (void *)addr, sizeof(*addr));
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
	struct jizhudizhi_st jizhudizhi;
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
	//ourmeb  www.embsky.com
	ret = sqlite3_open("./nettalk.sqlite", &db);	
	if (ret != SQLITE_OK) {
		perror("sqlite3_open");
		exit(1);
	}

	//www.embsky.com  sqlite
	//ouremb --->sqlite3 mysql
	
	sql = "create table if not exists dizhi(no integer primary key autoincrement not null, count text not null, addr blob)";
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
	server_addr.sin_port = htons(JIZHUDIZHI_SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sd, (void *)&server_addr, sizeof(struct sockaddr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, &jizhudizhi, sizeof(jizhudizhi), 0, (void *)&client_addr, &addr_len);
		if (ret < 0) {
			continue;
		}
		pid = fork();
		if (pid == 0) {
			//处理登录
			if (addr_handler(sd, &jizhudizhi, &client_addr) < 0) {
				fprintf(stderr, "jizhudizhi shibai\n");
			};
		
			exit(0);
		}
	}

	return 0;
}





