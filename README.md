AVT
===

Installation
------------

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
