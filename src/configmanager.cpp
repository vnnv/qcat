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
#include <QWidget>
#include <QtGui>

#include "defsandtools.h"
#include "configmanager.h"
#include "logger.h"


ConfigManager::ConfigManager()
{
    allSettings = new QSettings(APPNAME, APPCOMPANY);
}


ConfigManager::~ConfigManager()
{
    if (!allSettings)
        return;
	FREE_PTR(allSettings);
}

void ConfigManager::loadSettings()
{
    int colsCatalogSizes[] = {160, 90, 90, 150, 90, 60, 80, 80};
    int colsDiskSizes[] = {260, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80};
    
    if (!allSettings)
        return;
    
    appPos = allSettings->value(SCR_POS, QPoint(200, 200)).toPoint();
    appSize = allSettings->value(SCR_SIZE, QSize(600, 400)).toSize();
    lastFile = allSettings->value(LAST_FILE_USED, "").toString();
    lastDir = allSettings->value(LAST_DIR_USED, "").toString();
    autoOpenLastFile = allSettings->value(AUTO_OPEN_LAST_FILE, true).toBool();
    dontCloseAfterScan = allSettings->value(DONT_CLOSE_AFTER_SCAN, true).toBool();
    searchFileNames = allSettings->value(SEARCH_FN, true).toBool();
    searchDirNames = allSettings->value(SEARCH_DI, true).toBool();
    searchDescriptions = allSettings->value(SEARCH_DE, true).toBool();
    searchCaseSensitive = allSettings->value(SEARCH_CS, false).toBool();
    
    catalogsColumns = allSettings->value(COLS_CATALOG, COL_CATALOG_DEFAULT).toInt();
    disksColumns = allSettings->value(COLS_DISK, COL_DISK_DEFAULT).toInt();
    
    for (int i = 0; i < 8; ++i)
    {
        catColumnSizes[i] = allSettings->value("CAT_COLUMN_NO_" + QString::number(i), colsCatalogSizes[i]).toInt();
    }
    for (int i = 0; i < 11; ++i)
    {
        diskColumnSizes[i] = allSettings->value("DISK_COLUMN_NO_" + QString::number(i), colsDiskSizes[i]).toInt();
    }
	numPlaces = allSettings->beginReadArray(SCAN_PLACES);
	for (int i = 0; i < numPlaces; ++i)
	{
		allSettings->setArrayIndex(i);
		structScanPlaces sp;
		sp.name = allSettings->value("spName").toString();
		sp.path = allSettings->value("spPath").toString();
		sp.itemType = allSettings->value("spType").toInt();
		sp.useMount = allSettings->value("spMnt").toBool();
		scanPlaces.append(sp);
	}
	allSettings->endArray();
}


/**
 * 
 */
void ConfigManager::saveSettings()
{
    allSettings->setValue(SCR_POS, appPos);
    allSettings->setValue(SCR_SIZE, appSize);
    allSettings->setValue(LAST_FILE_USED, lastFile);
    allSettings->setValue(LAST_DIR_USED, lastDir);
    allSettings->setValue(AUTO_OPEN_LAST_FILE, autoOpenLastFile);
    allSettings->setValue(DONT_CLOSE_AFTER_SCAN, dontCloseAfterScan);
    allSettings->setValue(COLS_CATALOG, catalogsColumns);
    allSettings->setValue(COLS_DISK, disksColumns);
    allSettings->setValue(SEARCH_CS, searchCaseSensitive);
    allSettings->setValue(SEARCH_FN, searchFileNames);
    allSettings->setValue(SEARCH_DI, searchDirNames);
    allSettings->setValue(SEARCH_DE, searchDescriptions);
    
    for (int i = 0; i < 8; ++i)
    {
        allSettings->setValue("CAT_COLUMN_NO_" + QString::number(i), catColumnSizes[i]);
    }
    for (int i = 0; i < 11; ++i)
    {
        allSettings->setValue("DISK_COLUMN_NO_" + QString::number(i), diskColumnSizes[i]);
    }
	allSettings->beginWriteArray(SCAN_PLACES);
	for (int i = 0; i < scanPlaces.size(); ++i)
	{
		allSettings->setArrayIndex(i);
		allSettings->setValue("spName", scanPlaces.at(i).name);
		allSettings->setValue("spPath", scanPlaces.at(i).path);
		allSettings->setValue("spType", scanPlaces.at(i).itemType);
		allSettings->setValue("spMnt", scanPlaces.at(i).useMount);
	}
	allSettings->endArray();
	

}

bool ConfigManager::isCatalogColumnVisible(int columnNo)
{
    // I know that there is no need for break, but I put it for the style
	switch (columnNo)
    {
        case 0:
            return (catalogsColumns & COL_CATALOG_NAME) ? true : false;
            break;
        case 1:
            return (catalogsColumns & COL_CATALOG_TYPE) ? true : false;
            break;
        case 2:
            return (catalogsColumns & COL_CATALOG_CAPACITY) ? true : false;
            break;
        case 3:
            return (catalogsColumns & COL_CATALOG_LAST_UPDATE) ? true : false;
            break;
        case 4:
            return (catalogsColumns & COL_CATALOG_DESCRIPTION) ? true : false;
            break;
        case 5:
            return (catalogsColumns & COL_CATALOG_DISK_NO) ? true : false;
            break;
        case 6:
            return (catalogsColumns & COL_CATALOG_DISK_LOCATION) ? true : false;
            break;
        case 7:
            return (catalogsColumns & COL_CATALOG_FLAGS) ? true : false;
            break;
        default:
            return false;
    }
}

bool ConfigManager::isDiskColumnVisible(int columnNo)
{
    // I know that there is no need for break, but I put it for the style
    switch (columnNo)
    {
        case 0:
            return (disksColumns & COL_DISK_NAME) ? true : false;
            break;
        case 1:
            return (disksColumns & COL_DISK_EXT) ? true : false;
            break;
        case 2:
            return (disksColumns & COL_DISK_SIZE) ? true : false;
            break;
        case 3:
            return (disksColumns & COL_DISK_DATE) ? true : false;
            break;
        case 4:
            return (disksColumns & COL_DISK_TIME) ? true : false;
            break;
        case 5:
            return (disksColumns & COL_DISK_ATTRIBUTES) ? true : false;
            break;
        case 6:
            return (disksColumns & COL_DISK_DESCRIPTION) ? true : false;
            break;
        case 7:
            return (disksColumns & COL_DISK_OWNER) ? true : false;
            break;
        case 8:
            return (disksColumns & COL_DISK_GROUP) ? true : false;
            break;
        case 9:
            return (disksColumns & COL_DISK_FLAGS) ? true : false;
            break;
        case 10:
            return (disksColumns & COL_DISK_DISK_NO) ? true : false;
            break;
        default:
            return false;
    }
    
}

void ConfigManager::testCM()
{
	logger.debug("ConfigManager Works", __FILE__, __LINE__);
}
