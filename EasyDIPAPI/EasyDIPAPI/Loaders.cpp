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
		std::regex decimal("^[-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?$");
		std::regex integer("^[+-]?[0-9]+$");
		std::string line;
		glm::vec3 buffer;
		glm::vec3 center;
		glm::vec3 maxvec;
		glm::vec3 minvec;
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec3> faces;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec3> normals;
		std::vector<std::vector<int>> faceIndex;
		std::vector<glm::vec3> faceColors;
		std::string pend;
		int act = 1, r, v, f, e = 0, normalizerX, normalizerY, normalizerZ;
		float x, y, z, xmax = 0.0f, ymax = 0.0f, zmax = 0.0f, xmin = 0.0f, ymin = 0.0f, zmin = 0.0f;

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
			xmax = x;
			xmin = x;
			ifs >> line;
			y = std::strtof((line).c_str(), 0);
			ymax = y;
			ymin = y;
			ifs >> line;
			z = std::strtof((line).c_str(), 0);

			zmax = z;
			zmin = z;

			buffer = glm::vec3(x, y, z);
			vertex.push_back(buffer);

		}

		for (int i = act; i < v; ++i) {
			ifs >> line;

			while (!(std::regex_match(line, decimal)) || !(std::regex_match(line, integer))){
				ifs >> line;
			}

			x = std::strtof((line).c_str(), 0);
			if (x > xmax) {
				xmax = x;
			}
			if (x < xmin) {
				xmin = x;
			}
			ifs >> line;
			y = std::strtof((line).c_str(), 0);
			if (y > ymax) {
				ymax = y;
			}
			if (y < ymin) {
				ymin = y;
			}
			ifs >> line;
			z = std::strtof((line).c_str(), 0);
			if (z > zmax) {
				zmax = z;
			}
			if (z < zmin) {
				zmin = z;
			}

			buffer = glm::vec3(x, y, z);
			vertex.push_back(buffer);

			std::cout << "vertex " << i+1 << " loaded" << std::endl;
		}

		std::cout << "vertexs loaded" << std::endl;

		act = 1;
		for (int i = 0; i < f; ++i) {
			std::vector<int> temp;
			
			while (act) {
				ifs >> line;
				std::cout << line << std::endl;
				std::cout << i << std::endl;
				std::cout << std::regex_match(line, integer) << std::endl;
				//std::cout << "ignoring line: " << line << std::endl;
				//std::cout << std::regex_match(line, integer) << std::endl;
				if (std::regex_match(line, integer)) {
					act = 0;
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



			while (act) {
				ifs >> line;
				std::cout << i << std::endl;
				std::cout << line << std::endl;
				std::cout << std::regex_match(line, decimal) << std::endl;
				//std::cout << "ignoring line: " << line << std::endl;
				//std::cout << std::regex_match(line, integer) << std::endl;
				if (std::regex_match(line, integer)) {
					act = 0;
				}
				else {
					glm::vec3 temp2;
					temp2.x = std::strtof((line).c_str(), 0);
					ifs >> line;
					temp2.y = std::strtof((line).c_str(), 0);
					ifs >> line;
					temp2.z = std::strtof((line).c_str(), 0);
					faceColors.push_back(temp2);
					act = 0;
				}
			}
			act = 1;
			faceIndex.push_back(temp);
		}

		//generating normal vectors
		std::cout << "Finished loading Faces" << std::endl;

	

		std::cout << std::regex_match(line, decimal) << std::endl;

		maxvec = glm::vec3(xmax, ymax, zmax);
		minvec = glm::vec3(xmin, ymin, zmin);

		normalizerX = glm::max(abs(maxvec.x), abs(minvec.x));
		normalizerY = glm::max(abs(maxvec.y), abs(minvec.y));
		normalizerZ = glm::max(abs(maxvec.z), abs(minvec.z));


		center = (maxvec + minvec) * 0.5f; 

		for (std::vector<glm::vec3>::iterator it = vertex.begin(); it != vertex.end(); ++it) {

			glm::vec3 temp = *it;
			temp = temp - center;
			temp.x = temp.x / normalizerX;
			temp.y = temp.y / normalizerY;
			temp.z = temp.z / normalizerZ;
		}

		for (int i = 0; i < faceIndex.size(); i++) {

			std::vector<int> temp = faceIndex[i];
			int a = temp.size(), pivot;
			for (size_t i = 0; i < a - 2; ++i) {

				pivot = temp[0];

				normals.push_back(glm::cross(vertex[temp[i + 1]], vertex[temp[i + 2]]));

			}

		}
		
		/*for (auto it : faceIndex) {

		}*/
		



		//std::cout << ifs.is_open() << std::endl;
		//std::cout << ifs.good() << std::endl;
		

		
	}
}
