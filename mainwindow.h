#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "stairs.h"
#include "platformstairs.h"
#include "ustairs.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Slots called when values changed
    void on_stairsHeight_valueChanged(double arg1);
    void on_stepDepth_valueChanged(double arg1);
    void on_stepHeight_valueChanged(double arg1);
    void on_stepWidth_valueChanged(double arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_PlatformDepth_valueChanged(double arg1);
    void on_segmentHeight_valueChanged(int arg1);

    //Slots called when buttons are clicked
    void on_resetCamera_clicked();

private:
    Ui::MainWindow *ui;
    Stairs *stairs;
};

#endif // MAINWINDOW_H
