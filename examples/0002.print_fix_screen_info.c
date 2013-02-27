/*
 	print framebuffer fixed screen info


	(from /usr/include/linux/fb.h)
	struct fb_fix_screeninfo {
	char id[16];			// identification string eg "TT Builtin" 
	unsigned long smem_start;	// Start of frame buffer mem 
					// (physical address) 
	__u32 smem_len;			// Length of frame buffer mem 
	__u32 type;			// see FB_TYPE_*		
	__u32 type_aux;			// Interleave for interleaved Planes 
	__u32 visual;			// see FB_VISUAL_*		 
	__u16 xpanstep;			// zero if no hardware panning  
	__u16 ypanstep;			// zero if no hardware panning  
	__u16 ywrapstep;		// zero if no hardware ywrap    
	__u32 line_length;		// length of a line in bytes    
	unsigned long mmio_start;	// Start of Memory Mapped I/O   
					// (physical address) 
	__u32 mmio_len;			// Length of Memory Mapped I/O  
	__u32 accel;			// Indicate to driver which	
					//  specific chip/card we have	
	__u16 capabilities;		// see FB_CAP_*			
	__u16 reserved[2];		// Reserved for future compatibility 
	};

*/
/*
sample output:(both in X Windows system and an empty tty)

[host@host fb]$ sudo ./a.out 
id           = radeondrmfb
smem_start   = 0x80142000
smem_len     = 0x3e8000			// = 4 x screen_pixels(1280x800). is this means the RGBA bytes a screen needs?
type         = 0			// FB_TYPE_PACKED_PIXELS
type_aux     = 0			// FB_AUX_TEXT_MDA or FB_AUX_VGA_PLANES_VGA4
visual       = 2			// FB_VISUAL_TRUECOLOR	true color
xpanstep     = 1
ypanstep     = 1
ywrapstep    = 0
line_length  = 0x1400			// = 4 x line_pixels (1280)
mmio_start   = 0x0
mmio_len     = 0x0
accel        = 0			// FB_ACCEL_NONE
capabilities = 0
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

    //2. get fix screen info
    struct fb_fix_screeninfo fixinfo;
    memset (&fixinfo, 0, sizeof (struct fb_fix_screeninfo));

    if (ioctl (fbfd, FBIOGET_FSCREENINFO, &fixinfo) == -1)
    {
    	printf (" can not get fix screen info\n");
    	exit (0);
    }
    close (fbfd);

    printf ("id           = %s\n", fixinfo.id);
    printf ("smem_start   = 0x%x\n", fixinfo.smem_start);
    printf ("smem_len     = 0x%x\n", fixinfo.smem_len);
    printf ("type         = %u\n", fixinfo.type);
    printf ("type_aux     = %u\n", fixinfo.type_aux);
    printf ("visual       = %u\n", fixinfo.visual);
    printf ("xpanstep     = %u\n", fixinfo.xpanstep);
    printf ("ypanstep     = %u\n", fixinfo.ypanstep);
    printf ("ywrapstep    = %u\n", fixinfo.ywrapstep);
    printf ("line_length  = 0x%x\n", fixinfo.line_length);
    printf ("mmio_start   = 0x%x\n", fixinfo.mmio_start);
    printf ("mmio_len     = 0x%x\n", fixinfo.mmio_len);
    printf ("accel        = %u\n", fixinfo.accel);
    printf ("capabilities = %u\n", fixinfo.capabilities);
}
