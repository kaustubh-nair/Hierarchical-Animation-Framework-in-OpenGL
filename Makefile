run:
	g++ -std=c++11 source/*.cpp -I -w -lGL -lglfw -lGLEW -o bin/out
	./bin/out
test:
	g++ -std=c++11 test.cpp source/shader.cpp -I -w -lGL -lglfw -lGLEW -o bin/test
	./bin/test
