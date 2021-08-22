// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


namespace utils{

	enum class fileType{HEADER, SOURCE, TEXTURE, SHADER };

	std::string getPath(const std::string& name, const fileType& type);

	float* getCubePoints(size_t& size);

	// utility function for loading a 2D texture from file
	unsigned int loadTexture(const std::string& name);
}