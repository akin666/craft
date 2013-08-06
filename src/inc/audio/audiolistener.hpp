/*
 * audiolistener.hpp
 *
 *  Created on: 31.7.2013
 *      Author: akin
 */

#ifndef AUDIOLISTENER_HPP_
#define AUDIOLISTENER_HPP_

#include <glm/glm>

namespace audio
{

class Listener
{
private:
	glm::vec4 up;
	glm::vec4 at;
	glm::vec4 position;
	float orientation[6];
	int error;
public:
	Listener();
	~Listener();

	void setPosition( const glm::mat4& matrix );
	void setVelocity( const glm::vec4& velocity );
	void setVolume( float volume );
};

} // namespace audio
#endif // AUDIOLISTENER_HPP_
