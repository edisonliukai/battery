#pragma once

#include <QWidget>
#include<QToolButton>
#include<QMap>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QLineEdit>
const int ALL_KEY_NUM = 40;
enum SPEICAL_BUTTON_TYPE
{
  SPEICAL_BUTTON_CHANGED = 29,
  SPEICAL_BUTTON_CH      = 37,
  SPEICAL_BUTTON_CLEAR_ALL,
  SPEICAL_BUTTON_DELETE_ONE,
  SPEICAL_BUTTON_DELETE_OTHER
};

enum KEY_POS_FUN
{

  KEY_SMALL,
  KEY_BIG,
  KEY_CH
};
namespace Ui {
class TkeyBoard;
}

class TkeyBoard : public QWidget
{
    Q_OBJECT

public:
    explicit TkeyBoard(QWidget *parent = 0);
    ~TkeyBoard();
    void initKeyboardInfo();
    void changekeyFun(KEY_POS_FUN fun);
 signals:
    void SigSendCmd(QString,SPEICAL_BUTTON_TYPE);

public slots:
    void SlotKeyBoardClicked();
    void SlotCurrentFcousChanged(QWidget*,QWidget*current);
private:
    Ui::TkeyBoard *ui;
    QLineEdit *m_currentFocus;
    QVBoxLayout*m_vlayout;
    QGridLayout*m_layout;
    QWidget*m_widget;
    QToolButton* m_btn[ALL_KEY_NUM];
    //std::map<int,QToolButton*>m_btnInfo;
    QString m_keyCmd;
    KEY_POS_FUN m_keyFun;

};


