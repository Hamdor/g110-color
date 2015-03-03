all:
	g++ -lusb -std=c++11 main.cpp controller.cpp args.cpp -o g110

clean:
	rm -f g110

