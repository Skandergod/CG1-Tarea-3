#include "Loaders.h"
#include <fstream>
#include <string>
#include <regex>
#include <vector>

namespace CG
{ 
	void Load(const std::string path)
	{
		//if path termina en .obj
		LoadOff(path);
		//else if path termina en .off
	}

	void LoadObj(const std::string path) {
		glm::vec3 test;
	}

	void LoadOff(const std::string path) {
		std::ifstream ifs;
		std::regex decimal("^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$");
		std::regex integer("((?:^|\s)([+-]?[[:digit:]]+(?:\.[[:digit:]]+)?)(?=$|\s))");
		std::string line;
		glm::vec3 buffer;
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec3> faces;
		std::vector<glm::vec3> colors;
		std::vector<std::vector<int>> faceIndex;
		std::vector<glm::vec3> faceColors;
		std::string pend;
		int act = 1, r, v, f, e = 0;
		float x, y, z;

		ifs.open("C:/Users/Daniel/Desktop/proyectos/CG1-Tarea-3/EasyDIPClient/EasyDIPClient/Objects/Object.off", std::ifstream::in);
		

		while (act) {
			ifs >> line;
			std::cout << "ignoring line: " << line << std::endl;
			std::cout << std::regex_match(line, integer) << std::endl;
			if (std::regex_match(line,integer)) {
				act = 0;
			}
		}
		std::cout << "ignored comments" << std::endl;
		v = std::stoi(line);
		ifs >> line;
		f = std::stoi(line);
		ifs >> line;

		if (std::regex_match(line, integer)) {
			e = std::stoi(line);
		}
		else {

			act = 1;	
			x = std::strtof((line).c_str(),0);
			ifs >> line;
			y = std::strtof((line).c_str(), 0);
			ifs >> line;
			z = std::strtof((line).c_str(), 0);

			buffer = glm::vec3(x, y, z);
			vertex.push_back(buffer);

		}

		for (int i = act; i < v; ++i) {
			ifs >> line;

			while (!(std::regex_match(line, decimal)) || !(std::regex_match(line, integer))){
				ifs >> line;
			}

			x = std::strtof((line).c_str(), 0);
			ifs >> line;
			y = std::strtof((line).c_str(), 0);
			ifs >> line;
			z = std::strtof((line).c_str(), 0);

			buffer = glm::vec3(x, y, z);
			vertex.push_back(buffer);

			std::cout << "vertex " << i+1 << " loaded" << std::endl;
		}

		std::cout << "vertexs loaded" << std::endl;

		for (int i = 0; i < f; ++i) {
			std::vector<int> temp;
			
			while (act) {
				ifs >> line;
				//std::cout << "ignoring line: " << line << std::endl;
				std::cout << std::regex_match(line, integer) << std::endl;
				if (std::regex_match(line, integer)) {
					act = 0;
				}
				else if (std::regex_match(line, decimal)) {
					std::vector<float> temp;
					x = std::strtof((line).c_str(), 0);
					ifs >> line;
					y = std::strtof((line).c_str(), 0);
					ifs >> line;
					z = std::strtof((line).c_str(), 0);
					faceColors.push_back(glm::vec3(x, y, z));
				}
			}

			r = std::stoi(line);
			act = 1;

			for (int i = 0; i < r; ++i) {
				
				/*while (act) {
					ifs >> line;
					//std::cout << "ignoring line: " << line << std::endl;
					std::cout << std::regex_match(line, integer) << std::endl;
					if (std::regex_match(line, integer)) {
						act = 0;
					}
				}*/
				//act = 1;
				ifs >> line;
				temp.push_back(std::stoi(line));

				//faceIndex.push_back(temp);
			}
			faceIndex.push_back(temp);
		}




		



		//std::cout << ifs.is_open() << std::endl;
		//std::cout << ifs.good() << std::endl;
		

		
	}
}
