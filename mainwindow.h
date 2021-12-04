#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showTime();
    void ChangeFormat();
    void on_button_24_toggled(bool checked);
    void on_setTime_clicked();
    void setTime();
    void on_checkBox_toggled(bool checked);
    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_timeZoneComboBox_currentTextChanged(const QString &arg1);
    void on_refresh_clicked();
    void on_checkBox_2_toggled(bool checked);
    void setTimeToTimeZone();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
