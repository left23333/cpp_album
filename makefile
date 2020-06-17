main:*.cpp
	arm-linux-g++ $^ -o $@ -std=c++11 -pthread

clean:
	rm -rf main
