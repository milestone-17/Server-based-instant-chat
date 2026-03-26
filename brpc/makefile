all:server client
server : server.cc mian.pb.cc
	g++ -std=c++17 $^ -o $@  -lbrpc -lleveldb -lgflags -lssl -lcrypto -lprotobuf
client : client.cc mian.pb.cc
	g++ -std=c++17 $^ -o $@  -lbrpc -lleveldb -lgflags -lssl -lcrypto -lprotobuf
