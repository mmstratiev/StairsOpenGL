#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QOpenGLWidget>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    //Sets up UI and OpenGL
    ui->setupUi(this);
    stairs = new Stairs(ui->stepWidth->value(), ui->stepHeight->value(), ui->stepDepth->value(), ui->stairsHeight->value());
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);

    ui->openGLWidget->setFormat(format);
    ui->openGLWidget->setObjectToDraw(stairs);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stairsHeight_valueChanged(double arg1)
{
    stairs->setStairsHeight(arg1);
    ui->stepHeight->setMaximum(arg1/2);
    ui->openGLWidget->refresh();
}

void MainWindow::on_stepDepth_valueChanged(double arg1)
{
    stairs->setStepDepth(arg1);
    ui->PlatformDepth->setMinimum(arg1);
    ui->openGLWidget->refresh();
}

void MainWindow::on_stepHeight_valueChanged(double arg1)
{
    stairs->setStepHeight(arg1);
    ui->openGLWidget->refresh();
}

void MainWindow::on_stepWidth_valueChanged(double arg1)
{
    stairs->setStepWidth(arg1);
    ui->openGLWidget->refresh();
}

//changes the Stairs object and refreshes the OpenGL
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Straight Stairs"){
        ui->PlatformDepth->setEnabled(false);
        ui->segmentHeight->setEnabled(false);
        ui->PlatformLabel->setEnabled(false);
        ui->SegmentLabel->setEnabled(false);
        stairs = new Stairs(ui->stepWidth->value(), ui->stepHeight->value(), ui->stepDepth->value(), ui->stairsHeight->value());
    }
    else if(arg1 == "Platform Stairs"){
        ui->PlatformDepth->setEnabled(true);
        ui->segmentHeight->setEnabled(true);
        ui->PlatformLabel->setEnabled(true);
        ui->SegmentLabel->setEnabled(true);
        stairs = new PlatformStairs(ui->stepWidth->value(), ui->stepHeight->value(), ui->stepDepth->value(),
                                    ui->segmentHeight->value(), ui->stairsHeight->value(), ui->PlatformDepth->value());
    }
    else if(arg1 == "U Shaped Stairs"){
        ui->PlatformDepth->setEnabled(true);
        ui->segmentHeight->setEnabled(true);
        ui->PlatformLabel->setEnabled(true);
        ui->SegmentLabel->setEnabled(true);
        stairs = new UStairs(ui->stepWidth->value(), ui->stepHeight->value(), ui->stepDepth->value(),
                             ui->segmentHeight->value(), ui->stairsHeight->value(), ui->PlatformDepth->value());
    }
    ui->openGLWidget->setObjectToDraw(stairs);
    ui->openGLWidget->refresh();
}

void MainWindow::on_PlatformDepth_valueChanged(double arg1)
{
    if(ui->PlatformDepth->isEnabled()){
        dynamic_cast<PlatformStairs*>(stairs)->setPlatformDepth(arg1);
        ui->openGLWidget->refresh();
    }
}

void MainWindow::on_segmentHeight_valueChanged(int arg1)
{
    dynamic_cast<PlatformStairs*>(stairs)->setSegmentHeight(arg1);
    ui->openGLWidget->refresh();
}

void MainWindow::on_resetCamera_clicked()
{
    ui->openGLWidget->resetCamera();
}
