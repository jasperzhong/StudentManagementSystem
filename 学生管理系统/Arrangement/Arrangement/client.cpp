#include "mylib.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

int main()
{
	Arrangement MyClass;
	MyClass.readFile();

	while (true)
	{
		
		cout << "########################输入您要做的操作########################\n"
		   	<<  "#                1.插入                  2.删除                #\n"
			<<  "#                3.查询                  4.修改                #\n"
			<<  "#                5.排序                  6.统计                #\n"
		    <<	"#                7.输出                  8.保存                #\n"
			<<  "#                9.退出                                        #\n"
			<<  "################################################################\n";


		int yourOrder;
		while (cin >> yourOrder)
		{
			if (yourOrder >= 1 && yourOrder <= 9)
				break;
			cout << "您所输入的数字超出了范围,请在输入1 - 9中的数字\n";
		}

		switch (yourOrder)
		{
		case 1:
			MyClass.append();
			break;
		case 2:
			MyClass.del();
			break;
		case 3:
			MyClass.search();
			break;
		case 4:
			MyClass.set();
			break;
		case 5:
			MyClass.sort();
			break;
		case 6:
			MyClass.statistics();
			break;
		case 7:
			MyClass.displayAll();
			break;
		case 8:
			MyClass.save();
			break;
		case 9:
			MyClass.quit();
			break;
		default:
			continue;
		}

		while (cin.get() != '\n')
			continue;
	}

	cout << "Bye\n";
	system("pause");
	return 0;
}



