
#define print(a) std::cout<< a << std::endl
#define print_array(a,size) for(int i = 0; i < size; i++){print(a[i]);}

/* return values / codes used in the program */

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


#define CHANGE_CAMERA 22

#define MOVE_FORWARD 23
#define MOVE_LEFT 24
#define MOVE_BACKWARD 25
#define MOVE_RIGHT 26
