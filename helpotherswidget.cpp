/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     zhanglei <zhanglei_cm@deepin.com>
 *
 * Maintainer: zhanglei <zhanglei_cm@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "helpotherswidget.h"
#include <QMessageBox>
#include <QDebug>
#include <QValidator>

#define TIMER_TIMEOUT   (3*1000)

HelpOthersWidget::HelpOthersWidget(QWidget *parent)
    : QWidget(parent),firstIndex(0)
{
    m_pSeekHelp = new SeekHelpWidget;
    initUI();
    connect(m_suggestButton, &DSuggestButton::pressed, this, &HelpOthersWidget::respSuggestButton);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

}

void HelpOthersWidget::initUI()
{
    m_pStackedWidget = new QStackedWidget;
    m_mainVLayout = new QVBoxLayout;
    m_suggestButton = new DSuggestButton;
    m_suggestButton->setText("取消");
    m_suggestButton->setFixedWidth(120);
    inputVarifyCodeWidget();
    connectWidget();
    connectFailedWidget();
    disConnectWidget();
    m_pStackedWidget->addWidget(m_InputWidget);
    m_pStackedWidget->addWidget(m_pConnectWidget);
    m_pStackedWidget->addWidget(m_pConnectFailedWidget);
    m_pStackedWidget->addWidget(m_pDisconnectWidget);
    m_pStackedWidget->setCurrentWidget(m_InputWidget);

    //获取当前页面的序号
    firstIndex = m_pStackedWidget->currentIndex();

    m_mainVLayout->addWidget(m_pStackedWidget);
    m_mainVLayout->addWidget(m_suggestButton, 0, Qt::AlignCenter);
    m_mainVLayout->setContentsMargins(0, 30, 0, 30);
    setLayout(m_mainVLayout);

}

QWidget *HelpOthersWidget::inputVarifyCodeWidget()
{
    m_InputWidget = new QWidget;
    m_pVarifyCodeVLayout = new QVBoxLayout;
    m_pVerifyCodeLineEdit = new QLineEdit;
    m_pVerifyCodeLineEdit->setFixedWidth(320);
    ///////////////////////////////////////////

    class QValidator *validator = new QIntValidator(0,999999,this);

    m_pVerifyCodeLineEdit->setAlignment( Qt::AlignCenter);
    m_pVerifyCodeLineEdit->setFont(QFont( "Timers" , 28 ,  QFont::Thin));
    m_pVerifyCodeLineEdit->setValidator(validator);
    m_pVerifyCodeLineEdit->setPlaceholderText("输入六位数字");



    m_pVerifyCodeTipsLabel = new DLabel;

    m_pVarifyCodeVLayout->addWidget(m_pVerifyCodeLineEdit, 0, Qt::AlignCenter);
    m_pVarifyCodeVLayout->addWidget(m_pVerifyCodeTipsLabel, 0, Qt::AlignCenter);

    QFont font ("Microsoft YaHei", 8, 0); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    m_pVerifyCodeTipsLabel->setFont(font);
    m_pVerifyCodeTipsLabel->setText("请在上方输入你想帮助的人提供给你的验证码，完成后点击连接开始\n协助对方");
    m_pVerifyCodeTipsLabel->setAlignment(Qt::AlignCenter);

   // connect(m_pVerifyCodeLineEdit, &QLineEdit::textChanged, this, &HelpOthersWidget::lineEditChange);

   connect(m_pVerifyCodeLineEdit, &QLineEdit::textChanged, this,
                  [=](const QString &text)
    {
        qDebug()<<"***********";
        qDebug()<<"lineEdit"<<text;
        //////////////////
        class QValidator *validator = new QIntValidator(0,999999,this);

        m_pVerifyCodeLineEdit->setAlignment( Qt::AlignCenter);
        m_pVerifyCodeLineEdit->setFont(QFont( "Timers" , 28 ,  QFont::Thin));
        m_pVerifyCodeLineEdit->setValidator(validator);

        qDebug()<<"count"<<text.count();
        if(text.count() == 6)
        {
            m_suggestButton->setText("连接");
        }
    });

    m_InputWidget->setLayout(m_pVarifyCodeVLayout);

    return m_InputWidget;
}

QWidget *HelpOthersWidget::connectWidget()
{
    m_pConnectWidget = new QWidget;
    m_pConnectVLayout = new QVBoxLayout;
    m_pConnectSpinner = new DSpinner;
    m_pConnectSpinner->setFixedSize(32, 32);
    m_pConnectSpinner->start();
    m_pConnectTipsLabel = new DLabel;
    QFont font ("Microsoft YaHei", 8, 0); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    m_pConnectTipsLabel->setFont(font);
    m_pConnectTipsLabel->setText("正在等待连接，请稍后...");
    m_pConnectVLayout->addWidget(m_pConnectSpinner, 0, Qt::AlignCenter);
    m_pConnectVLayout->addWidget(m_pConnectTipsLabel, 0, Qt::AlignCenter);
    m_pConnectWidget->setLayout(m_pConnectVLayout);
    return m_pConnectWidget;
}

QWidget *HelpOthersWidget::connectFailedWidget()
{
     m_pConnectFailedWidget = new QWidget;
     m_pConnectFailedVLayout  = new QVBoxLayout;
     m_pConnectFailedLabel = new DLabel;
     m_pConnectFailedTipsLabel = new DLabel;
     QFont font ("Microsoft YaHei", 8, 0); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
     m_pConnectFailedLabel->setFont(font);
     m_pConnectFailedTipsLabel->setFont(font);
     m_pConnectFailedLabel->setText("连接失败");
     m_pConnectFailedTipsLabel->setText("网络连接状态不是很稳定，点击重试按钮再次尝试连接");
      m_pConnectFailedTipsLabel->setAlignment(Qt::AlignCenter);

     m_pConnectFailedVLayout->addWidget(m_pConnectFailedLabel, 0, Qt::AlignCenter);
     m_pConnectFailedVLayout->addWidget(m_pConnectFailedTipsLabel, 0, Qt::AlignCenter);
     m_pConnectFailedWidget->setLayout(m_pConnectFailedVLayout);
     return m_pConnectFailedWidget;

}

QWidget *HelpOthersWidget::disConnectWidget()
{
    m_pDisconnectWidget = new QWidget;
    m_pDisconnectVLayout  = new QVBoxLayout;
    m_pDisconnectLabel = new DLabel;
    m_pDisconnectTipsLabel = new DLabel;
    QFont font ("Microsoft YaHei", 8, 0); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    m_pDisconnectLabel->setFont(QFont("Microsoft YaHei", 12, 0));
    m_pDisconnectTipsLabel->setFont(font);
    m_pDisconnectLabel->setText("您正在进行远程协助");
    m_pDisconnectTipsLabel->setText("当前已经有一个连接会话，如果您想建立新的连接，请先断开");
    m_pDisconnectTipsLabel->setAlignment(Qt::AlignCenter);

    m_pDisconnectVLayout->addWidget(m_pDisconnectLabel, 0, Qt::AlignCenter);
    m_pDisconnectVLayout->addWidget(m_pDisconnectTipsLabel, 0, Qt::AlignCenter);
    m_pDisconnectWidget ->setLayout(m_pDisconnectVLayout);
    return m_pDisconnectWidget;
}

void HelpOthersWidget::respSuggestButton()
{
    if(m_pTimer->isActive()){
        m_pTimer->stop();
    }

     //m_pStackedWidget->setCurrentWidget(m_InputWidget);

    if((m_suggestButton->text().compare(QString::fromLocal8Bit("取消"))  == 0) || (m_suggestButton->text().compare(QString::fromLocal8Bit("断开"))== 0))
    {
       m_suggestButton->setText("取消");
         m_pStackedWidget->setCurrentWidget(m_InputWidget);
       emit backMainWindow();
    }
    if(m_suggestButton->text().compare(QString::fromLocal8Bit("重试"))  == 0)
    {
       m_suggestButton->setText("取消");
       m_pStackedWidget->setCurrentWidget(m_InputWidget);
    }

    if(m_suggestButton->text().compare(QString::fromLocal8Bit("连接"))  == 0)
    {
        qDebug()<<"======"<<m_strValifyCode<<m_pVerifyCodeLineEdit->text();
        if(m_strValifyCode.compare(m_pVerifyCodeLineEdit->text()) == 0)
        {
            qDebug()<<"Enter timeout processing function\n";
            m_pStackedWidget->setCurrentWidget(m_pConnectWidget);
            m_suggestButton->setText("取消");
            m_pTimer->start(TIMER_TIMEOUT);
        }
        else {
            qDebug()<<"retry";
            m_suggestButton->setText("重试");
            m_pStackedWidget->setCurrentWidget(m_pConnectFailedWidget);

        }
    }
   // m_suggestButton->setText("取消");
    m_pVerifyCodeLineEdit->setText("");
}

QWidget *HelpOthersWidget::wrapLayout(QLayout *layout)
{
    auto wrapWidget = new QWidget;
    wrapWidget->setLayout(layout);
    return wrapWidget;
}

void HelpOthersWidget::handleTimeout()
{
    qDebug()<<"+++++++";
    if(m_pTimer->isActive()){
        m_pTimer->stop();
    }
    m_suggestButton->setText("断开");
    m_pStackedWidget->setCurrentWidget(m_pDisconnectWidget);

}

QString HelpOthersWidget::getVarifyCode(const QString str)
{
    qDebug()<<"str"<<str;
    m_strValifyCode = str;
    return m_strValifyCode;
}

