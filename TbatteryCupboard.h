#pragma once

#include <QWidget>
#include<QObject>
#include<QDebug>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include<QRectF>
#include<QTimer>
#include<QPushButton>
#include<QToolButton>
#include<QScrollBar>
#include<QSoundEffect>
#include"Tscenewidget.h"
#include"TkeyBoard.h"
#include"Tbattery.h"
namespace Ui {
class TbatteryCupboard;
}

class TbatteryCupboard : public QWidget
{
    Q_OBJECT

public:
    explicit TbatteryCupboard(QWidget *parent = 0);
    ~TbatteryCupboard();
public:
    void setMainScene();
    void setMoveBtn();
    void dealItem();
    void resizeEvent(QResizeEvent *);
    void timerEvent(QTimerEvent *event);

private slots:
    void SlotCheckBatteryBtnClicked();
    void Slotpro();
    void SlotSmartButtonDoubleClicked();
    void SlotSmartButtonPress();
    void SlotGetCmdFromKeyBoard(QString cmd,SPEICAL_BUTTON_TYPE type);
private:
    Ui::TbatteryCupboard *ui;
    QGraphicsScene  m_mainScene;
    int m_timeId;
    QTimer *m_timer;
    //rollLabel*m_moveLabel;
    QToolButton*m_moveBtn;
    TkeyBoard*m_keyBoard;
    QSoundEffect*m_sound;
    double m_pos;
    int  m_secNum;     // 计数器数字
    bool m_direction; // 主页Logo移动方向，向右为true
    bool m_isItemPage;// 是否是管理页面

};


