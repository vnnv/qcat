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
#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include <ui_newdialog.h>

/**
	@author Victor Nike <victor.nike@gmail.com>
*/
class QCatDataModuleClass;

class NewDialog : public QDialog, public Ui::NewDBDialog
{
    Q_OBJECT
    public:
        NewDialog(QCatDataModuleClass *_dm, QWidget *parent = 0);
    
        ~NewDialog();
    
    private slots:
        void dbTypeItemChanged(int index);
        void fileBrowseClicked();
        
    private:
        QCatDataModuleClass *dm;
        QString fileName;

};

#endif
