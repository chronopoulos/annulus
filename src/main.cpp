/*
Questions/confusion:
    - what's the difference between declaring these two ways:
        QWidget window;
        QVBoxLayout *layout = new QVBoxLayout();
    - what's the difference between . and -> for addressing methods?
*/


#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
