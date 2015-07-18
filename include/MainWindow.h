#include <vector>
#include <QtGui>
#include <AudioThread.h>
#include <PlayPauseButton.h>

using namespace std;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();

    private:
        QGridLayout* layout;
        PlayPauseButton* playPauseButton;
        QPushButton* settingsButton;
        vector<Looper*>* loopers;
        QPushButton* addButton;

        void refreshLoopers(void);

        AudioThread* audioThread;

    public slots:
        void addLooper(void);
        void startAudio(void);
        void stopAudio(void);
        void keyPressEvent(QKeyEvent*);

};
