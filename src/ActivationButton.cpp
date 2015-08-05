#include <iostream>
#include <ActivationButton.h>

using namespace std;

ActivationButton::ActivationButton() : QPushButton() {

    setInactive();

}

void ActivationButton::setInactive(void) {

    setStyleSheet("background-color:rgba(255,0,0, 255);");

}

void ActivationButton::setDeprimed(void) {

    setStyleSheet("background-color:rgba(255,0,0, 100);");

}

void ActivationButton::setPrimed(void) {

    setStyleSheet("background-color:rgba(0,255,0, 100);");

}

void ActivationButton::setActive(void) {

    setStyleSheet("background-color:rgba(0,255,0, 255);");

}

void ActivationButton::mousePressEvent(QMouseEvent* e) {

    if (e->buttons() == Qt::LeftButton) {   
        emit clicked(true); 
    } else if (e->buttons() == Qt::RightButton) {
        emit clicked(false); 
    }

}
