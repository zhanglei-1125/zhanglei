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

#ifndef HELPOTHERSWIDGET_H
#define HELPOTHERSWIDGET_H

#include <QWidget>
#include <DMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <DLabel>
#include <DSpinner>
#include <DSuggestButton>

#include "seekhelpwidget.h"


DWIDGET_USE_NAMESPACE

class HelpOthersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HelpOthersWidget(QWidget *parent = nullptr);

private:
    void initUI();
    QWidget *inputVarifyCodeWidget();
    QWidget *connectWidget();
    QWidget *connectFailedWidget();
    QWidget *disConnectWidget();
    QWidget *wrapLayout(QLayout *layout);
    int firstIndex;
private:
    SeekHelpWidget *m_pSeekHelp;
    QTimer *m_pTimer;

private:

    QStackedWidget *m_pStackedWidget;
    QVBoxLayout *m_mainVLayout;

    QWidget *m_InputWidget;
    QVBoxLayout *m_pVarifyCodeVLayout;
    QLineEdit *m_pVerifyCodeLineEdit;
    DLabel *m_pVerifyCodeTipsLabel;

    QWidget *m_pConnectWidget;
    QVBoxLayout *m_pConnectVLayout;
    DSpinner *m_pConnectSpinner;
    DLabel *m_pConnectTipsLabel;

    QWidget *m_pConnectFailedWidget;
    QVBoxLayout *m_pConnectFailedVLayout;
    DLabel *m_pConnectFailedLabel;
    DLabel *m_pConnectFailedTipsLabel;

    QWidget *m_pDisconnectWidget;
    QVBoxLayout *m_pDisconnectVLayout;
    DLabel *m_pDisconnectLabel;
    DLabel *m_pDisconnectTipsLabel;

    DSuggestButton *m_suggestButton;

signals:
   void backMainWindow();

private slots:
    void respSuggestButton();
    void handleTimeout();

public:
    QString m_strValifyCode;
    QString getVarifyCode(const QString str);
};

#endif // HELPOTHERSWIDGET_H
