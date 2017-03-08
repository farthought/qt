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

#include <QtGui>

#include "window.h"
#include "setbirthday.h"
#include <QDebug>
#include <QString>

Window::Window()
{
    createPreviewGroupBox();
    createGeneralOptionsGroupBox();
    createDatesGroupBox();
    createTextFormatsGroupBox();
#ifdef Right_Menu
    CreateContextMenu();
#endif

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(previewGroupBox, 0, 0);
    layout->addWidget(generalOptionsGroupBox, 0, 1);
    layout->addWidget(datesGroupBox, 1, 0);
    layout->addWidget(textFormatsGroupBox, 1, 1);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);

    previewLayout->setRowMinimumHeight(0, calendar->sizeHint().height());
    previewLayout->setColumnMinimumWidth(0, calendar->sizeHint().width());

    setWindowTitle(tr("Calendar Widget"));
    setWindowIcon(QIcon(":/images/icon.ico"));

    m_clock = NULL;
    if (!m_clock) {
        m_clock = new Clock(this);
    }
    m_Today = QDate(calendar->selectedDate());
    ReadHistorySettings();
}

void Window::localeChanged(int index)
{
    calendar->setLocale(localeCombo->itemData(index).toLocale());
}

void Window::firstDayChanged(int index)
{
    calendar->setFirstDayOfWeek(Qt::DayOfWeek(
                                firstDayCombo->itemData(index).toInt()));
}

void Window::selectionModeChanged(int index)
{
    calendar->setSelectionMode(QCalendarWidget::SelectionMode(
                               selectionModeCombo->itemData(index).toInt()));
}

void Window::horizontalHeaderChanged(int index)
{
    calendar->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat(
        horizontalHeaderCombo->itemData(index).toInt()));
}

void Window::verticalHeaderChanged(int index)
{
    calendar->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat(
        verticalHeaderCombo->itemData(index).toInt()));
}

void Window::selectedDateChanged()
{
    QString outLunarMD = "", outLunarYear = "", outLunarMonth = "", outLunarDay = "";
    currentDateEdit->setDate(calendar->selectedDate());
    m_detail->setText(calendar->selectedDate().toString("yyyy-MM-dd dddd"));
    m_day->setText(calendar->selectedDate().toString("dd"));

    if (((calendar->selectedDate().year() > 1921 )
        || (calendar->selectedDate().year() == 1921 && calendar->selectedDate().month() > 2)
        || (calendar->selectedDate().year() == 1921 && calendar->selectedDate().month() == 2 && calendar->selectedDate().day() >= 8))
        && (calendar->selectedDate().year() < 2021))
    {
        get_chinese_calendar(calendar->selectedDate(), outLunarMD, outLunarYear, outLunarMonth, outLunarDay);
        m_mouthday->setVisible(true);
        m_gregorian->setVisible(true);
        m_mouthday->setText(outLunarMD);
        m_gregorian->setText(outLunarYear + " " + outLunarMonth + " " + outLunarDay);
    }
    else {
        m_mouthday->setVisible(false);
        m_gregorian->setVisible(false);
    }
}

void Window::minimumDateChanged(const QDate &date)
{
    calendar->setMinimumDate(date);
    maximumDateEdit->setDate(calendar->maximumDate());
}

void Window::maximumDateChanged(const QDate &date)
{
    calendar->setMaximumDate(date);
    minimumDateEdit->setDate(calendar->minimumDate());
}

void Window::weekdayFormatChanged()
{
    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(
        weekdayColorCombo->itemData(weekdayColorCombo->currentIndex())));
    calendar->setWeekdayTextFormat(Qt::Monday, format);
    calendar->setWeekdayTextFormat(Qt::Tuesday, format);
    calendar->setWeekdayTextFormat(Qt::Wednesday, format);
    calendar->setWeekdayTextFormat(Qt::Thursday, format);
    calendar->setWeekdayTextFormat(Qt::Friday, format);
}

void Window::weekendFormatChanged()
{
    QTextCharFormat format;

    format.setForeground(qvariant_cast<QColor>(
        weekendColorCombo->itemData(weekendColorCombo->currentIndex())));
    calendar->setWeekdayTextFormat(Qt::Saturday, format);
    calendar->setWeekdayTextFormat(Qt::Sunday, format);
}

void Window::reformatHeaders()
{
    QString text = headerTextFormatCombo->currentText();
    QTextCharFormat format;

    if (text == tr("Bold")) {
        format.setFontWeight(QFont::Bold);
    } else if (text == tr("Italic")) {
        format.setFontItalic(true);
    } else if (text == tr("Green")) {
        format.setForeground(Qt::green);
    }
    calendar->setHeaderTextFormat(format);
}

void Window::reformatCalendarPage()
{
    QDate firstFriday(calendar->yearShown(), calendar->monthShown(), 1);
    while (firstFriday.dayOfWeek() != Qt::Friday)
        firstFriday = firstFriday.addDays(1);
    QTextCharFormat firstFridayFormat;

    if (firstFridayCheckBox->isChecked()) {
        firstFridayFormat.setForeground(Qt::darkYellow);
        firstFridayFormat.setFont(QFont("", 11, QFont::Bold));
    }
    else {
        Qt::DayOfWeek m_DayOfWeek(static_cast<Qt::DayOfWeek>(firstFriday.dayOfWeek()));
        firstFridayFormat.setForeground(calendar->weekdayTextFormat(m_DayOfWeek).foreground());
    }
    calendar->setDateTextFormat(firstFriday, firstFridayFormat);

    //May First in Red takes precedence
    const QDate mayFirst(calendar->yearShown(), 5, 1);
    QTextCharFormat mayFirstFormat;

    if (mayFirstCheckBox->isChecked()) {
        mayFirstFormat.setForeground(Qt::red);
        mayFirstFormat.setFont(QFont("Arial", 11, QFont::Bold));
    }
    else {
        Qt::DayOfWeek m_DayOfWeek(static_cast<Qt::DayOfWeek>(mayFirst.dayOfWeek()));
        mayFirstFormat.setForeground(calendar->weekdayTextFormat(m_DayOfWeek).foreground());
    }
    calendar->setDateTextFormat(mayFirst, mayFirstFormat);
}

void Window::createPreviewGroupBox()
{
    previewGroupBox = new QGroupBox(tr("Calendar"), this);
    calendar = new QCalendarWidget;
    calendar->setMinimumDate(QDate(1900, 1, 1));
    calendar->setMaximumDate(QDate(3000, 1, 1));
    calendar->setGridVisible(true);

    connect(calendar, SIGNAL(currentPageChanged(int,int)),
            this, SLOT(reformatCalendarPage()));

    m_detail = new QLabel;
    m_detail->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_detail->setStyleSheet("font-size:14px; color: #008080;");
    m_detail->setText(calendar->selectedDate().toString("yyyy-MM-dd dddd"));

    m_day = new QLabel;
    m_day->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_day->setStyleSheet("font-size:40px; color:#800080; font:bold;");
    m_day->setText(QString::number(calendar->selectedDate().day()));

    QString outLunarMD = "", outLunarYear = "", outLunarMonth = "", outLunarDay = "";
    get_chinese_calendar(calendar->selectedDate(), outLunarMD, outLunarYear, outLunarMonth, outLunarDay);

    m_mouthday = new QLabel;
    m_mouthday->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_mouthday->setStyleSheet("font-size:14px; color: #008080;");
    m_mouthday->setText(outLunarMD);


    m_gregorian = new QLabel;
    m_gregorian->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_gregorian->setStyleSheet("border: 1px solid gray;font-size:14px; color:#008000;");
    m_gregorian->setText(outLunarYear + " " +outLunarMonth + " " +outLunarDay);

    m_ReturnToday = new DisplayButton;
    m_ReturnToday->setIcon(QIcon(":/images/go_back_today.png"));
    m_ReturnToday->setToolTip(tr("go back today"));     //回到今天
    connect(m_ReturnToday, SIGNAL(clicked()),
            this, SLOT(ReturnToday()));

    m_ShowClock = new DisplayButton;
    m_ShowClock->setIcon(QIcon(":/images/clock.ico"));
    m_ShowClock->setToolTip(tr("clock"));    //时钟
    connect(m_ShowClock, SIGNAL(clicked()),
            this, SLOT(ShowClockButtonClicked()));

    m_ConfigureButton = new DisplayButton;
    m_ConfigureButton->setText("display");
    m_ConfigureButton->setIcon(QIcon(":/images/configure.png"));
    m_ConfigureButton->setToolTip(tr("display setup"));    //显示设置
    connect(m_ConfigureButton, SIGNAL(clicked()),
            this, SLOT(ConfigureButtonClicked()));

    m_AboutButton = new DisplayButton;
    m_AboutButton->setIcon(QIcon(":/images/about.png"));
    m_AboutButton->setToolTip(tr("about produce"));     //关于产品
    connect(m_AboutButton, SIGNAL(clicked()),
            this, SLOT(AboutButtonClicked()));

    previewLayout = new QGridLayout;
    previewLayout->addWidget(calendar, 0, 0, Qt::AlignCenter);
    QHBoxLayout* showLayout = new QHBoxLayout;
    showLayout->addStretch();
    showLayout->addWidget(m_ReturnToday);
    showLayout->addWidget(m_ShowClock);
    showLayout->addWidget(m_ConfigureButton);
    showLayout->addWidget(m_AboutButton);
    showLayout->addStretch();

    QHBoxLayout* detailLayout = new QHBoxLayout;
    detailLayout->addWidget(m_detail);
    detailLayout->addStretch();
    detailLayout->addWidget(m_day);
    detailLayout->addStretch();
    detailLayout->addWidget(m_mouthday);

    QHBoxLayout* callLayout = new QHBoxLayout;
    callLayout->addStretch();
    callLayout->addWidget(m_gregorian);
    callLayout->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(previewLayout);
    mainLayout->addLayout(showLayout);
    mainLayout->addLayout(detailLayout);
    mainLayout->addLayout(callLayout);

    previewGroupBox->setLayout(mainLayout);

#ifdef Right_Menu
        // TODO:  Context Menu
        m_ReturnTodayAction = new QAction(tr("Mtoday"), this);
        m_ReturnTodayAction->setIcon(QIcon(":/images/go_back_today.png"));
        m_ReturnTodayAction->setShortcut(tr("F9"));
        m_ShowClockAction = new QAction(tr("Mclock"), this);
        m_ShowClockAction->setIcon(QIcon(":/images/clock.ico"));
        m_ShowClockAction->setShortcut(tr("F10"));
        m_ConfigureButtonAction = new QAction(tr("Msetup"), this);
        m_ConfigureButtonAction->setIcon(QIcon(":/images/configure.png"));
        m_ConfigureButtonAction->setShortcut(tr("Ctrl+G"));
        connect(m_ReturnTodayAction, SIGNAL(triggered()), this, SLOT(ReturnToday()));
        connect(m_ShowClockAction, SIGNAL(triggered()), SLOT(ShowClockButtonClicked()));
        connect(m_ConfigureButtonAction, SIGNAL(triggered()), this, SLOT(ConfigureButtonClicked()));
#endif
}

void Window::createGeneralOptionsGroupBox()
{
    generalOptionsGroupBox = new QGroupBox(tr("General Options"));

    localeCombo = new QComboBox;
    int curLocaleIndex = -1;
    int index = 0;
    for (int _lang = QLocale::C; _lang <= QLocale::LastLanguage; ++_lang) {
        QLocale::Language lang = static_cast<QLocale::Language>(_lang);
        QList<QLocale::Country> countries = QLocale::countriesForLanguage(lang);
        for (int i = 0; i < countries.count(); ++i) {
            QLocale::Country country = countries.at(i);
            QString label = QLocale::languageToString(lang);
            label += QLatin1Char('/');
            label += QLocale::countryToString(country);
            QLocale locale(lang, country);
            if (this->locale().language() == lang && this->locale().country() == country)
                curLocaleIndex = index;
            localeCombo->addItem(label, locale);
            ++index;
        }
    }
    if (curLocaleIndex != -1)
        localeCombo->setCurrentIndex(curLocaleIndex);
    localeLabel = new QLabel(tr("&Locale"));
    localeLabel->setBuddy(localeCombo);

    firstDayCombo = new QComboBox;
    firstDayCombo->addItem(tr("Sunday"), Qt::Sunday);
    firstDayCombo->addItem(tr("Monday"), Qt::Monday);
    firstDayCombo->addItem(tr("Tuesday"), Qt::Tuesday);
    firstDayCombo->addItem(tr("Wednesday"), Qt::Wednesday);
    firstDayCombo->addItem(tr("Thursday"), Qt::Thursday);
    firstDayCombo->addItem(tr("Friday"), Qt::Friday);
    firstDayCombo->addItem(tr("Saturday"), Qt::Saturday);

    firstDayLabel = new QLabel(tr("Wee&k starts on:"));
    firstDayLabel->setBuddy(firstDayCombo);

    selectionModeCombo = new QComboBox;
    selectionModeCombo->addItem(tr("Single selection"),
                                QCalendarWidget::SingleSelection);
    selectionModeCombo->addItem(tr("None_Select"), QCalendarWidget::NoSelection);

    selectionModeLabel = new QLabel(tr("&Selection mode:"));
    selectionModeLabel->setBuddy(selectionModeCombo);

    gridCheckBox = new QCheckBox(tr("&Grid"));
    gridCheckBox->setChecked(calendar->isGridVisible());

    navigationCheckBox = new QCheckBox(tr("&Navigation bar"));
    navigationCheckBox->setChecked(true);

    horizontalHeaderCombo = new QComboBox;
    horizontalHeaderCombo->addItem(tr("Single letter day names"),
                                   QCalendarWidget::SingleLetterDayNames);
    horizontalHeaderCombo->addItem(tr("Short day names"),
                                   QCalendarWidget::ShortDayNames);
    horizontalHeaderCombo->addItem(tr("None_Names"),
                                   QCalendarWidget::NoHorizontalHeader);
    horizontalHeaderCombo->setCurrentIndex(1);

    horizontalHeaderLabel = new QLabel(tr("&Horizontal header:"));
    horizontalHeaderLabel->setBuddy(horizontalHeaderCombo);

    verticalHeaderCombo = new QComboBox;
    verticalHeaderCombo->addItem(tr("ISO week numbers"),
                                 QCalendarWidget::ISOWeekNumbers);
    verticalHeaderCombo->addItem(tr("None_ISO"), QCalendarWidget::NoVerticalHeader);

    verticalHeaderLabel = new QLabel(tr("&Vertical header:"));
    verticalHeaderLabel->setBuddy(verticalHeaderCombo);

    connect(localeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(localeChanged(int)));
    connect(firstDayCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(firstDayChanged(int)));
    connect(selectionModeCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(selectionModeChanged(int)));
    connect(gridCheckBox, SIGNAL(toggled(bool)),
            calendar, SLOT(setGridVisible(bool)));
    connect(navigationCheckBox, SIGNAL(toggled(bool)),
            calendar, SLOT(setNavigationBarVisible(bool)));
    connect(horizontalHeaderCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(horizontalHeaderChanged(int)));
    connect(verticalHeaderCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(verticalHeaderChanged(int)));

    QHBoxLayout *checkBoxLayout = new QHBoxLayout;
    checkBoxLayout->addWidget(gridCheckBox);
    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(navigationCheckBox);

    QGridLayout *outerLayout = new QGridLayout;
    outerLayout->addWidget(localeLabel, 0, 0);
    outerLayout->addWidget(localeCombo, 0, 1);
    outerLayout->addWidget(firstDayLabel, 1, 0);
    outerLayout->addWidget(firstDayCombo, 1, 1);
    outerLayout->addWidget(selectionModeLabel, 2, 0);
    outerLayout->addWidget(selectionModeCombo, 2, 1);
    outerLayout->addLayout(checkBoxLayout, 3, 0, 1, 2);
    outerLayout->addWidget(horizontalHeaderLabel, 4, 0);
    outerLayout->addWidget(horizontalHeaderCombo, 4, 1);
    outerLayout->addWidget(verticalHeaderLabel, 5, 0);
    outerLayout->addWidget(verticalHeaderCombo, 5, 1);
    generalOptionsGroupBox->setLayout(outerLayout);
    generalOptionsGroupBox->setHidden(true);

    firstDayChanged(firstDayCombo->currentIndex());
    selectionModeChanged(selectionModeCombo->currentIndex());
    horizontalHeaderChanged(horizontalHeaderCombo->currentIndex());
    verticalHeaderChanged(verticalHeaderCombo->currentIndex());
}

void Window::createDatesGroupBox()
{
    datesGroupBox = new QGroupBox(tr("Dates"));

    setBirthday = new QPushButton(tr("set_birthday"));
    connect(setBirthday, SIGNAL(clicked()), this, SLOT(GoSetBirthday()));

    goBirthday = new QPushButton(tr("go_to_birthday"));
    connect(goBirthday, SIGNAL(clicked()), this, SLOT(GoToBirthday()));

    minimumDateEdit = new QDateEdit;
    minimumDateEdit->setDisplayFormat("yyyy-MM-dd");
    minimumDateEdit->setDateRange(calendar->minimumDate(),
                                  calendar->maximumDate());
    minimumDateEdit->setDate(calendar->minimumDate());

    minimumDateLabel = new QLabel(tr("&Minimum Date:"));
    minimumDateLabel->setBuddy(minimumDateEdit);

    currentDateEdit = new QDateEdit;
    currentDateEdit->setDisplayFormat("yyyy-MM-dd");
    currentDateEdit->setDate(calendar->selectedDate());
    currentDateEdit->setDateRange(calendar->minimumDate(),
                                  calendar->maximumDate());

    currentDateLabel = new QLabel(tr("&Current Date:"));
    currentDateLabel->setBuddy(currentDateEdit);

    maximumDateEdit = new QDateEdit;
    maximumDateEdit->setDisplayFormat("yyyy-MM-dd");
    maximumDateEdit->setDateRange(calendar->minimumDate(),
                                  calendar->maximumDate());
    maximumDateEdit->setDate(calendar->maximumDate());

    maximumDateLabel = new QLabel(tr("Ma&ximum Date:"));
    maximumDateLabel->setBuddy(maximumDateEdit);

    connect(currentDateEdit, SIGNAL(dateChanged(QDate)),
            calendar, SLOT(setSelectedDate(QDate)));
    connect(calendar, SIGNAL(selectionChanged()),
            this, SLOT(selectedDateChanged()));
    connect(minimumDateEdit, SIGNAL(dateChanged(QDate)),
            this, SLOT(minimumDateChanged(QDate)));
    connect(maximumDateEdit, SIGNAL(dateChanged(QDate)),
            this, SLOT(maximumDateChanged(QDate)));

    QGridLayout *dateBoxLayout = new QGridLayout;
    dateBoxLayout->addWidget(setBirthday, 0, 0);
    dateBoxLayout->addWidget(goBirthday, 0, 1);
    dateBoxLayout->addWidget(currentDateLabel, 2, 0);
    dateBoxLayout->addWidget(currentDateEdit, 2, 1);
    dateBoxLayout->addWidget(minimumDateLabel, 1, 0);
    dateBoxLayout->addWidget(minimumDateEdit, 1, 1);
    dateBoxLayout->addWidget(maximumDateLabel, 3, 0);
    dateBoxLayout->addWidget(maximumDateEdit, 3, 1);
    dateBoxLayout->setRowStretch(3, 1);

    datesGroupBox->setLayout(dateBoxLayout);
    datesGroupBox->setHidden(true);
}

void Window::createTextFormatsGroupBox()
{
    textFormatsGroupBox = new QGroupBox(tr("Text Formats"));

    weekdayColorCombo = createColorComboBox();
    weekdayColorCombo->setCurrentIndex(
            weekdayColorCombo->findText(tr("Black")));

    weekdayColorLabel = new QLabel(tr("&Weekday color:"));
    weekdayColorLabel->setBuddy(weekdayColorCombo);

    weekendColorCombo = createColorComboBox();
    weekendColorCombo->setCurrentIndex(
            weekendColorCombo->findText(tr("Red")));

    weekendColorLabel = new QLabel(tr("Week&end color:"));
    weekendColorLabel->setBuddy(weekendColorCombo);

    headerTextFormatCombo = new QComboBox;
    headerTextFormatCombo->addItem(tr("Bold"));
    headerTextFormatCombo->addItem(tr("Italic"));
    headerTextFormatCombo->addItem(tr("Plain"));

    headerTextFormatLabel = new QLabel(tr("&Header text:"));
    headerTextFormatLabel->setBuddy(headerTextFormatCombo);

    firstFridayCheckBox = new QCheckBox(tr("&First Friday in darkyellow"));

    mayFirstCheckBox = new QCheckBox(tr("May &1 in red"));

    connect(weekdayColorCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(weekdayFormatChanged()));
    connect(weekendColorCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(weekendFormatChanged()));
    connect(headerTextFormatCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(reformatHeaders()));
    connect(firstFridayCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(reformatCalendarPage()));
    connect(mayFirstCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(reformatCalendarPage()));

    QHBoxLayout *checkBoxLayout = new QHBoxLayout;
    checkBoxLayout->addWidget(firstFridayCheckBox);
    checkBoxLayout->addStretch();
    checkBoxLayout->addWidget(mayFirstCheckBox);

    QGridLayout *outerLayout = new QGridLayout;
    outerLayout->addWidget(weekdayColorLabel, 0, 0);
    outerLayout->addWidget(weekdayColorCombo, 0, 1);
    outerLayout->addWidget(weekendColorLabel, 1, 0);
    outerLayout->addWidget(weekendColorCombo, 1, 1);
    outerLayout->addWidget(headerTextFormatLabel, 2, 0);
    outerLayout->addWidget(headerTextFormatCombo, 2, 1);
    outerLayout->addLayout(checkBoxLayout, 3, 0, 1, 2);
    textFormatsGroupBox->setLayout(outerLayout);
    textFormatsGroupBox->setHidden(true);

    weekdayFormatChanged();
    weekendFormatChanged();

    reformatHeaders();
    reformatCalendarPage();
}

void Window::ReadHistorySettings()
{
    QSettings m_settings("i-soft.com.cn", "calendar");
    localeCombo->setCurrentIndex(m_settings.value("Language").toInt());
    firstDayCombo->setCurrentIndex(m_settings.value("WeekStart").toInt());
    selectionModeCombo->setCurrentIndex(m_settings.value("Selection_Mode").toInt());
    gridCheckBox->setChecked(m_settings.value("Show_Grid").toBool());
    navigationCheckBox->setChecked(m_settings.value("Show_Navigation_Bar").toBool());
    horizontalHeaderCombo->setCurrentIndex(m_settings.value("Horizontal_Header").toInt());
    verticalHeaderCombo->setCurrentIndex(m_settings.value("Vertival_Header").toInt());
    weekdayColorCombo->setCurrentIndex(m_settings.value("WeekdayColor").toInt());
    weekendColorCombo->setCurrentIndex(m_settings.value("WeekendColor").toInt());
    headerTextFormatCombo->setCurrentIndex(m_settings.value("Header_Font").toInt());
    firstFridayCheckBox->setChecked(m_settings.value("First_Friday").toBool());
    mayFirstCheckBox->setChecked(m_settings.value("May_First").toBool());
    m_clock->restoreGeometry(m_settings.value("Clock_Geometry").toByteArray());
    m_Birthday = QDate::fromString(m_settings.value("Birthday_Date").toString(), "yyyy-MM-dd");
    this->restoreGeometry(m_settings.value("Calendar_Geometry").toByteArray());

    if (m_Birthday.isNull())
        goBirthday->setEnabled(false);
}

void Window::WriteCurrentSettings()
{
    QSettings m_settings("i-soft.com.cn", "calendar");
    m_settings.setValue("Language", localeCombo->currentIndex());
    m_settings.setValue("WeekStart", firstDayCombo->currentIndex());
    m_settings.setValue("Selection_Mode", selectionModeCombo->currentIndex());
    m_settings.setValue("Show_Grid", gridCheckBox->isChecked());
    m_settings.setValue("Show_Navigation_Bar", navigationCheckBox->isChecked());
    m_settings.setValue("Horizontal_Header", horizontalHeaderCombo->currentIndex());
    m_settings.setValue("Vertival_Header", verticalHeaderCombo->currentIndex());
    m_settings.setValue("WeekdayColor", weekdayColorCombo->currentIndex());
    m_settings.setValue("WeekendColor", weekendColorCombo->currentIndex());
    m_settings.setValue("Header_Font", headerTextFormatCombo->currentIndex());
    m_settings.setValue("First_Friday", firstFridayCheckBox->isChecked());
    m_settings.setValue("May_First", mayFirstCheckBox->isChecked());
    m_settings.setValue("Clock_Geometry", m_clock->saveGeometry());
    m_settings.setValue("Birthday_Date", m_Birthday.toString ("yyyy-MM-dd"));
    m_settings.setValue("Calendar_Geometry", this->saveGeometry());
}

QComboBox *Window::createColorComboBox()
{
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem(tr("Red"), Qt::red);
    comboBox->addItem(tr("Blue"), Qt::blue);
    comboBox->addItem(tr("Black"), Qt::black);
    comboBox->addItem(tr("Magenta"), Qt::magenta);
    comboBox->addItem(tr("Green"), Qt::green);
    comboBox->addItem(tr("Gray"), Qt::gray);
    return comboBox;
}

void Window::ShowClockButtonClicked()
{
    if (!m_clock) {
        m_clock = new Clock(this);
    }
    m_clock->setModal(true);
    m_clock->show();
}

void Window::ConfigureButtonClicked()
{
    if (m_ConfigureButton->text() == tr("display")) {
        generalOptionsGroupBox->setHidden(false);
        datesGroupBox->setHidden(false);
        textFormatsGroupBox->setHidden(false);
        m_ConfigureButton->setText(tr("hidden"));
        m_ConfigureButton->setToolTip(tr("hide setup"));

        previewGroupBox->setTitle(tr("Preview"));
    }
    else if (m_ConfigureButton->text() == tr("hidden")) {
        generalOptionsGroupBox->setHidden(true);
        datesGroupBox->setHidden(true);
        textFormatsGroupBox->setHidden(true);
        m_ConfigureButton->setText(tr("display"));
        m_ConfigureButton->setToolTip(tr("display setup"));

        previewGroupBox->setTitle(tr("Calendar"));
    }
}

void Window::ReturnToday()
{
    calendar->setSelectedDate(m_Today);
}

void Window::AboutButtonClicked()
{
    QMessageBox::about(this, tr("About Calendar"),
         tr("<h1> Calendar 2014</h1>"

         "<p><h4>Release 1.0</h4>"
         "<p>Copyright &copy; 2013-2014 Inc. & isoft "
         "All rights reserved."
         "<p>版权所有 © 2013-2014 Inc. & isoft。 保留所有权利。"
         "<p>警告：本计算机程序受著作权法和国际公约的保护，未经授权擅自复制或传播本程序"
         "的部分或全部，可能受到严厉的民事及刑事制裁，并将在法律许可的范围内受到最大"
         "可能的起诉。"
            ));
}

void Window::GoToBirthday()
{
   if (goBirthday->text() == tr("go_to_birthday")) {
       calendar->setSelectedDate(m_Birthday);
       goBirthday->setText(tr("back_today"));
   }
   else if (goBirthday->text() == tr("back_today")) {
       ReturnToday();
       goBirthday->setText(tr("go_to_birthday"));
   }
}

void Window::GoSetBirthday()
{
    SetBirthday *m_birthday = new SetBirthday(this);
    connect(m_birthday, SIGNAL(send_date(QDate)), this, SLOT(get_date(QDate)));
    m_birthday->exec();
}

void Window::get_date(const QDate &dbirthday)
{
    m_Birthday = dbirthday;
    if (goBirthday->text() == tr("back_today")) {
        goBirthday->setText(tr("go_to_birthday"));
    }
    goBirthday->setEnabled(true);
}

void Window::closeEvent(QCloseEvent *event)
{
    WriteCurrentSettings();
    event->accept();
}

#ifdef Right_Menu
void Window::CreateContextMenu()
{
    previewGroupBox->addAction(m_ReturnTodayAction);
    previewGroupBox->addAction(m_ShowClockAction);
    previewGroupBox->addAction(m_ConfigureButtonAction);
    previewGroupBox->setContextMenuPolicy(Qt::ActionsContextMenu);
}
#endif
/*------------农历转换函数-----------*/
void Window::get_chinese_calendar(QDate english_calendar, QString &outLunarMD, QString &outLunarYear, QString &outLunarMonth, QString &outLunarDay)
{
    int currentYear = 0, currentMonth = 0, currentDay = 0;
    int nTheDate = 0, nTheMonth = 0;
    int nisEnd = 0, flag = 0, n = 0, k = 0, nBit = 0, i = 0;
    char m_LunarMD[100] = {0}, m_LunarYear[50] = {0}, m_LunarMonth[50] = {0}, m_LunarDay[50] = {0}, m_zodiak[50] = {0};
    /*天干名称*/
    const char *m_TianGan[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
    /*地支名称*/
    const char *m_DiZhi[] = {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};
    /*属相名称*/
    const char *m_ShuXiang[] = {"鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"};
    /*农历日期名*/
    const char *m_DayName[] = {"*","初一","初二","初三","初四","初五",
          "初六","初七","初八","初九","初十",
          "十一","十二","十三","十四","十五",
          "十六","十七","十八","十九","二十",
          "廿一","廿二","廿三","廿四","廿五",
          "廿六","廿七","廿八","廿九","三十"};
     /*农历月份名*/
    const char *m_MonthName[] = {"*","正","二","三","四","五","六","七","八","九","十","十一","腊"};
    /*公历每月前面的天数*/
    const int m_DayAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
    /*农历数据*/
    const int m_LunarData[100]= {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
                                 ,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
                                 ,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
                                 ,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
                                 ,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
                                 ,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
                                 ,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
                                 ,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
                                 ,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
                                 ,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877};

    currentYear = english_calendar.year();
    currentMonth = english_calendar.month();
    currentDay = english_calendar.day();
    nTheMonth = (currentYear- 1921) * 12 - 2 + currentMonth;

    sprintf(m_LunarMonth, "%s%s月", m_TianGan[(nTheMonth + 6) % 10], m_DiZhi[(nTheMonth + 2) % 12]);

    /*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/
    nTheDate = (currentYear - 1921) *365 + (currentYear - 1921)/4  + m_DayAdd[currentMonth - 1] + currentDay - 31 - 7;
    if((!(currentYear % 4)) && (currentMonth > 2))
        nTheDate = nTheDate + 1;

    sprintf(m_LunarDay, "%s%s日", m_TianGan[(nTheDate + 7) % 10], m_DiZhi[(nTheDate + 1) % 12]);

    /*--计算农历天干、地支、月、日---*/
    nisEnd = 0;
    flag = 0;
    while (nisEnd != 1) {
        if (m_LunarData[flag] < 4095)  k = 11;
        else  k = 12;
        n = k;
        while (n >= 0) {
             //m_LunarData(flag)的第n个二进制位的值
            nBit = m_LunarData[flag];
            for (i = 1; i < n + 1; i++)  nBit = nBit / 2;
            nBit = nBit % 2;
            if (nTheDate <= (29 + nBit)) {
                nisEnd = 1;
                break;
            }
            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }
        if (nisEnd)  break;
        flag = flag + 1;
    }
    currentYear = 1921 + flag;
    currentMonth = k - n + 1;
    currentDay = nTheDate;
    if (k == 12) {
        if (currentMonth == m_LunarData[flag] / 65536 + 1)  currentMonth = 1 - currentMonth;
        else if (currentMonth > m_LunarData[flag] / 65536 + 1)  currentMonth = currentMonth - 1;
    }
    /*--生成农历天干、地支、属相*/
    sprintf(m_zodiak, "%s", m_ShuXiang[((currentYear - 4) % 60) % 12]);
    sprintf(m_LunarYear, "%s%s年 【%s年】", m_TianGan[((currentYear - 4) % 60) % 10], m_DiZhi[((currentYear - 4) % 60) % 12], m_zodiak);
    /*--生成农历月、日*/
    if (currentMonth < 1)
        sprintf(m_LunarMD ,"闰%s", m_MonthName[-1 * currentMonth]);
    else
        strcpy(m_LunarMD, m_MonthName[currentMonth]);
    strcat(m_LunarMD,"月");
    strcat(m_LunarMD, m_DayName[currentDay]);

    outLunarMD = tr(m_LunarMD);
    outLunarYear = tr(m_LunarYear);
    outLunarMonth = tr(m_LunarMonth);
    outLunarDay = tr(m_LunarDay);
}
