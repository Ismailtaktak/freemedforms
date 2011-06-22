/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2011 by Eric MAEKER, MD (France) <eric.maeker@free.fr>        *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *   Main Developpers :                                                    *
 *       Guillaume Denry <guillaume.denry@gmail.com>                       *
 *       Eric MAEKER, MD <eric.maeker@gmail.com>                           *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADRESS>                                                *
 ***************************************************************************/
#ifndef CALENDAR_ITEMEDITORWIDGET_H
#define CALENDAR_ITEMEDITORWIDGET_H

#include <calendar/calendar_exporter.h>

#include <QWidget>

namespace Calendar {
class CalendarItem;
class UserCalendar;

namespace Internal {
class ItemEditorWidgetPrivate;
}

class CALENDAR_EXPORT ItemEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemEditorWidget(QWidget *parent = 0);
    ~ItemEditorWidget();

    void clear();

    void setCalendarEvent(const Calendar::CalendarItem &event);
    Calendar::CalendarItem calendarEvent() const;

    void setAvailableUserCalendar(const QList<Calendar::UserCalendar *> &userCals);

public Q_SLOTS:
    void submit();

private Q_SLOTS:
    void on_selectIconButton_clicked();
    void changeDuration(const int comboIndex);

protected:
    void changeEvent(QEvent *e);

private:
    Internal::ItemEditorWidgetPrivate *d;
};

}  // End namespace Calendar

#endif // CALENDAR_ITEMEDITORWIDGET_H
