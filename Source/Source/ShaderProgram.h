#ifndef CHALLENGE_SHADERPROGRAM_H
#define CHALLENGE_SHADERPROGRAM_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Source/NonCopyable.hpp>
#include <Math\Math.h>
#include <Math\Transform.h>

#include <map>
#include <string>

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

	void bindAttributeLocation(GLuint _location, const std::string& _name);

	GLint getAttributeLocation(const std::string& _name);
	GLint getUniformLocation(const std::string& _name);

	void setUniform(const std::string& _name, float _x);
	void setUniform(const std::string& _name, float _x, float _y);
	void setUniform(const std::string& _name, float _x, float _y, float _z);
	void setUniform(const std::string& _name, float _x, float _y, float _z, float _w);
	void setUniform(const std::string& _name, unsigned int _x);
	void setUniform(const std::string& _name, int _x);
	void setUniform(const std::string& _name, bool _x);

	void setUniform(const std::string& _name, const	 Vector2& _v);
	void setUniform(const std::string& _name, const  Vector3& _v);
	void setUniform(const std::string& _name, const	 Vector4& _v);
	void setUniform(const std::string& _name, const  Matrix4& _v);
	void setUniform(const std::string& _name, const  Transform& _t);
	void setUniform(const std::string& _name, const  Quaternion& _q);

	inline GLuint getObject() const { return m_object; }
	inline const std::string& getErrorLog() const { return m_errorLog; }

private:
	GLuint m_object;
	bool m_linked;
	std::string m_errorLog;
private:

	std::map<const std::string, GLint> m_attribLocations;
	std::map<const std::string, GLint> m_uniformLocations;
};
}
#endif // !#define CHALLENGE_SHADERPROGRA_H
