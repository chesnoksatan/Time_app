#ifndef MY_TIME_H
#define MY_TIME_H

#include <sys/fcntl.h>
#include <sys/ioctl.h>

#include "time_device.h"

#define CHAR_DEVICE_NAME "/dev/TIME"

typedef struct my_date {
    unsigned int sec, min, hour; // поля структуры определяющие время
    unsigned int year, mon, day; // поля структуры определяющие дату
} my_date;

// Определение "Магических" чисел для ioctl
#define TIME_IOC_MAGIC 'k'
#define TIME_IOCSET _IOWR(TIME_IOC_MAGIC, 1, struct my_date *)
#define TIME_IOCREAD _IOWR(TIME_IOC_MAGIC, 2, struct my_date *)

#endif // MY_TIME_H
