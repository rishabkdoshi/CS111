extended from [src](https://github.com/raoulmillais/linux-system-programming/blob/master/src/poll-example.c)
 
```c

#include <stdio.h>

#include <unistd.h>

#include <sys/poll.h>

#define TIMEOUT 5

int main(void) {
    struct pollfd fds[2];
    int ret;
    char buff[100];

    printf("Initial value of POLLIN - %d, POLLOUT - %d\n", POLLIN, POLLOUT); 

    /* watch stdin for input */
    printf("Watching for input on STDIN_FILENO\n");
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    /* watch stdout for ability to read also*/
    printf("Watching for input on STDOUT\n");
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLIN;
    
    printf("Waiting for 5 seconds before checking POLLIN, POLLOUT\n");
    ret = poll(fds, 2, TIMEOUT * 1000);

    if (ret == -1) {
        perror("poll");
        return 1;
    }

    if (!ret) {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }
    printf("Values now \n");
    printf("POLLIN - %d POLLOUT - %d %d %d", POLLIN, POLLOUT, fds[0].revents, fds[1].revents);

    if (fds[0].revents & POLLIN) {
        printf("stdin is readable, attempting to read 100 bytes\n");    
        count = read(STDIN_FILENO, buf, sizeof(buf));
        printf("STDIN Read %d bytes , contents - %s\n", count, buff);
        
    }


    if (fds[1].revents & POLLOUT) {
        printf("stdout is writable\n");    
        count = read(STDOUT_FILENO, buf, sizeof(buf));
        printf("STDOUT Read %d bytes , contents - %s\n", count, buff);
    }


    return 0;

}


```
