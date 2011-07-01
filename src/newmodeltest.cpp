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
#include "newmodeltest.h"
#include "ui_newmodeltest.h"
#include "defsandtools.h"
#include <QDebug>

#include "qcatitemmodel.h"


NewModelTest::NewModelTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewModelTest)
{
    ui->setupUi(this);
}

NewModelTest::~NewModelTest()
{
	FREE_PTR(ui);
}

void NewModelTest::init(QCatDataModuleClass *db, QAbstractItemModel *model){
	this->db = db;
	this->model = model;
	ui->treeView->setModel(model);
	ui->treeView->setColumnHidden(1, true);
	ui->treeView->setColumnHidden(2, true);
	ui->treeView->setColumnHidden(3, true);
	ui->treeView->setColumnHidden(4, true);
	ui->treeView->setColumnHidden(5, true);
	ui->treeView->setColumnHidden(6, true);
	ui->treeView->setColumnHidden(7, true);
	ui->tableView->setModel(model);
//	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//	ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
	connect(ui->treeView, SIGNAL(activated(QModelIndex)), this, SLOT(activatedTreeItem(QModelIndex)));
	connect(ui->tableView, SIGNAL(activated(QModelIndex)), this, SLOT(activatedTableItem(QModelIndex)));
}


void NewModelTest::activatedTreeItem(const QModelIndex index){
	qDebug() << "Activated";
	ui->tableView->setRootIndex(index);
	ui->tableView->setCurrentIndex(index);
}
void NewModelTest::activatedTableItem(const QModelIndex index){
	qDebug() << "Activated table row = " << index.row() ;
//	ui->tableView->
	//ui->tableView->update(index);
}
