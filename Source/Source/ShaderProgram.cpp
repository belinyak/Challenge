#include <Source/ShaderProgram.h>
#include <fstream>
#include <assert.h> //TODO(mate): boost assert??

namespace Challenge
{

std::string 
StringfromFile(const std::string& _fileName)
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

	return( output);
}


ShaderProgram::ShaderProgram()
	: m_object(0)
	, m_linked(false)
	, m_errorLog()
{
	m_object = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if (m_object){
		glDeleteProgram(m_object);
	}
	glDeleteProgram(m_object);
}

bool
ShaderProgram::attachShaderfromFile(ShaderType _type,
									const std::string _fileName)
{
	std::string source = StringfromFile(_fileName);

	return( attachShaderfromMemory(_type, source));
}

bool
ShaderProgram::attachShaderfromMemory(ShaderType _type,
									  const std::string _source)
{
	if (!m_object){
		m_object = glCreateProgram();
	}
	const char* shaderSource = _source.c_str();

	GLuint shader;

	if (_type == ShaderType::Vertex){
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (_type == ShaderType::Fragment){
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	glShaderSource(shader, 1, &shaderSource, nullptr);
	glAttachShader(m_object, shader);
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
			m_errorLog.append(msg);

			glDeleteShader(shader);

			return(false);
		}
	}
	return(true);
}

void
ShaderProgram::Use() const
{
	if (!isInUse()) {
		glUseProgram(m_object);
	}
}

bool
ShaderProgram::isInUse() const
{
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM,
				  &currentProgram);

	return( (currentProgram == (GLint)m_object) );
}

void
ShaderProgram::stopUsing() const
{
	if (isInUse()) {
		glUseProgram(0);
	}
}

bool
ShaderProgram::Link()
{
	if (!m_object) {
		m_object = glCreateProgram();
	}

	if (!isLinked())
	{
		glLinkProgram(m_object);

		//Note(mate): error handling
		{
			GLint status;
			glGetProgramiv(m_object, GL_LINK_STATUS, &status);

			if (status == GL_FALSE)
			{
				std::string msg("Program linking failure : \n");

				GLint infoLogLength;

				glGetProgramiv(m_object, GL_INFO_LOG_LENGTH, &infoLogLength);
				char* strInfoLog = new char[infoLogLength + 1];
				glGetProgramInfoLog(m_object, infoLogLength, NULL, strInfoLog);
				msg.append(strInfoLog);
				delete[] strInfoLog;

				msg.append("\n");
				m_errorLog.append(msg);

				glDeleteProgram(m_object);
				m_object = 0;

				m_linked = false;
				return(m_linked);
			}
		}

		m_linked = true;
	}
	return( m_linked);
}

bool
ShaderProgram::isLinked()
{
	return( m_linked);
}

void
ShaderProgram::bindAttributeLocation(GLuint _location,
									 const GLchar* _name)
{
	glBindAttribLocation(m_object, _location, _name);
}

GLint
ShaderProgram::getAttributeLocation(const GLchar* _name)
{
	return( glGetAttribLocation(m_object, _name));
}

GLint
ShaderProgram::getUniformLocation(const GLchar* _name)
{
	return( glGetUniformLocation(m_object, _name));
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  float _x)
{
	if (!isInUse()){
		Use();
	}
	glUniform1f(getUniformLocation(_name), _x);
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  float _x, float _y)
{
	if (!isInUse()){
		Use();
	}
	glUniform2f(getUniformLocation(_name), _x, _y);
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  float _x, float _y, float _z)
{
	if (!isInUse()){
		Use();
	}
	glUniform3f(getUniformLocation(_name), _x, _y, _z);
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  float _x, float _y, float _z,
						  float _w)
{
	if (!isInUse()){
		Use();
	}
	glUniform4f(getUniformLocation(_name), _x, _y, _z, _w);
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  int _x)
{
	if (!isInUse()){
		Use();
	}
	glUniform1i(getUniformLocation(_name), _x);
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  bool _x)
{
	if (!isInUse()){
		Use();
	}
	glUniform1i(getUniformLocation(_name), _x);
}

void
ShaderProgram::setUniform(const GLchar* _name,
						  unsigned int _x)
{
	if (!isInUse()){
		Use();
	}
	glUniform1ui(getUniformLocation(_name), _x);
}

void 
ShaderProgram::setUniform(const GLchar* _name, Vector2& _v)
{
	if (!isInUse()){
		Use();
	}
	glUniform2fv(getUniformLocation(_name), 1, _v.data);
}

void 
ShaderProgram::setUniform(const GLchar* _name, Vector3& _v)
{
	if (!isInUse()) {
		Use();
	}
	glUniform3fv(getUniformLocation(_name), 1, _v.data);
}

void
ShaderProgram::setUniform(const GLchar* _name, Vector4& _v)
{
	if (!isInUse()) {
		Use();
	}
	glUniform4fv(getUniformLocation(_name), 1, _v.data);
}

void 
ShaderProgram::setUniform(const GLchar* _name, const Matrix4& _m)
{
	if (!isInUse()) {
		Use();
	}
	glUniformMatrix4fv(getUniformLocation(_name), 1,GL_FALSE, _m[0].data);
	}

} // !namespace Challenge
