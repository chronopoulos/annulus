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


        QPushButton* addButton;

        void refreshLoopers(void);

        AudioThread* audioThread;

    public slots:
        void addLoopers(void);
        void startAudio(void);
        void stopAudio(void);
        void keyPressEvent(QKeyEvent*);

};
