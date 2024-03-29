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
#ifndef NEWMODELTEST_H
#define NEWMODELTEST_H

#include <QDialog>
#include <QAbstractItemModel>

namespace Ui {
    class NewModelTest;
}

class QCatDataModuleClass;

class NewModelTest : public QDialog
{
    Q_OBJECT

public:
    explicit NewModelTest(QWidget *parent = 0);
    ~NewModelTest();

	void init(QCatDataModuleClass *db, QAbstractItemModel *model);

public slots:
	void activatedTreeItem(const QModelIndex index);
	void activatedTableItem(const QModelIndex index);

private:
    Ui::NewModelTest *ui;
	QCatDataModuleClass *db;
	QAbstractItemModel *model;
};

#endif // NEWMODELTEST_H
