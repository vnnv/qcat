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
#include "qcatitemmodel.h"
#include "qcatitem.h"
#include "QDebug"
#include "defsandtools.h"
#include "datamodule.h"
#include "catalogclass.h"
#include "dbnode.h"
#include "iconmanager.h"
#include <QIcon>

QCatItemModel::QCatItemModel(QCatDataModuleClass *dbmodule) : dm(dbmodule)
{
//	setupModel();
	setupModelDb();
//	root = new QCatItem("root", 0);
//	QCatItem *item1 = new QCatItem("Item1", root);
//	QCatItem *item2 = new QCatItem("item2", root);
//	QCatItem *item2_1 = new QCatItem("Item 2_1", item2);
//	QCatItem *item3 = new QCatItem("item3", root);

//	root->addChild(item1);
//	root->addChild(item2);
//	item2->addChild(item2_1);
//	root->addChild(item3);
}


QVariant QCatItemModel::data(const QModelIndex &index, int role) const{
//	qDebug() << "data()";
	if (!index.isValid())
		 return QVariant();

	if (role == Qt::DisplayRole){
		QCatItem *item = static_cast<QCatItem*>(index.internalPointer());
		return item->data(dm, index.column(), role);
		return QString(item->getName());

		if (item->isRoot()){
			return QString("Catalog %1").arg(index.row());
		}else{
			//qDebug() << item->getName();
			return item->getName();
		}
		 //return QString("%1 %2").arg(item->data()).arg(index.row());
	}

	if (role == Qt::DecorationRole){
		QCatItem *item = static_cast<QCatItem*>(index.internalPointer());
		return item->data(dm, index.column(), role);
		/*
		QIcon result = QIcon();
		int iconId = 0;
		int itemType = item->itemType();
		int catId = 0;
		if (itemType == CATALOG_ELEMENT){
			iconId = item->getCatNode()->iconId;
			catId = item->getCatNode()->catId;
		}else{
			iconId = item->getItemNode()->iconId;
			catId = item->getItemNode()->catId;
		}
		switch (itemType)
		{
			case GROUP_ELEMENT:
			{
				QPixmap *pix = 0;
				if (!iconId)
				{
					pix = dm->im->getPixmap(0, DISK_GROUP_ICON);
				}else{
					pix = dm->im->getPixmap(catId, iconId);
				}
				if (pix)
					result =  QIcon(*pix);
				delete pix;
			}
			break;
			case DISK_ELEMENT:
			{
				QPixmap *pix = 0;
				if (!iconId)
				{
					pix = dm->im->getDefaultPixmap(DISK_ELEMENT, item->getItemNode()->iconId);
//					pix = dm->im->getDefaultPixmap(DISK_ELEMENT, item->getItemNode()->fullType);
				}else{
					pix = dm->im->getPixmap(catId, iconId);
				}
				if (pix)
					result =  QIcon(*pix);
				delete pix;
			}
			break;
			case FOLDER_ELEMENT:
			{
				QPixmap *pix = 0;
				if (!iconId)
				{
					pix = dm->im->getPixmap(0, FOLDER_CLOSED_ICON);
				}else{
					pix = dm->im->getPixmap(catId, iconId);
				}
				if (pix)
					result =  QIcon(*pix);
				delete pix;
			}
			break;
		}
		return result;

	}
 */}

	return QVariant();
}

Qt::ItemFlags QCatItemModel::flags(const QModelIndex &index) const{
	if (!index.isValid())
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	return QAbstractItemModel::flags(index);

}
QVariant QCatItemModel::headerData(int section, Qt::Orientation orientation, int role) const{
	if (role != Qt::DisplayRole)
		 return QVariant();

	 if (orientation == Qt::Horizontal)
		 return QString("Column %1").arg(section);
	 else
		 return QString("Row %1").arg(section);
}
QModelIndex QCatItemModel::index(int row, int column,
								 const QModelIndex &parent) const{
//	qDebug() << "index() " << "Row = " << row << " col = " << column;
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	QCatItem *parentItem = 0;
	if (!parent.isValid()){
//		qDebug() << "********************Parent is root";
		parentItem = root;
	}else{
		parentItem = static_cast<QCatItem*>(parent.internalPointer());
	}

	QCatItem *childItem = parentItem->getChildren()->value(row);
	if (childItem){
		return createIndex(row, column, childItem);
	}else{
		return QModelIndex();
	}

	/*
	  old
	if (parent.isValid()){
		qDebug() << "Valid parent. Name = " << parentItem->getName() ;

		if (parentItem->getChildren()->size() == 0){
			return QModelIndex();
		}
		QCatItem *child = parentItem->getChildren()->at(row);
		if (child){
			return createIndex(row, column, child);
		}

	}else{
		return createIndex(row, column, root->getChildren()->at(row));
	}
*/


}
QModelIndex QCatItemModel::parent(const QModelIndex &index) const{


//	qDebug() << "parent() " << "Row = " << index.row() << " col = " << index.column();

	if (!index.isValid()){
		qDebug() << "ret QModelIndex()";
		return QModelIndex();
	}
	QCatItem *childItem = static_cast<QCatItem*>(index.internalPointer());
	QCatItem *parentItem = childItem->parent();
	if (parentItem->isRoot()){
		return QModelIndex();
	}else{
		return createIndex(parentItem->getChildren()->indexOf(const_cast<QCatItem*>(childItem)), 0, parentItem);
	}
/* old
	if (item != NULL){
		//qDebug() << " Parent name = " << item->getName();

		QCatItem *parentItem = item->parent();
		if (parentItem->isRoot()){
			return QModelIndex();
		}else{
			return createIndex(parentItem->getChildren()->indexOf(item), index.column(), item);
		}


	}*/
	return QModelIndex();

}
int QCatItemModel::rowCount(const QModelIndex &parent) const{
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid()){
//		qDebug() << "---------Parent is not valid!";
		return root->getChildren()->count();
	}else{
		QCatItem *parent_item = static_cast<QCatItem*>(parent.internalPointer());
//		qDebug() << "******* Rows = " << parent_item->getChildren()->size();
		return parent_item->getChildren()->size();
	}
}
int QCatItemModel::columnCount(const QModelIndex &parent) const{
	return 8;
}

bool QCatItemModel::hasChildren(const QModelIndex &parent) const{

	if (parent.isValid()){
		QCatItem *item = static_cast<QCatItem*>(parent.internalPointer());
		return item->getChildren()->size();
	}else{

		return root->getChildren()->size();
		//return false;
	}
	/*
	QCatItem *item = static_cast<QCatItem*>(parent.internalPointer());
	return item->isRoot();
	*/
}

void QCatItemModel::setupModel(){
	root = new QCatItem(MODEL_ROOT, 0);
	root->setRoot(true);

	QCatItem *i;
	CatNode *catNode;
	ItemNode *itemNode;

	i = new QCatItem(CATALOG_ELEMENT, root);
	catNode = i->getCatNode();
	catNode->catName = "Catalog1";
	catNode->catId = 1;
	root->addChild(i);

	i = new QCatItem(CATALOG_ELEMENT, root);
	catNode = i->getCatNode();
	catNode->catName = "Catalog2";
	catNode->catId = 2;
	root->addChild(i);

	i = new QCatItem(CATALOG_ELEMENT, root);
	catNode = i->getCatNode();
	catNode->catName = "Catalog3";
	catNode->catId = 3;
	root->addChild(i);

	i = new QCatItem(CATALOG_ELEMENT, root);
	catNode = i->getCatNode();
	catNode->catName = "Catalog4";
	catNode->catId = 4;
	root->addChild(i);

	// 3 catalogs created

	i = new QCatItem(DISK_ELEMENT, root->getChildren()->value(0));
	itemNode = i->getItemNode();
	itemNode->diskNo = 1;
	itemNode->nodeName = "Disk1";
	QList<QCatItem*> *l = root->getChildren();

	QCatItem *ll = l->at(0);
	*ll->getChildren() << i;

	i = new QCatItem(DISK_ELEMENT, root->getChildren()->value(0));
	itemNode = i->getItemNode();
	itemNode->diskNo = 2;
	itemNode->nodeName = "Disk2";
	*root->getChildren()->at(0)->getChildren() << i;

	i = new QCatItem(DISK_ELEMENT, root->getChildren()->value(1));
	itemNode = i->getItemNode();
	itemNode->diskNo = 3;
	itemNode->nodeName = "Disk3";
	*root->getChildren()->at(1)->getChildren() << i;

	i = new QCatItem(FOLDER_ELEMENT, root->getChildren()->value(1)->getChildren()->value(0));
	itemNode = i->getItemNode();
	itemNode->diskNo = 3;
	itemNode->nodeName = "Folder1";
	*root->getChildren()->at(1)->getChildren()->at(0)->getChildren() << i;



}

void QCatItemModel::setupModelDb(){
	root = new QCatItem(MODEL_ROOT, 0);
	root->setRoot(true);

	if (dm->cat->items.size() > 0)
	{
		qDebug() << "Found " << dm->cat->items.size() << " catalogs.";
		for (int i = 0; i < dm->cat->items.size(); ++i){
			QCatItem *item = new QCatItem(CATALOG_ELEMENT, root);
			item->setItemType(CATALOG_ELEMENT);
			item->getCatNode()->catName = dm->cat->items.value(i)->catName;
			item->getCatNode()->catFlags = dm->cat->items.value(i)->catFlags;
			item->getCatNode()->catId = dm->cat->items.value(i)->catId;
			item->getCatNode()->iconId = dm->cat->items.value(i)->iconId;
			item->getCatNode()->catFlags = dm->cat->items.value(i)->catFlags;
			item->getCatNode()->catFlags = dm->cat->items.value(i)->catFlags;
			root->getChildren()->append(item);

//			QCatItem *t = new QCatItem()
			dm->readItemsFromCatalog(item, true, true);

		}
	}else{

	}

}
