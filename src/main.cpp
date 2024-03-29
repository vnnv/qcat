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


#include <QApplication>

#include "mainwindow.h"
#include "logger.h"

#define console1

int main(int argc, char *argv[])
{
#ifdef console
	QCoreApplication app(argc, argv);
	//test_createDB();
	//test_fill_data();
#else

	Q_INIT_RESOURCE(application);
	//QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	//test_icons_save();
	//test_icons_to_db();
	//test_xml_parser();
	//test_diskClass();
	QApplication app(argc, argv);
	logger.setLevel(DEBUG);
	logger.debug("Starting application", __FILE__, __LINE__);

    
    MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
	
#endif
}

