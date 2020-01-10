#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int YEAR_UNSET=-1, JUNIOR = 1, SENIOR = 2;

int
main(int argc, char **argv)
{
	int c;
	int option_index = 0;
	

	int year_flag = YEAR_UNSET;
	int uid;
	char name[20];//max name size allowed is 20

	while (1) {
		int option_index = 0;
		
        struct option long_options[] = {
			{"uid", required_argument, NULL, 'u'}, //what is the students UID?
			{"name", required_argument, 0, 'n'}, //what is the students name?
			{"senior", no_argument, &year_flag, SENIOR}, //is the student a senior
			{"junior", no_argument, &year_flag, JUNIOR}, //is the student a junior
			{NULL, 0, NULL, 0}//end of long options
		};

        c = getopt_long(argc, argv, "u:n:sj", long_options, &option_index);
            
		if (c == -1) break;

		switch (c) {
			case 0:
				printf("option %s\n", long_options[option_index].name);
				if (year_flag == SENIOR) printf("Student set as SENIOR");
				if (year_flag == JUNIOR) printf("Student set as JUNIOR");
                printf("\n");
                break;
			case 'u':
				printf("Recognized option %s. Setting UID to %d\n", long_options[option_index].name, atoi(optarg));                   	
				break;
			case 'n':
				printf("Recognized option %s. Setting name to %s\n", long_options[option_index].name, optarg);
				strncpy(name, optarg, 20);
				break;
			case 's':
				printf("Recognized option %s. Setting student as senior \n", long_options[option_index].name);
				printf("no_argument here,optarg value should be null - %s", optarg);
				break;
			case 'j':
				printf("Recognized option %s. Setting student as junior \n", long_options[option_index].name);
				printf("no_argument here,optarg value should be null - %s", optarg);
				break;
			
			//some option that was not in optstring
			case '?':
				break;

			default:
				printf("?? getopt returned character code 0%o ??\n", c);
		}
	}
	
	if (optind < argc) {
		printf("non-option ARGV-elements: \n");
		while (optind < argc)
			printf("%s ", argv[optind++]);
			printf("\n");
	}   

}
