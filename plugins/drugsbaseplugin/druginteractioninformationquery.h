/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2015 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
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
 *  Main developer: Eric MAEKER, <eric.maeker@gmail.com>                   *
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef DRUGINTERACTIONINFORMATIONQUERY_H
#define DRUGINTERACTIONINFORMATIONQUERY_H

#include <drugsbaseplugin/drugsbase_exporter.h>

#include <QString>

namespace DrugsDB {
class DrugInteractionResult;
class IDrug;

struct DRUGSBASE_EXPORT DrugInteractionInformationQuery
{
    enum ProcessTime {
        BeforePrescription = 0,
        DuringPrescription,
        AfterPrescription,
        BeforePrinting
    };

    enum MessageType {
        DetailledAlert = 0,
        InformationAlert,
        ShortToolTip,
        DetailledToolTip
    };

    enum IconSize {
        SmallSize = 0,
        MediumSize,
        BigSize
    };

    DrugInteractionInformationQuery(const DrugInteractionInformationQuery &query);
    DrugInteractionInformationQuery();

    ~DrugInteractionInformationQuery();

    int messageType;
    int processTime;
    int iconSize;
    int levelOfWarningStaticAlert, levelOfWarningDynamicAlert;
    QString engineUid;
    DrugsDB::DrugInteractionResult *result;
    DrugsDB::IDrug *relatedDrug;
};

}  // End namespace DrugsDB

#endif // DRUGINTERACTIONINFORMATIONQUERY_H
