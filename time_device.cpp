#include "time_device.h"
#include "my_time.h"

time_device::time_device()
{
    _devHandel = -1;

};

time_device::~time_device()
{
    close_device();
};

inline bool time_device::is_Open()
{
    return (_devHandel>=0) ? true : false;
}

bool time_device::open_device()
{
    if(is_Open()) {return true;}

        _devHandel = open(CHAR_DEVICE_NAME,O_RDWR);
        if (_devHandel <=0) {
            qDebug()<<"/dev/TIME open false.";
            _devHandel = -1;
            return false;
        }
        qDebug()<<"/dev/TIME open true.";

        return true;
}

void time_device::close_device()
{
    if (!is_Open()) return;

      ::close(_devHandel);
      _devHandel = -1;
}

void time_device::set_time(struct my_date *user_date)
{
    if (!is_Open()) {
        qDebug() << "device not open";
        return;
    }
    ioctl(_devHandel,TIME_IOCSET, user_date);
}

void time_device::read_time_from_dev(struct my_date *user_date)
{
    if (!is_Open()) {
        qDebug() << "device not open";
        return;
    }
    ioctl(_devHandel,TIME_IOCREAD, user_date);
}
