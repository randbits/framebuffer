/*
sample output:(both in X Windows system and an empty tty)

cannot get con2fbmap

*/
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int
main (int argc, char** argv)
{
	//1. open fb device
	int fbfd;
	fbfd = open ("/dev/fb0", O_RDWR);
	if (fbfd == -1)
	{
		perror("/dev/fb0 open failed");
		exit (0);
	}

	// get color map.
	struct fb_con2fbmap cfmap;
	memset (&cfmap, 0, sizeof (struct fb_con2fbmap));
	if (ioctl (fbfd, FBIOGET_CON2FBMAP, &cfmap) == -1)
	{
		perror("cannot get con2fbmap");
		exit (1);
	}
	close (fbfd);

	printf ("console\t= %u\n", cfmap.console);
	printf ("framebuffer\t= %u\n", cfmap.framebuffer);
}
