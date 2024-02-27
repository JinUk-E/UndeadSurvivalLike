#pragma once
class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

	virtual void Load(const wstring& path);
	virtual void Save(const wstring& path);
};

