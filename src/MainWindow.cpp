#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include <MainWindow.h>

using namespace std;

// constructor
MainWindow::MainWindow(void) : QWidget() {

    QVBoxLayout* layout = new QVBoxLayout;
    QLabel* helloLabel = new QLabel("Hello");
    QLabel* worldLabel = new QLabel("World");

    layout->addWidget(helloLabel);
    layout->addWidget(worldLabel);

    this->setLayout(layout);
    this->resize(250, 150);
    this->setWindowTitle("Window Title Goes Here");

}

// destructor
MainWindow::~MainWindow(void) {

    cout << "Destructor called!" << endl;

}
