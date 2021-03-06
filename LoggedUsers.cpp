/*
 * LoggedUsers.cpp
 *
 *  Created on: 15/lug/2013
 *      Author: Stefano Ceccherini
 */

#include "LoggedUsers.h"
#include "Support.h"

#include <ctime>

#include <utmpx.h>

LoggedUsers::LoggedUsers()
{
	setutxent();

	struct utmpx* record = NULL;
	while ((record = getutxent()) != NULL) {
		if (record->ut_type == USER_PROCESS) {
			user_entry entry;
			entry.login = record->ut_user;
			time_t loginTime = record->ut_tv.tv_sec;
			entry.logintime = loginTime;
			struct tm* timeinfo = localtime(&loginTime);
			char timeString[64];
			strftime(timeString, sizeof(timeString), "%a %b %d %R", timeinfo);
			entry.logintimestring = timeString;
			fUsers.push_back(entry);
		}
	}

	endutxent();
}


LoggedUsers::~LoggedUsers()
{
}


int
LoggedUsers::Count() const
{
	return fUsers.size();
}


user_entry
LoggedUsers::UserEntryAt(int i) const
{
	return fUsers[i];
}


std::string
LoggedUsers::LoginNameAt(int i) const
{
	return fUsers[i].login;
}
