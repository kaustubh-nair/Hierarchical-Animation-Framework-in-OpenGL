# Hierarchical Animation Framework

This project provides an abstract layer to make animations simpler in OpenGL.

It currently supports:
* Parent/child relationships between nodes.
* Timer and event based updates for animation.
* Movable camera, lights and mesh nodes.
* Collision detection.
* Target constrained relationships between nodes.
* Configurable textures.

## Dependencies

Make sure you include [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) in `/include`. If you choose to include it somewhere else, modify the Makefile appropriately.

## Overview

Here's a brief overview of the various classes and methods available for animating a scene. For a more complete example, look at `source/main.cpp` in the `example` branch.

### Scene Nodes

`CameraNode`, `LightNode`, and `MeshNode` are the three available classes for creating Scene nodes. Custom overrides can be made to these classes by inheriting them. Specifically, the `MeshNode` class **must** be inherited and the `update()` method should be implemented for making the objects move. Currently, only `.ply` files can be loaded as meshes.

### Node Relationships

Since the nodes are stored in a tree, any transformations applied to a parent node will be applied to all of its child nodes. Parent/child dependencies can be defined in the `MeshNode` constructors using their the object ids. Target relationships can be defined between nodes when an object's state/action depends on another object, but the nodes do not have a parent/child relationship. These can be defined by creating a `TargetNode` object and storing the respective target id in the `MeshNode` object.

### Defining movement

There are three transformation matrices for defining movement in `MeshNode` - `translationMat`, `rotationMat`, `scalingMat`. All these matrices are passed to the nodes' children. If a transformation is supposed to by applied only to the current node and not it's children, then new matrices need to be used and composed during `MeshNode.render()`. As an example, look at `selfScalingMat`. All these matrices are defined in the constructors and modified the inherited `MeshNode`'s `update()` method for actions/movement.

There is a global timer, and on every tick the transformation matrices are updated and scene is rendered. Events can be defined in `include/definitions.h` and used in the `update()` methods.

### Collision detection

Collision detection can be implemented with the help of the bounding sphere and minimum seperation defined in `MeshNode`.

### Misc.

* Group nodes exist for performing group operations on a specific node type.
* Multiple windows can be created for multiple views.
* Input callbacks are defined in `View.listenToCallbacks()` and passed to `Controller.reactToCallback()`
