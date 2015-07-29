#include <iostream>
#include <QPushButton>
#include <PlayPauseButton.h>

using namespace std;

PlayPauseButton::PlayPauseButton() : QPushButton() {

    QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(toggle(void)));

    this->setIcon(QIcon("img/play.png"));
    isPlaying = false;

}

void PlayPauseButton::toggle(void) {

    if (isPlaying) {
        this->setIcon(QIcon("img/play.png"));
        this->setStyleSheet("");
        isPlaying = false;
        emit pauseSelected();
    } else {
        this->setIcon(QIcon("img/pause.png"));
        this->setStyleSheet("background:rgb(200,100,150);");
        isPlaying = true;
        emit playSelected();
    }

}

void PlayPauseButton::reset(void) {
        this->setIcon(QIcon("img/play.png"));
        this->setStyleSheet("");
        isPlaying = false;
}
