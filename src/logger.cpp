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
#include "logger.h"

#include <QDebug>

Logger Logger::INSTANCE = Logger();
LogLevel Logger::level = DEBUG;

Logger::Logger(){

}

Logger::~Logger(){

}

void Logger::setLevel(LogLevel _level){
	this->level = _level;
}

void Logger::print(const QString &msg){
	qDebug() << msg.toUtf8();
}

void Logger::trace(const QString &msg, const QString &className, int line){
	if (level <= TRACE){
		QString res = "[TRACE] " + className + ":" + QString::number(line) + " - " + msg;
		print(res);
	}
}
void Logger::debug(const QString &msg, const QString &className, int line){
	if (level <= DEBUG){
		QString res = "[DEBUG] " + className + ":" + QString::number(line) + " - " + msg;
		print(res);
	}
}
void Logger::info(const QString &msg, const QString &className, int line){
	if (level <= INFO){
		QString res = "[INFO] " + className + ":" + QString::number(line) + " - " + msg;
		print(res);
	}
}
void Logger::warn(const QString &msg, const QString &className, int line){
	if (level <= WARN){
		QString res = "[WARN] " + className + ":" + QString::number(line) + " - " + msg;
		print(res);
	}
}
void Logger::error(const QString &msg, const QString &className, int line){
	if (level <= ERROR){
		QString res = "[ERROR] " + className + ":" + QString::number(line) + " - " + msg;
		print(res);
	}
}
