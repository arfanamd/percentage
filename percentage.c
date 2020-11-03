#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define UNI 3
#define INTERUPT 1
#define NO_ERROR 0

enum Mode {NORMI, DIFFE, FRACT};

/* only numbers are allowed */
int onlyNUM(const char *input) {
	int length = strlen(input);
	for (int i = 0; i < length; i++) {
		if (!isdigit(input[i])) return INTERUPT;
	}
	return NO_ERROR;
}
void diffe_m(const unsigned int *const input_data) {
	unsigned int compare = input_data[0];
	unsigned int to      = input_data[1];
	/* value of compare must always be greater than to */
	if (to > compare) {
		unsigned int temp = compare;
		compare = to; to  = temp;
	}
	float difference = compare - to;
	float average    = ((float)compare + (float)to) / 2;
	float percentage = (difference / average) * 100;
	fprintf(stdout, "%2.2f(%%)\n", percentage);
}
void fract_m(const unsigned int *const input_data) {
	unsigned int compare = input_data[0];
	unsigned int to      = input_data[1];
	/* value of compare must always be greater than to */
	if (to > compare) {
		unsigned int temp = compare;
		compare = to; to  = temp;
	}
	float percentage = ((float)compare / (float)to) * 100;
	fprintf(stdout, "%2.2f(%%)\n", percentage);
}
void normi_m(const unsigned int *const input_data) {
	unsigned int compare = input_data[0];
	unsigned int to      = input_data[1];
	/* value of compare must always be greater than to */
	if (to > compare) {
		unsigned int temp = compare;
		compare = to; to  = temp;
	}
	float percentage = (float)to / ((float)compare / 100);
	fprintf(stdout, "%2.2f(%%)\n", percentage);
}
/* function pointer */
void (*data_proc[])(const unsigned int *const) = {normi_m, diffe_m, fract_m};

int main(int argc, const char *argv[]) {
	/* arguments must exceeded */
	if (argc < UNI) {
		fprintf(stderr, "%s%s\n", argv[0], ": need more data.");
		fprintf(stderr, "%s%s%s\n", "usage: ", argv[0], " [-ndf] <compare> <to>");
		return INTERUPT;
	}
	int Mod, EX;
	if (argc == 3) {
		Mod = 0;
		EX  = 0; }
	else {
		switch(argv[1][1]) {
			case 'd':
			case 'D':
				Mod = DIFFE; break;
			case 'f':
			case 'F':
				Mod = FRACT; break;
			case 'n':
			case 'N':
				Mod = NORMI; break;
			default:
				fprintf(stderr, "%s%s\n", "unknown option ", argv[1]); return INTERUPT;
		}
		EX  = 1;
	}
	/* data container */
	unsigned int *input_data = malloc(UNI * sizeof(unsigned int));
	if (!input_data) {
		fprintf(stderr, "%s%s\n", argv[0], ": memory error, something is wrong.");
		return INTERUPT;
	}
	/* validate and assign value to container */
	for (int i = (1 + EX); i < (UNI + EX); i++) {
		if (onlyNUM(argv[i]) == 0) {
			input_data[i - (1 + EX)] = atoi(argv[i]); }
		else {
			fprintf(stderr, "%s%s\n", argv[0], ": wrong value. Try again!");
			goto SUSPEND;
		}
	}
	/* processing data */
	(*data_proc[Mod])(input_data);
SUSPEND:
	if (input_data) free(input_data);
	return NO_ERROR;
}
