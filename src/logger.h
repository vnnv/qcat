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
#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

enum LogLevel{
	TRACE = 0,
	DEBUG,
	INFO,
	WARN,
	ERROR
};


class Logger
{
public:
	static Logger getInstance() {return INSTANCE;}
	void setLevel(LogLevel level);
	LogLevel getLevel(){ return level;}

	void trace(const QString &msg, const QString &className = "<not_specifed>", int line = -1);
	void debug(const QString &msg, const QString &className = "<not_specifed>", int line = -1);
	void info(const QString &msg, const QString &className = "<not_specifed>", int line = -1);
	void warn(const QString &msg, const QString &className = "<not_specifed>", int line = -1);
	void error(const QString &msg, const QString &className = "<not_specifed>", int line = -1);
	~Logger();

private:
    Logger();
	void print(const QString &msg);
	static Logger INSTANCE;
	static LogLevel level;
};

static Logger logger = Logger::getInstance();

#endif // LOGGER_H
