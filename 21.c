#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		perror("Socket wasn't created");
		return -1;
	}
	
	int port = 7542, Mode = 0;
	switch (argc) {
		case 2: port = atoi(argv[1]);  
			break;
		case 3: port = atoi(argv[1]); 
			if (strcmp(argv[2], "-c") == 0)
				Mode = 1;
			break;
		case 5: port = atoi(argv[1]); 
			if (strcmp(argv[2], "-f") == 0)
				Mode = 2;
			break;
	}

	struct sockaddr_in local_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = htonl(INADDR_ANY),
	};
	if (bind(sock, (const struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
		perror("Name to socket wasn't binded");
		close(sock);
		return 1;
	}
	while(1) {
		struct sockaddr_in remote_addr;
		socklen_t remote_addr_size = sizeof(remote_addr);
		char data[2048];
		ssize_t data_len = recvfrom(sock, data, sizeof(data), 0,
				(struct sockaddr *)&remote_addr, 
				&remote_addr_size);
		if (data_len < 0) {
			perror("Message wasn't received");
			break;
		}
		char remote_addr_str [INET_ADDRSTRLEN];
		inet_ntop(remote_addr.sin_family, 
				&remote_addr.sin_addr, 
				remote_addr_str, 
				sizeof(remote_addr_str));
		printf("received packet from %s: %d, content: '%*s'\n", 
				remote_addr_str, ntohs(remote_addr.sin_port), 
				(int)data_len, data);
		if (Mode < 1) {
			char reply[1024];
			snprintf(reply, sizeof(reply), 
				"Got the request of %zd bytes!\n", data_len);
			if (sendto(sock, reply, strlen(reply), 0,
					(const struct sockaddr *)&remote_addr, 
					sizeof(remote_addr)) == -1)
			perror ("Request wasn't sent");
		}

		if (Mode == 2) {
			int dest_port = atoi(argv[4]);
			in_addr_t caddr = inet_addr(argv[3]);
			struct sockaddr_in dest_addr = {
				.sin_family = AF_INET,
				.sin_port = htons(dest_port),
				.sin_addr.s_addr = caddr,
			};
			if (sendto(sock, data, strlen(data), 0,
					(const struct sockaddr *)&dest_addr, 
					sizeof(dest_addr)) == -1)
				perror ("Request wasn't resent");
			else
				printf("Request was resent\n");
		}	
	}
	close(sock);
	return 0;
}
