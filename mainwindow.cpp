#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<QDateTime>
#include <QTimeZone>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint); //to disable the window resizable option
    ui->button_24->setIcon(QIcon(":/images/tog-off.png")); //set the icons
    ui->button_24->setIconSize(QSize(50,50)); //resize the icons
    QList<QByteArray> ids = QTimeZone::availableTimeZoneIds(); //get available timezones
    foreach (QByteArray id, ids) {
        ui->timeZoneComboBox->addItem(id);
    }

}

MainWindow::~MainWindow()
{
    delete ui;

}

//show 24 hour time when refresh button is clicked
void MainWindow::on_refresh_clicked()
{
    ui->timeZone->setText("Asia/Colombo");
    QTimer *timer = new QTimer(this);
    ui->button_24->setIcon(QIcon(":/images/tog-off.png"));
    ui->button_24->setIconSize(QSize(50,50));
    ui->TimeFormat->setText("24 Hour");
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
}

//method to change time format to 24 hour
void MainWindow::showTime(){

    //if edit time option is checked
    if(ui->checkBox->isChecked()){
        //ui->Clock->setText("00 : 00 : 00");
    }

    //change time format to 24 hour according to the selected time zone
    else if(ui->checkBox_2->isChecked()){
        QByteArray id = ui->timeZoneComboBox->currentText().toLatin1();
        QTimeZone zone = QTimeZone(id);
        QDateTime dateTime = QDateTime::currentDateTime();
        QDateTime newDateTime =  dateTime.toTimeZone(zone);
        ui->Clock->setText(newDateTime.time().toString("hh : mm : ss"));
    }

    //change the current time to 24 hour format
    else{
        QTime time= QTime::currentTime();
        QString time_text = time.toString("hh : mm : ss");
        if ((time.second()%2)==0){
            time_text[3]=' ';
            time_text[8]=' ';
        }
        ui->Clock->setText(time_text);
    }


}

//method to change time format to 12 hour
void MainWindow::ChangeFormat(){

    //if edit time option is checked
    if(ui->checkBox->isChecked()){
        //ui->Clock->setText("00 : 00 : 00");

    }

    //change time format to 12 hour according to the selected time zone
    else if(ui->checkBox_2->isChecked()){
        QByteArray id = ui->timeZoneComboBox->currentText().toLatin1();
        QTimeZone zone = QTimeZone(id);
        QDateTime dateTime = QDateTime::currentDateTime();
        QDateTime newDateTime =  dateTime.toTimeZone(zone);
        ui->Clock->setText(newDateTime.time().toString("hh : mm : ss AP"));
    }

    //change the current time to 12 hour format
    else{
        QTime time = QTime::currentTime();
        QString time_text = time.toString("hh : mm : ss AP");
        if ((time.second()%2)==0){
            time_text[3]=' ';
            time_text[8]=' ';
        }
        ui->Clock->setText(time_text);
    }


}

//mthod to toggle the time format
void MainWindow::on_button_24_toggled(bool checked)
{
    QTimer *timer = new QTimer(this);
        if(ui->button_24->isEnabled()){
            if(checked){
                ui->button_24->setIcon(QIcon(":/images/tog-on.png")); //change icon when button is toggled
                ui->button_24->setIconSize(QSize(50,50));
                ui->TimeFormat->setText("12 Hour");
                connect(timer,SIGNAL(timeout()),this,SLOT(ChangeFormat()));
            }
            else{
                ui->button_24->setIcon(QIcon(":/images/tog-off.png")); //change icon when button is toggled
                ui->button_24->setIconSize(QSize(50,50));
                ui->TimeFormat->setText("24 Hour");
                connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
            }
            timer->start();
        }
        else{
            timer->stop();
        }
}

//method to set time
/*once time was edited and agin if it needs to be edited, no need of clicking 'Set Time' button, just change the new time to be edited and automatically
 time will be changed.*/
//in here both 12 hour and 24 hour time will be displayed.
void MainWindow::setTime(){
    if(ui->checkBox_2->isChecked()){
        //ui->Clock->setText("00 : 00 : 00");

    }
    else{
        QTime nowTime = ui->timeEdit->time();
        QTime ctime = nowTime.addSecs(1);
        ui->timeEdit->setTime(ctime);
        QString time_text = ctime.toString("hh : mm ");
        ui->Clock->setText(time_text);
    }

}

//method to start the timer for editing option
void MainWindow::on_setTime_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(setTime()));
    timer->start(1000);
}

//method to enable time editing option
void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked){
        ui->checkBox_2->setEnabled(false);//disable timezone changing option untill uncheck this
        ui->setTime->setEnabled(true);
        ui->refresh->setEnabled(false); //disable refresh button
        ui->timeEdit->setEnabled(true); //enable editing option
        ui->button_24->setEnabled(false); //disable toggle button
        ui->Clock->setText("00 : 00 : 00");
    }
    else{
        ui->checkBox_2->setEnabled(true);
        ui->setTime->setEnabled(false);
        ui->timeEdit->setEnabled(false);//disable editing option
        ui->refresh->setEnabled(true); //enable refresh button
        ui->button_24->setEnabled(true); //enable toggle button
        ui->Clock->setText("00 : 00 : 00");
    }
}

//method to edit the time
void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    QString time_text = time.toString("hh : mm : ss");
    ui->Clock->setText(time_text);
}

//method to show time according to the time zones (Only time will be shown in 24 hour format)
void MainWindow::on_timeZoneComboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 != "Select Time Zone"){
        QByteArray id = ui->timeZoneComboBox->currentText().toLatin1();
        QTimeZone zone = QTimeZone(id);
        QDateTime dateTime = QDateTime::currentDateTime();
        QDateTime newDateTime =  dateTime.toTimeZone(zone);
        ui->timeZone->setText(arg1);
        ui->TimeFormat->setText("24 Hour");
        ui->Clock->setText(newDateTime.time().toString("hh : mm : ss"));
        QTimer *timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(setTimeToTimeZone()));
        timer->start(1000);
    }

}

//method to update the time according to the timezone
void MainWindow::setTimeToTimeZone()
{
    if(ui->checkBox->isChecked()){
        //
    }
    else{
        QByteArray id = ui->timeZoneComboBox->currentText().toLatin1();
        QTimeZone zone = QTimeZone(id);
        QDateTime dateTime = QDateTime::currentDateTime();
        QDateTime newDateTime =  dateTime.toTimeZone(zone);
        ui->Clock->setText(newDateTime.time().toString("hh : mm : ss"));
        QString time_text = ui->Clock->text();
        QTime time = QTime::fromString(time_text,"hh : mm : ss");
        if ((time.second()%2)==0){
            time_text[3]=' ';
            time_text[8]=' ';
        }
        ui->Clock->setText(time_text);
    }


}

//method to enable finding time from time zones
/*
 * when this is checked, all the other options will be disabled
 uncheck it to enable other options
*/
void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if(checked){
        ui->checkBox->setEnabled(false);//disable time editing option until uncheck this
        ui->timeZoneComboBox->setEnabled(true);//disable selecting option
        ui->setTime->setEnabled(false);
        ui->refresh->setEnabled(false); //disable refresh button
        ui->timeEdit->setEnabled(false); //disable editing option
        ui->Clock->setText("00 : 00 : 00");
    }
    else{
        ui->checkBox->setEnabled(true);
        ui->timeZoneComboBox->setEnabled(false);//disable selecting option
        ui->setTime->setEnabled(false);
        ui->timeEdit->setEnabled(false);//disable editing option
        ui->refresh->setEnabled(true); //enable refresh button
        ui->timeZone->setText("Asia/Colombo");
        QTime time = QTime::currentTime();
        QString time_text = time.toString("hh : mm : ss");
        ui->Clock->setText(time_text);
    }
}


