
#define print(a) std::cout<< a << std::endl;
#define print_array(a,size) for(int i = 0; i < size; i++){print(a[i]);}

/* return values / codes used in the program */

// make sure this is 0 indexed
#define SCENE_1 0
#define SCENE_2 1
#define SCENE_3 2
#define SCENE_4 3
#define SCENE_5 4

// picking objects
#define SELECT_OBJECT_1 41
#define SELECT_OBJECT_2 42
#define SELECT_OBJECT_3 43
#define SELECT_OBJECT_4 44
#define SELECT_OBJECT_5 45
#define UNSELECT_OBJECT 46

#define TRANSLATE_OBJECT 7

// translation
#define RIGHT 11
#define LEFT 12
#define DOWN 13
#define UP 14

#define ROTATE_OBJECT 15

#define SCALE_OBJECT_DOWN 17
#define SCALE_OBJECT_UP 18

#define CLOCKWISE 19
#define ANTICLOCKWISE 20

#define TOGGLE_WIREFRAME 21

#define TOGGLE_NORMAL_COLORING 25

// texture rendering styles
#define CYLINDER_PROJECT 26
#define CYLINDER_NORMAL_FROM_OBJECT 27
#define CYLINDER_NORMAL 28
#define SPHERICAL_PROJECT 29
#define SPHERICAL_NORMAL 30
#define SPHERICAL_NORMAL_FROM_OBJECT 31
#define NO_TEXTURES 36

#define SUBDIVIDE 32


