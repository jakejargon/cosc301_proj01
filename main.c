
/*
 *
 Jacob Ellison
 COSC 301
 Proj_01
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */
            /* just equate stdin with our datafile */
            datafile = stdin;
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

	//Jacob's code starts here vvv

	printf("***List Contents Begin***\n");

	struct node *head = NULL;
	char buffer[1024];
	while (fgets(buffer, 1024, datafile) != NULL) {
		//get rid of all comments in the string
		int buff_len = strlen(buffer);
		int i = 0;
		for (; i < buff_len; i++) {
			if (buffer[i] == '#') {
				buffer[i] = '\0';
				break;
			}
		}

		const char * sep = " \n\t";
		char * tmp, * word;
		char * s = strdup(buffer);

		for (word = strtok_r (s, sep, &tmp); word != NULL; word = strtok_r(NULL, sep, &tmp)) {
			int word_len = strlen(word);
			i = 0;
			int addit = 0;
			int test;
			if (word[0] == '-') {
				i++;
			}
			for (; i < word_len; i++) {
				test = isdigit(word[i]);
				if (test == 0 || word[i] == '.') {
					addit = 0;
					break;
				}
				else {
					addit = 1;
				}
			}
			if (addit == 1) {
				printf("%s\n", word);
				int word_as_num = atoi(word);
				insert_sort(word_as_num, &head);
			}
		}
	}

	printf("***List Contents End***\n");
	list_clear(head);

	struct rusage ru;
	getrusage(RUSAGE_SELF, &ru);
	printf("System time: ");
	printf("%ld.%06ld\n", ru.ru_stime.tv_sec);
	printf("User time: ");
	printf("%ld.%06ld\n", ru.ru_utime.tv_usec);


    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */


    fclose(datafile);
    return 0;
}

