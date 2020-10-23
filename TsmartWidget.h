#pragma once
#include<QWidget>
#include <QObject>
#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
#include<QLabel>
#include<QHBoxLayout>
/****智能按钮 ，实际是继承widget重写单击，双击，长按事件***/
class TsmartButton : public QWidget
{
    Q_OBJECT
public:
    explicit TsmartButton(QWidget *parent = nullptr);
public:
    //
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void SigDoubleClicked();
    void SigMousePress();
public slots:

};

class TimerLabel : public QWidget
{
    Q_OBJECT
public:
    explicit TimerLabel(QWidget *parent = nullptr);
    void setLabelText(QString text);
private:
    QHBoxLayout m_layout;
    QLabel m_label;
    QWidget m_widget;
};
