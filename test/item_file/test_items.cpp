#include <iostream>

using namespace std;
#undef DEF_ITEM
#define DEF_ITEM(name_last, nanme_first, age, sex) {name_last, nanme_first, age, sex}

typedef struct family{
	name_last,
	name_first,
	age,
	sex
}family_t;

family_t family[] = {
#include "test.items"
}


void test_config2param(int cfg_item, char*  param)
{
	E_FAMILY_T item = (E_FAMILY_T) cfg_item;
	
	if(cfg_item > MAX_NUM_MEMNER)
	{
		printf("%s-%d out of range \n", __FUNCTION__,item)
		return;
	}
	
	if(param == NULL)
	{
		printf("%s-%dparam is NULL ",__FUNCTION__,  item);
	}
	
	
}

int main()
{
	
	return 0;
}
