#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "read_device_thread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("TIME_CHANGE");

    // "Лампочка"
    ui->bulb->setFixedSize( 10, 10 );
    ui->bulb->setStyleSheet( "border-radius: 5px; background-color: red;" );

    ui->spinBox_Hour->setMaximum(23);       ui->spinBox_Hour->setWrapping(true);
    ui->spinBox_Min->setMaximum(59);        ui->spinBox_Min->setWrapping(true);
    ui->spinBox_Sec->setMaximum(59);        ui->spinBox_Sec->setWrapping(true);

    ui->now_time->clear();

    if (my_device.open_device())
    {
        ui->bulb->setStyleSheet( "border-radius: 5px; background-color: green;" );    

        thread_read= new QThread;
        read_time = new Read_device_thread(&my_device);

        start_thread();
    }
}

MainWindow::~MainWindow()
{
    thread_read->quit();
    my_device.~time_device();
    delete ui;
}

void MainWindow::on_set_new_time_clicked()
{
    QDate user_date = ui->calendarWidget->selectedDate();

    // Структура, отвечает за смену времени
    struct my_date users_date;

    users_date.year = static_cast<unsigned int>(user_date.year());
    users_date.mon =  static_cast<unsigned int>(user_date.month());
    users_date.day =  static_cast<unsigned int>(user_date.day());

    users_date.hour = static_cast<unsigned int>(ui->spinBox_Hour->value());
    users_date.min = static_cast<unsigned int>(ui->spinBox_Min->value());
    users_date.sec = static_cast<unsigned int>(ui->spinBox_Sec->value());

    if (users_date.year < 1970)
    {
        qDebug() << " Programm change your year to 1970";
        users_date.year = 1970;
    }

    if (my_device.open_device())
    {
        my_device.set_time(&users_date);
        read_time->set_flag(true);
    }

}

void MainWindow::update(struct my_date * visible_time)
{
    QString str;
    str = QString::number(visible_time->hour) + ":" + QString::number(visible_time->min)
                + ":" +  QString::number(visible_time->sec);

    ui->now_time->setText(str);
}

void MainWindow::start_thread()
{

    read_time->moveToThread(thread_read);

    connect(read_time, SIGNAL(send(struct my_date *)),
            this, SLOT(update(struct my_date *)));

    connect(thread_read, SIGNAL(started()),
            read_time, SLOT(read_time()));

    connect(read_time, SIGNAL (finished()),
            thread_read, SLOT (quit()));

    thread_read->start();
}
void MainWindow::on_spinBox_Hour_valueChanged(int arg)
{
    if(read_time->get_flag())
    {
        read_time->set_flag(false);
    }
}

void MainWindow::on_spinBox_Min_valueChanged(int arg)
{
    if(read_time->get_flag())
    {
        read_time->set_flag(false);
    }
}

void MainWindow::on_spinBox_Sec_valueChanged(int arg)
{
    if(read_time->get_flag())
    {
        read_time->set_flag(false);
    }
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    if(read_time->get_flag())
    {
        read_time->set_flag(false);
    }
}
