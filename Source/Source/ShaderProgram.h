#ifndef CHALLENGE_SHADERPROGRA_H
#define CHALLENGE_SHADERPROGRA_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

#include <Source/NonCopyable.hpp>

namespace Challenge
{

enum class ShaderType
{
	Vertex,
	Fragment
};

class ShaderProgram : public NonCopyable
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	bool attachShaderfromFile(ShaderType _type, const std::string _fileName);
	bool attachShaderfromMemory(ShaderType _type, const std::string _source);

	void Use() const;
	bool isInUse() const;
	void stopUsing() const;

	bool Link();
	bool isLinked();

	void bindAttributeLocation(GLuint _location, const GLchar* _name);

	GLint getAttributeLocation(const GLchar* _name);
	GLint getUniformLocation(const GLchar* _name);

	void setUniform(const GLchar* _name, float _x);
	void setUniform(const GLchar* _name, float _x, float _y);
	void setUniform(const GLchar* _name, float _x, float _y, float _z);
	void setUniform(const GLchar* _name, float _x, float _y, float _z, float _w);
	void setUniform(const GLchar* _name, unsigned int _x);
	void setUniform(const GLchar* _name, int _x);
	void setUniform(const GLchar* _name, bool _x);

	inline GLuint getObject() const { 
		return( m_object); 
	}
	inline const std::string& getErrorLog() const { 
		return( m_errorLog); 
	}

private:
	GLuint m_object;
	bool m_linked;
	std::string m_errorLog;
};
}
#endif // !#define CHALLENGE_SHADERPROGRA_H
