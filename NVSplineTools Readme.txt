

 NV Spline Tools
 Modular splinemesh system
 
  Version 6.0

 Copyright (C) 2021

===========================


Introduction:
=============

NV Spline Tools is a system for setting up a modular sequence of meshes to follow the path of a spline.
It is built entirely in Blueprints, and is designed to be used at edit time to help create levels.

It can be used to quickly create flexible level features such as fences, walls, tracks, pipes, etc.

These tools are designed to be a customisable base system for any kind of flexible architecture.

While two simple sets of example meshes are included, this system is primarily designed to be used with user-supplied static meshes.

Note that when creating your own meshes to use with this system, the meshes should be aligned along the X axis, as the meshes will be placed along the spline from -X to +X.




Features:
=========

 - Place and deform spline meshes along a spline:

	- Repeating segments along the entire length of the spline
	- Repeating segments between each point on the spline
	- Segments stretched between each point on the spline

 - Place static meshes along a spline:

	- At fixed distances along the spline
	- Between deformed segments
	- At points on the spline

 - Adjust the placement of meshes based on the length of the spline:

	- Stretch meshes to cover the distance
	- Stop placing meshes shortly before the end of the spline if there is not enough space to fit a full mesh

 - Select from a list of meshes to use:

	- Randomly
	- Sequentially

 - Adjust the mesh sequence based on the distance to cover:

	- Complete the sequence by using the mesh that most closely matches the remaining distance
	- Always use the longest segment(s) until the last segment

 - Use different meshes for the first or last segment in the sequence

 - Automatically snap the spline to the ground underneath it

 - Regenerate of the sequence at run-time





Usage Instructions:
===================

The system is used entirely through the "BP_NVSplineMesh" Blueprint actor.
It can either be used directly, by placing the actor in your world and then configuring it, or it can be subclassed to create a preset to be reused.

To configure the system:
 1)	Click on the + button next to Spline Mesh Details in the "NV Spline Mesh Configuration" property section.
	This will add a new group of meshes to place along the spline.

 2) Click the + button next to the Meshes array.
 
 3) Select a mesh to use as part of this group of meshes.
 
 4) Repeat steps 2-3 until you have added all the desired variants of the mesh to use in this group.
 
 5) Select the placement method
	- "Repeating" will place and deform the meshes along the full length of the curve.

	- "Repeating between points" will place and deform the meshes between each point along the spline.
	  Each point will force a break between the meshes, acting as hard boundary that no single mesh can cross.

	- "Stretched between points" will place and deform exactly one mesh between each point along the spline, regardless of length.
	  The meshes may be badly stretched or squashed depending on the distance between points.

	- "Between segments" will place a mesh between each segment of a Repeating or Stretched group.
	  The "Parent Group" option must be set to the index of the group to place meshes between the segments of.
  
	- "Periodic" will place a mesh at fixed distances along the spline.

	- "At points" will place a mesh at each point along the spline.

 6) Select the stretch mode
	- "Cover full length of spline" will stretch or squash the sequence of meshes to exactly cover the entire length of the spline.

	- "Preserve Spacing" will preserve the length or spacing of each mesh.
	  The sequence may end slightly before the full length of the spline if there is not enough space for another segment.

 7) Select the mesh sequence
	- "Random" will select each mesh in the sequence at random (using the seed specified in the Random Stream property)

	- "Sequential" will select the meshes in sequential order, first to last, and then repeat

 8)Select the mesh sequence distance modifier
	- "Best match" will use the mesh with the best-matching length to end the sequence as close to the desired length as possible.
	- "Longest first" will always try to use the longest mesh that will fit in the remaining distance along the spline.
	- "Strict sequence" will strictly follow the sequence, and not adjust it to try to better match the length of the spline.

 9) For placed meshes (Between Segments, Periodic or At Points), choose which locations along the spline the mesh should be placed at:
	- "At Start" will place a mesh at the start of the sequence.
	- "In Middle" will place meshes at all locations other than the start or end of the sequence.
	- "At End" will place a mesh at the end of the sequence.

10) (optional) Select the desired spacing
	- For Periodic placed meshes, this will determine how far apart the meshes will be placed.
	- For stretched meshes, this will override the desired length of the mesh.
	  Leave at 0.0 to use the actual length of each mesh, which is recommended in most cases.

11) Select the gap between segments.
This amount of space will be left between each segment along the spline.

12) For "Between Segments" placed meshes, specify the Parent Group.
This determines which mesh sequence's segments should be followed

13) Choose the Mobility of the mesh components
The "Mobility" option will determine the mobility setting of the components created by the tool.
If the sequence needs to be moved or rebuilt at run-time, then this should be set to Movable.
Static and Stationary can be used to allow baked lighting.
See the Unreal Engine documentation on actor mobility for more information.

14) (optional) Select a Mesh Length Tolerance
If the length of two meshes are within this tolerance, they will be treated as the same length by the "Longest First" and "Best Match" algorithms.
This can be used to allow the mesh sequences to still work as expected if there are minor variations in length between mesh variants.

15) Select if the spline points should snap to ground level
If the "Snap to Ground" box is ticked, then the spline points will snap to the closest ground level below their positions.  This can help set up the spline to more closely match uneven surfaces or terrain.
If the "Snap to Ground Angle" box is ticked, then the spline points will also be tilted based on the angle of the ground under them.  This can be used to bank parts of the spline as they travel over tilted terrain.

16) (optional) Choose Start and End Meshes
There are two additional sets of meshes, found under "Start Meshes" and "End Meshes".
If Start Meshes are specified, then the first segment of the mesh sequence will use one of the meshes in this list.
If End Meshes are specified, then the last segment of the mesh sequence will use one of the meshes in this list.
If either is not specified, then the normal mesh sequence will be used in that position instead.

17) (optional) Choose the alignment to use for the model being curved along the spline.
This can allow the system to use models that were not built aligned to the X axis.


18) (optional) Select the desired number of twists that you wish to have in the spline mesh sequence.
A value of 1.0 will make the mesh sequence twist around 360° over the full length of the spline;
higher or lower values will increase or decrease the number of twists.
Negative numbers will reverse the twist direction. 
Leave at 0.0 for no twisting.

19) (optional) Set a Scale Multiplier for the sequence.  All of the meshes in this sequence will be scaled by the scale multiplier.
This allows uniform scaling of all meshes along the spline, including the length.  The scale can still be adjusted further at the individual spline points.

20) (optional) For placed meshes (Between Segments, Periodic or At Points), choose an offset transformation
Each placed mesh will be offset from its usual position with the chosen transformation.  This can be used to offset the static meshes from the spline, e.g. to place details on the side of the main splinemesh sequence.
There are two values to configure.  The values specified in "Offset Transform" will be applied equally to all meshes, and then a random transform up to the values specified in "Random Offset Transform" will be applied on top of that.  This can be used to give each mesh in the sequence a slightly different transform.

21) (optional) Override the Curve Type
The curve type can be overridden by ticking the "Override Curve Type" box, and specifying the desired "Curve Type".
This can be used to quickly change the type of every point along the curve, without needing to change it manually.




To place a sequence of meshes in the world:

 1) Drag and drop the BP_NVSplineMesh actor (or a child blueprint) into the world.

 2) If the spline handles are not visible, make sure that "Game Mode" view is not active (press 'G' to toggle)

 3) Adjust the spline as desired.

To manipulate a spline, select one of the spline handles (a white square along the spline) and move it to the desired location.
To add additional points to the spline, right-click at any point along the spline and select "Add Spline Point".
Each spline point also has red "tangent" handles which can be manipulated to adjust the curve of the spline.

To adjust the type of spline point, select the “Spline (Inherited)” component in the Details panel, then select the spline point you would like to modify.  Alternatively, you can use the Override Curve Type option to set the curve type of all points at once.


Changing the “Type” under Selected Points to “Linear” will cause the meshes to be arranged in straight lines around that point, rather than curving.  You will need to set this on every point along the spline that you wish to not be curved.
Note that Linear paths only work for Repeating Between Points and Stretched Between Points placement methods; because meshes using the Repeating placement method can cross the spline point boundaries, the first and last mesh between each segment may still be curved.



To re-generate the sequence at run time, call the "Build Spline Mesh Sequence" function on the Blueprint actor.
Note that this is an expensive function, so calling it frequently may negatively affect performance.


If you want to further customise the mesh components which are created by the system, then you can create a child blueprint and override the "Set Mesh Component Properties" function.
This function is run for each mesh component (spline mesh component, static mesh component, or instanced static mesh component) after it is created.  It does nothing by default, but can be used to set properties on each mesh, such as lighting, shadow, collision options, etc.




Debug features:
===================
Debug features can be found in the "NV Spline Mesh Debug Options" property section.

The Show Mesh Numbers option will show which mesh is being used for each part of the sequence, by drawing the index number of that mesh above it in the world.
The numbers are displayed in pink above splinemeshes, and in purple above static meshes.



Version history:
===================

v6.0
	- Added ability to customise the mesh components via the "Set Mesh Component Properties" function.
	- Added Scale Multiplier, allowing the meshes along the spline to be scaled correctly.
	- Added debug option to show which mesh number is being used for each segment.

v5.0
	- Added support for scaling the spline points.  The meshes around that point will be scaled accordingly.
	- Added the option to snap spline points to the angle of ground under them.

v4.1
	- Fixed a bug where the sequence of meshes chosen could change when rebuilding the sequence in-game (for Sequential mesh selection.)

v4.0
	- Added the ability to twist the sequence of meshes.
	- Added the ability to set the alignment axis of the spline mesh model (for models which were built along the Y instead of the X axis.)

v3.1
	- Added an option to choose whether to use hierarchical instanced static meshes, instanced static meshes, or normal static meshes
	- Fixed a bug where the collision settings for spline meshes were not consistent - they now correctly use the standard "BlockAll" preset
	- Fixed a bug with the "gap" distance, so that it will work properly if the gap is larger than the size of the mesh
	- Fixed some (mostly harmless) Blueprints warnings and errors during the mesh build sequence

v3
	- Now uses hierarchical instanced static meshes instead instanced static meshes, to allow LODs
	- Added the option to specify an offset transform for "Between Segments", "Periodic", and "At Points" modes
	- Added the option to specify a random offset transform for "Between Segments", "Periodic", and "At Points" modes

v2
	- Now uses instanced static meshes for "Between Segments", "Periodic", and "At Points" modes
	- Can now be called at run-time via the "Build Spline Mesh Sequence" function
		- It will re-use the previous components as much as possible to improve performance
	- Added the option to specify the Mobility of the created components
	- Added the option to globally override the curve type of the points in the spline
	- Added the option to automatically drop the spline points to the closest surface under them
	- Added the ability to use separate sets of meshes for the start and the end of the sequence
	- Fixed a bug where the choice of last segment in a randomised sequence did not use the random seed
	- Fixed a bug where the sequencing of meshes would be off if more than one series of meshes used it

v1
	- Initial release
