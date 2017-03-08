#include <QApplication>
#include <QSound>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSound::play("/home/sg-os/code/qt/qtlearning/qsound/22.wav");
//    QSound::play("./金玟岐 - 城市背后.wav");

    return a.exec();
}
