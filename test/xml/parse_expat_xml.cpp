#include <string.h>
#include <iostream>
#include <vector>
#include <expat.h>

using namespace std;
char * elempt = "tree";
string buf =	"<name>"  
					"<red sex='female' time='2018'>apple<\/red>" 
					"<blue><\/blue>" 
					"<green>tree<\/green>" 
					"<pink>hello kitty<\/pink>" 
				"<\/name>";


typedef struct{
	string red;

	string blue;

	string green;

	string pink;
}fruit;
fruit g_table;
vector <fruit> mytable;
int flag=0;

void StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts)
{
	if(!strcmp(name, "name"))
	{
		//cout << "\tstart name" << endl;
	}
	if(!strcmp(name, "red"))
	{
		flag=1;
		//cout << name << "\tstart_of_red" << endl;;

		//cout << atts[0] << "\t" << atts[1]<< "\t" << atts[2]<< "\t" << atts[3]<< endl;
	}
	
	if(!strcmp(name,"blue"))            //当遇到<red>时，将flag置2	
	{		
		//cout << name << "\tstart_of_blue" << endl;
		flag = 2;	
	}	
	if(!strcmp(name,"green"))            //当遇到<red>时，将flag置3	
	{		
		//cout << name << "\tstart_of_green" << endl;		
		flag = 3;	
	}	
	if(!strcmp(name,"pink"))            //当遇到<red>时，将flag置4	
	{		
		//cout << name << "\tstart_of_pink" << endl;
		flag = 4;	
	}
}
void EndElementHandler(void *userData, const XML_Char *name)
{	
	if(!strcmp(name,"pink"))
		//当遇到pink结束标签时，表示4个数据都得到了，将结构体放入vecotr中	
	{		
		//cout << name << "\tend_of_name" << endl;		
		mytable.push_back(g_table);	
	}	
	if(!strcmp(name,"red"))	
	{		
		//cout << name << "\tend_of_red" << endl;	
	}	
	if(!strcmp(name,"blue"))	
	{		
		//cout << name << "\tend_of_blue" << endl;	
	}	
	if(!strcmp(name,"green"))	
	{		
		//cout << name << "\tend_of_green" << endl;
	}	
	if(!strcmp(name,"pink"))	
	{		
		//cout << name << "\tend_of_pink" << endl;	
	}
}

void CharacterDataHandler(void *userData, const XML_Char *s, int len)
{	
	string str2 = s;
	string str1;	
	//cout << str2 << endl;	
	for(int i=0;i<len;i++)//str1就是从s中读取到了len长度的值	
	{		
		str1 += str2.at(i);	//at 会把每个值都读出来
	}	
	/*把从当前标签位置到结束，把所有的内容显示出来，只有debug的作用*/
	cout << str1 << endl;  
	if(!strcmp((char *)userData,str1.c_str()))
	{		
		cout << "this is tree" << endl;	
	}	
	if(flag == 1)
	//根据flag的值，将str1放入结构体中相应的位置	
	{		
		g_table.red = str1;	
	}	
	if(flag == 2)	
	{		
		g_table.blue = str1;	
	}	
	if(flag == 3)	
	{		
		g_table.green = str1;
	}	
	if(flag == 4)	
	{		
		g_table.pink = str1;	
	}
}

int main()
{
	XML_Parser parser = XML_ParserCreate(NULL);     //设置XML解析的对象
	XML_SetUserData(parser, elempt);                //设置传递给回调函数的参数
	XML_SetElementHandler(parser,StartElementHandler,EndElementHandler);
	XML_SetCharacterDataHandler(parser,CharacterDataHandler);    //设置遇到正文内容时的回调函数
	XML_Parse(parser, buf.c_str(), buf.length(), 1);    //正式解析XML
	
	cout << mytable[0].red << endl;	
	cout << mytable[0].blue << endl;	
	cout << mytable[0].green << endl;	
	cout << mytable[0].pink << endl; 	
	XML_ParserFree(parser);	return 0;

}








