/*
 * graphicsconfiguration.hpp
 *
 *  Created on: 27.5.2013
 *      Author: akin
 */

#ifndef GRAPHICSCONFIGURATION_HPP_
#define GRAPHICSCONFIGURATION_HPP_

#include <stdtypes>
#include <unordered_map>

namespace graphics {

class Configuration
{
private:
	std::unordered_map< std::string , unsigned int > textureUnits;
public:
	Configuration();
	~Configuration();

	void setTextureUnit( const std::string& name , unsigned int unit );

	unsigned int textureUnitFor( const std::string& name ); // "normal" "diffuse" "shine" whatever.
};

} // namespace graphics
#endif // GRAPHICSCONFIGURATION_HPP_
