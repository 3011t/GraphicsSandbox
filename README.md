# GraphicsSandbox
This README is very much Work in Progress, same goes for all of my code
that this repository currently contains.

A repository that I use for playing around with real-time computer graphics.

The project currently targets OpenGL v4.6, though the version can be lowered in Sandbox constructor to v4.3 with no other changes. 
The version should be able to go as low as v3.3 is you disable OpenGL debug prints.

# Known issues & TODOs
There are very many current issues with how I load, represent and render the scene,
I'm currently only trying to create a working prototype that I will probably completely
refactor later.

# Acknowledgement
Some of this code was written while following TheCherno's OpenGL tutorial series. Some of the code is also inspired by a course I'm currently taking(2020/2021).

# Libraries used
 - GLFW (https://www.glfw.org/)
 - GLAD (https://glad.dav1d.de/)
 - GLM (https://github.com/g-truc/glm)
 - STB, specifically stb_image.h and stb_image_write.h (https://github.com/nothings/stb)
 - TinyOBJLoader and TinyGLTF (https://github.com/tinyobjloader/tinyobjloader and https://github.com/syoyo/tinygltf)
 - nlohmann/json, as a dependency for TinyGLTF (https://github.com/nlohmann/json)