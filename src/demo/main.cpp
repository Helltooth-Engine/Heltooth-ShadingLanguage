#include <fstream>
#include <string>
#include <sstream>

#include <iostream>

#include <chrono>

#include <Parser.hpp>

int main(int argc, char* argv[]) {

	std::ifstream f("res/demo2.frag");
	
	f.seekg(0, f.end);
	int length = f.tellg();
	f.seekg(0, f.beg);

	char* buffer = new char[length];
	f.read(buffer, length);

	std::string result(buffer);

	f.close();

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

	htsl::Parser::Init();
	htsl::Parser::Get()->Set("MAX_VERSION", "300 core");
	auto shaders =  htsl::Parser::Get()->Parse(result);
	for (int i = 0; i < shaders.size(); i++)
		std::cout << shaders[i] << std::endl;

	std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	
	std::cout << "It took " << time.count() << " to parse shader(s)." << std::endl;
	std::cin.get();

	return 0;
}