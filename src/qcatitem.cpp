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
#include "defsandtools.h"
#include "datamodule.h"
#include "iconmanager.h"

#include "qcatitem.h"
#include <QDateTime>
#include <QDate>
#include <QTime>

QCatItem::QCatItem(int itemType, QCatItem *parent)
	: m_itemType(itemType), m_parent(parent), m_catNode(0), m_itemNode(0), m_isRoot(false){
	if (m_itemType == MODEL_ROOT){
		return;
	}
	if (m_itemType == CATALOG_ELEMENT){
		m_catNode = new CatNode;
		initCatNodeData(m_catNode);
	}else{
		m_itemNode = new ItemNode;
		initItemNodeData(m_itemNode);
	}

}

QCatItem::~QCatItem(){
	FREE_PTR(m_catNode)
	FREE_PTR(m_itemNode)
}

int QCatItem::itemType()const {
	return m_itemType;
}

void QCatItem::setItemType(int _itemType){
	m_itemType = _itemType;
}

CatNode* QCatItem::getCatNode()const{
	return m_catNode;
}
ItemNode* QCatItem::getItemNode()const{
	return m_itemNode;
}

QCatItem* QCatItem::parent() const{
	return m_parent;
}

QString QCatItem::data() const{
	if (itemType() == CATALOG_ELEMENT)
		return QString("Catalog");
	else
		return QString("Disk");
}

bool QCatItem::hasChildren(){
	return (m_children.size() > 0);
}

QList<QCatItem*> *QCatItem::getChildren() {
	return &m_children;
}

void QCatItem::addChild(QCatItem *item){
	m_children.append(item);
}

void QCatItem::removeChild(QCatItem *item){
	int i = m_children.indexOf(item);
	if (i != -1){
		m_children.removeAt(i);
	}
}

bool QCatItem::isRoot() const{
	return m_isRoot;
}

void QCatItem::setRoot(bool root){
	m_isRoot = root;
}

QString QCatItem::getName() const{
	if (isRoot()){
		return QString("Root Node.");
	}else{
		if (itemType() == CATALOG_ELEMENT){
			return getCatNode()->catName;
		}else{
			return getItemNode()->nodeName;
		}
	}
}

void QCatItem::initCatNodeData(CatNode *node){
	if (node){
		node->catDescription = QString();
		node->catFlags = 0;
		node->catId = -1;
		node->catName = QString();
		node->catReadPass = QString();
		node->catSize = 0;
		node->catWritePass = QString();
		node->dateTime = 0;
		node->iconId = -1;
		node->isOpened = false;
		node->isReadProtected = false;
		node->isReadUnlocked = false;
		node->isWriteProtected = false;
		node->isWriteUnlocked = false;
		node->numCD = 0;
		node->numDirs = 0;
		node->numDVD = 0;
		node->numFDD = 0;
		node->numFiles = 0;
		node->numFlash = 0;
		node->numGroups = 0;
		node->numHDD = 0;
		node->numNetDrives = 0;
	}
}

void QCatItem::initItemNodeData(ItemNode *node){
	if (node){
		node->catId = -1;
		node->dateTime = 0;
		node->diskNo = -1;
		node->iconId = -1;
		node->id = -1;
		node->nodeAttr = 0;
		node->nodeDesc = QString();
		node->nodeFlags = 0;
		node->nodeGrp = QString();
		node->nodeMimeType = QString();
		node->nodeName = QString();
		node->nodeOwner = QString();
		node->nodeSize = 0;
		node->nodeType = 0;
		node->otherNum = 0;
		node->parent = 0;
	}
}

int QCatItem::getCatalogId() const{
	if (itemType() == CATALOG_ELEMENT)
		return getCatNode()->catId;
	else
		return getItemNode()->catId;
}

QVariant QCatItem::data(QCatDataModuleClass *dm, int column, int role) const{

	if (role == Qt::DisplayRole){
		if (isRoot())
			return QString(tr("Root"));
		if (itemType() == CATALOG_ELEMENT){
			switch(column){
			case 0: return getName();
			default:
				return QVariant();
			}
		}else{
			vFileName data;
			parseFileName(getName(), data);
			QDateTime dt = QDateTime::fromTime_t(getItemNode()->dateTime);

			if (itemType() == GROUP_ELEMENT || itemType() == DISK_ELEMENT){
				switch(column){
				case 0: return getName();
				case 1: return QString(tr("MediaType"));
				case 2: return QString::number(getItemNode()->nodeSize);
				case 3: return QDateTime::fromTime_t(getItemNode()->dateTime);
				case 4: return QString(getItemNode()->nodeDesc);
				case 5: return QString(getItemNode()->diskNo);
				case 6: return QString(tr("Location - dev"));
				default:
					return QVariant();
				}
			}else{
				switch(column){
				case 0: return QString(data.fileName);
				case 1: return QString(data.fileExt);
				case 2: return QString::number(getItemNode()->nodeSize);
				case 3: return dt.date().toString(Qt::LocalDate);
				case 4: return dt.time().toString(Qt::LocalDate);
				case 5: return QString(permsToQString(getItemNode()->nodeAttr));
				case 6: return QString(getItemNode()->nodeDesc);
				case 7: return QString(getItemNode()->diskNo);
				default:
					return QVariant();
				}

			}

		}

	}

	if (role == Qt::DecorationRole){
		QIcon result = QIcon();
		if (column > 0) return result;

		int iconId = 0;
		int catId = 0;
		if (itemType() == CATALOG_ELEMENT){
			iconId = getCatNode()->iconId;
			catId = getCatNode()->catId;
		}else{
			iconId = getItemNode()->iconId;
			catId = getItemNode()->catId;
		}
		switch (itemType())
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
				FREE_PTR(pix);
			}
			break;
			case DISK_ELEMENT:
			{
				QPixmap *pix = 0;
				if (!iconId)
				{
					pix = dm->im->getDefaultPixmap(DISK_ELEMENT, getItemNode()->iconId);
//					pix = dm->im->getDefaultPixmap(DISK_ELEMENT, item->getItemNode()->fullType);
				}else{
					pix = dm->im->getPixmap(catId, iconId);
				}
				if (pix)
					result =  QIcon(*pix);
				FREE_PTR(pix);
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
				FREE_PTR(pix);
			}
			break;
		}
		return result;

	}
	return QVariant();
}
