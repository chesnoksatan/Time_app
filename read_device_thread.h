#ifndef READ_DEVICE_THREAD_H
#define READ_DEVICE_THREAD_H

#include <QObject>
#include <QMutex>

#include "time_device.h"

class Read_device_thread : public QObject
{
    Q_OBJECT
public:
    Read_device_thread(time_device *);

    void set_flag(bool);
    bool get_flag();

signals:
    void send(struct my_date *);
    void finished();

public slots:
    void read_time();

private:
    time_device *my_dev;
    bool flag_thread;
    QMutex mutex;
};

#endif // READ_DEVICE_THREAD_H
