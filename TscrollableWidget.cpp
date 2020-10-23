#include "TscrollableWidget.h"

TscrollableWidget::TscrollableWidget(QWidget *parent) : QWidget(parent)
  ,m_scrollArea(new QScrollArea(this))
  ,m_scrollWidget(NULL)
  ,m_ifMousePressed(false)
  ,m_layout(new QGridLayout)
{
   initWidgetInfo();
}

void TscrollableWidget::initWidgetInfo()
{
    if(!m_scrollArea)
    {
        return;
    }
    m_scrollWidget = new QWidget(m_scrollArea);
    if(!m_scrollWidget)
    {
        return;
    }
    m_scrollArea->setFixedSize(this->width(),this->height());
    m_scrollWidget->setFixedSize(m_scrollArea->width(),m_scrollArea->height()*2);
    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollArea->setAlignment(Qt::AlignCenter);
    // 隐藏滑动块
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
              "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
              "QScrollBar::handle:hover{background:green;}"
              "QScrollBar::sub-line{background:transparent;}"
              "QScrollBar::add-line{background:transparent;}");
    m_scrollArea->move(0, 0);
    m_scrollWidget->move(0, 0);
  for(int j=0;j<2;++j)
  {
    for(int i = 0;i<8;++i)
    {
        m_btn[i] = new Tgroup(this);
        m_btn[i]->setStyleSheet("background-color: rgb(233, 185, 110);border-radius:30px;");


        m_layout->addWidget(m_btn[i],i,j,1,1);
        //m_btn[i]->show();
    }
  }
    m_scrollWidget->setLayout(m_layout);
}

void TscrollableWidget::resizeEvent(QResizeEvent *)
{
    m_scrollArea->setFixedSize(this->width(),this->height());
    m_scrollWidget->setFixedSize(m_scrollArea->width(),m_scrollArea->height()*2);
}

void TscrollableWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_ifMousePressed)
    {
        return;
    }

    QPoint currentPos = e->pos();

    int distance = m_mousePressPosition.y() - currentPos.y();

    m_scrollArea->verticalScrollBar()->setValue(m_scrollArea->verticalScrollBar()->value() + distance);

    m_mousePressPosition = currentPos;
}

void TscrollableWidget::mousePressEvent(QMouseEvent *e)
{
    m_ifMousePressed = true;
    // 记录鼠标按下的位置
    m_mousePressPosition = e->pos();
}

void TscrollableWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    m_ifMousePressed = false;
    // reset
    m_mousePressPosition.setX(0);
    m_mousePressPosition.setY(0);
}
