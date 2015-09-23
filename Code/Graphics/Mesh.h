#ifndef CHALLENGE_MESH_H
#define CHALLENGE_MESH_H

#include <Graphics/Vertex.h>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


enum AttribLocation
{
    Position = 0,
    Color = 1,
    TexCoord = 2,
};

class Mesh
{
public:
    struct Data
    {
	GLenum drawType = GL_TRIANGLES;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
    };

    Mesh();
    Mesh(const Data& data);
    virtual ~Mesh() {destroy();}
    void generate();
    void draw();

    inline void destroy() 
	{
	    glDeleteBuffers(1, &m_vbo);
	    glDeleteBuffers(1, &m_ibo);
	}

    inline void print()
	{
	    for(int i=0;
		i<m_data.vertices.size();
		i++)
	    {
		std::cout << i <<  ".: "
			  << m_data.vertices[i].texCoord.x << " "
			  << m_data.vertices[i].texCoord.x << "\n";
	    }
	}
	
    inline void changeTextCoord(std::vector<Vector2> _texcoord)
	{
	    m_data.vertices[0].texCoord = _texcoord[0];
	    m_data.vertices[1].texCoord = _texcoord[1];
	    m_data.vertices[2].texCoord = _texcoord[2];
	    m_data.vertices[3].texCoord = _texcoord[3];
	    m_generated = false;
	}

    
private:
    Data m_data;

    bool m_generated;

    GLuint m_vbo;
    GLuint m_ibo;
    GLenum m_drawType;
    GLint m_drawCount;
};


#endif CHALLENGE_MESH_H
 
