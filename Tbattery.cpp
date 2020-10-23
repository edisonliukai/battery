#pragma execution_character_set("utf-8")

#include "Tbattery.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"
#include<QDebug>
rollLabel::rollLabel(QWidget *parent):QLabel(parent)

{
    this->setStyleSheet("font-size:12;color;red;border:1px;");
    //setMinimumWidth(200);
    //setMinimumHeight(40);
    m_curIndex = 0;
    m_showText = "每一个认真生活的人都值得被认真对待，飞哥换电，绿色出行，您值得拥有!";
    m_charWidth = fontMetrics().width("a")/3;

}


void rollLabel::flushPos()
{
    update();
    m_curIndex++;
    if(m_curIndex*m_charWidth>this->width())
    {
        m_curIndex = 0;
    }
}
void rollLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font;
    QPen pen(Qt::red);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    //font.setPointSize(Y_AXIS_DESC_SIZE);
    font.setFamily("LiSu");
    font.setPixelSize(20);
    //font.setLetterSpacing(QFont::AbsoluteSpacing,0);
    painter.setFont(font);

    painter.drawText(0,30,m_showText.mid(m_curIndex));
    painter.drawText(width()-m_charWidth*m_curIndex,30,m_showText.left(m_curIndex));
}
Tgroup::Tgroup(QWidget *parent): QWidget(parent)
{

   m_layout.addWidget(&m_battery);

   m_layout.addWidget(&m_label);
   m_layout.setStretch(0,2);
   m_layout.setStretch(1,1);
   m_label.setAlignment(Qt::AlignCenter);
   setLayout(&m_layout);
   m_label.setText(tr("正在充电"));
   m_label.setStyleSheet("font-size:20px;color:red");
}

Tbattery::Tbattery(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    alarmValue = 30;
    step = 0.5;

    borderRadius = 8;
    bgRadius = 5;
    headRadius = 3;

    borderColorStart = QColor(100, 100, 100);
    borderColorEnd = QColor(80, 80, 80);
    alarmColorStart = QColor(250, 118, 113);
    alarmColorEnd = QColor(204, 38, 38);
    normalColorStart = QColor(50, 205, 51);
    normalColorEnd = QColor(60, 179, 133);

    isForward = false;
    currentValue = 0;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    valueTimer = new QTimer(this);
    connect(valueTimer, SIGNAL(timeout()), this, SLOT(setCurrentValue()));
    valueTimer->start(1000);
}

Tbattery::~Tbattery()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void Tbattery::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制头部
    drawHead(&painter);
}

void Tbattery::drawBorder(QPainter *painter)
{
    painter->save();

    double headWidth = width() / 10;
    double batteryWidth = width() - headWidth;

    //绘制电池边框
    QPointF topLeft(5, 5);
    QPointF bottomRight(batteryWidth, height() - 5);
    batteryRect = QRectF(topLeft, bottomRight);

    painter->setPen(QPen(borderColorStart, 5));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(batteryRect, borderRadius, borderRadius);

    painter->restore();
}

void Tbattery::drawBg(QPainter *painter)
{
    painter->save();

    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));
    if (currentValue <= alarmValue) {
        batteryGradient.setColorAt(0.0, alarmColorStart);
        batteryGradient.setColorAt(1.0, alarmColorEnd);
    } else {
        batteryGradient.setColorAt(0.0, normalColorStart);
        batteryGradient.setColorAt(1.0, normalColorEnd);
    }

    int margin = qMin(width(), height()) / 20;
    double unit = (batteryRect.width() - (margin * 2)) / 100;
    double width = currentValue * unit;
    QPointF topLeft(batteryRect.topLeft().x() + margin, batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + 5, batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rect, bgRadius, bgRadius);

    painter->restore();
}

void Tbattery::drawHead(QPainter *painter)
{
    painter->save();

    QPointF headRectTopLeft(batteryRect.topRight().x(), height() / 3);
    QPointF headRectBottomRight(width(), height() - height() / 3);
    QRectF headRect(headRectTopLeft, headRectBottomRight);

    QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
    headRectGradient.setColorAt(0.0, borderColorStart);
    headRectGradient.setColorAt(1.0, borderColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(headRectGradient);
    painter->drawRoundedRect(headRect, headRadius, headRadius);

    painter->restore();
}

void Tbattery::updateValue()
{

    /*if (isForward) {
        currentValue -= step;

        if (currentValue <= value) {
            timer->stop();
        }
    } else {
        currentValue += step;

        if (currentValue >= value) {
            timer->stop();
        }
    }

    this->update();*/
}

double Tbattery::getMinValue() const
{
    return this->minValue;
}

double Tbattery::getMaxValue() const
{
    return this->maxValue;
}

double Tbattery::getValue() const
{
    return this->value;
}

double Tbattery::getAlarmValue() const
{
    return this->alarmValue;
}

double Tbattery::getStep() const
{
    return this->step;
}

int Tbattery::getBorderRadius() const
{
    return this->borderRadius;
}

int Tbattery::getBgRadius() const
{
    return this->bgRadius;
}

int Tbattery::getHeadRadius() const
{
    return this->headRadius;
}

QColor Tbattery::getBorderColorStart() const
{
    return this->borderColorStart;
}

QColor Tbattery::getBorderColorEnd() const
{
    return this->borderColorEnd;
}

QColor Tbattery::getAlarmColorStart() const
{
    return this->alarmColorStart;
}

QColor Tbattery::getAlarmColorEnd() const
{
    return this->alarmColorEnd;
}

QColor Tbattery::getNormalColorStart() const
{
    return this->normalColorStart;
}

QColor Tbattery::getNormalColorEnd() const
{
    return this->normalColorEnd;
}

QSize Tbattery::sizeHint() const
{
    return QSize(150, 80);
}

void Tbattery::setCurrentValue()
{
    int num = qrand()%100;
    currentValue = (double)num;

    update();
}
QSize Tbattery::minimumSizeHint() const
{
    return QSize(30, 10);
}

void Tbattery::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        setValue(minValue);
    } else if (value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void Tbattery::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void Tbattery::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void Tbattery::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void Tbattery::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    if (value > currentValue) {
        isForward = false;
    } else if (value < currentValue) {
        isForward = true;
    } else {
        return;
    }

    this->value = value;
    this->update();
    emit valueChanged(value);
    timer->start();
}

void Tbattery::setValue(int value)
{
    setValue((double)value);
}

void Tbattery::setAlarmValue(double alarmValue)
{
    if (this->alarmValue != alarmValue) {
        this->alarmValue = alarmValue;
        this->update();
    }
}

void Tbattery::setAlarmValue(int alarmValue)
{
    setAlarmValue((double)alarmValue);
}

void Tbattery::setStep(double step)
{
    if (this->step != step) {
        this->step = step;
        this->update();
    }
}

void Tbattery::setStep(int step)
{
    setStep((double)step);
}

void Tbattery::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->update();
    }
}

void Tbattery::setBgRadius(int bgRadius)
{
    if (this->bgRadius != bgRadius) {
        this->bgRadius = bgRadius;
        this->update();
    }
}

void Tbattery::setHeadRadius(int headRadius)
{
    if (this->headRadius != headRadius) {
        this->headRadius = headRadius;
        this->update();
    }
}

void Tbattery::setBorderColorStart(const QColor &borderColorStart)
{
    if (this->borderColorStart != borderColorStart) {
        this->borderColorStart = borderColorStart;
        this->update();
    }
}

void Tbattery::setBorderColorEnd(const QColor &borderColorEnd)
{
    if (this->borderColorEnd != borderColorEnd) {
        this->borderColorEnd = borderColorEnd;
        this->update();
    }
}

void Tbattery::setAlarmColorStart(const QColor &alarmColorStart)
{
    if (this->alarmColorStart != alarmColorStart) {
        this->alarmColorStart = alarmColorStart;
        this->update();
    }
}

void Tbattery::setAlarmColorEnd(const QColor &alarmColorEnd)
{
    if (this->alarmColorEnd != alarmColorEnd) {
        this->alarmColorEnd = alarmColorEnd;
        this->update();
    }
}

void Tbattery::setNormalColorStart(const QColor &normalColorStart)
{
    if (this->normalColorStart != normalColorStart) {
        this->normalColorStart = normalColorStart;
        this->update();
    }
}

void Tbattery::setNormalColorEnd(const QColor &normalColorEnd)
{
    if (this->normalColorEnd != normalColorEnd) {
        this->normalColorEnd = normalColorEnd;
        this->update();
    }
}
