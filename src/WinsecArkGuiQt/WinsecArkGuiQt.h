#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WinsecArkGuiQt.h"

class WinsecArkGuiQt : public QMainWindow
{
    Q_OBJECT

public:
    WinsecArkGuiQt(QWidget *parent = nullptr);
    ~WinsecArkGuiQt();

private:
    Ui::WinsecArkGuiQtClass ui;
};
