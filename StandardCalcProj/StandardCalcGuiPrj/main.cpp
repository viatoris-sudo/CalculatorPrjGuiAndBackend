#include "standardCalcGui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Calculator calc(nullptr );
    calc.show();
    return a.exec();
}

