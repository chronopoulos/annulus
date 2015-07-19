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

    loopersMutex.lock();
    loopers = new vector<Looper*>();
    loopersMutex.unlock();

    addButton = new QPushButton("+");
    addButton->setFocusPolicy(Qt::NoFocus);
    QObject::connect(addButton, SIGNAL(clicked(bool)),
                        this, SLOT(addLoopers()));

    layout->addWidget(playPauseButton, 0,0);
    layout->addWidget(settingsButton, 0,1);
    layout->addWidget(addButton, 1,0, 1,2);

    this->setLayout(layout);
    this->setWindowTitle("annulus");
    this->setMinimumWidth(300);

    audioThread = new AudioThread(this, loopers, &loopersMutex);
    QObject::connect(playPauseButton, SIGNAL(playSelected(void)),
                        audioThread, SLOT(start(void)));
    QObject::connect(playPauseButton, SIGNAL(pauseSelected(void)),
                        audioThread, SLOT(stop(void)));
    QObject::connect(audioThread, SIGNAL(xrunOccurred(void)),
                        playPauseButton, SLOT(reset(void)));

}

void MainWindow::addLoopers(void) {

    QStringList files = QFileDialog::getOpenFileNames(this, "Select Loops",
            "/home/chrono/music/samples/loops/annulus");
    int n = files.size();
    if (n>0) {
        QMutexLocker locker(&loopersMutex);
        cout << "addLoopers got mutex" << endl;
        for (int i=0; i<files.size(); i++) {
            loopers->push_back(new Looper(this, files.at(i)));
        }
        refreshLoopers();
    }

}

void MainWindow::refreshLoopers(void) {

    int nloopers = loopers->size();
    for (int i=0; i<nloopers; i++) {
        layout->addWidget(loopers->at(i), i+2,0, 1,2);
    }
    this->show();

}

void MainWindow::startAudio(void) {

    audioThread->start();

}

void MainWindow::stopAudio(void) {

    audioThread->stop();

}

void MainWindow::keyPressEvent(QKeyEvent* k) {

    if (!k->isAutoRepeat()) {
        switch (k->key()) {
            case Qt::Key_Space:
                playPauseButton->toggle();
                break;
            case Qt::Key_I:
                addLoopers();
                break;
        }
    }

}



