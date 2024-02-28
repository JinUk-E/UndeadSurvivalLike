#pragma once

// singletons setting
#define CREATE_SINGLETONS(classname)						\
	private:										\
		classname() {}								\
	public:											\
		static classname* GetInstance()				\
		{											\
			static classname instance;				\
			return &instance;						\
		}											

// singletons getting
#define GET_SINGLE(classname) classname::GetInstance()


// Safe delete
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }