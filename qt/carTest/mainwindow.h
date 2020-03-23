#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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
    void on_horizontalSliderControl_sliderMoved(int position);
    void on_verticalSliderMove_sliderMoved(int position);
    void on_pushButtonConnect_clicked(bool checked);
    void on_checkBoxLight_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial;
    QTimer *timer;
    bool beep = false;
    bool light = false;

    void send();
};

#endif // MAINWINDOW_H
