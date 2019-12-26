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

#ifndef SEEKHELPWIDGET_H
#define SEEKHELPWIDGET_H

#include <QWidget>
#include <DMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <DSpinner>
#include <DLabel>
#include <DSuggestButton>
#include <QTimer>


DWIDGET_USE_NAMESPACE

class MainWindow;

class SeekHelpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SeekHelpWidget(QWidget *parent = nullptr);
    ~SeekHelpWidget();

private:
    void initUI();
    QWidget *generateVarifyCodeWidget();
    QWidget *varifyCodeWidget();
    QWidget *successCopyWidget();
    QWidget *wrapLayout(QLayout *layout);


private slots:
    void respSuggestButton();
    void handleTimeout();

 signals:
    void backMainWindow();


private:
    QStackedWidget *m_pStackedWidget;
    QVBoxLayout *m_mainVLayout;

    QWidget *m_pGenerateVarifyCodeWidget;
    QVBoxLayout *m_pGenerateVarifyVLayout;
    DSpinner *m_loadSpinner;
    DLabel *m_generateCodeLabel;

    QWidget *m_pVarifyCodeWidget;
    QVBoxLayout *m_pVarifyCodeVLayout;
    DLabel *m_pVerifyCodeLabel;
    DLabel *m_pVerifyCodeTipsLabel;

    QWidget *m_pSuccessCopyWidget;
    QVBoxLayout *m_pSuccessCopyVLayout;
    DLabel *m_pSuccessCopyLabel;
    DLabel *m_pSuccessCopyTipsLabel;

    DSuggestButton *m_suggestButton;
public:
        QTimer *m_pTimer;

private:
    bool bFlag;
    int firstIndex;
    MainWindow *m_pMainWindow;
    QString str;

public:
    QString generateRandomNumber();
    QString setVarifyCode();

};

#endif // SEEKHELPWIDGET_H
