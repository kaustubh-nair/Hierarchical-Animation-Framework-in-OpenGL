run:
	g++ -std=c++11 source/*.cpp source/scene_node/*.cpp -I -w -lGL -lglfw -lGLEW -o bin/run
	./bin/run
debug:
	g++ -std=c++11 -g source/*.cpp source/scene_node/*.cpp -I -w -lGL -lglfw -lGLEW -o bin/debug
	gdb bin/debug
clean:
	rm bin/run bin/debug
