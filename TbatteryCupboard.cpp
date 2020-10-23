#include "TbatteryCupboard.h"
#include "ui_tbatterycupboard.h"
const int ITEM_PAGE_BACK_TIME = 3000;
extern int g_VolValue;
TbatteryCupboard::TbatteryCupboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TbatteryCupboard)
  ,m_timer(new QTimer(this))
  //,m_moveLabel(new rollLabel)
  ,m_moveBtn(new QToolButton)
  ,m_keyBoard(new TkeyBoard)
  ,m_sound(NULL)
  ,m_pos(10)
  ,m_secNum(ITEM_PAGE_BACK_TIME)
  ,m_direction(true)
  ,m_isItemPage(false)
{
    ui->setupUi(this);
    m_keyBoard->hide();

   //m_keyBoard->setParent(ui->kbwidgetN);
    //m_keyBoard->resize(ui->kbwidgetN->width(),ui->kbwidgetN->height());
    m_timeId = 0;
    m_moveBtn->setParent(ui->widget_4);
    //m_moveLabel->setParent(ui->widget_3);
   // m_moveLabel->resize(300,40);
    //m_moveLabel->setStyleSheet("background-color:red;border:1px;");
    this->setWindowTitle(QObject::tr("拓邦换电"));
    this->resize(1280, 720);
    ui->stackedWidget->setCurrentWidget(ui->mainpage);
    //connect(ui->checkBatteryBtn,SIGNAL(clicked(bool)),this,SLOT(SlotCheckBatteryBtnClicked()));
    connect(ui->helpBtn,&QToolButton::clicked,[=](){
       ui->stackedWidget->setCurrentWidget(ui->helpbackgroundpage);
    });
    connect(ui->helpReturnBtn,&QPushButton::clicked,[=](){
       ui->stackedWidget->setCurrentWidget(ui->mainpage);
    });
   //ui->sceneWdt->setScene(&m_mainScene);
   //setMainScene();
    setMoveBtn();
    dealItem();
}

TbatteryCupboard::~TbatteryCupboard()
{
    delete ui;
}

void TbatteryCupboard::setMainScene()
{

    QRectF rect(0,0,this->width(),this->height());
    QGraphicsRectItem *parent = m_mainScene.addRect(rect);
    //parent->setPen(Qt::NoPen);
    //parent->setZValue(1);

    //background
    QGraphicsPixmapItem *background = m_mainScene.addPixmap(QPixmap(":/image/background.png"));
    background->setParentItem(parent);
    background->setZValue(0);
}

void TbatteryCupboard::resizeEvent(QResizeEvent *)
{
    //m_moveLabel->setParent(ui->widget_3);
    //m_moveLabel->resize(ui->widget_3->width(),40);

    /*ui->helpBtn->move(this->width()-ui->helpBtn->width(),this->height()-ui->helpBtn->height());
    ui->checkBatteryBtn->move(this->width()/3-ui->checkBatteryBtn->width()/2,this->height()-ui->checkBatteryBtn->height()-40);*/
    ui->helpReturnBtn->move((this->width()*7/8-ui->helpReturnBtn->width()),this->height()*3/4-ui->helpReturnBtn->height());
    m_keyBoard->setFixedSize(ui->kbwidgetN->width(),ui->kbwidgetN->height());
    //m_moveLabel->resize(ui->widget_3->width(),40);
}

void TbatteryCupboard::setMoveBtn()
{

    m_moveBtn->setStyleSheet("border-image:url(:/image/check.png)");
    m_moveBtn->setFixedSize(200,80);
    //m_moveBtn->setDefault(false);
    m_moveBtn->move(m_pos,ui->widget_4->height()/2);
    //QTimer*timer = new QTimer(this);
    connect(m_moveBtn,&QToolButton::clicked,[=](){
        //qDebug()<<"this moveBtn clicked";
        ui->stackedWidget->setCurrentWidget(ui->batteryPage);
        m_isItemPage = true;
    });
    connect(m_timer,SIGNAL(timeout()),SLOT(Slotpro()));
    m_timer->start(50);

    connect(ui->backtoMainPageBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentWidget(ui->mainpage);
        if(m_secNum!= ITEM_PAGE_BACK_TIME)
        {
            m_secNum = ITEM_PAGE_BACK_TIME;
        }
    });

    /*ui->scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
          "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
          "QScrollBar::handle:hover{background:green;}"
          "QScrollBar::sub-line{background:transparent;}"
          "QScrollBar::add-line{background:transparent;}");*/
    connect(ui->delayBtn,SIGNAL(SigMousePress()),this,SLOT(SlotSmartButtonPress()));
    connect(ui->delayBtn,SIGNAL(SigDoubleClicked()),this,SLOT(SlotSmartButtonDoubleClicked()));


    connect(ui->backtoBatteryBtn,&QPushButton::clicked,[=](){
         ui->stackedWidget->setCurrentWidget(ui->batteryPage);

             m_isItemPage = true;
             m_secNum = ITEM_PAGE_BACK_TIME;


    });

   // connect(ui->backtoBatteryBtn,SIGNAL(SigDoubleClicked()),this,SLOT(SlotSmartButtonDoubleClicked()));

}

void TbatteryCupboard::dealItem()
{
    connect(ui->changeIp,&QToolButton::clicked,[=](){
        ui->stackedWidget_2->setCurrentWidget(ui->inputPasswordPage);
    });

    connect(ui->backBtnInChangeIp,&QToolButton::clicked,[=](){

        ui->stackedWidget_2->setCurrentWidget(ui->itemPage);
    });

    connect(ui->offlineBtn,&QToolButton::clicked,[=](){
        ui->stackedWidget->setCurrentWidget(ui->offlinepage);
        if(!m_keyBoard->isVisible())
        {
            m_keyBoard->setParent(ui->kbwidgetN);
            m_keyBoard->show();
            m_keyBoard->setFixedSize(ui->kbwidgetN->width(),ui->kbwidgetN->height());
        }
    });
    connect(m_keyBoard,SIGNAL(SigSendCmd(QString,SPEICAL_BUTTON_TYPE)),this,SLOT(SlotGetCmdFromKeyBoard(QString,SPEICAL_BUTTON_TYPE)));
    connect(ui->offlinebacktomainBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentWidget(ui->mainpage);
        if(m_keyBoard->isVisible())
        {
            m_keyBoard->hide();
        }
    });

    connect(ui->changeVolBacktoItemBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget_2->setCurrentWidget(ui->itemPage);
    });
    connect(ui->changeVolBtnInItem,&QToolButton::clicked,[=](){
        ui->stackedWidget_2->setCurrentWidget(ui->changeVolPage);
    });
    connect(ui->checkStatusBtn,&QToolButton::clicked,[=](){
        ui->stackedWidget_2->setCurrentWidget(ui->scrollpage);
    });
}

void TbatteryCupboard::SlotGetCmdFromKeyBoard(QString cmd,SPEICAL_BUTTON_TYPE type)
{
    //ui->deviceNamelineEdit->setFocus();
    /*if(type == SPEICAL_BUTTON_CHANGED)
    {

    }
    else if(type == SPEICAL_BUTTON_DELETE_ONE)
    {
        ui->deviceNamelineEdit->del();
    }
    else if(type == SPEICAL_BUTTON_CLEAR_ALL)
    {
        ui->deviceNamelineEdit->clear();
    }
    else
    {
        //ui->deviceNamelineEdit->insert(cmd);
        ui->passwdlineEdit->insert(cmd);
    }*/

}

void  TbatteryCupboard::Slotpro()
{
    ui->widget_3->flushPos();
    //if(m_moveLabel)
    //{

       // m_moveLabel->flushPos();
    //}
    if(m_isItemPage)
    {
        //m_secNum = ITEM_PAGE_BACK_TIME;
        QString str = QString::number(m_secNum/20);
        ui->alarmWdt->setLabelText(str);

        m_secNum--;
        if(m_secNum == 0)
        {
            ui->stackedWidget->setCurrentWidget(ui->mainpage);
            m_isItemPage = false;
            m_secNum = ITEM_PAGE_BACK_TIME;
        }
    }


    if(m_pos<=ui->widget_4->width()/5&&m_direction)
    {

            m_pos+=1;

            //qDebug()<<"向右移动";
            //qDebug()<<"m_pos = "<<m_pos;

    }
    else
    {
       // qDebug()<<"向左移动";
        //qDebug()<<"m_pos = "<<m_pos;
        m_direction = false;
        m_pos-=1;
        if(m_pos<=10)
        {
            m_direction = true;
        }
    }
    m_moveBtn->move(m_pos,ui->widget_4->height()/2-m_moveBtn->height()/2);
}
void TbatteryCupboard::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_timeId)
    {
        m_timeId = startTimer(1000);
        //qDebug()<<"this is timeevent";
    }
}
void TbatteryCupboard::SlotCheckBatteryBtnClicked()
{
    qDebug()<<"查看电池";
}

void TbatteryCupboard::SlotSmartButtonDoubleClicked()
{
    qDebug()<<"smart btn 2 clicked";
    ui->stackedWidget->setCurrentWidget(ui->secondpage);
    //m_isItemPage = true;

}

void TbatteryCupboard::SlotSmartButtonPress()
{
    qDebug()<<"this delay btn clikec";
    //ui->stackedWidget->setCurrentWidget(ui->secondpage);
}
