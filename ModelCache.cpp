#include "ModelCache.h"
#include"Model.h"


ModelCache* ModelCache::Instance;

void ModelCache::UnInit()
{
	for (auto& itr : Instance->Chache) {
		delete itr.second;
	}
	Instance->Chache.clear();
	SAFE_DELETE(Instance);
}

Model* ModelCache::GetCache(const std::string& path)
{
	if (Chache.find(path) == Chache.end())
	{
		Chache[path] = new Model();
	}
	return Chache[path];
}
