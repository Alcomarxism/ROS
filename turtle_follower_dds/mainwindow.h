#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "turtleteleopkeywidget.h"
#include "turtlewidget.h"
#include "turtlefollowerwidget.h"
#include <vector>
#include "dds/dds.h"

#define NUM_TURTLES 200

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    dds_entity_t participant;
    TurtleTeleopKeyWidget* teleopWidget;
    std::vector<TurtleWidget*> turtles;
    std::vector<TurtleFollowerWidget*> turtlesFollowers;
    TurtleFollowerWidget *flw;
    Ui::MainWindow *ui;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};
#endif // MAINWINDOW_H
