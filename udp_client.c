#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512 
#define PORT 7777 

int main()
{
	struct sockaddr_in si_other;
	int s, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];

	if((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		fprintf(stderr, "Can't create socket");
		return -1;
	}

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);

	if (inet_aton(SERVER, &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		return -1;
	}

	while(1)
	{
		printf("Enter message: ");
		fgets(message, BUFLEN, stdin);

		if(strcmp(message, "exit\n") == 0)
			break;

		if(sendto(s, message, strlen(message)+1, 0, (struct sockaddr*)&si_other, slen) == -1)
		{
			fprintf(stderr, "Can't send the message");
			return -1;
		}

		memset(buf, '\0', BUFLEN);

		if(recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
		{
			fprintf(stderr, "Can't receive the message");
			return -1;
		}

	printf("%s", buf);
	}
	close(s);
	return 0;
}
