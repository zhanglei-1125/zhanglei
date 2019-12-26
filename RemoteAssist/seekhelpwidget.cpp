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

#include "seekhelpwidget.h"
#include <QDebug>
#include <QTime>
#include <qrandom.h>
#include <QApplication>
#include <QClipboard>
#include "mainwindow.h"

SeekHelpWidget::SeekHelpWidget(QWidget *parent)
    : QWidget(parent)
    ,bFlag(false)
{
    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));

    initUI();
    connect(m_suggestButton, &DSuggestButton::clicked, this, &SeekHelpWidget::respSuggestButton);
    //MainWindow m;
  //  connect(&m, &MainWindow::startupTimer, this, &SeekHelpWidget::startTimer);
}

SeekHelpWidget::~SeekHelpWidget()
{

}

void SeekHelpWidget::initUI()
{
     m_pStackedWidget = new QStackedWidget;
     m_mainVLayout = new QVBoxLayout;
     m_suggestButton = new DSuggestButton;
     m_suggestButton->setText("取消");
     m_suggestButton->setFixedWidth(120);
     generateVarifyCodeWidget();
     varifyCodeWidget();
     successCopyWidget();
     m_pStackedWidget->addWidget(m_pGenerateVarifyCodeWidget);
     m_pStackedWidget->addWidget(m_pVarifyCodeWidget);
     m_pStackedWidget->addWidget(m_pSuccessCopyWidget);
     m_pStackedWidget->setCurrentWidget(m_pGenerateVarifyCodeWidget);
     //获取当前页面的序号
     firstIndex = m_pStackedWidget->currentIndex();

     m_mainVLayout->addWidget(m_pStackedWidget);
     m_mainVLayout->addWidget(m_suggestButton, 0, Qt::AlignCenter);
     m_mainVLayout->setContentsMargins(0, 30, 0, 30);
     setLayout(m_mainVLayout);
}

QWidget *SeekHelpWidget::generateVarifyCodeWidget()
{
    m_pGenerateVarifyCodeWidget = new QWidget;
    m_pGenerateVarifyVLayout = new QVBoxLayout;
    m_loadSpinner = new DSpinner;
    m_loadSpinner->setFixedSize(32, 32);
    m_loadSpinner->start();
    m_generateCodeLabel = new DLabel;
    m_generateCodeLabel->setText("正在生成请求验证码，请稍后...");
    m_pGenerateVarifyVLayout->addWidget(m_loadSpinner, 0, Qt::AlignCenter);
    m_pGenerateVarifyVLayout->addWidget(m_generateCodeLabel, 0, Qt::AlignCenter);
    m_pGenerateVarifyCodeWidget->setLayout(m_pGenerateVarifyVLayout);
    return m_pGenerateVarifyCodeWidget;
}

QWidget *SeekHelpWidget::varifyCodeWidget()
{
    m_pVarifyCodeWidget = new QWidget;
    m_pVarifyCodeVLayout = new QVBoxLayout;
    m_pVerifyCodeLabel = new DLabel;
    m_pVerifyCodeTipsLabel = new DLabel;
    m_pVarifyCodeVLayout->addWidget(m_pVerifyCodeLabel, 0, Qt::AlignCenter);
    m_pVarifyCodeVLayout->addWidget(m_pVerifyCodeTipsLabel, 0, Qt::AlignCenter);
    m_pVerifyCodeLabel->setText(" ");
    QFont font ("Microsoft YaHei", 8, 0); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    m_pVerifyCodeLabel->setFont(QFont( "Timers" , 28 ,  QFont::Thin));
    m_pVerifyCodeTipsLabel->setText("要开始共享您的桌面，请将上面的验证码提供给协助您的人员，他们输\n入验证码后，您的共享会话会立即开始");
    m_pVerifyCodeTipsLabel->setAlignment(Qt::AlignCenter);
    m_pVerifyCodeTipsLabel->setFont(font);
    m_pVarifyCodeWidget->setLayout(m_pVarifyCodeVLayout);
    return m_pVarifyCodeWidget;
}

QWidget *SeekHelpWidget::successCopyWidget()
{
    m_pSuccessCopyWidget = new QWidget;
    m_pSuccessCopyVLayout = new QVBoxLayout;
    m_pSuccessCopyLabel = new DLabel;
    m_pSuccessCopyTipsLabel = new DLabel;
    m_pSuccessCopyVLayout->addWidget(m_pSuccessCopyLabel, 0, Qt::AlignCenter);
    m_pSuccessCopyVLayout->addWidget(m_pSuccessCopyTipsLabel, 0, Qt::AlignCenter);
    m_pSuccessCopyLabel->setText("成功复制到剪贴板");
    m_pSuccessCopyTipsLabel->setText("正在等待连接，请稍后...\n连接成功后，此界面会自动隐藏到任务栏");
    m_pSuccessCopyTipsLabel->setAlignment(Qt::AlignCenter);
    m_pSuccessCopyWidget->setLayout(m_pSuccessCopyVLayout);
    return m_pSuccessCopyWidget;
}


void SeekHelpWidget::respSuggestButton()
{
    m_pStackedWidget->setCurrentWidget(m_pGenerateVarifyCodeWidget);
    if(m_suggestButton->text().compare(QString::fromLocal8Bit("取消"))  == 0)
    {
       emit backMainWindow();
    }
    if(m_suggestButton->text().compare(QString::fromLocal8Bit("返回"))  == 0)
    {
        m_suggestButton->setText("取消");
       emit backMainWindow();
    }
    if(m_suggestButton->text().compare(QString::fromLocal8Bit("复制"))  == 0)
    {
        m_suggestButton->setText("返回");
        QClipboard *board = QApplication::clipboard();
        qDebug()<<"back"<<str;
        board->setText(str);
        m_pStackedWidget->setCurrentWidget(m_pSuccessCopyWidget);
    }

}

void SeekHelpWidget::handleTimeout()
{
    qDebug()<<"Enter timeout processing function\n";
    str =generateRandomNumber();
    qDebug()<<"-----str"<<str;
    m_pVerifyCodeLabel->setText(str);
    m_suggestButton->setText("复制");
    m_pStackedWidget->setCurrentWidget(m_pVarifyCodeWidget);


    if(m_pTimer->isActive()){
        m_pTimer->stop();
    }
}

QWidget *SeekHelpWidget::wrapLayout(QLayout *layout)
{
    auto wrapWidget = new QWidget;
    wrapWidget->setLayout(layout);
    return wrapWidget;
}

 QString SeekHelpWidget::generateRandomNumber()
 {
     qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
     return QString::number((qrand() % (999999 - 100000) + 100000));
 }

 QString SeekHelpWidget::setVarifyCode()
 {
    return str;
 }



