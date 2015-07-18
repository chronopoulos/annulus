#include <iostream>
#include <QtCore>
#include <MainWindow.h>

using namespace std;

// constructor
MainWindow::MainWindow(void) : QWidget() {

    layout = new QGridLayout;

    playPauseButton = new PlayPauseButton;
    playPauseButton->setFocusPolicy(Qt::NoFocus);
    settingsButton = new QPushButton();
    settingsButton->setFocusPolicy(Qt::NoFocus);
    settingsButton->setIcon(QIcon("img/settings.png"));

    loopers = new vector<Looper*>();

    addButton = new QPushButton("+");
    addButton->setFocusPolicy(Qt::NoFocus);
    QObject::connect(addButton, SIGNAL(clicked(bool)),
                        this, SLOT(addLooper()));

    layout->addWidget(playPauseButton, 0,0);
    layout->addWidget(settingsButton, 0,1);
    layout->addWidget(addButton, 1,0, 1,2);

    this->setLayout(layout);
    this->setWindowTitle("annulus");
    this->setMinimumWidth(300);

    audioThread = new AudioThread(this, loopers);
    QObject::connect(playPauseButton, SIGNAL(playSelected(void)),
                        audioThread, SLOT(start(void)));
    QObject::connect(playPauseButton, SIGNAL(pauseSelected(void)),
                        audioThread, SLOT(stop(void)));


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

}

void MainWindow::stopAudio(void) {

    audioThread->stop();

}

void MainWindow::keyPressEvent(QKeyEvent* k) {

    if (k->key()==Qt::Key_Space) {
        if (!k->isAutoRepeat()) {
            playPauseButton->toggle();
        }
    }

}



