FLAGS = -w
CPP = g++
OPENSSL = -lssl -lcrypto

TCP-PORT = 8001
UDP-PORT = 9000
IP = 127.0.0.1

build: tcp-server udp-server client

tcp-server: tcp-server.cpp
	$(CPP) $(FLAGS) tcp-server.cpp -o tcp-server $(OPENSSL)

udp-server: udp-server.cpp
	$(CPP) $(FLAGS) udp-server.cpp -o udp-server $(OPENSSL)

client: client.cpp
	$(CPP) $(FLAGS) client.cpp -o client $(OPENSSL)

run-tcp-server: 
	./tcp-server $(TCP-PORT)

run-udp-server:
	./udp-server $(UDP-PORT)

run-client:
	./client $(IP) $(TCP-PORT) $(UDP-PORT)

clean:
	rm -f tcp-server
	rm -f udp-server
	rm -f client
