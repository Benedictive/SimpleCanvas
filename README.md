# SimpleCanvas
SimpleCanvas is a simple tool to draw RGB data directly to the screen.
It does not pay much consideration to performance or efficiency.
The primary consideration was getting the desired data to show up on the screen
with as little mental effort as possible.

## Dependencies
This tool uses SDL2 to do the actual drawing of the desired data.
It is particularly suited to this task because it was the first cross-platform result
that showed up on *arbitrary search engine*.

Get the latest stable release from [here](https://www.libsdl.org/).
Make sure the binaries are in the correct system location for libraries or the path is otherwise known to cmake.
See cmake `find_package` documentation for more (Hint: You might be looking for `CMAKE_PREFIX_PATH`).

## Usage
Just clone/submodule this into whatever experiment you run, which is why there are no prebuilt binaries available.

In your code, create a `SimpleCanvas` instance, throw an EventHandler in there if you need it (`SimpleCanvas::RegisterEventHandler()`), then execute the `SimpleCanvas::run`-Method, passing it whatever function you want to run each frame.
You are now in your eventloop.

For events, check SDL2 `SDL_Event`.