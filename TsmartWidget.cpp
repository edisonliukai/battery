#include "TsmartWidget.h"

TsmartButton::TsmartButton(QWidget *parent) : QWidget(parent)
{
  //this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    this->setStyleSheet("background-color: blue");
}

void TsmartButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        emit SigDoubleClicked();
    }
}


void TsmartButton::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"prss";
    if(event->button() == Qt::LeftButton)
    {
        emit SigMousePress();
    }
}

void TimerLabel::setLabelText(QString text)
{
   m_label.setText(text);
}

TimerLabel::TimerLabel(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet("font-size:30px;background-color: rgb(173, 127, 160);");
    m_layout.addWidget(&m_widget);
    m_layout.addWidget(&m_label);
    m_layout.setStretch(0,1);
    m_layout.setStretch(1,1);
    m_label.setAlignment(Qt::AlignCenter);
    m_layout.setSpacing(0);
    m_widget.setStyleSheet("border-image: url(:/image/alarm.png);border-top-left-radius:15px;border-bottom-left-radius:15px");
    m_label.setText("120");
    setLayout(&m_layout);

}
