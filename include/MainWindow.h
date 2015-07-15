#include <vector>
#include <QtGui>
#include <AudioThread.h>

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
        vector<Looper*>* loopers;
        QPushButton* addButton;

        void refreshLoopers(void);

        AudioThread* audioThread;

    public slots:
        void addLooper(void);
        void startAudio(void);
        void stopAudio(void);

};
