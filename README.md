GameEngine
Engine Github Assigment 2:
https://github.com/Game-Masters/Game-Engine-Unreal


Collaborators Github:

Nicolas Babot:
Github: https://github.com/nicobabot
Daniel Olondriz: 
Github: https://github.com/danielolondriz
Arstation: https://www.artstation.com/drixxart


##VERSIONS:
	check [NEW] tag for the new things implemented in the last version (please check important notes down below) :

	We are students from the UPC CITM and we are making a game engine for 3D videogames.
	v0.01
	In the first version we added the ImGui Library and if you run it you should press the 'GRAVE' to show the game engine GUI. Also, if you press F1 button you can move around 
	the 3D world with the mouse.

	V0.02
	On this version the 3D engine has:
	A window for all the options of every module, such as: wireframe mode, show normal, size of the window, title window, full screen�
	A window that shows the performance of the engine. You can see the frames average and also the time spend in every module.
	Console to see the outputs of the Engine.
	Drag and drop of FBX in the Engine and importing geometry.

	V0.03
	The geometry is imported with the same transformation and it can have normals and textures
	You can move arround the world using WASD and also the wheel mouse to Zoom if yoy press alt you will rotate the camera arround the geometry in the world
	We also added the system of Dock to make the UI of our Engine better
	Added JSON library to access to XML files
	
	[NEW]
	V0.4
	Code is based on a structure of gameobjects and components, and files are saved in our own file format (.ric). You can save and load scenes
	from your directories (serialization), and load meshes and fbx aswell. Optimization has been added to the scene, like frustrum Culling and Octree implementation.
	You can select the diferent objects by clicking on them (mouse picking) and you can move, scale and rotate using Gizmos. You can also play, 
	pause and stop in scene(time managment).
	Resource Managment is implemented aswell, like reference counting, assets bar inside game engine UI, texture updated in realtime.
	



##CONTROLS:
Check info window inside engine for more detailed info!

Camera Movement:
	ALT+LEFT CLICK: Click alt+left click to orbit around axis, or the center of the object, if there is one.
	SCROLL WHEEL: use the scroll wheel to zoom in/ zoom out.
	W A S D: use w a s d to move around the world.
	R F: use R & F to go up or go down in the Y axis.

Tabs:
	Right tabs:
		Imspector:It displays info of the meshes that are loaded in scene, like position, rotation, texture, texture size and others.
		Information: Every important variable of each module is displayed here, like your computer's info, change scene background and others.

	Main tabs:
		Rendering options:Buttons that let you activate different rendering options, check out it's help icon for more...
	[NEW]	UPDATE: There is also the OCTREE window and PLAY PAUSE buttons

		World:World is displayed.

		About:Info about the engine and its creators.

		Application:Performance graphs.
	[NEW]	Assets: Directories, FBX and textures are displayed here. 
	Left tabs:
	[NEW]	Scene Inspector: here you can see all gameobjects in scene with his parents. Click on "root" to open it's children.


Menu:
	Console:opens the console.
	Open github:opens developer github's page.
	Close:closes the app.
	[NEW] Save & Load Scene: You can save and load scenes

[NEW] Gameobject:
	Create Empty Gameobject: Creates new empty gameobject.
	Create Camera: Creates camera gameobject with Frustum.



[NEW]

##IMPORTANT NOTES AND HOW TO LOAD FBX AND GAMEOBJECTS

When you drag and drop fbx, they are imported to the libraries, not in scene.
When you create a Empty Game Object, it is created in scene. Doubleclick it in the SCENE TAB and It's components will show in the INSPECTOR.
You can add 2 new components in the inspector:

	MESH: Double click the fbx to load it (without textures!)
	TEXTURE: Select the png or texture you want to load to your mesh (NOTE: This only works if the Gameobject has already a Mesh component!!)

If you want to load fbx with its textures, you can double click them in the ASSETS window, and they will be loaded with textures.
You can create a directory by RIGHT CLICKING in the asset tab.
You can also create a gameobject, or a camera gameobject by RIGHTCLICKING the SCENE INSPECTOR tab.

NOTE: If you find that controls are not responsive, please keep in mind that we use a focus system, so if you want to create a directory be sure
to LEFT CLICK over the asset window before doing it, and same for any control that involves clicking over a certain window.





Thanks to ImGui, Assimp, Devil, JSON and also cereal libraries.


