# serial_openwrt: test_serial.cpp serial.cpp
# 	../../mips-openwrt-linux-g++ -std=c++0x test_serial.cpp serial.cpp -o serial_openwrt

serial_test: test.cpp
	../../mips-openwrt-linux-g++ -std=c++0x test.cpp -o serial_test

clean:
	rm serial_openwrt serial_test
