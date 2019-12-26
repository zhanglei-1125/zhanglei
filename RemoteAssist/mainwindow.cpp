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

#include "mainwindow.h"
#include <QPixmap>
#include <QDebug>

#define TIMER_TIMEOUT   (2*1000)

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    head = nullptr;
    initUI();
    tit= this->titlebar();
    connect(m_seekHelpButton, &DToolButton::pressed, this, &MainWindow::respSeekHelpButton);
    connect(m_helpOthersButton, &DToolButton::pressed, this,  &MainWindow::respHelpOthersButton);
    connect(m_pSeekHelpWidget, &SeekHelpWidget::backMainWindow, this, &MainWindow::showMainWindow);
    connect(m_pHelpOthersWidget, &HelpOthersWidget::backMainWindow, this, &MainWindow::showMainWindow);

}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    m_pStackedWidget = new QStackedWidget(this);
    setCentralWidget(m_pStackedWidget);
    m_pMainwidget = new QWidget;
    m_pSeekHelpWidget = new SeekHelpWidget;
    m_pHelpOthersWidget = new HelpOthersWidget;
    m_mainVLayout = new QVBoxLayout;
    m_svgLabel = new DLabel;
    m_svgLabel->setFixedSize(50, 50);
    QPixmap *pixmap = new QPixmap(":/images/homepage.svg");
    pixmap->scaled(m_svgLabel->size(), Qt::KeepAspectRatio);
    m_svgLabel->setScaledContents(true);
    m_svgLabel->setPixmap(*pixmap);

    m_tipsLabel = new DLabel;
    QFont font ("Microsoft YaHei", 8, 0); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    m_tipsLabel->setFont(font);
    m_tipsLabel->setText("这是由deepin团队开发的远程协助应用，如果您在使\n用的过程中遇到了问题，或者有人求助于你，请点击\n下方的我要求助或帮助别人。");
    m_tipsLabel->setAlignment(Qt::AlignCenter);

    m_seekHelpButton = new DToolButton;
    m_seekHelpButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_seekHelpButton->setText("我要求助");

    m_helpOthersButton = new DToolButton;
    m_helpOthersButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_helpOthersButton->setText("帮助别人");

    //设置图标
    QSize size(30, 20);
    QPixmap hand_pixmap(":/images/hand.svg");
    m_seekHelpButton->setIcon(hand_pixmap);
    m_seekHelpButton->setIconSize(size);
    m_seekHelpButton->setFixedSize(size.width()+100, size.height()+20);


    QFont scan_font = m_seekHelpButton->font();
    scan_font.setPointSize(8);
    m_seekHelpButton->setFont(scan_font);
    m_helpOthersButton->setFont(scan_font);

    //设置图标
    QPixmap heart_pixmap(":/images/heart.svg");
    m_helpOthersButton->setIcon(heart_pixmap);
    m_helpOthersButton->setIconSize(size);
    m_helpOthersButton->setFixedSize(size.width()+100, size.height()+20);

    m_mainVLayout->addWidget(m_svgLabel, 0, Qt::AlignCenter);
    m_mainVLayout->addSpacing(15);
    m_mainVLayout->addWidget(m_tipsLabel, 0, Qt::AlignCenter);
    m_mainVLayout->addSpacing(20);
    m_mainVLayout->addWidget(m_seekHelpButton, 0, Qt::AlignCenter);
    m_mainVLayout->addWidget(m_helpOthersButton, 0, Qt::AlignCenter);

    m_mainVLayout->setContentsMargins(0, 10, 0, 30);

    m_pMainwidget->setLayout(m_mainVLayout);

    //QStackWidget
    m_pStackedWidget->addWidget(m_pMainwidget);
    m_pStackedWidget->addWidget(m_pSeekHelpWidget);
    m_pStackedWidget->addWidget(m_pHelpOthersWidget);
    m_pStackedWidget->setCurrentWidget(m_pMainwidget);

}

void MainWindow::respSeekHelpButton()
{
    m_pStackedWidget->setCurrentWidget(m_pSeekHelpWidget);
    m_pSeekHelpWidget->m_pTimer->start(TIMER_TIMEOUT);
    setAppTitle(":/images/hand.svg", "我要求助");

}

void MainWindow::respHelpOthersButton()
{
    m_pStackedWidget->setCurrentWidget(m_pHelpOthersWidget);
    m_pHelpOthersWidget->getVarifyCode(m_pSeekHelpWidget->setVarifyCode());
    setAppTitle(":/images/heart.svg", "帮助别人");


}

void MainWindow::showMainWindow()
{
    setAppTitle(nullptr, "远程协助");
    m_pStackedWidget->setCurrentWidget(m_pMainwidget);
}


void MainWindow::setAppTitle(const QString &path,const QString &name)
{
    if(!head)
        {
            QImage *ima=new QImage;
            left=new DLabel(this);
            left->setPixmap(QPixmap::fromImage(*ima));
            left->setScaledContents(true);
            left->setFixedSize(16,16);
            right=new DLabel(this);

            QHBoxLayout* myLayout = new QHBoxLayout();
            myLayout->addSpacing(100);
            myLayout->addWidget(left);
            myLayout->addSpacing(5);
            myLayout->addWidget(right);
            myLayout->addStretch(2);

            head = new DWidget(this);
            head->setLayout(myLayout);
            tit->setCustomWidget(head);
        }
        left->setPixmap(QPixmap(path));
        right->setText(name);
}
