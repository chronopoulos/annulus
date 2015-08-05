#include <QtGui>
#include <QtCore>

class ActivationButton : public QPushButton
{
    Q_OBJECT

    public:
        ActivationButton();

    signals:
        void clicked(bool); // true for left-click, false for right-click

    public slots:
        void mousePressEvent(QMouseEvent*);
        void setInactive(void);
        void setDeprimed(void);
        void setPrimed(void);
        void setActive(void);

};

