#pragma once

#include <QWidget>
#include<QDebug>
#include<QSoundEffect>
#include<QUrl>
namespace Ui {
class volChanged;
}

class volChanged : public QWidget
{
    Q_OBJECT

public:
    explicit volChanged(QWidget *parent = 0);
    ~volChanged();
    void playVol(QString path);
public slots:
    void SlotSetVol(int value);
private:
    Ui::volChanged *ui;
    QSoundEffect *m_soundEffect;
};

