#include <QApplication>
#include "Annulus.h"
#include "MainWindow.h"
#include <iostream>

using namespace std;

bool VERBOSE = false;

Annulus annulus;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = app.arguments();
    if ( args.contains(QString("-v"))
            || args.contains(QString("--verbose"))) {
        VERBOSE = true;
        cout << "Verbose mode set" << endl;
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
