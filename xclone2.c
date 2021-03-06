#define _GNU_SOURCE
#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <limits.h>
#include <linux/sched.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <sys/stat.h>
#include "params.h"

// #define CLONE_PROT_MV 0x000000ff1
// #define CLONE_PROT_ZIP 0x000000ff2
// #define CLONE_PROT_ENC 0x000000ff4


#ifndef __NR_xclone2
#error xclone2 system call not defined
#endif

#ifndef __NR_xclone2async
#error xclone2async system call not defined
#endif

static int child_clone(void *arg)
{

	int rc,size=0;
     struct Param* param;
     struct stat st;
     param = (struct Param*)arg;
    stat(param->fname, &st);
    size = st.st_size;

    printf("File %s size %d \n",param->fname,size);

    if(size>4096)
    {
            printf("async sys call called\n");
        rc = syscall(__NR_xclone2async, (void *) arg);

    }
    else
    {
     printf("Filename in clone %s\n",param->fname);
	printf("Child Process\n");
	rc = syscall(__NR_xclone2, (void *) arg);

    }
	// int rc;
     // struct Param* param;
	// 
     // param = (struct Param*)arg;
     // printf("Filename in clone %s\n",param->fname);
	// printf("Child Process\n");
	// 
     // rc = syscall(__NR_xclone2, (void *)arg);
	if (rc >= 0) {
		if (rc == 0)
			printf("syscall returned %d\n", rc);
		else
			printf("number of identical bytes %d\n", rc);
	} else
		printf("syscall returned %d (errno=%d)\n", rc, errno);

     return rc;
}

int main(int argc, char * const argv[]) {
	int rc = 0;
	int c;
     int pid;
     char* stack;

     struct Param *params;

     params = (struct Param*)malloc(sizeof(struct Param));
     if(params == NULL){
          printf("Insufficient memory\n");
          return -ENOMEM;
     }
     stack = (char*)malloc(sizeof(char)*(1024*1024));
     if(stack == NULL){
          printf("Insufficient memory\n");
          return -ENOMEM;
     }

	params->b1 = 0x00;
     params->fname = (char*)malloc(sizeof(char)*PATH_MAX);
     if(params->fname == NULL){
          printf("Insufficient memory\n");
          return -ENOMEM;
     }

	printf("Hello world!!!\n");

	while ((c = getopt(argc, argv, "mcep")) != -1) {
		switch (c) {
		case 'm':
			params->b1 |= 0x000000ff1;
			break;

		case 'c':
			params->b1 |= 0x000000ff2;
			break;

		case 'e':
			params->b1 |= 0x000000ff4;
			break;

		case 'p':
			params->b1 = 0x000000fff;
			printf("I am in p\n");
			break;

		case '?':
			if (optopt == 'm' || optopt == 'c' || optopt == 'e') {
				perror("xclone2: option requires an argument \n");
				perror(
						"Usage: ./xclone2 [-mce] file1.txt");
			} else {
				perror("xclone2: invalid option \n");
				perror("Usage: xdedup [-npd] outfile.txt file1.txt file2.txt\n");
			}
			return 1;
		default:
			abort();

		}
	}

     if(argv[optind] == NULL){
		printf("Insufficient arguments\n");
		return -1;
	}
	else{
		strcpy(params->fname,argv[optind++]);
	}

     // printf("The filename is %s\n",params->fname);

	printf("Hello world!!!!!!\n");

	printf("CLone flags total is %d\n",params->b1);


     if(params->b1 == 0x000000ff1){
		printf("i am in move\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff1, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == 0x000000ff2){
		printf("i am in compress\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff2, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == 0x000000ff4){
		printf("i am in encrypt\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff4, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == (0x000000ff1 | 0x000000ff4)){
		printf("i am in move and encrypt\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff1 | 0x000000ff4, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == (0x000000ff1 | 0x000000ff2)){
		printf("i am in move and compress\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff1 | 0x000000ff2, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == (0x000000ff4 | 0x000000ff2)){
		printf("i am in enc and compress\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff4 | 0x000000ff2, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == (0x000000ff1 | 0x000000ff4 | 0x000000ff2)){
		printf("i am in move comp and enc\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000ff1 | 0x000000ff4 | 0x000000ff2, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }

	else if(params->b1 == (0x000000fff)){
		printf("i am in complete purge\n");
          pid = clone(child_clone, stack+(1024*1024), 0x000000fff, (void*)params);
     	if (pid == -1) {
     		printf("Clonning failed\n");
     		return -1;
	     }
     }


     exit(rc);
     return 0;

}
