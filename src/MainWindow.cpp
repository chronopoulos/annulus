#include <iostream>
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
    QObject::connect(startButton, SIGNAL(clicked(bool)),
                        this, SLOT(startAudio()));
    QObject::connect(stopButton, SIGNAL(clicked(bool)),
                        this, SLOT(stopAudio()));

    loopers = new vector<Looper*>();

    addButton = new QPushButton("+");
    QObject::connect(addButton, SIGNAL(clicked(bool)),
                        this, SLOT(addLooper()));

    layout->addWidget(startButton, 0,0);
    layout->addWidget(stopButton, 0,1);
    layout->addWidget(addButton, 1,0, 1,2);

    this->setLayout(layout);
    this->setWindowTitle("annulus");
    this->setMinimumWidth(300);

    audioThread = new AudioThread(this, loopers);

}

void MainWindow::refreshLoopers(void) {

    int nloopers = loopers->size();
    for (int i=0; i<nloopers; i++) {
        layout->addWidget(loopers->at(i), i+2,0, 1,2);
    }

}

void MainWindow::addLooper(void) {

    loopers->push_back(new Looper);
    refreshLoopers();

}

void MainWindow::startAudio(void) {

    audioThread->start();
    cout << "AudioThread started." << endl;

}

void MainWindow::stopAudio(void) {

    audioThread->terminate();
    cout << "AudioThread terminated." << endl;

}

