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

//#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QFileInfo>
#include <QDebug>

#include "defsandtools.h"
#include "dbnode.h"
#include "iconmanager.h"
#include "catalogclass.h"
#include "configmanager.h"
#include "catalogreports.h"
#include "datamodule.h"
#include "qcatitem.h"
#include "logger.h"

QCatDataModuleClass::QCatDataModuleClass()
{
	logger.debug("Constructing DataModule (default constructor)", __FILE__, __LINE__);
	im = NULL;
	cat = NULL;
	rpt = NULL;
	dbn = NULL;
	dbConnName = "";
}

QCatDataModuleClass::QCatDataModuleClass(const QString fileName)
{
	logger.debug(QString("Constructing DataModule with file %1").arg(fileName), __FILE__, __LINE__);
	bool fileExist = false;
    QFileInfo fi(fileName);
    
    fileExist = fi.exists();
    printQS(QString::number(fileExist));
	bool createNewDB = false;
	if (!fileExist)
	{
		QCatDataModuleClass::createDB(fileName, true);
		createNewDB = true;
	}
	
	dbConnName = fileName;
    
	db = QSqlDatabase::addDatabase(DBTYPE, dbConnName);
	db.setDatabaseName(fileName);
	if (!db.open())
	{
		errorCode = 1; // DB can not be opened
		errMsg = QObject::tr("DB %1 can not be opened.").arg(fileName);
		return;
	}
	dbn = new dbNodeClass(db);
	cat = new CatalogClass(db);
	rpt = new CatalogReports(db);
	im = new IconManager(db);
	if (createNewDB)
		im->fillDefaultIcons();
}

QCatDataModuleClass::~ QCatDataModuleClass()
{
	FREE_PTR(im);
	FREE_PTR(cat);
	FREE_PTR(rpt);
	FREE_PTR(dbn);
	db.close();
    QSqlDatabase::removeDatabase(dbConnName);
}

void QCatDataModuleClass::openDb(const QString fileName)
{
	logger.debug(QString("Open Database (%1)").arg(fileName), __FILE__, __LINE__);
	FREE_PTR(im);
	FREE_PTR(cat);
	FREE_PTR(rpt);
	FREE_PTR(dbn);
	
	if (!dbConnName.isEmpty())
		QSqlDatabase::removeDatabase(dbConnName);

    dbConnName = fileName;
	//db = QSqlDatabase::addDatabase(DBTYPE, dbConnName);
	db = QSqlDatabase::addDatabase(DBTYPE);
	
	bool createNewDB = false;
	if (!QFileInfo(fileName).exists())
	{
        createDB(fileName, true);
		createNewDB = true;
	}
    db.setDatabaseName(fileName);
    if (!db.open())
    {
        errorCode = 1; // DB can not be opened
        errMsg = QObject::tr("DB %1 can not be opened.").arg(fileName);
        return;
    }
    dbn = new dbNodeClass(db);
    cat = new CatalogClass(db);
    rpt = new CatalogReports(db);
    im = new IconManager(db);
	if (createNewDB)
    {
		im->fillDefaultIcons();
		FREE_PTR(im);
        // Re-read global icons
        im = new IconManager(db);
    }
        

}

bool QCatDataModuleClass::isOk()
{
	return (errorCode == 0);	
}

bool QCatDataModuleClass::createDB(const QString fileName, bool overwrite)
{
	bool fileExist = QFileInfo(fileName).exists();
	if (!overwrite && fileExist)
		return false;
     
	QSqlQuery *wq;
    
	QString dropIconsTable = "DROP TABLE IF EXISTS Icons";
	QString crIconsTable = "CREATE TABLE Icons (id INTEGER PRIMARY KEY AUTOINCREMENT, catId INTEGER(4), name TEXT(255), fileName TEXT(255), iconData BLOB)";
    
	QString dropNodeTypes = "DROP TABLE IF EXISTS nodeTypes";
	QString crNodeTypes = "CREATE TABLE NodeTypes (id INTEGER(8), nodeName TEXT(255), nodeIcon INT(4), PRIMARY KEY(id))";
    
	QString dropCatalogsTable = "DROP TABLE IF EXISTS Catalogs";
	QString crCatalogsTable = "CREATE TABLE Catalogs(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT(255), description TEXT(512), iconId INT, catSize INT, numFiles INT, numDirs INT, numGroups INT, numCD INT, numDVD INT, numNetDrives INT, numFlash INT, numHDD INT, numFDD INT, flags INT, readPass TEXT, writePass TEXT, datetime INT)";
    
	QString dropDiskNumbersTable = "DROP TABLE IF EXISTS DiskNumbers";
	QString crDiskNumbersTable = "CREATE TABLE DiskNumbers(id INTERGER, seq INTEGER)";
    
//	QSqlDatabase _db;
     //db = QSqlDatabase::addDatabase(DBTYPE, "AA");
	db.setDatabaseName(fileName);
	printQS(fileName);
	db.open();
    
	wq = new QSqlQuery(db);
	if (!wq->exec(dropIconsTable))
	{
		FREE_PTR(wq);
		return false;
	}
	if (!wq->exec(crIconsTable))
	{
		FREE_PTR(wq);
		return false;
	}
    if (!wq->exec(dropNodeTypes))
	{
		FREE_PTR(wq);
		return false;
	}
    if (!wq->exec(crNodeTypes))
	{
		FREE_PTR(wq);
		return false;
	}
	if (!wq->exec(dropCatalogsTable))
	{
		FREE_PTR(wq);
		return false;
	}
	if (!wq->exec(crCatalogsTable))
	{
		FREE_PTR(wq);
		return false;
	}
	if (!wq->exec(dropDiskNumbersTable))
	{
		FREE_PTR(wq);
		return false;
	}
	if (!wq->exec(crDiskNumbersTable))
	{
		FREE_PTR(wq);
		return false;
	}
	FREE_PTR(wq);
    
   // IconManager im(_db);
    //im.fillDefaultIcons();
    
	db.close();
	return true;
}


CatTreeItem::CatTreeItem(CatTreeItem * it) : QTreeWidgetItem(it)
{
}


CatTreeItem::~CatTreeItem()
{
}


bool CatTreeItem::contains(CatTreeItem * item)
{
	//printQS("---\nthis = " + text(0) + "\n find = " + item->text(0) + "\n---");
	if (this == item)
		return false;
	else
    	return findItem(this, item);
}

bool CatTreeItem::findItem(CatTreeItem * start, CatTreeItem * what)
{
    int childrenNum = start->childCount();
	for (int i = 0; i < childrenNum; i++)
	{
		CatTreeItem *_child = static_cast <CatTreeItem *> (start->child(i));
		if (_child == what)
				return true;
		else{
			bool res = false;
			if (_child->childCount() > 0)
				res = findItem(_child, what);
			if (res)
				return true;
		}
	}
	return false;
}

QList<QCatItem*> QCatDataModuleClass::readCatalogs(QCatItem *rootItem, bool recursive){

	QString sql =	"SELECT id, name, description, iconId, catSize, "
					"numFiles, numDirs, numGroups, numCD, numDVD, "
					"numNetDrives, numFlash, numHDD, numFDD, flags, "
					"readPass, writePass, dateTime FROM Catalogs";
	QSqlQuery *q = new QSqlQuery(db);
	QList<QCatItem*> result;

	if (!q->exec(sql))
	{
		FREE_PTR(q);
		return result;

	}else{

		while (q->next())
		{
			QCatItem *pCat			= new QCatItem(CATALOG_ELEMENT, rootItem);
			fillDataFromQueryForCatalog(q, pCat);
			result.append(pCat);
		}

	}
	FREE_PTR(q);
	return result;

}

QList<QCatItem*> QCatDataModuleClass::readItemsFromCatalog(int catId, int parentId, bool readFiles, bool recursive){
	QList<QCatItem*> result;
	return result;
}

QList<QCatItem*> QCatDataModuleClass::readItemsFromCatalog(QCatItem *parent, bool readFiles, bool recursive){
	QList<QCatItem*> result;

	if (parent){
		// It is a valid parent item. So let's extract the data and make some SQL Queries
		int itemType = parent->itemType();
		int catalogId = parent->getCatalogId();
		int parentId = 0;
		if (itemType != CATALOG_ELEMENT){
			parentId = parent->getItemNode()->id;
		}
		QString sql = QString("SELECT id, parent, itemType, name, size, dateTime, "
				"otherNum, iconId, description, attributes, owner, grp, flag, "
				"mimeType, diskNo FROM Catalog_%1 WHERE parent = %2 ORDER BY diskNo").arg(catalogId).arg(parentId);
		qDebug() << sql.toUtf8().data();

		QSqlQuery *q = new QSqlQuery(db);
		if (!q)
			return result;
		if (!q->exec(sql))
		{
			FREE_PTR(q);
			return result;
		}else{
			while (q->next()){
				QCatItem *item = new QCatItem(q->value(2).toInt(), parent);
				fillDataFromQueryForItem(q, item, catalogId);
				parent->getChildren()->append(item);
			}
		}
		if (readFiles){
			sql = QString("SELECT id, parent, itemType, name, size, dateTime, "
				  "otherNum, iconId, description, attributes, owner, grp, "
				  "flag, mimeType, diskNo FROM Files_%1 WHERE parent = '%2'").arg(catalogId).arg(parentId);
			if (q->exec(sql))
			{
				while (q->next())
				{

					QCatItem *item = new QCatItem(q->value(2).toInt(), parent);
					fillDataFromQueryForItem(q, item, catalogId);
					parent->getChildren()->append(item);
				}
			}
		}
		FREE_PTR(q);

		if (recursive){
			// Read all recursively
			foreach (QCatItem *item, *parent->getChildren()) {
				if (item->itemType() != FILE_ELEMENT){
					readItemsFromCatalog(item, readFiles, recursive);
				}
			}
		}

	}

	return result;
}

void QCatDataModuleClass::fillDataFromQueryForCatalog(QSqlQuery *query, QCatItem *item){
	if (query && item && item->getCatNode()){
		CatNode *node			= item->getCatNode();
		//catalogNode *pCat	 	= new catalogNode;
		node->catId 			= query->value(0).toInt();
		node->catName			= query->value(1).toString();
		node->catDescription	= query->value(2).toString();
		node->iconId 			= query->value(3).toInt();
		node->catSize 			= query->value(4).toInt();
		node->numFiles 			= query->value(5).toInt();
		node->numDirs 			= query->value(6).toInt();
		node->numGroups 		= query->value(7).toInt();
		node->numCD 			= query->value(8).toInt();
		node->numDVD 			= query->value(9).toInt();
		node->numNetDrives		= query->value(10).toInt();
		node->numFlash 			= query->value(11).toInt();
		node->numHDD 			= query->value(12).toInt();
		node->numFDD 			= query->value(13).toInt();
		node->catFlags 			= query->value(14).toInt();
		node->catReadPass 		= query->value(15).toString();
		node->catWritePass 		= query->value(16).toString();
		node->dateTime			= query->value(17).toInt();

		node->isReadProtected	= (node->catFlags & READ_PROTECTED) ? true : false;
		node->isWriteProtected	= (node->catFlags & WRITE_PROTECTED) ? true : false;
		node->isOpened			= (node->catFlags & CATALOG_OPENED)	? true : false;
		if (node->isReadProtected)
			node->isOpened = false;

		node->isReadUnlocked 	= false;
		node->isWriteUnlocked	= false;
	}else{
		logger.warn("Invalid incomming data. QCatDataModuleClass::fillDataFromQueryForCatalog()", __FILE__, __LINE__);
	}

}

void QCatDataModuleClass::fillDataFromQueryForItem(QSqlQuery *query, QCatItem *item, int catId){
	if (query && item && item->getItemNode()){
		ItemNode *node = item->getItemNode();

		node->catId			= catId;
		node->id			= query->value(0).toInt();
		node->parent		= query->value(1).toInt();
		node->nodeType		= query->value(2).toInt();
		node->nodeName		= query->value(3).toString();
		node->nodeSize		= query->value(4).toLongLong();
		node->dateTime		= query->value(5).toInt();
		node->otherNum		= query->value(6).toInt();
		node->iconId		= query->value(7).toInt();
		node->nodeDesc		= query->value(8).toString();
		node->nodeAttr		= query->value(9).toInt();
		node->nodeOwner		= query->value(10).toString();
		node->nodeGrp		= query->value(11).toString();
		node->nodeFlags		= query->value(12).toInt();
		node->nodeMimeType	= query->value(13).toString();
		node->diskNo		= query->value(14).toInt();

	}else{
		logger.warn("Invalid incomming data. QCatDataModuleClass::fillDataFromQueryForItem()", __FILE__, __LINE__);
	}
}
