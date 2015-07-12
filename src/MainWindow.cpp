#include <iostream>
#include <QtGui>
#include <QtCore>
#include <MainWindow.h>

using namespace std;

// constructor
MainWindow::MainWindow(void) : QWidget() {

    layout = new QGridLayout;

    startButton = new QPushButton();
    startButton->setIcon(QIcon("img/play.png"));
    stopButton = new QPushButton();
    stopButton->setIcon(QIcon("img/pause.png"));

    loopers = vector<Looper*>();

    loopers.push_back(new Looper);

    addButton = new QPushButton("+");
    QObject::connect(addButton, SIGNAL(clicked(bool)),
                        this, SLOT(addLooper()));

    layout->addWidget(startButton, 0,0);
    layout->addWidget(stopButton, 0,1);
    layout->addWidget(addButton, 1,0, 1,2);
    refreshLayout();

    this->setLayout(layout);
    this->setWindowTitle("annulus");
    this->setMinimumWidth(300);

}

void MainWindow::refreshLayout(void) {

    int nloopers = loopers.size();
    for (int i=0; i<nloopers; i++) {
        layout->addWidget(loopers[i], i+2,0, 1,2);
    }

}

void MainWindow::addLooper(void) {

    loopers.push_back(new Looper);
    refreshLayout();

}
