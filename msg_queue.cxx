/*
 * msg_queue.cxx
 * 
 * Copyright 2016 olegartys <olegartys@olegartys-HP-Pavilion-15-Notebook-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
	long mtype;
	char mtext[80];
};

int main(int argc, char **argv)
{
	key_t key = ftok("/tmp/msg.temp", 0);
	
	// Create queue
	int msqid = msgget(key, IPC_CREAT | 0666);
	if (msqid < 0) {
		perror("msqid");
		exit(errno);
	}
	
	// recieve message
	message msg;
	int res = msgrcv(msqid, &msg, sizeof(char)*80, 0, 0);
	if (res < 0) {
		perror("msgrcv");
		exit(errno);
	}
	
	// print message
	std::ofstream f("message.txt");
	f << msg.mtext << std::endl;
	f.close();
	
	// close queue
	res = msgctl(msqid, IPC_RMID, NULL);
	if (res < 0) {
		perror("msgctl");
		exit(errno);
	}
	
	return 0;
}

