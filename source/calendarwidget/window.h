/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include "displaybutton.h"
#include "clock.h"
#include <QWidget>
#include <QDate>
#include <QString>

QT_BEGIN_NAMESPACE
class QCalendarWidget;
class QCheckBox;
class QComboBox;
class QDate;
class QDateEdit;
class QGridLayout;
class QGroupBox;
class QLabel;

QT_END_NAMESPACE

#define Right_Menu

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
private slots:
    void localeChanged(int index);
    void firstDayChanged(int index);
    void selectionModeChanged(int index);
    void horizontalHeaderChanged(int index);
    void verticalHeaderChanged(int index);
    void selectedDateChanged();
    void minimumDateChanged(const QDate &date);
    void maximumDateChanged(const QDate &date);
    void weekdayFormatChanged();
    void weekendFormatChanged();
    void reformatHeaders();
    void reformatCalendarPage();

private:
    void createPreviewGroupBox();
    void createGeneralOptionsGroupBox();
    void createDatesGroupBox();
    void createTextFormatsGroupBox();

    void ReadHistorySettings();
    void WriteCurrentSettings();

    void get_chinese_calendar(QDate english_calendar, QString &outLunarMD, QString &outLunarYear, QString &outLunarMonth, QString &outLunarDay);

    QComboBox *createColorComboBox();

    QGroupBox *previewGroupBox;
    QGridLayout *previewLayout;
    QCalendarWidget *calendar;

    QGroupBox *generalOptionsGroupBox;
    QLabel *localeLabel;
    QLabel *firstDayLabel;
//! [0]
    QLabel *selectionModeLabel;
    QLabel *horizontalHeaderLabel;
    QLabel *verticalHeaderLabel;
    QComboBox *localeCombo;
    QComboBox *firstDayCombo;
    QComboBox *selectionModeCombo;
    QCheckBox *gridCheckBox;
    QCheckBox *navigationCheckBox;
    QComboBox *horizontalHeaderCombo;
    QComboBox *verticalHeaderCombo;

    QGroupBox *datesGroupBox;
    QLabel *currentDateLabel;
    QLabel *minimumDateLabel;
    QLabel *maximumDateLabel;
    QDateEdit *currentDateEdit;
    QDateEdit *minimumDateEdit;
    QDateEdit *maximumDateEdit;
    QPushButton *setBirthday;
    QPushButton *goBirthday;

    QGroupBox *textFormatsGroupBox;
    QLabel *weekdayColorLabel;
    QLabel *weekendColorLabel;
    QLabel *headerTextFormatLabel;
    QComboBox *weekdayColorCombo;
    QComboBox *weekendColorCombo;
    QComboBox *headerTextFormatCombo;

    QCheckBox *firstFridayCheckBox;
//! [1]
    QCheckBox *mayFirstCheckBox;

    QLabel *m_detail;
    QLabel *m_day;
    QLabel *m_mouthday;
    QLabel *m_gregorian;

    DisplayButton *m_ConfigureButton;
    DisplayButton *m_ReturnToday;
    DisplayButton *m_TimeZoneButton;
    DisplayButton *m_AboutButton;
    DisplayButton *m_ShowClock;

    QDate m_Today;  //m_Today记录着今天的日期
    Clock *m_clock;
    QDate m_Birthday;
#ifdef Right_Menu
    // TODO:  Context Menu
    void CreateContextMenu();
    QAction*         m_ShowClockAction;
    QAction*         m_ReturnTodayAction;
    QAction*         m_ConfigureButtonAction;
#endif
 private slots:
    void ShowClockButtonClicked();
    void ConfigureButtonClicked();
    void ReturnToday();
    void AboutButtonClicked();
    void GoToBirthday();
    void GoSetBirthday();

    void get_date(const QDate &dbirthday);
    void closeEvent(QCloseEvent *event);
};
//! [1]

#endif
