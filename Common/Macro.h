template <typename T>
inline void Safe_Delete(T& _ref)
{
	if (_ref)
	{
		delete _ref;
		_ref = NULL;
	}
}


//** com 객체를 지우기 위함.
#define SAFE_RELEASE(ref)	\
{							\
	ref->Release();			\
}

#define SafeDeleteArray(Array)	\
{								\
	if(Array)					\
	{							\
		delete[] (Array);		\
		(Array) = NULL;			\
	}							\
}



#define DECLARE_SINGLETON(type)			\
	static type** GetInstance(void)		\
	{									\
		static type* pInstance = new type;	\
		if (pInstance == NULL)			\
			pInstance = new type;		\
		return& pInstance;				\
	}									\
	static void DestroyInstance(void)	\
	{									\
		type** ppInstance = GetInstance();	\
		if (*ppInstance != NULL)			\
			{								\
				delete *ppInstance;		\
				ppInstance = NULL;		\
			}							\
	}


#define GET_SINGLE(type)(*type::GetInstance())
#define DESTROY_SINGLE(type)(*type::GetInstance())->DestroyInstance()


class InputManager;
#define PUSH_KEY(key) GET_SINGLE(InputManager)->GetKey() & key ? true : false
#define UP_KEY(key) GET_SINGLE(InputManager)->GetKey() & key ? false :true

#define ERROR_MESSAGE(str) MessageBox(NULL, str, NULL, NULL)