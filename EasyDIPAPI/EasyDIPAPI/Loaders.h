#include "EDpch.h"
#include "Object.h"


namespace CG
{

	void Load(const std::string path, Object *a);
	static void LoadObj(const std::string path, Object *a);
	static void LoadOff(const std::string path, Object *a);
}