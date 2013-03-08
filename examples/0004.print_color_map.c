/*
sample output:(both in X Windows system and an empty tty)

cannot get colormap

//it seems that fb based on kms cannot use colormap.
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
		printf ("/dev/fb0 open failed\n");
		exit (0);
	}

	// get color map.
	struct fb_cmap colormap;
	memset (&colormap, 0, sizeof (struct fb_cmap));
	if (ioctl (fbfd, FBIOGETCMAP, &colormap) == -1)
	{
		perror ("cannot get colormap");
		exit (1);
	}
	close (fbfd);
	if (colormap.len != 0)
	{
		printf ("start\t= %u\n", colormap.start);
		printf ("len\t= %u\n", colormap.len);
		int i = 0;
		for (; i < colormap.len; i++)
		{
			printf ("red\t= %u\t",colormap.red[i]);
			printf ("green\t= %u\t", colormap.green[i]);
			printf ("blue\t= %u\t", colormap.blue[i]);
			printf ("transp\t= %u\t", colormap.transp[i]);
		}
	}
}
