# GraphicsSandbox
A repository that I use for playing around with real-time computer graphics.

The project currently targets OpenGL v4.6, though the version can be lowered in Sandbox constructor to v4.3 with no other changes. 
The version can go as low as v3.3 is you disable OpenGL debug prints.

# Known issues & TODOs
- Add Mesh and Model classes
- The transforms are acting a bit weird(Camera class)
- Clean up Sandbox.cpp(it's completely all over the place at this point)
- Movement is inconsistent relative to direciton
- Movement forward and backward is flipped for some reason

# Acknowledgement
Some of this code was written while following TheCherno's OpenGL tutorial series. Some of the code is also inspired by a course I'm currently taking(2020/2021).

# Libraries used
 - GLFW (https://www.glfw.org/)
 - GLAD (https://glad.dav1d.de/)
 - GLM (https://github.com/g-truc/glm)
 - STB, specifically stb_image.h (https://github.com/nothings/stb)
