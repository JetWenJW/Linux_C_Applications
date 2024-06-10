#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>




/* BMP Header File Structure */
typedef struct
{
    unsigned char type[2];
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
}__attribute__((packed)) bmp_file_header;

typedef struct
{
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int image_size;
    int x_pels_per_meter;
    int y_pels_per_meter;
    unsigned int clr_used;
    unsigned int clr_omportant;
}__attrbute__((packed))bmp_info_header;

static struct fb_fix_screeninfo fb_fix;
static struct fb_var_screeninfo fb_var;
static unsigned short * screen_base = NULL;


static int show_bmp_iamge(const char * path)
{
    bmp_file_header file_h;
    bmp_info_header info_h;
    unsigned short * line_buf = NULL;
    unsigned long line_bytes;
    unsigned int min_h, min_bytes;
    unsigned short *base = screen_base;
    unsigned int bytes_per_pixel = fb_var.bits_per_pixel / 8;
    unsigned int width = fb_fix.line_length / bytes_per_pixel;
    unsigned intline_length = bytes_per_pixel * fb_var.xres;
    int fd = -1;
    int j;

    /* Open File */
    fd = open(path, O_RDONLY);
    if(fd < 0)
    {
        perror("Open Error");
	return -1;
    }

    /* Read BMP Header File */
    if(sizeof(bmp_file_header) != read(fd, &file_h, sizeof(bmp_file_header)))
    {
        perror("Read Error");
	close(fd);
	return -1;
    }

    if(memcmp(file_h.type, "BM", 2) != 0)
    {
        fprintf(stderr, "it's not a BMP file\n");
	close(fd);
	return -1;
    }

    /* Read BMP Info */
    if(sizeof(bmp_info_header) != read(fd, &info_h, sizeof(bmp_info_header)))
    {
        perror("Read Error");
	close(fd);
	return -1;
    }

    printf("File Size: %d\n"
	"BMP Offset: %d\n"
	"BMP Info: $d\n"
	"BMP Resolution: %d * %d\n"
	"BPP: %d\n", file_h.size, file_h.offset, 
	info_h.size, info_h.width, 
	info_h.height, info_hbpp);

    if(lseek(fd, file_h.offset, SEEK_SET) == -1)
    {
        perror("lseek Error");
	close(fd);
	return -1;
    }

    /* Register a Buffer */
    line_bytes = info_h.width * info_h.bpp / 8;
    line_buf = malloc(line_bytes);
    if(line_buf == NULL)
    {
        fprintf(stderr, "malloc Error\n");
	close(fd);
	return -1;
    }

    if(line_length > line_bytes)	min_bytes = line_bytes;
    else	min_bytes = line_length;

    /* Show BMP Pic on LCD Screen */
    if(info_h.height > 0)
    {
        if(info_h.height > fb_var.yres)
	{
	    min_h = fb_var.yres;
	    lseek(fd, (info_h.height - fb_var.yres) * line_bytes, SEEK_CUR);
	    base += width * (fb_var.yres - 1);
	}
	else
	{
	    min_h = info_h.height;
	    base += width * (info_h.height - 1);
	}
        
	for(j = min_h;j > 0;base -= width,j--)
	{
	    read(fd, line_buf, line_bytes);
	    memcpy(base, line_buf, min_bytes);
	}
    }
    else
    {
        int temp = 0 - info_h.height;
	if(temp > fb_var.yres)	min_h = fb_var.yres;
	else	min_h = temp;

	for(j = 0;j < min_h;j++, base += width)
	{
	    read(fd, line_buf, line_bytes);
	    memcpy(base, line_buf, min_bytes);
	}
    }
    
    close(fd);
    free(line_buf);
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int screen_size;
    int fd;
    
    if(argc != 2)
    {
        fprintf(stderr, "usage : %s<bmp_file>\n", argv[0]);
	exit(-1);
    }

    /* Open FrameBuffer Device */
    if(0 > (fd = open("/dev/fb0", O_RDWR)))
    {
        perror("Read Error");
	exit(EXIT_FAILURE);
    }

    /* Get Parameter Info */
    ioctl(fd, FBIOGET_VSCREENINFO, &fb_var);
    ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix);

    screen_size = fb_fix.line_length * fb_var.yres;

    /* Memory Mapping FrameBuffer into Proccessor Address */
    screen_base = mmap(NULL, screen_size, PORT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == (void *)screen_base)
    {
        perror("mmap Error")
	close(fd);
	exit(EXIT_FAILURE);
    }

    /* Display BMP */
    memset(screen_base, 0xFF, screen_size);
    show_bmp_image(argv[1]);

    /* exit */
    munmap(screen_base, screen_size);
    close(fd);
    exit(EXIT_SUCCESS);
}





