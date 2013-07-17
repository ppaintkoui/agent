/*
 * RunningProcesses.cpp
 *
 *  Created on: 16/lug/2013
 *      Author: stefano
 */

#include "ProcReader.h"
#include "RunningProcessesList.h"

#include <dirent.h>
#include <stdlib.h>

#include <iostream>

static bool
IsNumber(std::string string)
{
	return !string.empty()
			&& string.find_first_not_of("0123456789") == std::string::npos;
}


RunningProcessesList::RunningProcessesList()
{
	DIR* dir = ::opendir("/proc/");
	if (dir != NULL) {
		dirent* entry = NULL;
		while ((entry = ::readdir(dir)) != NULL) {
			std::string procPid = entry->d_name;
			if (IsNumber(procPid)) {
				std::string fullName = "/proc/";
				fullName.append(procPid);
				process_info info;
				_ReadProcessInfo(info, procPid.c_str());
				fProcesses.push_back(info);
			}
		}
		::closedir(dir);
	}

	Rewind();
}


RunningProcessesList::~RunningProcessesList()
{
}


void
RunningProcessesList::Rewind()
{
	fIterator = fProcesses.begin();
}


bool
RunningProcessesList::GetNext(process_info &info)
{
	if (fIterator == fProcesses.end())
		return false;

	info = *fIterator;
	fIterator++;
	return true;
}


void
RunningProcessesList::_ReadProcessInfo(process_info& info, std::string pid)
{
	info.pid = strtol(pid.c_str(), NULL, 10);
	info.cmdline = ProcReader(pid.append("/cmdline").c_str()).ReadLine();
}