#include <QtGui>

class Counter : public QObject
{

    Q_OBJECT

    public:
        Counter();
        void increment(void);
        void reset(void);
        bool isReset(void);

    public slots:
        void setLength(int);

    private:
        int index;
        int length;

};
