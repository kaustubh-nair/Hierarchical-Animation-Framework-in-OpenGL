#define print(a) std::cout<< a << std::endl
#define print_array(a,size) for(int i = 0; i < size; i++){print(a[i]);}



/* return values / codes used in the program */
#define NONE 0

#define CHANGE_CAMERA 1


#define MOVE_FORWARD 2
#define MOVE_LEFT 3
#define MOVE_BACKWARD 4
#define MOVE_RIGHT 5


#define TOGGLE_LIGHT_0 6
#define TOGGLE_LIGHT_1 7
#define TOGGLE_LIGHT_2 8
#define TOGGLE_LIGHT_3 9
#define TOGGLE_LIGHT_4 10
#define TOGGLE_LIGHT_5 11
#define TOGGLE_LIGHT_6 12
#define TOGGLE_LIGHT_7 13
#define TOGGLE_LIGHTS 14

#define LOOK_AROUND 15

#define SPHERICAL_MAPPING 16
#define CYLINDERICAL_MAPPING 17

#define SPOTLIGHT 18
#define POINTLIGHT 19

#define PASSED_FROM_TARGET_PARENT_FLAG 20
#define NO_FLAG 21

