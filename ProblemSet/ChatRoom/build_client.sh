g++ -g -pthread -o client/client client/main.cpp client/src/*.cpp utils/lib/message.pb.cc -I. -Iutils/lib -lprotobuf && ./client/client
