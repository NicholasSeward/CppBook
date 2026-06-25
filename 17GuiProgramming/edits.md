put warn big and up front.  make 00


don't tell them to skip SDL_Destroy

remove all mention of SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#canvas");

mention what opengl vulkan etc are

Qt is not native to everything.  just say if you need windowing in c++ it is a common option.

add some motion or changing to most examples so it is easy to see that they are running.

mention that eventually if you make a class for a game like connect4 or tictactoe you can add a draw(renderer) function so you can hand the renderer to it and it can paint itself.

talk about renderpresent with flip the buffers.  so you are always drawing on the previous frame .  double buffering.  this is great so no flicker but can also create flicker if you are doing nothing but the two buffers are different.  for now it is common to completely redraw everything everytime.  clear background and draw forground.  it is more preformant to reuse the parts of the buffer that haven't changed but that requires much more delibrate design. modern cpus even with no gpu acceleration can easily keep up with 60fps while drawing 100s of items per frame if not 1000s.

talk about sdlk 

line to list of key sym names.

add links to resources throughout

talk about if you load an image how to turn to a texture.  talk about different between image and texture.  

talk about draw different parts of textures and scaling

talk about rotating an image  [example of dude.png rotating]

talk about the Rect struct.  talk about passing null means take it all

add mouse motion example

mention how you can add a set to keep a list of current keys down so you can just ask if key is down in later logic.

demo with falling circles that bounce and display bounce count.

add demo with background music

explain what cmake is and how it can do the copy and build for something like this vcpkge aware.  explain vcpkg.

make engine a class.  have it keep track of GameObjects...they just draw a circle at thier xy.  update randomly changes xy abit...  keep pretty simple

mention that you often want to store positions as a double instead of an int.  this is odd because you can only draw at int locations but imaging you want to have something smoothing slide 10 pixels in 1 second.  that is 1/6th of a pixel per frame.  you need to be able to track progress even if the draw position isn't moving or you will never move.  use doubles/floats and cast when drawing




