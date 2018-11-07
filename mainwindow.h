#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>

#include "my_time.h"
#include "read_device_thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_set_new_time_clicked();
    void update(struct my_date *);
    void start_thread();

    void on_spinBox_Hour_valueChanged(int);

    void on_spinBox_Min_valueChanged(int);

    void on_spinBox_Sec_valueChanged(int);

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    time_device my_device;
    QThread *thread_read;
    Read_device_thread *read_time;
};

#endif // MAINWINDOW_H
