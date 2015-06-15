#include <Source/ShaderProgram.hpp>
#include <fstream>
#include <assert.h> 

namespace Challenge
{
INTERNAL std::string StringfromFile(const std::string& _fileName)
{
	std::ifstream file;
	file.open(_fileName.c_str(),
				 std::ios::in | std::ios::binary);

	std::string output;
	std::string line;

	assert(file.is_open() && "Failed to open file at StringfromFile");

	while (file.good())
	{
		getline(file, line);
		output.append(line + "\n");
	}

	file.close();

	assert(output.length() != 0 && "StringfromFile output = null");

	return(output);
}

ShaderProgram::ShaderProgram()
	: object(0)
	, isLinked(false)
	, errorLog()
{
	object = glCreateProgram();
}
ShaderProgram::~ShaderProgram()
{
	if (object) {
		glDeleteProgram(object);
	}
	glDeleteProgram(object);
}

bool ShaderProgram::attachShaderfromFile(ShaderType _type, const std::string _fileName)
{
	std::string source = StringfromFile(_fileName);

	return(attachShaderfromMemory(_type, source));
}
bool ShaderProgram::attachShaderfromMemory(ShaderType _type, const std::string _source)
{
	if (!object) {
		object = glCreateProgram();
	}
	const char* shaderSource = _source.c_str();

	GLuint shader;

	if (_type == ShaderType::Vertex) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (_type == ShaderType::Fragment) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glAttachShader(object, shader);
	glCompileShader(shader);

	// Note(mate): error handling
	{
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			std::string msg("compile failure in shader: \n");

			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog = new char[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
			msg.append(strInfoLog);
			delete[] strInfoLog;
			msg.append("\n");
			errorLog.append(msg);

			glDeleteShader(shader);

			return(false);
		}
	}
	return(true);
}

void ShaderProgram::Use() const
{
	if (!isInUse()) {
		glUseProgram(object);
	}
}
bool ShaderProgram::isInUse() const
{
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM,
					  &currentProgram);

	return((currentProgram == (GLint)object));
}
void ShaderProgram::stopUsing() const
{
	if (isInUse()) {
		glUseProgram(0);
	}
}

bool ShaderProgram::Link()
{
	if (!object) {
		object = glCreateProgram();
	}

	if (!isLinked)
	{
		glLinkProgram(object);

		//Note(mate): error handling
		{
			GLint status;
			glGetProgramiv(object, GL_LINK_STATUS, &status);

			if (status == GL_FALSE)
			{
				std::string msg("Program linking failure : \n");

				GLint infoLogLength;

				glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLogLength);
				char* strInfoLog = new char[infoLogLength + 1];
				glGetProgramInfoLog(object, infoLogLength, NULL, strInfoLog);
				msg.append(strInfoLog);
				delete[] strInfoLog;

				msg.append("\n");
				errorLog.append(msg);

				glDeleteProgram(object);
				object = 0;

				isLinked = false;
				return(isLinked);
			}
		}
		isLinked = true;
	}
	return(isLinked);
}

void ShaderProgram::bindAttributeLocation(GLuint _location, const std::string& _name)
{
	glBindAttribLocation(object, _location, _name.c_str());
	m_attribLocations[_name] = _location;
}

GLint ShaderProgram::getAttributeLocation(const std::string& _name)
{
	auto found = m_attribLocations.find(_name);
	if (found != m_attribLocations.end()) {
		return(found->second);
	}

	GLint loc = glGetAttribLocation(object, _name.c_str());
	m_attribLocations[_name] = loc;
	return(loc);
}
GLint ShaderProgram::getUniformLocation(const std::string& _name)
{
	auto found = m_uniformLocations.find(_name);
	if (found != m_uniformLocations.end()) {
		return(found->second);
	}

	GLint loc = glGetUniformLocation(object, _name.c_str());
	m_uniformLocations[_name] = loc;
	return(loc);
}


void ShaderProgram::setUniform(const std::string& _name, float _x)
{
	if (!isInUse()) {
		Use();
	}

	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform1f(getUniformLocation(_name), _x);
}
void ShaderProgram::setUniform(const std::string& _name, float _x, float _y)
{
	if (!isInUse()) {
		Use();
	}

	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}

	glUniform2f(getUniformLocation(_name), _x, _y);
}
void ShaderProgram::setUniform(const std::string& _name, float _x, float _y, float _z)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform3f(getUniformLocation(_name), _x, _y, _z);
}
void ShaderProgram::setUniform(const std::string& _name, float _x, float _y, float _z, float _w)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform4f(getUniformLocation(_name), _x, _y, _z, _w);
}

void ShaderProgram::setUniform(const std::string& _name, int _x)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform1i(getUniformLocation(_name), _x);
}
void ShaderProgram::setUniform(const std::string& _name, bool _x)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform1i(getUniformLocation(_name), _x);
}
void ShaderProgram::setUniform(const std::string& _name, unsigned int _x)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform1ui(getUniformLocation(_name), _x);
}

void ShaderProgram::setUniform(const std::string& _name, const Vector2& _v)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform2fv(getUniformLocation(_name), 1, _v.data);
}
void ShaderProgram::setUniform(const std::string& _name, const Vector3& _v)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform3fv(getUniformLocation(_name), 1, _v.data);
}
void ShaderProgram::setUniform(const std::string& _name, const Vector4& _v)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform4fv(getUniformLocation(_name), 1, _v.data);
}
void ShaderProgram::setUniform(const std::string& _name, const Matrix4& _m)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniformMatrix4fv(getUniformLocation(_name), 1, GL_FALSE, _m[0].data);
}
void ShaderProgram::setUniform(const std::string& _name, const Quaternion& _q)
{
	if (!isInUse()) {
		Use();
	}
	GLint loc = getUniformLocation(_name);
	if (loc == -1) {
		return;
	}
	glUniform4fv(loc, 1, _q.data);
}
void ShaderProgram::setUniform(const std::string& _name, const  Transform& _t)
{
	setUniform(_name + ".position", _t.position);
	setUniform(_name + ".orientation",_t.orientation);
	setUniform(_name + ".scale", _t.scale);
}
} // !namespace Challenge
