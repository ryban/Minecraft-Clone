Minecraft-Clone
===============

An in the works Minecraft clone. Started as a project to help me learn OpenGL and procedural generation.

Right now it only renders a world. It can technically generate terrain infinitely like Minecraft, but that is not implimented.

To build you need SFML 2.0-rc from http://www.sfml-dev.org/download.php. It's a 2D graphics library, but I use it to handle windows and load images. Works well enough for 3D.

I have SFML lib and include dirs in the top folder for the project. OpenGL is not, so you need to have it installed and make sure it links properly.

I am building on Linux, but it should comile fine on Windows and OSX. I use premake4 (http://industriousone.com/premake) to generate the make files, which should work with MinGW and OSX's make. premake4 does have options for xcode and Visual Studio projects, but I am not sure how well they work. You can try them if you want.

After you ahve compiled the code when you run the application it will take about 20 seconds for the world to generate and create the vertex buffers, then the world will render and you can fly around and look at the terrain. ESC with close the window.