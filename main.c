#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <err.h>

void args_process(int argc, char **argv);
void arg_process(char *arg);
void gotsig(int sig);
void init_args(void);
void prompt_run(void);

enum ui {
	NCURSES,
	TERM,
	GTK,
};

struct args {
	enum ui ui;			// One of NCURSES, TERM, GTK, maybe more
	bool allow_x;	// Whether we want to allow [Xx] as an option to execute programs
};

struct args args;

int main(int argc, char **argv) {
	init_args();
	args_process(argc, argv);
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
	if (args.allow_x == true) {
		fprintf(stdout, "\nYou may also use one of [Xx] to execute a program: ");
	}
	c=getchar();
	if (c=='Q' || c=='q' || c=='E' || c=='e') {
		fprintf(stdout, "Have a nice day!\n");
		exit(EXIT_SUCCESS);
	}
	else if (args.allow_x == true) {
		if (c == 'x' || c == 'X' ) {
			prompt_run();
		}
	}
	else {
		fprintf(stdout, "Going to sleep again, with anger to you that you woke me up!\n");
	}
	while ((c=getchar()) != '\n');
	return;
}


void args_process(int argc, char **argv) {
	int i;
	for ( i=1 ; i<argc ; i++){
		arg_process(argv[i]);
	}
	return;
}

void arg_process(char *arg) {
	if (strcmp(arg, "--allow-x") == 0) args.allow_x = true ;
	else if (strcmp(arg, "--help") == 0) err(0, "Not yet implemented, sorry!!") ;
	else errx(1, "Unexpected argument, see --help");
}

void init_args (void) {
	args.allow_x = false;
	return;
}

void prompt_run(void) {
	// TODO: make a prompt here, not use dmenu!! (X dependecy is bad!!)
	if ( fork() == 0 ) {
		execl("/bin/dmenu_run", "dmenu_run", NULL);
		perror("Exec");		// Should not get here, just in case
	}
	else {
#ifdef DEBUG
			perror("Fork");
#endif
	}
	return;
}
