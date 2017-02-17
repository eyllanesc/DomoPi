#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QTimer>

#include <QDateTimeAxis>
#include <QValueAxis>
#include <QChartView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setText("http://192.168.2.9/api/sensors/");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getData()));

}

MainWindow::~MainWindow()
{
    delete ui;
    reply->deleteLater();
}

void MainWindow::getData()
{
    reply = nam.get(request);

    while(!reply->isFinished())
        qApp->processEvents();

    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);
    QJsonArray array = json.array();
    QDateTime d;
    QString str;
    series = new QLineSeries();
    series2 = new QLineSeries();


    foreach(QJsonValue val, array){
        str = val.toObject().take("date_created").toString();
        d = QDateTime::fromString(str, Qt::ISODate);
        series->append(d.toMSecsSinceEpoch(), val.toObject().take("temperature").toDouble());
        series2->append(d.toMSecsSinceEpoch(), val.toObject().take("humidity").toDouble());
        //qDebug()<< d.toString()<<status<<QDateTime::currentDateTimeUtc().toString();
    }

    draw();

}

void MainWindow::on_startBtn_clicked()
{
    timer->start(1000);
    request = QNetworkRequest(QUrl(ui->lineEdit->text()));

}

void MainWindow::draw()
{

    chart = new QChart();
    chart->removeAllSeries();

    chart->addSeries(series);
    chart->addSeries(series2);

    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM HH:mm:ss");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis;
    //axisY->setLabelFormat("%d");
    axisY->setTitleText("Temperatura");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setRange(0, 100);

    axisY2 = new QValueAxis;
    //axisY->setLabelFormat("%d");
    axisY2->setTitleText("Humedad");
    chart->addAxis(axisY2, Qt::AlignRight);
    series2->attachAxis(axisY2);
    axisY2->setRange(0, 100);


    chart->legend()->hide();
    chart->setTitle("Humedad y Temperatura ESP8266-DHT11");



    ui->chartview->setChart(chart);
    ui->chartview->setRenderHint(QPainter::Antialiasing);

}
