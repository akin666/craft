/*
 * atlas.h
 *
 *  Created on: 25.5.2011
 *      Author: akin
 */

#ifndef EXT_ATLAS_H_
#define EXT_ATLAS_H_

#ifndef ATLAS_WIDTH
# define ATLAS_WIDTH 1024
#endif

#ifndef ATLAS_HEIGHT
# define ATLAS_HEIGHT 1024
#endif

#ifndef ATLAS_PADDING
# define ATLAS_PADDING 1
#endif

#ifndef NO_GLM
# include <glm/glm>
#endif

#include <vector>

class Atlas
{
protected:
	class Node
	{
	public:
		Node();
		Node( const Node& other );
		Node( const signed int& ax , const signed int& ay , const signed int& width );

		~Node();

		signed int x,y;
		signed int width;
	};

	typedef std::vector<Node> NodeSet;

	signed int dimensionX;
	signed int dimensionY;
	signed int padding;
	NodeSet nodes;
	bool init;
	signed int usage;

	void merge();
	int fit( NodeSet::iterator iter , size_t width, size_t height );
public:
	Atlas();
	Atlas( const Atlas& other );
	~Atlas();

	void reset();

	bool initialized() const;

	void initialize( signed int width = ATLAS_WIDTH , signed int height = ATLAS_HEIGHT , signed int padding = ATLAS_PADDING );

	unsigned int getPadding() const;

	/**
	 * Request
	 * request a certain width & height, if there is space free, X and Y gets
	 * filled with the information.
	 * The X and Y will contain the padding. So if padding is 1 the real reserved
	 * area is [X-padding,X+widht+padding][Y-padding,Y+height+padding].
	 *
	 * IF the request cannot be satisfied false is returned.
	 */
	bool request( signed int req_width , signed int req_height , signed int& x , signed int& y );

	/**
	 * proxyRequest
	 * request a certain width & height, if there is space free returns true,
	 * but does not reserve the space.
	 *
	 * IF the request cannot be satisfied false is returned.
	 */
	bool proxyRequest( signed int req_width , signed int req_height );

	/**
	 * Release
	 * request to release a certain area.
	 * Width, Height, X and Y should be the same that were handled with request() function,
	 * the function will take into account the padding.
	 */
	bool release( signed int width , signed int height , signed int x , signed int y );

	/**
	 * Resize
	 * resize will resize the atlas to a specified size, also keeping the previously
	 * acquired areas intact and alive.
	 */
	bool resize( signed int new_width , signed int new_height );

	signed int getWidth() const;
	signed int getHeight() const;

#ifndef NO_GLM
	void initialize( const glm::ivec2& dimensions , signed int padding = ATLAS_PADDING );
	bool request( const glm::ivec2& dimensions , glm::ivec2& spot );
	bool release( const glm::ivec2& dimensions , const glm::ivec2& spot );
	bool resize( const glm::ivec2& dimensions );
#endif
};

#endif // EXT_ATLAS_H_
