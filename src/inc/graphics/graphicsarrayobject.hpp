/*
 * graphicsarrayobject.hpp
 *
 *  Created on: 29.4.2013
 *      Author: akin
 */

#ifndef GRAPHICSARRAYOBJECT_HPP_
#define GRAPHICSARRAYOBJECT_HPP_

namespace graphics {

class ArrayObject
{
private:
	unsigned int id;
public:
	ArrayObject();
	~ArrayObject();

	void release();

	bool hasInitialized() const;
	void initialize();

	unsigned int getID() const;

	void bind() const;
	void unbind() const;
};

} // namespace graphics
#endif // GRAPHICSARRAYOBJECT_HPP_
