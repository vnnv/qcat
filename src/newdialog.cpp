/***************************************************************************
 *   Copyright (C) 2007-2011 by Victor Nikiforov                           *
 *   victor.nike@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <QFileDialog>


#include "newdialog.h"
#include "datamodule.h"
#include "configmanager.h"

NewDialog::NewDialog(QCatDataModuleClass *_dm, QWidget *parent)
 : dm(_dm), QDialog(parent), Ui::NewDBDialog()
{
    setupUi(this);
    connect(dbTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(dbTypeItemChanged(int)));
    dbTypeComboBox->addItem(tr("SQLite db file"));
    dbTypeComboBox->addItem(tr("MySQL Server"));
    dbTypeComboBox->addItem(tr("PostgreSQL Server"));
    
    connect(browseToolButton, SIGNAL(clicked()), this, SLOT(fileBrowseClicked()));
    
}


NewDialog::~NewDialog()
{
}

void NewDialog::dbTypeItemChanged(int index)
{
    switch (index)
    {
        case 0:
            sqlSrvGroupBox->setVisible(false);
            sqliteGroupBox->setVisible(true);
            break;   
        case 1:
        case 2:
            sqliteGroupBox->setVisible(false);
            sqlSrvGroupBox->setVisible(true);
            break;   
    }
    adjustSize();
}

void NewDialog::fileBrowseClicked()
{
    fileName = QFileDialog::getSaveFileName(this, tr("New SQLite Catalog"), dm->settings->lastDir, "*.qcat");
}


