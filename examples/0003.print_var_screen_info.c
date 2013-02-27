/*
 *	print variable screen info
 *
	struct fb_var_screeninfo {
	__u32 xres;			// visible resolution		
	__u32 yres;
	__u32 xres_virtual;		// virtual resolution	
	__u32 yres_virtual;
	__u32 xoffset;			// offset from virtual to visible 
	__u32 yoffset;			// resolution			

	__u32 bits_per_pixel;		// guess what		
	__u32 grayscale;		// 0 = color, 1 = grayscale,	
					// >1 = FOURCC			
	struct fb_bitfield red;		// bitfield in fb mem if true color, 
	struct fb_bitfield green;	// else only length is significant 
	struct fb_bitfield blue;
	struct fb_bitfield transp;	// transparency			

	__u32 nonstd;			// != 0 Non standard pixel format 

	__u32 activate;			// see FB_ACTIVATE_*		

	__u32 height;			// height of picture in mm    
	__u32 width;			// width of picture in mm     

	__u32 accel_flags;		// (OBSOLETE) see fb_info.flags 

	// Timing: All values in pixclocks, except pixclock (of course) 
	__u32 pixclock;			// pixel clock in ps (pico seconds) 
	__u32 left_margin;		// time from sync to picture	
	__u32 right_margin;		// time from picture to sync	
	__u32 upper_margin;		// time from sync to picture	
	__u32 lower_margin;
	__u32 hsync_len;		// length of horizontal sync	
	__u32 vsync_len;		// length of vertical sync	
	__u32 sync;			// see FB_SYNC_*		
	__u32 vmode;			// see FB_VMODE_*		
	__u32 rotate;			// angle we rotate counter clockwise 
	__u32 colorspace;		// colorspace for FOURCC-based modes 
	__u32 reserved[4];		// Reserved for future compatibility 
	};
 */
/*
sample output:(both in X Windows system and an empty tty)
[hukang@hooke fb]$ sudo ./a.out 
xres		= 1280	yres		= 800
xres_virtual	= 1280	yres_virtual	= 800
xoffset		= 0	yoffset		= 0

bits_per_pixel	= 32	grayscale	= 0  			//color
red	: offset = 16,	length =8,	msb_right = 0
green	: offset = 8,	length =8,	msb_right = 0
blue	: offset = 0,	length =8,	msb_right = 0
transp	: offset = 0,	length =0,	msb_right = 0

nonstd		= 0						//standard pixel format
activate	= 0						//FB_ACTIVATE_NOW  set values immediately (or vbl)
height		= 0xffffffff	width		= 0xffffffff
accel_flags(OBSOLETE) = 1

pixclock	= 0
left_margin	= 0
right_margin	= 0
upper_margin	= 0
lower_margin	= 0
hsync_len	= 0	vsync_len     = 0
sync		= 0
vmode		= 0
rotate		= 0
colorspace 	= 0

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
    	perror ("/dev/fb0 open failed: ");
    	exit (0);
    }

    //2. get var screen info
    struct fb_var_screeninfo varinfo;
    memset (&varinfo, 0, sizeof (struct fb_var_screeninfo));

    if (ioctl (fbfd, FBIOGET_VSCREENINFO, &varinfo) == -1)
    {
    	printf (" can not get var screen info\n");
    	exit (0);
    }
    close (fbfd);
    printf ("xres\t\t= %u\tyres\t\t= %u\n", varinfo.xres, varinfo.yres);
    printf ("xres_virtual\t= %u\tyres_virtual\t= %u\n", varinfo.xres_virtual, varinfo.yres_virtual);
    printf ("xoffset\t\t= %u\tyoffset\t\t= %u\n", varinfo.xoffset, varinfo.yoffset);
    printf ("\n");
    printf ("bits_per_pixel\t= %u\tgrayscale\t= %u\n", varinfo.bits_per_pixel, varinfo.grayscale);
#define printcolor(color)	\
    printf (#color"\t: offset = %u,\tlength =%u,\tmsb_right = %u\n", \
    	varinfo.color.offset, varinfo.color.length, varinfo.color.msb_right)

    printcolor(red);
    printcolor(green);
    printcolor(blue);
    printcolor(transp);
    printf ("\n");
    printf ("nonstd\t\t= %u\n", varinfo.nonstd);
    printf ("activate\t= %u\n", varinfo.activate);
    printf ("height\t\t= 0x%x\nwidth\t\t= 0x%x\n", varinfo.height, varinfo.width);
    printf ("\naccel_flags(OBSOLETE) = %u\n", varinfo.accel_flags);
    printf ("\n");
    printf ("pixclock	= %u\n", varinfo.pixclock);
    printf ("left_margin	= %u\n", varinfo.left_margin);
    printf ("right_margin	= %u\n", varinfo.right_margin);
    printf ("upper_margin	= %u\n", varinfo.upper_margin);
    printf ("lower_margin	= %u\n", varinfo.lower_margin);
    printf ("hsync_len	= %u\nvsync_len       = %u\n", varinfo.hsync_len, varinfo.vsync_len);
    printf ("sync		= %u\n", varinfo.sync);
    printf ("vmode		= %u\n", varinfo.vmode);
    printf ("rotate		= %u\n", varinfo.rotate);
    printf ("colorspace 	= %u\n", varinfo.colorspace);
}
