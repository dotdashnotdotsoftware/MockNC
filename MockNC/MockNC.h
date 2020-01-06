#pragma once

#ifdef MNC
#define MNC_NAME(i) i##_Imp
#define MNC_MOCK_STRUCT_NAME(i) i##_Struct
#define MNC_DEF(r,i,p) \
	r MNC_NAME(i)p##; \
	r(*i)p = MNC_NAME(i); \
	r MNC_NAME(i)##p

#define MNC_DEC(r,i,p) \
	extern r(*i)p;

#define MNC_MOCK(r,i,p) \
	typedef struct MNC_MOCK_STRUCT_NAME(i) { \
		r(*MockFunc)p##; \
		r ReturnValue; \
		int CallCount; \
	} MNC_MOCK_STRUCT_NAME(i); \
	r MNC_NAME(i)p##; \
	MNC_MOCK_STRUCT_NAME(i) i = { \
		.MockFunc = MNC_NAME(i), \
		.CallCount = 0 \
	}; \
	r MNC_NAME(i)p { \
		i.CallCount++; \
		return i.ReturnValue; \
	}

#define MNC_VOID_MOCK(i,p) \
	typedef struct MNC_MOCK_STRUCT_NAME(i) { \
		void(*MockFunc)p##; \
		int CallCount; \
	} MNC_MOCK_STRUCT_NAME(i); \
	void MNC_NAME(i)p##; \
	MNC_MOCK_STRUCT_NAME(i) i = { \
		.MockFunc = MNC_NAME(i), \
		.CallCount = 0 \
	}; \
	void MNC_NAME(i)p { \
		i.CallCount++; \
	}

void MNC_Swap_Imp(void *ptr1, void *ptr2);
#define MNC_SWAP(i1,i2) MNC_Swap_Imp(&i1,i2);
void MNC_RESET();

typedef struct node_ {
	void *cacheAddress, *cacheValue;
	struct node_ *next;
} MNC_History;

#else
#define MNC_DEF(r,i,p) \
	r i##p
#define MNC_DEC(r,i,p) \
	r i##p;
#endif

#define MNC_DEFINITION(r,i,p) \
	MNC_DEF(r,i,p)
#define MNC_DECLARATION(r,i,p) \
	MNC_DEC(r,i,p)