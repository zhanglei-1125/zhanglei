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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <DLabel>
#include <DToolButton>
#include <QStackedWidget>
#include <DTitlebar>
#include "seekhelpwidget.h"
#include "helpotherswidget.h"


DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    int firstIndex;

private:
    QStackedWidget *m_pStackedWidget;
    QWidget *m_pMainwidget;
    QVBoxLayout *m_mainVLayout;
    DLabel *m_svgLabel;
    DLabel *m_tipsLabel;
    DToolButton *m_seekHelpButton;
    DToolButton *m_helpOthersButton;
private:
    SeekHelpWidget *m_pSeekHelpWidget;
    HelpOthersWidget *m_pHelpOthersWidget;

private slots:
    void respSeekHelpButton();
    void respHelpOthersButton();
    void showMainWindow();

private:
    DTitlebar *tit;
    DWidget *head;
    DLabel * left;
    DLabel * right;

public:
    void setAppTitle(const QString &path,const QString &name);
};

#endif // MAINWINDOW_H
