#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define DEBUG

void gotsig(int sig);

int main(void) {
	fprintf(stdout, "Waiting for SIGINT (^C), sleeping until then.\n");
	signal(SIGINT, &gotsig);
	start:
		pause();
		goto start;
	return EXIT_SUCCESS;
}

void gotsig(int sig) {
	fprintf(stdout, "Signal received\n");
	char c;
	fprintf(stdout, "Enter one of [QqEe] to exit or anything else to go sleeping again: ");
	c=getchar();
	if (c=='Q' || c=='q' || c=='E' || c=='e') {
		fprintf(stdout, "Have a nice day!\n");
		exit(EXIT_SUCCESS);
	} else {
		fprintf(stdout, "Going to sleep again, with anger to you that you woke me up!\n");
	}
	while ((c=getchar()) != '\n');
	return;
}
