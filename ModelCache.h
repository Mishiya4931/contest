#pragma once
#include<unordered_map>
#include<string>
class Model;
class ModelCache
{
private:
	ModelCache()
	{
		Instance = nullptr;
	};
public:
	static void Init()
	{
		if (Instance != nullptr)
		{
			return;
		}
		Instance = new ModelCache();
	}
	static ModelCache* GetInstance()
	{
		return Instance;
	}
	static void UnInit();
	Model* GetCache(const std::string& path);
private:
	static ModelCache* Instance;
	std::unordered_map<std::string, Model*> Chache;
};
