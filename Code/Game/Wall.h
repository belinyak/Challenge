#ifndef CHALLENGE_WALL_H
#define CHALLENGE_WALL_H


namespace Wall
{
    enum Type
    {
	Static =  1,
	Dynamic = 2,
    };
    enum Direction
    {
	Vertical = 0,
	Horizontal = 1,
    };

    struct dWalls
    {
	Direction direction;
	Vector3 velocity;
	std::vector<ModelInstance> Walls;

	void update();
    };
    struct sWalls
    {
	std::vector<ModelInstance> Walls;
    };
      
    void dWalls::update()
    {
	float acceleration = sin(glfwGetTime())/100.0f;
	if(direction == Direction::Vertical)
	{
	    velocity = {0.0f,acceleration,0.0f};
	}
	else
	{
	    velocity = {acceleration,0.0f,0.0f};	    
	}
	for(int i=0;
	    i<Walls.size();
	    i++)
	{
	    Walls[i].transform.position += velocity;
	}
    }

    //NOTE(mate): split string by delim
    std::vector<std::string> split(const std::string &s, char delim)
    {
	std::vector<std::string> value;
	std::stringstream ss(s);
	std::string word;
	while(std::getline(ss, word, delim))
	{
	    value.push_back(word);
	}
	return(value);
    }

    std::string stringfromFile(const std::string& _fileName)
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
    
    INTERNAL std::vector<ModelInstance> loadWallInstances (ModelAsset* g_sprite,
							   std::string _fileName,
							   Wall::Type type)
    {
	std::vector<ModelInstance> g_instances;
	std::string data = stringfromFile( _fileName);
	std::vector<std::string> lines;

	lines = split(data, ';');

	ModelInstance instance;
	instance.asset = g_sprite;

	for(int i=0;
	    i<lines.size();
	    i++)
	{
	    std::vector<std::string> values;
	    values = split(lines[i], ' ');
	    if( (values[0] != "//" ) &&
		(atof(values[0].c_str()) == (float)type))
	    {
		instance.transform.position.x = atof(values[1].c_str());
		instance.transform.position.y = atof(values[2].c_str());
		instance.transform.position.z = atof(values[3].c_str());

		instance.transform.scale.x = atof(values[4].c_str());
		instance.transform.scale.y = atof(values[5].c_str());
		instance.transform.scale.z = atof(values[6].c_str());

		g_instances.push_back(instance);   
	    }
	}
	return(g_instances);
    }   
}
#endif
