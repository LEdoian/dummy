#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define DEBUG

bool finish;

void gotsig(int sig);

int main(void) {
#ifdef DEBUG
	long long unsigned int i = 0;
#endif
	fprintf(stdout, "Waiting for SIGINT (^C), sleeping until then.\n");
	signal(SIGINT, &gotsig);
	finish = false;
	while (!finish) {
#ifdef DEBUG
		fprintf(stderr, "DEBUG: Iteration: %llu\n", i++);
#endif
		pause();
	}
	return EXIT_SUCCESS;
}

void gotsig(int sig) {
	fprintf(stdout, "Signal received\n");
	
	char c;
	fprintf(stdout, "Enter one of [QqEe] to exit or anything else to go sleeping again: ");
	c=getchar();
	if (c=='Q' || c=='q' || c=='E' || c=='e') {
		finish = true;
		fprintf(stdout, "Have a nice day!\n");
	} else {
		fprintf(stdout, "Going to sleep again, with anger to you that you woke me up!\n");
	}
	while ((c=getchar()) != '\n');
	return;
}
