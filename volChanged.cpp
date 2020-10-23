#include "volChanged.h"
#include "ui_volChanged.h"
#include "TbatteryCupboard.h"
qreal g_VolValue;

volChanged::volChanged(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::volChanged)
  ,m_soundEffect(new QSoundEffect)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->progressBar,SLOT(setValue(int)));
    connect(ui->progressBar,SIGNAL(valueChanged(int)),this,SLOT(SlotSetVol(int)));

    connect(ui->volIncreaseBtn,&QToolButton::clicked,[=](){
        // qDebug()<<"vol is "<<g_VolValue/100;
        int value = ui->progressBar->value();
        value+=10;
        if(value>100)
        {
            value = 100;
        }
        ui->progressBar->setValue(value);
       playVol("usr/task/wav/Cmd40Action1.wav");
    });
    connect(ui->volDecreaseBtn,&QToolButton::clicked,[=](){
         //qDebug()<<"vol is "<<g_VolValue/100;
        int value = ui->progressBar->value();
        value-=10;
        if(value<0)
        {
            value = 0;
        }
        ui->progressBar->setValue(value);
        playVol("usr/task/wav/Cmd40Action1.wav");
    });
}

volChanged::~volChanged()
{
    delete ui;
}

void volChanged::SlotSetVol(int value)
{
    qDebug()<<"value is "<<value;
    if(value<=0)
    {
        value = 0;
    }
    else if(value >100)
    {
        value = 100;
    }
    else
    {
        g_VolValue = value/10;

    }
    g_VolValue/=10;
}

void volChanged::playVol(QString path)
{
    if(!m_soundEffect)
    {
        return;
    }
    m_soundEffect->setSource(QUrl::fromLocalFile(path));
    m_soundEffect->setVolume(g_VolValue);
    m_soundEffect->play();
}
