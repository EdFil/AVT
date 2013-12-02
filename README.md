AVT
===

Installation
------------

###Temas.

* Picking and manipulating objects with mouse and keyboard (1.0) **Sena**
* Code to load external meshes/materials from an existing format (1.0) **Catia**
* Modo de animação (1.0)**Edgar**

* Saving a snapshot of the application to a known image file format (0.5) **Sena**
* Creating a format allowing to save, load the full scene, and resume the interaction (1.0) **Sena**
* A photorealistic lighting/shading model, e.g. Phong or Blinn-Phong model (0.5) **Edgar**
* A realistic or stylized solid material for the objects of your scene, e.g. wood, stone, marble (1.0)**Catia**
* 
* A non-photorealistic lighting/shading model with silhouette in modern OpenGL, e.g. Cel or Gooch shading (1.0)
* Generic scene graph handling hierarchical drawing (e.g. matrices, shaders, textures)  (1.5)
* Matrix stack for hierarchical drawing and its use in the scene (0.5)
* A realistic or stylized material with transparencies, e.g. glass, crytal (1.5)
* Buffer based special effects such as reflections or planar shadows (1.0)
* Shader based special effects, e.g. normal or displacement mapping (1.0)
* Scene post processing, e.g. using image filters (1.0)


###Git para o Visual Studio.

* Se o Visual Studio for **2012 ou superior** instalar **[Visual Studio Tools for Git][GitVS2012]**
* Se o Visual Studio **menor que 2012** instalar **[Git Source Control Provider][GitVS2010]**

###Fazer clone do proj para uma pasta *(consola)*

* Ir para a pasta desejada
* Fazer `git clone https://github.com/EdFil/AVT.git`

###Copiar ficheiros do visual studio para a pasta do git

	/
	|.. dependencies /
	|                |.. ----freeglut----
	|                |.. ----glew----
	|.. projects /
	|            |.. Assignment 4 /
	|            |                |.. scripts /
	|            |                |           |.. ----Assignment 4.vxproj----
	|            |                |           |.. (etc)
	|            |                |..src
	|            |..bin /
	|            |      |.. ----freeglut.dll----
	|            |      |.. ----glew32.dll----
	|.. scripts /
	|           |.. ----AVT.sln----
	|           |.. ----AVT.sdf----

<!--Links-->

[GitVS2012]: http://visualstudiogallery.msdn.microsoft.com/abafc7d6-dcaa-40f4-8a5e-d6724bdb980c
[GitVS2010]: http://visualstudiogallery.msdn.microsoft.com/63a7e40d-4d71-4fbb-a23b-d262124b8f4c
