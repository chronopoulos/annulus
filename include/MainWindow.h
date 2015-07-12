#include <QtGui>
#include <Looper.h>
#include <vector>

using namespace std;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();

    private:
        QGridLayout* layout;
        QPushButton* startButton;
        QPushButton* stopButton;
        vector<Looper*> loopers;
        QPushButton* addButton;

        void refreshLayout(void);

    public slots:
        void addLooper(void);

};
