#include "Loaders.h"
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#define UPDATE_BB(xmax, xmin, x) if (x > xmax) {\
	xmax = x;\
}\
if (x < xmin) {\
	xmin = x;\
}\


namespace CG
{ 
	void Load(const std::string path, Object *a)
	{
		//if path termina en .obj
		LoadOff(path, a);
		//else if path termina en .off
	}

	void LoadObj(const std::string path, Object *a) {
		glm::vec3 test;
	}

	void LoadOff(const std::string path, Object *a) {
		std::ifstream ifs;
		std::regex decimal("^[-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?$");
		std::regex integer("^[+-]?[0-9]+$");
		std::string token;
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
		int act = 1, r, v, f, e = 0;
		float  normalizerX, normalizerY, normalizerZ;
		float x, y, z, xmax = 0.0f, ymax = 0.0f, zmax = 0.0f, xmin = 0.0f, ymin = 0.0f, zmin = 0.0f;

		ifs.open("C:/Users/Daniel/Desktop/proyectos/CG1-Tarea-3/EasyDIPClient/EasyDIPClient/Objects/Object.off", std::ifstream::in);
		

		while (act) {
			ifs >> token;
			std::cout << "ignoring line: " << token << std::endl;
			std::cout << std::regex_match(token, integer) << std::endl;
			if (std::regex_match(token,integer)) {
				act = 0;
			}
		}
		std::cout << "ignored comments" << std::endl;
		v = std::stoi(token);
		ifs >> token;
		f = std::stoi(token);
		ifs >> token;
		// ifs >> line;
		

			/*act = 1;	
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
			vertex.push_back(buffer);*/

		

		for (;  v--; ) {

	/*		while (!(std::regex_match(token, decimal)) || !(std::regex_match(token, integer))){
				ifs >> token;
			}*/

			//CLEAR_COMMENTS();
			buffer = glm::vec3();

			ifs >> token;
			buffer.x = std::strtof((token).c_str(), 0);
			ifs >> token;
			buffer.y = std::strtof((token).c_str(), 0);
			ifs >> token;
			buffer.z = std::strtof((token).c_str(), 0);


			UPDATE_BB(xmax, xmin, buffer.x);
			UPDATE_BB(ymax, ymin, buffer.y);
			UPDATE_BB(zmax, zmin, buffer.z);

			vertex.push_back(buffer);

			//std::cout << "vertex " << i+1 << " loaded" << std::endl;
		}

		std::cout << "vertexs loaded" << std::endl;

		act = 1;
		for (int i = 0; i < f; ++i) {
			std::vector<int> temp;
			glm::vec3 color;
			
			/*while (act) {
				ifs >> token;
				std::cout << token << std::endl;
				std::cout << i << std::endl;
				std::cout << std::regex_match(token, integer) << std::endl;
				//std::cout << "ignoring line: " << line << std::endl;
				//std::cout << std::regex_match(line, integer) << std::endl;
				if (std::regex_match(token, integer)) {
					act = 0;
				}
			}*/

			ifs >> token;
			r = std::stoi(token);
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
				ifs >> token;
				temp.push_back(std::stoi(token));	

				//faceIndex.push_back(temp);
			}
			faceIndex.push_back(temp);

			ifs >> token;
			color.x = std::strtof((token).c_str(), 0);
			ifs >> token;
			color.y = std::strtof((token).c_str(), 0);
			ifs >> token;
			color.z = std::strtof((token).c_str(), 0);


			faceColors.push_back(color);
			/*while (act) {
				ifs >> token;
				std::cout << i << std::endl;
				std::cout << token << std::endl;
				std::cout << std::regex_match(token, decimal) << std::endl;
				//std::cout << "ignoring line: " << line << std::endl;
				//std::cout << std::regex_match(line, integer) << std::endl;
				if (std::regex_match(token, integer)) {
					act = 0;
				}
				else {
					glm::vec3 temp2;
					temp2.x = std::strtof((token).c_str(), 0);
					ifs >> token;
					temp2.y = std::strtof((token).c_str(), 0);
					ifs >> token;
					temp2.z = std::strtof((token).c_str(), 0);
					faceColors.push_back(temp2);
					act = 0;
				}
			}*/

		}

		//generating normal vectors
		std::cout << "Finished loading Faces" << std::endl;

	

		std::cout << std::regex_match(token, decimal) << std::endl;

		maxvec = glm::vec3(xmax, ymax, zmax);
		minvec = glm::vec3(xmin, ymin, zmin);

		normalizerX = glm::max(abs(maxvec.x), abs(minvec.x));
		normalizerY = glm::max(abs(maxvec.y), abs(minvec.y));
		normalizerZ = glm::max(abs(maxvec.z), abs(minvec.z));
		
		

		center = (maxvec + minvec) * 0.5f; 

		for (std::vector<glm::vec3>::iterator it = vertex.begin(); it != vertex.end(); ++it) {

			glm::vec3 temp = *it;
			temp = temp - center;
			if(normalizerX >= 0)
			temp.x = temp.x / normalizerX;

			if(normalizerY >= 0)
			temp.y = temp.y / normalizerY;

			if(normalizerZ >= 0)
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
		center.x = 0.0f;
		center.y = 0.0f;
		center.z = 0.0f;
		std::cout << "Done!" << std::endl;
		
	}
}
