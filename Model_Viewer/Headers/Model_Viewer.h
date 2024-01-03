#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Model_Viewer.h"

class Model_Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Model_Viewer(QWidget *parent = nullptr);
    ~Model_Viewer();

private:
    Ui::Model_ViewerClass ui;
};
