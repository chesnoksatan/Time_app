#ifndef TIME_DEVICE_H
#define TIME_DEVICE_H

#include <QDebug>

#include <unistd.h>

class time_device
{
private:
    int _devHandel;
public:
    time_device();
    ~time_device();

    // Открыт ли файл устройства
    bool is_Open();

    // Открыть/Закрыть файл устройства
    bool open_device();
    void close_device();

    // С помощью ioctl() установить время
    void set_time(struct my_date *);

    // Чтение даты из файла устройства
    void read_time_from_dev(struct my_date *);
};

#endif // TIME_DEVICE_H
