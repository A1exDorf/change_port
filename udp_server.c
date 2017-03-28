#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{

	int s, recv_len, slen;
	char buf[1024];
	struct sockaddr_in si_me, si_other;
	slen = sizeof(si_other);
	
	s = socket(AF_INET, SOCK_DGRAM, 0);

	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(7778);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(s, (struct sockaddr*)&si_me, sizeof(si_me));

	while(1)
	{
		fprintf(stderr,"Waiting for data...");

		recv_len = recvfrom(s, buf, 1024, 0, (struct sockaddr *)&si_other, &slen);
		fprintf(stderr,"Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

		sendto(s, buf, recv_len, 0, (struct sockaddr*)&si_other, sizeof(si_other));
	}

	return 0;
}
