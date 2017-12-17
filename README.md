GameEngine
Engine Github Assigment 3:
https://github.com/Game-Masters/Game-Engine-Unreal


Collaborators Github:

Nicolas Babot:
Github: https://github.com/nicobabot
Daniel Olondriz: 
Github: https://github.com/danielolondriz
Arstation: https://www.artstation.com/drixxart


Link to our website:
There you can see more detailed explanations with gifs of the shader pipeline, and the how the Engine Works.
https://nicobabotaltisen.wixsite.com/zenigine

Link to the official License:
https://www.apache.org/licenses/LICENSE-2.0

##VERSIONS:
	check [NEW] tag for the new things implemented in the last version (please check important notes down below) :
	
	V0.7 [NEW]
	
	Now the game engine works with the Shader Pipeline. Now any mesh will be rendered using shaders. You can create vertex and fragment shaders and link them
	to a Program Shader. You can switch between shaders from the inspector tab. If you double click on a shader, it will open in a built-in editor, where you can 
	edit and save your shaders. Shaders will change in realtime, so you can see the changes you're making. Keep in mind that if a shader does not compile
 	the shader will show an uncompiled shader.

	V0.4
	Code is based on a structure of gameobjects and components, and files are saved in our own file format (.ric). You can save and load scenes
	from your directories (serialization), and load meshes and fbx aswell. Optimization has been added to the scene, like frustrum Culling and Octree implementation.
	You can select the diferent objects by clicking on them (mouse picking) and you can move, scale and rotate using Gizmos. You can also play, 
	pause and stop in scene(time managment).
	Resource Managment is implemented aswell, like reference counting, assets bar inside game engine UI, texture updated in realtime.
	
	V0.03
	The geometry is imported with the same transformation and it can have normals and textures
	You can move arround the world using WASD and also the wheel mouse to Zoom if yoy press alt you will rotate the camera arround the geometry in the world
	We also added the system of Dock to make the UI of our Engine better
	Added JSON library to access to XML files
	We are students from the UPC CITM and we are making a game engine for 3D videogames.
	

	V0.02
	On this version the 3D engine has:
	A window for all the options of every module, such as: wireframe mode, show normal, size of the window, title window, full screen…
	A window that shows the performance of the engine. You can see the frames average and also the time spend in every module.
	Console to see the outputs of the Engine.
	Drag and drop of FBX in the Engine and importing geometry.

	v0.01
	In the first version we added the ImGui Library and if you run it you should press the 'GRAVE' to show the game engine GUI. Also, if you press F1 button you can move around 
	the 3D world with the mouse.
	
	

	
##INNOVATION
-Assets tab, unity style ( and double click in one fbx to load it with textures!).
-Octree is adaptative to the mesh dropped in scene.
-You can add components (mesh and material) to a gameobject.
-Gizmos.
-You can clean scene.
[NEW]- You can choose the colors of the light, albedo, and shines of the water shader, from the shader inspector.
[NEW]- Water Shader Variations.

[NEW]
##SHADER PIPELINE

	If you want to load the scene asked in the 3rd Assignment, go to Menu, Load Scene, open the Assets/Scene tab and Choose Scene_Water_Assignment3.json
	Please check the Assigment 3 Notes paragraph  for more info in the scene.
 
	##Create a shader
	Go to gameobject menu-> Create New Shader. 
	Choose the type of shader and its name and press Enter to save it.

	##Edit a shader in the builtIn Editor
	In the Assets tab, go to the Shader Folder, double click your shader and the editor will open.
	There you can edit and Save all the changes.

	##Build a Program Shader
	Go to gameobject menu->Link new shader program.
	Choose the two shaders you want to attach, add a name to the Shader Program and press Enter to save it.
	##Change shader
	The Default shader is set if you double click a fbx in the Asset Window.
	To change it, double click the object in the World Window or select the mesh from the Scene window. 
	In the Inspector Window, click Shader Type, and select the shader you want to use.
	
	




##CONTROLS:
The controls in the info button inside the Engine are outdated! Check the following ones for correct inputs:

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
		UPDATE: There is also the OCTREE window and PLAY PAUSE buttons

		World:World is displayed.

		About:Info about the engine and its creators.

		Application:Performance graphs.
		Assets: Directories, FBX and textures are displayed here. Double clikc a folder to open it, press ESC to go back.
 
	Left tabs:
		Scene Inspector: here you can see all gameobjects in scene with his parents. Click on "root" to open it's children.


Menu:
	Console:opens the console.
	Open github:opens developer github's page.
	Close:closes the app.
	Save & Load Scene: You can save and load scenes

Gameobject:
	Create Empty Gameobject: Creates new empty gameobject.
	Create Camera: Creates camera gameobject with Frustum.



[NEW]
##ASSIGMENT 3 NOTES
	The scene is composed by the Street Enviroment rendered with the Default Shader and 3 planes with a water shader. 
	The right one is render with the shader Water_with_Foam which should be the definitive and most complete water shader, with homogeneous foam on top of the waves. 
	However we added two variations to the shader, with the middle one having no foam on top  of the waves and using the Water_No_Foam shader, and the third one
	with non homogeneous foam on top  of the waves with the shader Water_With_Foam_NoUniform. 
	All those three shaders use 3 color pickers, where you can change the color of the albedo, light, and specular light maps. 
	Advice: Try not to load or save while the engine is in play mode because it has some bugs.
	



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


