GameEngine


##VERSIONS:

	We are students from the UPC CITM and we are making a game engine for 3D videogames.
	v0.01
	In the first version we added the ImGui Library and if you run it you should press the 'GRAVE' to show the game engine GUI. Also, if you press F1 button you can move around the 3D world with the mouse.

	V0.02
	On this version the 3D engine has:
	A window for all the options of every module, such as: wireframe mode, show normal, size of the window, title window, full screen…
	A window that shows the performance of the engine. You can see the frames average and also the time spend in every module.
	Console to see the outputs of the Engine.
	Drag and drop of FBX in the Engine and importing geometry.

	V0.03
	The geometry is imported with the same transformation and it can have normals and textures
	You can move arround the world using WASD and also the wheel mouse to Zoom if yoy press alt you will rotate the camera arround the geometry in the world
	We also added the system of Dock to make the UI of our Engine better
	Added JSON library to access to XML files




##CONTROLS:

EXTRA INFO: The engine is opened at 1280x720p, however you can change the resolution in the INFORMATION --> WINDOW tab options.
When the engine is opened you will find a QUESTION MARK button(Controls info) near to the MENU tab.
There you will find all the controls of the Engine explained in a more confortable UI, and in a more friendly way.

Even so, here you have the main controls of the engine:

CAMERA TYPES
When the engine is started, the camera is set to default, you can press RIGHT CLICK to activate FREE CAMERA MODE.
Default Camera: 
	ALT+LEFT CLICK: Click alt+left click to orbit around axis, or the center of the object, if there is one.
	SCROLL WHEEL: use the scroll wheel to zoom in/ zoom out.
Free Camera:
	RIGHT CLICK: Activates the free camera mode.
	LEFT CLICK: rotates freely around the world.
	W A S D: use w a s d to move around the world.
	R F: use R & F to go up or go down in the Y axis.
	SCROLL WHEEL: use the scroll wheel to zoom in/ zoom out.
TABS:
	Right tabs:
		Geometry scene:It displays info of the meshes that are loaded in scene, like position, rotation, texture, texture size and others.
		Information: Every important variable of each module is displayed here, like your computer's info, change scene background and others.
	Main tabs:
		Rendering options:Buttons that let you activate different rendering options, check out it's help icon for more...
		World:World is displayed.
		About:Info about the engine and its creators.
		Application:Performance graphs.
MENU:
	Console:opens the console.
	Open github:opens developer github's page.
	Close:closes the app.
SPECIAL CONTROLS:
	Z :turns on\off the editor
HOW TO LOAD FBX AND TEXTURES
	DRAG AND DROP:drag and drop your files.

Thanks to ImGui, Assimp, Devil, JSON and also cereal libraries.

Engine Github Assigment 1:
https://github.com/Game-Masters/Game-Engine-Unreal/tree/Assigment_1


Collaborators Github:

Nicolas Babot: https://github.com/nicobabot
Daniel Olondriz: https://github.com/danielolondriz

