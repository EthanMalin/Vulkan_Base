Build instructions

Mac
  - download and install the Vulkan SDK for macOS
  - install glfw3 via homebrew
  - ensure cmake is installed and accessible from the command line
  - at the root of the repo, `mkdir build && cd build && cmake ..`
  - to run, `./bin/power`

Windows
  - Pending test, but should be similar to above. Just specify you want a visual studio project in the cmake command.

To compile shaders there are scripts in the res/shaders directory. Vulkan must be *installed* on mac and glslc available through the command line. On windows you may need to change hardcoded values in the .bat file
