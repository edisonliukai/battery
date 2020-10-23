#include "TkeyBoard.h"
#include "ui_TkeyBoard.h"
#include<QDebug>

QString g_name[ALL_KEY_NUM]={
    "1","2","3","4","5","6","7","8","9","0",
    "q","w","e","r","t","y","u","i","o","p",
    "a","s","d","f","g","h","j","k","l","大",
    "z","x","c","v","b","n","m","符号","×","del"
    };
QString g_ch[37] ={
    "1","2","3","4","5","6","7","8","9","0",
    "!","@","#","$","%","^","&&","*","(",")",
    "~","[","]","{","}","+","-","=",":",";",
    ",",".","?","<",">","/","'"
};
TkeyBoard::TkeyBoard(QWidget *parent) :
    QWidget(parent)
  ,m_currentFocus(NULL)
  ,m_vlayout(new QVBoxLayout)
  ,m_layout(new QGridLayout)
  ,m_widget(new QWidget(this))
  ,m_keyCmd(" ")
    //,ui(new Ui::TkeyBoard)
{
    //ui->setupUi(this);
    this->setStyleSheet("QWidget{background-color:black;QFont::Bold}"

    "QToolButton{color:black;background-color: rgb(173, 127, 168);border-radius:2px}"
    "QToolButton:hover{color:green;background-color: rgb(245, 121, 0);border: 3px solid rgb(11 , 137 , 234);font-size:20px}"
    "QToolButton:pressed{color:red;background-color: rgb(245, 121, 0);border: 1px solid rgb(12 , 138 , 235);padding-left:5px;padding-top:5px;}"
    );
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(SlotCurrentFcousChanged(QWidget *, QWidget *)));
    m_keyFun  = KEY_SMALL;
    initKeyboardInfo();


}

TkeyBoard::~TkeyBoard()
{
    //delete ui;
    //if(!m_btnInfo.empty())
    //{
       // m_btnInfo.clear();
    //}
    for(int i=0;i<40;++i)
    {
        if(m_btn[i])
        {
            delete m_btn[i];
            m_btn[i] = NULL;
        }
    }

    if(m_layout)
    {
        delete m_layout;
        m_layout = NULL;
    }
    if(m_widget)
    {
        delete m_widget;
        m_widget = NULL;
    }
    if(m_vlayout)
    {
        delete m_vlayout;
        m_widget = NULL;
    }
}

void TkeyBoard::initKeyboardInfo()
{

     this->setLayout(m_vlayout);
     m_vlayout->addWidget(m_widget);
     m_vlayout->setSpacing(4);
     m_vlayout->setContentsMargins(4,4,4,4);
        for(int i = 0;i<40;++i)
        {
            QString name = QString::number(i);
            m_btn[i] = new QToolButton;
            m_btn[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
            m_btn[i]->setObjectName(name);
            m_btn[i]->setText(g_name[i]);
            m_layout->addWidget(m_btn[i],i/10,i%10,1,1);
            m_layout->setSpacing(4);
            m_layout->setContentsMargins(4,4,4,4);
            connect(m_btn[i],SIGNAL(clicked(bool)),this,SLOT(SlotKeyBoardClicked()));
        }

    m_widget->setLayout(m_layout);

}

void TkeyBoard::changekeyFun(KEY_POS_FUN fun)
{

        for(int i = 10;i<37;++i)
        {
            if(i!=29)
            {
                if(fun == KEY_BIG)
                {
                   m_btn[i]->setText(g_name[i].toUpper());
                }
                else if(fun == KEY_SMALL)
                {
                   m_btn[i]->setText(g_name[i].toLower());
                }
                else if(fun == KEY_CH)
                {
                   m_btn[i]->setText(g_ch[i]);
                }
            }
        }

}
void TkeyBoard::SlotKeyBoardClicked()
{

    QObject*obj = sender();
    m_keyCmd = obj->objectName();
    if(m_keyCmd == QString::number(SPEICAL_BUTTON_CHANGED))
    {

        if(m_keyFun == KEY_SMALL)
        {

            changekeyFun(KEY_BIG);
            m_keyFun = KEY_BIG;
            m_btn[29]->setText("小");
            qDebug()<<"changed daxiaoxie";
        }
        else if(m_keyFun == KEY_BIG)
        {
            changekeyFun(KEY_SMALL);
            m_keyFun = KEY_SMALL;
            m_btn[29]->setText("大");
        }
        else
        {
            m_keyFun = KEY_SMALL;
        }

        return;
    }
    else if(m_keyCmd == QString::number(SPEICAL_BUTTON_CH))
    {
        //emit SigSendCmd(m_keyCmd,SPEICAL_BUTTON_CH);
        changekeyFun(KEY_CH);

    }
    else if(m_keyCmd == QString::number(SPEICAL_BUTTON_CLEAR_ALL))
    {
        qDebug()<<"clear all ";

    }
    else if(m_keyCmd == QString::number(SPEICAL_BUTTON_DELETE_ONE))
    {
        qDebug()<<"delete one";
        emit SigSendCmd(m_keyCmd,SPEICAL_BUTTON_DELETE_ONE);
       if(m_currentFocus)
       {
           m_currentFocus->backspace();
       }
    }
    else if(m_keyCmd == SPEICAL_BUTTON_DELETE_OTHER)
    {
        emit SigSendCmd(m_keyCmd,SPEICAL_BUTTON_DELETE_OTHER);
        if(m_currentFocus)
        {
            qDebug()<<"m_ccurfous is not null";
            m_currentFocus->insert(m_keyCmd);
        }
    }

}

 void TkeyBoard::SlotCurrentFcousChanged(QWidget*,QWidget*current)
 {
     if(!this->isVisible())
     {
         return;
     }
     if (current && !this->isAncestorOf(current))
     {
         qDebug()<<"fcous changed";
         if(!m_currentFocus)
         {
             m_currentFocus = (QLineEdit*)current;
         }
     }
     else
     {
         qDebug()<<"nothing changed";
     }
 }
