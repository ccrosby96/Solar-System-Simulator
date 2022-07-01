#include "CubeMap.hpp"
#include "Image.hpp"

CubeMap::CubeMap(){
    Init();
}
void CubeMap::Init(){
    faces = {"right.jpg", 
             "left.jpg",
             "top.jpg",
             "bottom.jpg",
             "front.jpg",
             "back.jpg"};
}
void CubeMap::loadCubeMap(){
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

    for (unsigned int i = 0; i < faces.size(); i++){
        m_image = new Image(faces[i].c_str());
        m_image->loadJPG(true);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, 
                        GL_RGB, m_image->GetWidth(),
                        m_image->GetHeight(),
                        0,
                        GL_RGB,
                        GL_UNSIGNED_BYTE,
                        m_image->GetPixelDataPtr());  

        images.push_back(m_image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void CubeMap::LoadJPGTexture(const std::string filepath){
    // Set member variable
	m_filepath = filepath;

	m_image = new Image(filepath);
	m_image->loadJPG(true);

	glEnable(GL_TEXTURE_2D); 
	// Generate a buffer for our texture
    glGenTextures(1,&m_textureID);
    // Similar to our vertex buffers, we now 'select'
    // a texture we want to bind to.
    // Note the type of data is 'GL_TEXTURE_2D'
    glBindTexture(GL_TEXTURE_2D, m_textureID);
	// Now we are going to setup some information about
	// our textures.
	// There are four parameters that must be set.
	// GL_TEXTURE_MIN_FILTER - How texture filters (linearly, etc.)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	// Wrap mode describes what to do if we go outside the boundaries of
	// texture.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	// At this point, we are now ready to load and send some data to OpenGL.
	glTexImage2D(GL_TEXTURE_2D,
							0 ,
						GL_RGB,
                        m_image->GetWidth(),
                        m_image->GetHeight(),
						0,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						 m_image->GetPixelDataPtr()); // Here is the raw pixel data
    // We are done with our texture data so we can unbind.
    // Generate a mipmap
    glGenerateMipmap(GL_TEXTURE_2D);                        
	// We are done with our texture data so we can unbind.    
	glBindTexture(GL_TEXTURE_2D, 0);

}