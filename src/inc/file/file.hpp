/*
 * file.hpp
 *
 *  Created on: 14.3.2013
 *      Author: akin
 */

#ifndef FILE_HPP_
#define FILE_HPP_

#include <time/time.hpp>

class File
{
public:
	typedef std::vector<File> Set;
private:
	std::string fullPath;
	Second modified;
	size_t size;
	uint flags;
	static const std::string slash;
public:
	File();
	~File();

	void setModified( Second second );
	void setSize( size_t size );
	void setDirectory( bool val );
	void setPath( const File& parent , const std::string& filename );
	void setPath( const std::string& path );

	std::string getPath() const;
	std::string getFilename() const;
	std::string getExtension() const;
	size_t getSize() const;

	bool isDirectory() const;

	bool ls( Set& set ) const;
};

#endif // FILE_HPP_
