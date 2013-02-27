/*
*    So now, we can move on to using the device in a C program. Take a look at the following code:
  
     All in all, a pretty simple program. We open the framebuffer device file using the low-level open(),
     because the buffered, higher level fopen() is unsuitable for our needs.
     Next, we test the file descriptor to make sure that we were successful, and print a message 
     out that tells the user what happened.
     Note that if you #include <errno.h>, then you will be able to find out exactly why the open() 
     call fails. Check the man page for open() for more information on this
     Finally, we clean up by closing the file descriptor and returning. 
*/
/*
 *	compile: gcc ./0001.open_frame_buffer_device.c 
 *	run    : need root priviledge.
 *	         > sudo ./a.out
 */
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <error.h>

int main()
{
    int fbfd = 0;

    fbfd = open ("/dev/fb0", O_RDWR);
    if (fbfd == -1)
    {
	perror ("Error: cannot open framebuffer device: ");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    close(fbfd);
    return 0;
}
