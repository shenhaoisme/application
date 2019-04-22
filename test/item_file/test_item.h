#ifndef _TEST_ITEM_H_
#define _TEST_ITEM_H_


#undef DEF_ITEM
#define DEF_ITEM(s,...)      ITEM_##s

//从ale 高仿过来，先定一个不太恰当的作用
//从功能来看，他关心第一个参数，而我设置的是 shen，那就是姓氏了。
//
typedef enum
{
#include "test.items"
	MAX_NUM_MEMNER
}E_FAMILY_T;


#endif