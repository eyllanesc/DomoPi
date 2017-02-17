#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QChart>
#include <QValueAxis>
#include <QDateTimeAxis>

using namespace QtCharts;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLineSeries *series;
    QLineSeries *series2;
    QNetworkRequest request;
    QNetworkAccessManager nam;
    QChart *chart;
    QTimer *timer;
    QNetworkReply *reply;

    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QValueAxis *axisY2;


private slots:
    void getData();
    void on_startBtn_clicked();
    void draw();
};

#endif // MAINWINDOW_H
