#ifndef CHALLENGE_RENDER_H
#define CHALLENGE_RENDER_H

#include <Game/Common.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/Mesh.h>
struct Material
{
    ShaderProgram* shaders;
    Texture* texture;
};

struct ModelAsset
{
    Material* material;
    Mesh* mesh;  
};

struct ModelInstance
{
    ModelAsset* asset;
    Transform transform;
};

INTERNAL Material loadMaterial(const char* _imagePath, ShaderProgram* shader)
{
    Material material;
    material.shaders = shader;
    material.texture = new Texture();
    material.texture->loadFromFile( _imagePath);
    return(material);
}


INTERNAL ShaderProgram* loadShaders(std::string _vertPath, std::string _fragPath)
{
    static ShaderProgram* g_defaultShader;

    g_defaultShader = new ShaderProgram();
    if (!g_defaultShader->attachShaderfromFile(ShaderType::Vertex,
					       _vertPath))
    {
	throw std::runtime_error(g_defaultShader->getErrorLog());
    }
    if (!g_defaultShader->attachShaderfromFile(ShaderType::Fragment,
					       _fragPath))
    {
	throw std::runtime_error(g_defaultShader->getErrorLog());
    }

    g_defaultShader->bindAttributeLocation((std::uint32_t)AttribLocation::Position, "a_position");
    g_defaultShader->bindAttributeLocation((std::uint32_t)AttribLocation::Color, "a_color");
    g_defaultShader->bindAttributeLocation((std::uint32_t)AttribLocation::TexCoord, "a_texCoord");

    if (!g_defaultShader->Link())
    {
	throw std::runtime_error(g_defaultShader->getErrorLog());
    }

    return(g_defaultShader);
}



INTERNAL ModelAsset loadSpriteAsset(ShaderProgram* g_defaultShader)
{
    ModelAsset g_sprite;

//NOTE(mate): mesh test
    Mesh::Data meshData;

    meshData.vertices.push_back( { { 0.0f, 0.0f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0x00 } },{ 0.0f, 0.0f } });
    meshData.vertices.push_back( { { 1.0f, 0.0f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0x00 } },{ 1.0f, 0.0f } });
    meshData.vertices.push_back( { { 1.0f, 1.0f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0x00 } },{ 1.0f, 0.48f } });
    meshData.vertices.push_back( { { 0.0f, 1.0f, 0.0f },{ { 0xFF, 0xFF, 0xFF, 0x00 } },{ 0.0f, 0.48f } });
	
    meshData.indices.push_back(0);
    meshData.indices.push_back(1);
    meshData.indices.push_back(2);
    meshData.indices.push_back(2);
    meshData.indices.push_back(3);
    meshData.indices.push_back(0);

    g_sprite.mesh = new Mesh(meshData);
    return(g_sprite);
}


INTERNAL void renderInstance(const ModelInstance& _instance, Camera g_camera)
{

    _instance.asset->material->shaders->setUniform("u_camera", g_camera.getMatrix());
    _instance.asset->material->shaders->setUniform("u_transform", _instance.transform);
    _instance.asset->material->shaders->setUniform("u_tex", 0);

    _instance.asset->material->texture->bind(0);

    //_instance.asset->mesh->generate();
    _instance.asset->mesh->draw();
}

INTERNAL ModelInstance loadHeroInstance(ModelAsset* g_sprite)
{
    ModelInstance instance;

    Vector3 scale = {0.5f,1.5f,1};
    
    instance.asset = g_sprite;
    instance.transform.scale = scale;
    instance.transform.position = {0.5f,2.5f,0};
        
    return(instance);
}

#endif
