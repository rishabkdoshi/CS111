#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void printArgs(int argc, char *argv[]){
  int i=0;

  printf("[INFO] Printing argv array of size %d \n", argc);

  printf("[INFO] ");
  for(i = 0; i <argc; i++){
    printf("%s ", argv[i]);
  }
  printf("\n");

  printf("[INFO] Done printing argv\n");
  printf("\n\n");

}

void printCurrentStateOfExternVariables(int iter, int opt){
  printf("[INFO] iteration=%d opt=%c optarg = %s optind=%d\n",iter,opt,optarg,optind);
}

void printAllOptionCharacters(int argc, char *argv[]){
  printf("[INFO] printing all option characters\n");
  int iter=0, opt;
  while ((opt = getopt(argc, argv, "nt:")) != -1) {
      printCurrentStateOfExternVariables(iter, opt);
      iter++;      
  }
  printf("[INFO] Done\n");
}

int
main(int argc, char *argv[])
{
  int flags, opt;
  int nsecs, tfnd;

  int iter=0;

  nsecs = 0;
  tfnd = 0;
  flags = 0;

  printArgs(argc, argv);  
  
  //printAllOptionCharacters(argc,argv); exit(1);

  printf("[INFO] State of extern variables before calling getopt\n");
  printCurrentStateOfExternVariables(-1, -1); //-1 is a dummy value


  printf("[INFO] Processing command line arguments using getopt\n");

  while ((opt = getopt(argc, argv, "nt:")) != -1) {
      printCurrentStateOfExternVariables(iter, opt);
      iter++;
      switch (opt) {
      case 'n':
          printf("[INFO] Found argument n, setting flags value to 1 \n");

          flags = 1;
          break;
      case 't':
          printf("[INFO] Found argument t, setting nsecs value(from optarg) to %d \n", atoi(optarg));

          nsecs = atoi(optarg);
          tfnd = 1;
          break;
      default: /* '?' */
          printf("[INFO] Found non-standard opt value %c, printing error message and exiting with failure code\n", opt);
          fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n", argv[0]);
          exit(EXIT_FAILURE);
      }
  }

  printf("[INFO] Done processing command line arguments using getopt \n");  
  printf("\n\n");
  printf("[INFO] Printing message from original program \n");

  printf("flags=%d; tfnd=%d; optind=%d\n", flags, tfnd, optind);
  printf("\n");
  printf("[INFO] Understanding the above message\n");
  printf("[INFO] \tFlags value is set to \n\t\t1 if option n is provided\n\t\t0 if option n is not provided\n");
  printf("[INFO] \ttfnd value is set to \n\t\t1 if option t is provided\n\t\t0 if option t is not provided\n");
  printf("[INFO] \toptind is the index of the next element to be processed in argv\n");


  if (optind >= argc) {
      printf("[ERROR] optind(%d) is greater than or equal to argc(%d), exiting with EXIT_FAILURE \n",optind,argc);
      fprintf(stderr, "Expected argument after options\n");
      exit(EXIT_FAILURE);
  }

  printf("[INFO] option n refers to name argument in below message\n");

  printf("name argument = %s\n", argv[optind]);

  /* Other code omitted */

  exit(EXIT_SUCCESS);
}
