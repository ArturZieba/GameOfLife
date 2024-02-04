#Game of Life Unreal Engine 5 implementation summary

##Using the levels in the project
* Make sure that *GameOfLife* map has *World Settings > Game Mode > Selected GameMode > Game State Class* set to *GameStateBase* before starting *Play Mode*.
* In *GameOfLife* map you can type in a grid size into *Grid X* and *Grid Y* Text Boxes (even though they vanish) and click the *Generate Grid* button to create a grid with dead/alive cells of a stated size.
* Make sure that *GameOfLifeCPP* map has *World Settings > Game Mode > Selected GameMode > Game State Class* set to *BP_GameState* before starting *Play Mode*.
* *GameOfLifeCPP* grid size can be adjusted by going to *Content Browser > All > Content > Blueprints > GameOfLifeBP > BP_GameState* and in the *Event Graph* adjust the *X* and *Y* values in the *Create Grid* node (set to X: 32; Y: 20 by default), then *File > Save* the change and clicking *Compile* button.
* In *GameOfLifeCPP* you can click the *Left Mouse Button* to toggle individual cell's dead/alive state and click the *Right Mouse Button* to toggle the Game of Life cycle (it updates every 0.5 seconds).

##Explanation
In short this was done as an excercise, where I was supposed to implement Game of Life on a chosen programming language. C++ and Unreal Engine 5.3.1 were chosen, as this combination was most sought after, and I also wanted to do it in UE5 just as a way to learn a bit more for myself.

There are two implementations of the Game of Life in this project:
* The Blueprint Game of Life implementation was made without looking up completed Game of Life projects, most of it was just brainstorming ideas, looking up implementations for things I was not sure how to do myself (for example using Event Dispatchers to use OnClicked from Widget Blueprint elsewhere), experimenting with few unrelated things (UI input/"animated" materials), and just seeing how close to a working Game of Life I can get.
* The C++ Game of Life implementation was made with following existing, proven implementations of the game in mind. First off I have tried following pure C++/Console implementation but I found myself getting lost at translating std C++ library to equivalent UE5 syntax and sidetrack to creating blueprints based on C++ classes. In the end I have followed a longer guide on C++ implementaion and managed to implement it successfully with a few smaller changes.

Links to videos with both implementations:
* Blueprint Game of Life - https://www.youtube.com/watch?v=I2S0vNWpZv0
* C++ Game of Life - https://www.youtube.com/watch?v=C7vZXe5E3OQ

More details, thoughts and explanations to both implementations can be read below.

##Blueprint Game of Life
* General implementation I was targeting was to generate a grid of "Cell" actors which would be randomly dead or alive. Being dead/alive would be signified by the material used on the Cell (basic Cube mesh), and the Cells would check surrounding neighbours and their dead/alive state using some raycast method.
* One of the experimental things here were the "animated" materials, where mateiral color hue/value were changed using a timeline to make RGB/highlighting effect. First implementation of this was failed, as I was generating a dynamic material instance for each value change (which would keep ramping up the memory usage in Play mode), but in the end after talking about this problem to a colleague this was changed to create a dynamic material at the spawn, and then adjusting the dynamic material's properties. They turned out to not look good in practice, and affected how I approached the looks on the C++ implementation.
* Another experimental thing was creating the grid using UI Text Boxes/Button. This actually turned out basically as I wanted to do it, but in the end I did not look into retaining entered values in the Text Boxes. Main problem here was getting the OnClicked event from the Widget Blueprint to the BP_SpawnGrid (Blueprint used to spawn the Cell grid).
* When first figuring out a way for Cells to check neighbouring actors, I found a lot of suggestions about using Sphere Overlap Actors, but in the end I wanted to try out casting just 8 regular Line Trace By Channel casts, which turned out okay.
* Game of Life rules were implemented on BP_Cell (Blueprint representing a Cell). It checks the rules as they are stated on the Wikipedia page. I have implemented it three different ways using a 9 output switch, a small 3 way split, and a detailed nested branches after the C++ implementation was done.
* In the end it does not work as it should, as the implementation is missing a "buffer", so the Cells check their neighbours independently one-by-one, and they seem to get stuck at unexpected shapes. I have not pursued this any further, as this project have already taken more than I anticipated when I was starting.

##C++ Game of Life
* Original implementation spawned a grid of Cell Actors, which could be clicked to toggle their dead/alive state. The Game of Life update cycle can be toggled by clicking the Right Mouse Button.
* Created simple meshes in Blender for this implementation - a bigger and a smaller plane. Due to how "noisy" materials were in the Blueprint version, I wanted to make it look like a console window with "pixels". I have also wanted to make these meshes as simple as possible to affect performance as little as possible. Planes were chosen because they have just 4 vertices and 1 face (could go down to a triangle plane, but that would look odd) instead of meshes like cubes/spheres/cones etc. Applied Nanite to them to get another bit of performance boost. Made sure to use no light, background etc. in the map both for the "console look" and performance reasons. To make the planes visible without light I have created Unlit materials (which should be a bit easier on performance as well, due to using only the Emissive color, and disabling most of the PBR Material properties).
* Static Meshes for dead/alive cells are hard-defined in Cell.cpp, this could be better implemented via Blueprints, but as mentioned I wanted to use C++ as most as possible this time around, and at this point I wanted to start to wrap this project up.
* OnClicked functionality is basically a mirror of what I put together in the Blueprint implementation, but here the Cell Actors themselves are clicked, and not a Button component in the Widget Blueprint.
* Modified the original Cell implementation and used UKismetMathLibrary::RandomBool() to randomize the dead/alive state of a Cell Actor when spawning, so that a Game of Life can be initiated right after entering the Play Mode, without having to adjust Cell Actors manually.
* The most important difference between this and my ad hoc Blueprint implementation is that here all of the Cells' states are calculated on their classes, but the GOL (Class that populates the grid) is responsible for first checking their changes, and then applying them "at once" using a nested loop.