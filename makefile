main: main.cpp
	../../mips-openwrt-linux-g++ -std=c++0x main.cpp tool.cpp serial.cpp log.c -o main

clean:
	rm main
