#include "Mesh.h"
#include "VertexBufferLayout.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
   this->vertices = vertices;
   this->indices = indices;
   this->textures = textures;

   // now that we have all the required data, set the vertex buffers and its attribute pointers.
   setupMesh();
}

void Mesh::setupMesh()
{
    m_VAO = std::make_unique<VertexArray>();
    // !!!may cause error
    m_VertexBuffer = std::make_unique<VertexBuffer>(
        static_cast <void*>(&vertices), vertices.size() * sizeof(Vertex));
    VertexBufferLayout layout;
    //vertex positions
    layout.Push<float>(3);
    //vertex normals
    layout.Push<float>(3);
    //vertex texture coords
    layout.Push<float>(2);

}

void Mesh::Draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + i)); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        shader.SetUniform1i((name + number).c_str(), i);
        // GLCall(glUniform1i(glGetUniformLocation(shader.getRendererID(), (name + number).c_str()), i));
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // draw mesh
    m_VAO->Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    m_VAO->UnBind();

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}
