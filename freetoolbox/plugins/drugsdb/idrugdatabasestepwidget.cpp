/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
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
 *   Main developers: Eric MAEKER, <eric.maeker@gmail.com>                 *
 *   Contributors:                                                         *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
/*!
 * \class DrugsDB::Internal::IDrugDatabaseStepWidget
 */

#include "idrugdatabasestepwidget.h"
#include "idrugdatabasestep.h"

#include <coreplugin/icore.h>
#include <coreplugin/imainwindow.h>

#include <utils/log.h>
#include <translationutils/constants.h>

#include <QProgressDialog>
#include <QPointer>

#include <QDebug>

#include "ui_idrugdatabasestepwidget.h"

using namespace DrugsDB;
using namespace Internal;
using namespace Trans::ConstantTranslations;

static inline Core::IMainWindow *mainwindow() {return Core::ICore::instance()->mainWindow();}

namespace DrugsDB {
namespace Internal {

class IDrugDatabaseStepWidgetPrivate
{
public:
    IDrugDatabaseStepWidgetPrivate(IDrugDatabaseStepWidget *parent) :
        ui(0),
        _step(0),
        _progress(0),
        q(parent)
    {
    }
    
    ~IDrugDatabaseStepWidgetPrivate()
    {
    }

public:
    Ui::IDrugDatabaseStepWidget *ui;
    IDrugDatabaseStep *_step;
    QPointer<QProgressDialog> _progress;

private:
    IDrugDatabaseStepWidget *q;
};
}  // namespace Internal
} // end namespace DrugsDB

/*! Constructor of the DrugsDB::Internal::IDrugDatabaseStepWidget class */
IDrugDatabaseStepWidget::IDrugDatabaseStepWidget(QWidget *parent) :
    QWidget(parent),
    d(new IDrugDatabaseStepWidgetPrivate(this))
{
    d->ui = new Ui::IDrugDatabaseStepWidget();
    d->ui->setupUi(this);
    d->ui->progressBar->hide();
}

/*! Destructor of the DrugsDB::Internal::IDrugDatabaseStepWidget class */
IDrugDatabaseStepWidget::~IDrugDatabaseStepWidget()
{
    delete d->ui;
    if (d)
        delete d;
    d = 0;
}

/*! Initializes the object with the default values. Return true if initialization was completed. */
bool IDrugDatabaseStepWidget::initialize(IDrugDatabaseStep *step)
{
    Q_ASSERT(step);
    if (!step)
        return false;
    d->_step = step;
    d->ui->title->setText(step->displayName());
    return true;
}

void IDrugDatabaseStepWidget::on_startJobs_clicked()
{
    if (d->_progress)
        delete d->_progress;
    d->_progress = new QProgressDialog(mainwindow());
    d->_progress->setLabelText(tr("Starting jobs"));
    d->_progress->setRange(0, 1);
    d->_progress->setWindowModality(Qt::WindowModal);
    d->_progress->setValue(0);
    d->_progress->show();
    connect(d->_step, SIGNAL(progressRangeChanged(qint64,qint64)), this, SLOT(changeStepProgressRange(qint64,qint64)));
    connect(d->_step, SIGNAL(progress(int)), d->_progress, SLOT(setValue(int)));
    connect(d->_step, SIGNAL(progressLabelChanged(QString)), d->_progress, SLOT(setLabelText(QString)));

    if (d->ui->unzip->isChecked()) {
        if (d->_step->unzipFiles())
            d->ui->unzip->setText(d->ui->unzip->text() + " CORRECTLY DONE");
    }
    if (d->ui->prepare->isChecked()) {
        if (d->_step->prepareData())
            d->ui->prepare->setText(d->ui->prepare->text() + " CORRECTLY DONE");
    }
    if (d->ui->createDb->isChecked()) {
        if (d->_step->createDatabase())
            d->ui->createDb->setText(d->ui->createDb->text() + " CORRECTLY DONE");
    }
    if (d->ui->populate->isChecked()) {
        if (d->_step->populateDatabase())
            d->ui->populate->setText(d->ui->populate->text() + " CORRECTLY DONE");
    }
    if (d->ui->linkMols->isChecked()) {
        if (d->_step->linkMolecules())
            d->ui->linkMols->setText(d->ui->linkMols->text() + " CORRECTLY DONE");
    }
    Utils::Log::messagesToTreeWidget(d->ui->messages);
    Utils::Log::errorsToTreeWidget(d->ui->errors);
}

bool IDrugDatabaseStepWidget::on_download_clicked()
{
    d->ui->download->setEnabled(false);
    d->ui->progressBar->show();
    d->_step->downloadFiles(d->ui->progressBar);
    connect(d->_step, SIGNAL(downloadFinished()), this, SLOT(downloadFinished()));
    return true;
}

void IDrugDatabaseStepWidget::downloadFinished()
{
    d->ui->progressBar->hide();
    d->ui->download->setEnabled(true);
}

void IDrugDatabaseStepWidget::changeStepProgressRange(qint64 min, qint64 max)
{
    if (d->_step && d->_progress)
        d->_progress->setRange(min, max);
}
