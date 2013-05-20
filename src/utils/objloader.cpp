/*
 * objoader.cpp
 *
 *  Created on: 28.4.2013
 *      Author: akin
 */

#include "objloader.hpp"
#include <stdtypes>
#include <glm/glm>
#include <iostream> // streams in general..
#include <sstream>  // istringstream
#include <native>

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

// !!! Code from
// !!! http://stackoverflow.com/questions/14887012/object-loader-in-opengl

using namespace glm;
using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texcoord;
	glm::vec3 normal;
};

struct VertRef
{
	VertRef( int v, int vt, int vn )
	: v(v)
	, vt(vt)
	, vn(vn)
	{
	}

	int v, vt, vn;
};

vector< Vertex > LoadOBJ( istream& in )
{
    vector< Vertex > verts;

    vector< vec4 > positions( 1, vec4( 0, 0, 0, 0 ) );
    vector< vec3 > texcoords( 1, vec3( 0, 0, 0 ) );
    vector< vec3 > normals( 1, vec3( 0, 0, 0 ) );
    string lineStr;
    while( getline( in, lineStr ) )
    {
        istringstream lineSS( lineStr );
        string lineType;
        lineSS >> lineType;

        // vertex
        if( lineType == "v" )
        {
            float x = 0, y = 0, z = 0, w = 1;
            lineSS >> x >> y >> z >> w;
            positions.push_back( vec4( x, y, z, w ) );
        }

        // texture
        if( lineType == "vt" )
        {
            float u = 0, v = 0, w = 0;
            lineSS >> u >> v >> w;
            texcoords.push_back( vec3( u, v, w ) );
        }

        // normal
        if( lineType == "vn" )
        {
            float i = 0, j = 0, k = 0;
            lineSS >> i >> j >> k;
            normals.push_back( normalize( vec3( i, j, k ) ) );
        }

        // polygon
        if( lineType == "f" )
        {
            vector< VertRef > refs;
            string refStr;
            while( lineSS >> refStr )
            {
                istringstream ref( refStr );
                string vStr, vtStr, vnStr;
                getline( ref, vStr, '/' );
                getline( ref, vtStr, '/' );
                getline( ref, vnStr, '/' );
                int v = atoi( vStr.c_str() );
                int vt = atoi( vtStr.c_str() );
                int vn = atoi( vnStr.c_str() );
                v  = (  v >= 0 ?  v : positions.size() +  v );
                vt = ( vt >= 0 ? vt : texcoords.size() + vt );
                vn = ( vn >= 0 ? vn : normals.size()   + vn );
                refs.push_back( VertRef( v, vt, vn ) );
            }

            if( refs.size() < 3 )
            {
                // error, skip
                continue;
            }

            // triangulate, assuming n>3-gons are convex and coplanar
            VertRef* p[3] = { &refs[0], NULL, NULL };
            for( size_t i = 1; i+1 < refs.size(); ++i )
            {
                p[1] = &refs[i+0];
                p[2] = &refs[i+1];

                // http://www.opengl.org/wiki/Calculating_a_Surface_Normal
                vec3 U( positions[ p[1]->v ] - positions[ p[0]->v ] );
                vec3 V( positions[ p[2]->v ] - positions[ p[0]->v ] );
                vec3 faceNormal = normalize( cross( U, V ) );

                for( size_t j = 0; j < 3; ++j )
                {
                    Vertex vert;
                    vert.position = vec3( positions[ p[j]->v ] );
                    vert.texcoord = vec2( texcoords[ p[j]->vt ] );
                    vert.normal   = ( p[j]->vn != 0 ? normals[ p[j]->vn ] : faceNormal );
                    verts.push_back( vert );
                }
            }
        }
    }

    return verts;
}

bool OBJLoader::load( const std::string& path , Mesh::Ptr& mesh )
{
	if( !(mesh) )
	{
		return false;
	}

	std::string data;
	if( !native::readFile( path , data ) )
	{
		return false;
	}

	std::istringstream stream( data );
	vector< Vertex > vertexes = LoadOBJ( stream );

	// convert vertex vector into mesh..
	std::vector<glm::vec3>& mVert = mesh->accessVertexes();
	std::vector<glm::vec2>& mTex  = mesh->accessTextureCoordinates();

	mVert.resize( vertexes.size() );
	mTex.resize( vertexes.size() );

	// Populate..
	int i = 0;
	for( const auto& vert : vertexes )
	{
		mVert[ i ] = vert.position;
		mTex[ i ] = vert.texcoord;
		++i;
	}

	// Bake the mesh.
	mesh->bake();

	return true;
}
