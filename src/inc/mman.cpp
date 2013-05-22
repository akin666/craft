/*
 * mman.cpp
 *
 *  Created on: 20.2.2013
 *      Author: akin
 */

#include "mman"

#if defined(OS_WINDOWS)

int mmapResolvePage( int begin )
{
	return begin;
}

#else
// Unixeh!
// http://stackoverflow.com/questions/5074981/please-explain-what-this-piece-of-c-code-does
int mmapResolvePage( int begin )
{
	return begin & ~(sysconf(_SC_PAGE_SIZE) - 1);
}

#endif
