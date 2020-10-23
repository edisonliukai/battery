#pragma once

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>
#include <QMouseEvent>
#include<QVBoxLayout>
#include<QToolButton>
#include<QHBoxLayout>
#include<QGridLayout>
#include"Tbattery.h"
class TscrollableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TscrollableWidget(QWidget *parent = nullptr);

    void initWidgetInfo();

    void resizeEvent(QResizeEvent *);
protected:
        void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
        void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
signals:

public slots:
private:
        QScrollArea*    m_scrollArea;
        QWidget*        m_scrollWidget;

        bool            m_ifMousePressed;
        QPoint          m_mousePressPosition;
       QGridLayout      *m_layout;
       Tgroup          *m_btn[8];
};

