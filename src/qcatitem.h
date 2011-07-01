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
#ifndef QCATITEM_H
#define QCATITEM_H

#include <QStandardItem>
#include <QObject>
#include <QtGlobal>


class QCatDataModuleClass;

struct ItemNode{
	long int id;
	int catId;
	int parent;
	int nodeType;
	QString nodeName;
	qlonglong nodeSize;
	int dateTime;
	int otherNum;
	int iconId;
	QString nodeDesc;
	int nodeAttr;
	QString nodeOwner;
	QString nodeGrp;
	int nodeFlags;
	QString nodeMimeType;
	int diskNo;

};

struct CatNode{
	int catId;
	QString catName;
	QString catDescription;
	int iconId;
	qlonglong catSize;
	int numFiles;
	int numDirs;
	int numGroups;
	int numCD;
	int numDVD;
	int numNetDrives;
	int numFlash;
	int numHDD;
	int numFDD;
	int catFlags;
	QString catReadPass;
	QString catWritePass;
	int dateTime;

	bool isReadProtected;
	bool isReadUnlocked;
	bool isWriteProtected;
	bool isWriteUnlocked;
	bool isOpened;
};


class QCatItem : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int itemType READ itemType WRITE setItemType)



public:

	QCatItem(int itemType, QCatItem *parent = 0);
	virtual ~QCatItem();

	QCatItem* parent() const;

	// Children methods
	bool hasChildren();
	QList<QCatItem*> *getChildren() ;
	void addChild(QCatItem *item);
	void removeChild(QCatItem *item);

	int itemType() const;
	void setItemType(int _itemType);

	CatNode* getCatNode() const;
	ItemNode* getItemNode() const;
	virtual QString data() const;

	void setRoot(bool root);
	bool isRoot() const;
	QString getName() const;
	int getCatalogId() const;

	QVariant data(QCatDataModuleClass *dm, int column, int role) const;


public:
	QCatItem *m_parent;
	QList<QCatItem*> m_children;

	int m_itemType;
	bool m_isRoot;
	CatNode *m_catNode;
	ItemNode *m_itemNode;

private:
	void initItemNodeData(ItemNode *node);
	void initCatNodeData(CatNode *node);


};

#endif // QCATITEM_H
