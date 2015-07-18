#include <QPushButton>
#include <QString>

class PlayPauseButton : public QPushButton
{
    Q_OBJECT

    public:
        PlayPauseButton();

    private:
        bool isPlaying;

    public slots:
        void toggle(void);

    signals:
        void playSelected(void);
        void pauseSelected(void);
};
