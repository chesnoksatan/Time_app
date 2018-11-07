#include "read_device_thread.h"
#include "my_time.h"

#include <unistd.h>

Read_device_thread::Read_device_thread(time_device *new_device)
{
     my_dev = new_device;
     flag_thread = true;
}

void Read_device_thread::read_time()
{
    struct my_date visible_time;
    QString str;
    forever{
        if (flag_thread && my_dev->is_Open()) {
            my_dev->read_time_from_dev(&visible_time);
            send(&visible_time);
        }
        sleep(1);
    }
}

void Read_device_thread::set_flag(bool value)
{
    QMutexLocker locker(&mutex);
    flag_thread = value;
}

bool Read_device_thread::get_flag()
{
    return flag_thread;
}
