/** @file CubeMap.hpp
 *  @brief Draw a simple sphere primitive.
 *
 *  Draws a simple sphere primitive, that is derived
 *  from the Object class.
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#include "VertexBufferLayout.hpp"
#include "Geometry.hpp"
#include <cmath>
#include "Object.hpp"

class CubeMap : public Texture {
public:

    // Constructor for the CubeMap
    CubeMap();
    // The intialization routine for this object.
    void Init();

    void LoadJPGTexture(const std::string filepath);

    void loadCubeMap();

private:
    // vector to hold the names of the 6 jpeg images
    std::vector<std::string> faces;

    // vector to hold the 6 images that make up our skybox
    std::vector<Image*> images;
   
};

