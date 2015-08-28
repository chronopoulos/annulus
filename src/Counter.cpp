#include <Counter.h>
#include <iostream>

using namespace std;

Counter::Counter() : QObject() {

    index = 0;
    length = 88200; // 4 beats @ 120 bpm

}

void Counter::increment(void) {

    if (++index == length) {
        index = 0;
        cout << "counter looped!" << endl;
    }

}

void Counter::reset(void) {

    index = 0;

}

bool Counter::isReset(void) {

    return index==0;

}

void Counter::setLength(int length) {

    this->length = length;
    cout << "counter length set to " << length << endl;

}
