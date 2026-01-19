/**
 * @file lowlevel.c
 * @brief newlib lowlevel functions
 * @author KSEII T.Terazawa
 */

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/times.h>

#include <SystemServices/Mcu.h>
#include <SystemServices/SchM.h>
#include <IODrivers/Sci.h>


/**
 * @param file file descriptor
 * @return
 * @note stub implement always fail
 */
int close(int file)
{
    errno = EBADF;
    return (-1);
}


/**
 * @param file
 * @param st
 * @return
 * @note stub implement always return character device
 */
int fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return (0);
}


/**
 * @param __fildes file descriptor
 * @return
 * @note stub implement only success stdin/stdout/stderr
 */
int isatty(int __fildes)
{
    if ((__fildes == STDIN_FILENO) || (__fildes == STDOUT_FILENO) || (__fildes == STDERR_FILENO))
    {
        return (1);
    }

    errno = EBADF;
    return (0);
}


/**
 * @param __fildes
 * @param __offset
 * @param __whence
 * @return stub implemetnt always return 0
 */
off_t lseek(int __fildes, off_t __offset, int __whence )
{
    return (0);
}


/**
 * @brief read lowlevel api
 * @param __fd
 * @param __buf
 * @param __nbyte
 * @return
 */
_READ_WRITE_RETURN_TYPE read(int __fd, void *__buf, size_t __nbyte)
{
    size_t compbyte = 0;
    uint8_t rxByte;
    char *ptr = (char *)__buf;
    
    if (__fd == STDIN_FILENO)
    {
        if (__nbyte == 0)
        {
            return (0);
        }

        while (!Sci_Recv1BAsync(&rxByte))
        {

        }
        *ptr++ = rxByte;
        return (1);
    }

    errno = EBADF;
    return (-1);
}


/**
 * write lowlevel api
 * @param __fd
 * @param __buf
 * @param __nbyte
 * @return
 * @note stdout/stderr -> SCI, else no output.
 */
_READ_WRITE_RETURN_TYPE write(int __fd, const void *__buf, size_t __nbyte)
{
    size_t compbyte = 0;
    const char *ptr = (const char *)__buf;
    
    if ((__fd == STDOUT_FILENO) || (__fd == STDERR_FILENO))
    {
        while (compbyte < __nbyte)
        {
            while (Sci_Send1BAsync(*ptr) == FALSE)
            {
            }
            ptr++;

            compbyte++;
        }

        return (compbyte);
    }

    errno = EBADF;
    return (-1);
}


/**
 * getpid lowlevel api
 */
int getpid(void)
{
    return (1);
}


/**
 * kill lowlevel api
 * @param pid pid
 * @param sig signal
 */
int kill(int pid, int sig)
{
  errno = EINVAL;
  return -1;
}


/**
 * times lowlevel api
 * @param buf
 */
clock_t times(struct tms *buf)
{
    if (buf != NULL)
    {
        buf->tms_utime = SchM_Get1msCounter();
        buf->tms_stime = SchM_Get1msCounter();
        buf->tms_cutime = SchM_Get1msCounter();
        buf->tms_cstime = SchM_Get1msCounter();
    }

    return (SchM_Get1msCounter());
}
