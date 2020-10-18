WORK IN PROGRESS

This renderer is a little individual project made to put the basics of the rendering process into practice.
It is minimalist and low-level enough in order to show clearly the maths involved and not to overload the code uselessly.

This programm simply generate a ppm picture ("triangles_in_perspective.ppm") from the virtual camera in the current directory. 
The picture displays a set of triangles I placed arbitrary in front of the camera, you can change them in the main function as well as the camera's parameters (focal, screen resolution, pixels' dimensions).

Rendering features implemented:
-ray tracing for perspective
-backface culling
-zbuffering

Compilation command : "make all" or "g++ *.c -o tiny_renderer"
Launch command : ".\tiny_renderer" or "./tiny_renderer"

C++11 is needed.
