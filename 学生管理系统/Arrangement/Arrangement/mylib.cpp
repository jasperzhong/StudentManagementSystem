#define _CRT_SECURE_NO_WARNINGS
#include "mylib.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <windows.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

static inline bool checkIDIntegrity(long id);


Arrangement::Arrangement()
{
	Node * temp = new Node[1];     //申请首元节点
	if (temp == nullptr)
	{
		int result = MessageBox(NULL, TEXT("Error!Memory allocation failed.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		delete[]temp;
		exit(EXIT_FAILURE);
	}
	_head = temp;    
	_head->next = nullptr;      
	_total_num = 0;
}

bool Arrangement::is_empty()const
{
	return _total_num == 0;
}

bool Arrangement::is_full()const
{
	return _total_num == _MAX_NUM;
}

unsigned int Arrangement::size()const
{
	return _total_num;
}

bool Arrangement::insert(student & s,int n)
{
	if (is_full())
	{
		int result = MessageBox(NULL, TEXT("Error!The number is full.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		return false;
	}
	int count = 0;
	Node * pnew = new Node[1]; 
	Node * cur = this->_head->next;

	if (pnew == nullptr)
	{
		int result = MessageBox(NULL, TEXT("Error!Memory allocation failed.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		return false;
	}

	if (cur == nullptr) //空链表,所以放在开头
	{
		_head->next = pnew;
		pnew->stu = s;
		pnew->next = nullptr;
	}
	else {
		while (++count != n && cur->next != nullptr)
			cur = cur->next;
		cur->next = pnew;
		pnew->stu = s;
		pnew->next = nullptr;
	}

	_total_num++;
	return true;
}

bool Arrangement::erase(student & s,int n)
{
	int count = 0;
	Node * cur = this->_head;

	if (is_empty())
	{
		int result = MessageBox(NULL, TEXT("Error!Empty List.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		return false;
	}
	else
	{
		while (++count != n && cur->next != nullptr)  //指向要删的前一个节点
			cur = cur->next;
		s = cur->next->stu;  //存储给s，当然如果不想这么做可以重载一个erase，没有student的参数
		Node * tempNodeNext = cur->next->next;  //保存下一个节点
		delete[] cur->next;     //删除该节点
		cur->next = tempNodeNext;  //将前一个节点的next指向下一个节点
	}
	_total_num--;
	return true;
}


void Arrangement::displayAll()const //读
{
	Node *cur = _head;
	if (is_empty())
	{
		int result = MessageBox(NULL, TEXT("Error!Empty List.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		return;
	}
	else
	{
		while (cur->next != nullptr)
		{
			cur = cur->next;
			displayOne(cur);
		}
	}
}

void Arrangement::displayOne(Node * np)const
{
	cout << "姓名 :" << np->stu.name
		<< "\n学号 :" << np->stu.studentID
		<< "\n专业 :" << np->stu.major
		<< "\n语文成绩 :" << np->stu.gpa.chinese
	    << "\n数学成绩 :" << np->stu.gpa.math
	    << "\n英语成绩 :" << np->stu.gpa.english;
	cout << endl;
}


bool Arrangement::set()
{
	Node *cur = _head;
	if (is_empty())
	{
		return false;
	}
	else
	{
		while (true)
		{
			cur = _head;
			bool quit = false;

			cout << "您需要修改哪条信息？(1 - 5)\n"
				<< "1.姓名      2.学号\n"
				<< "3.成绩      4.专业\n"
				<< "5.退出\n";
			int choise;
			while (cin >> choise)
			{
				if (choise >= 1 && choise <= 5)
					break;
				cout << "您所输入的数字超出了范围，请输入1-5内的数字\n";
			}
			if (choise == 5)
				break;

			while (cin.get() != '\n')
				continue;

			cout << "您需要修改第几位学生的？（1-" << _total_num << "）\n";
			int n;
			while (cin >> n)
			{
				if (n >= 1 && n <= _total_num)
					break;
				cout << "您所输入的数字超出了范围,请在输入1 -" << _total_num << "中的数字\n";
			}
		
			int count = 0;
			while (++count != n && cur->next != nullptr)  //指向要删的前一个节点
				cur = cur->next;

			if (count == n)
				cur = cur->next;  //指向了那一个 
			else
				return false;

			switch (choise)
			{
			case 1:
			{
				string stuName;
				cout << "输入名字:";
				cin >> stuName;
				cur->stu.name = stuName;
				cout << endl;
				break;
			}
			case 2:
			{
				long id;
				cout << "请输入学生的学号(7位,1开头):";
				while (cin >> id)
				{
					if (checkIDIntegrity(id))
						break;
					cout << "您输入的ID不符合要求，请重新输入\n";
				}
				cur->stu.studentID = id;
				cout << endl;
				break;
			}
			case 3:
			{
				GPA gpa;
				cout << "输入语文成绩\n";
				while (cin >> gpa.chinese)
				{
					if (gpa.chinese >= 0)
						break;
					cout << "分数不能是负数\n";
				}
				cout << "输入数学成绩\n";
				while (cin >> gpa.math)
				{
					if (gpa.math >= 0)
						break;
					cout << "分数不能是负数\n";
				}
				cout << "输入英语成绩\n";
				while (cin >> gpa.english)
				{
					if (gpa.english >= 0)
						break;
					cout << "分数不能是负数\n";
				}

				cur->stu.gpa = gpa;
				cout << endl;
				break;
			}
			case 4:
			{
				string major;
				cout << "输入专业:";
				cin >> major;
				cur->stu.major = major;
				cout << endl;
				break;
			}
			default:
				quit = true;
				break;
			}
			if (quit == true)
				break;

			while (cin.get() != '\n')
				continue;
		}
	}
}

void Arrangement::del()
{
	struct student s2;
	cout << "您需要删除哪一个（1 -" << _total_num << ")\n";
	int n;
	while (cin >> n)
	{
		if (n >= 1 && n <= _total_num)
			break;
		cout << "您所输入的数字超出了范围,请在输入1 -" << _total_num << "中的数字\n";
	}

	erase(s2, n);

	cout << "删除成功!\n";
}

void Arrangement::append()
{
	readStdin();
}


bool Arrangement::clear()  //清空链表
{
	Node *cur;
	while (_head->next != nullptr)
	{
		cur = _head->next->next;
		delete[] _head->next;
		_head->next = cur;
	}
	return true;
}

Arrangement::~Arrangement()
{
	clear();     //delete[]
}


void Arrangement::sort()
{
	cout << "您需要根据什么排序（1.成绩，2.姓名，3.学号）？\n";
	int choose;
	while (cin >> choose)
	{
		if (choose >= 1 && choose <= 3)
			break;
		cout << "您所输入的数字超出了范围，请输入 1、2或者3 \n";
	}

	cout << "升序还是降序?(1.升序 2.降序)\n";
	int ch;
	while (cin >> ch)
	{
		if (ch == 1 || ch == 2)
			break;
		cout << "您所输入的数字超出了范围，请输入 1 或者 2\n";
	}
	switch (choose)
	{
	case 1:
	{
		int code;
		cout << "您需要根据哪门成绩排序？\n";
		cout << "1.语文 2.数学 3.英语\n";
		while (cin >> code)
		{
			if (code >= 1 && code <= 3)
				break;
			cout << "您所输入的数字超出了范围，请输入 1、2或者3 \n";
		}
		if (ch == 1) {
			auto lambda_func = [](float a, float b)->bool {return a < b; };
			sortWithGpa(lambda_func, code);
		}
		else if (ch == 2) {
			auto lambda_func = [](float a, float b)->bool {return a > b; };
			sortWithGpa(lambda_func, code);
		}
		break;
	}
	case 2:
	{
		if (ch == 1) {
			auto lambda_func = [](string a, string b)->bool {return a < b; };
			sortWithName(lambda_func);
		}
		else if (ch == 2) {
			auto lambda_func = [](string a, string b)->bool {return a > b; };
			sortWithName(lambda_func);
		}
		break;
	}
	case 3:
	{
		if (ch == 1) {
			auto lambda_func = [](long a, long b)->bool {return a < b; };
			sortWithID(lambda_func);
		}
		else if (ch == 2) {
			auto lambda_func = [](long a, long b)->bool {return a > b; };
			sortWithID(lambda_func);
		}
		break;
	}
	default:
		break;
	}
}

bool Arrangement::sortWithGpa(bool(*cmp)(float a, float b),int choise)   //插入排序
{
	Node *  head = this->_head;
	if (head == nullptr || head->next == nullptr)
	{
		return false;
	}
	Node *p = head->next, *q, *r;
	if (p != nullptr)
	{
		r = p->next; /* r保存*p结点后继结点的指针  */
		p->next = nullptr; /* 构造只含一个数据结点的有序表  */
		p = r;
		while (p != nullptr)
		{
			r = p->next; /* r保存*p结点后继结点的指针  */
			q = head;
			if (choise == 1)
			{
				while (q->next != nullptr && cmp(q->next->stu.gpa.chinese, p->stu.gpa.chinese))
					q = q->next;
			}
			else if (choise == 2)
			{
				while (q->next != nullptr && cmp(q->next->stu.gpa.math, p->stu.gpa.math))
					q = q->next;
			}
			else if (choise == 3)
			{
				while (q->next != nullptr && cmp(q->next->stu.gpa.english, p->stu.gpa.english))
					q = q->next;
			}
			
			p->next = q->next;
			q->next = p;
			p = r;
		}
	}
	displayAll();
	return true;
}

bool Arrangement::sortWithName(bool(*cmp)(string a, string b))   //插入排序
{
	Node *  head = this->_head;
	if (head == nullptr || head->next == nullptr)
	{
		return false;
	}
	Node *p = head->next, *q, *r;
	if (p != nullptr)
	{
		r = p->next; /* r保存*p结点后继结点的指针  */
		p->next = nullptr; /* 构造只含一个数据结点的有序表  */
		p = r;
		while (p != nullptr)
		{
			r = p->next; /* r保存*p结点后继结点的指针  */
			q = head;
			while (q->next != nullptr && cmp(q->next->stu.name, p->stu.name))
				q = q->next;
			p->next = q->next;
			q->next = p;
			p = r;
		}
	}
	displayAll();
	return true;
}

bool Arrangement::sortWithID(bool(*cmp)(long a, long b))   //插入排序
{
	Node *  head = this->_head;
	if (head == nullptr || head->next == nullptr)
	{
		return false;
	}
	Node *p = head->next, *q, *r;
	if (p != nullptr)
	{
		r = p->next; /* r保存*p结点后继结点的指针  */
		p->next = nullptr; /* 构造只含一个数据结点的有序表  */
		p = r;
		while (p != nullptr)
		{
			r = p->next; /* r保存*p结点后继结点的指针  */
			q = head;
			while (q->next != nullptr && cmp(q->next->stu.studentID, p->stu.studentID))
				q = q->next;
			p->next = q->next;
			q->next = p;
			p = r;
		}
	}
	displayAll();
	return true;
}

void Arrangement::search()const
{
	cout << "您需要按照什么条件查询?（1.姓名 2.学号)\n";
	int n;
	while (cin >> n)
	{
		if (n == 1 || n == 2)
			break;
		cout << "您所输入的数字超出了范围，请输入 1 或者 2\n";
	}
	if (n == 1)
	{
		string name;
		cout << "请输入学生的姓名:";
		cin >> name;
		auto lambda_func = [](const string& x, const string& dest)->bool
		{
			return x == dest;
		};
		searchWithName(name, lambda_func);
	}
	else if (n == 2)
	{
		long id;
		cout << "请输入学生的学号(7位,1开头):";
		while (cin >> id)
		{
			if (checkIDIntegrity(id))
				break;
			cout << "您输入的ID不符合要求，请重新输入\n";
		}
		auto lambda_func = [](const long& x, const long& dest)->bool
		{
			return x == dest;
		};
		searchWithID(id, lambda_func);
	}
}

void Arrangement::searchWithName(string& dest, bool(*cond)(const string& x, const string& dest))const //按姓名查询 （具体哪个姓名）
{
	Node * temp = this->_head;
	bool flag = false;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		if (cond(temp->stu.name, dest))
		{
			displayOne(temp);
			flag = true;
		}
	}
	if (!flag)
		int result = MessageBox(NULL, TEXT("没有结果！\n"), "错误", MB_ICONINFORMATION | MB_OK);

}

void Arrangement::searchWithID(long& dest, bool(*cond)(const long& x, const long& dest))const//按学号查询 （具体哪个学号）
{
	Node * temp = this->_head;
	bool flag = false;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		if (cond(temp->stu.studentID, dest))
		{
			displayOne(temp);
			flag = true;
		}
	}
	if (!flag)
		int result = MessageBox(NULL, TEXT("没有结果！\n"), "错误", MB_ICONINFORMATION | MB_OK);

}

void Arrangement::readStdin()
{
	student s;
	cout << "输入名字\n";
	cin >> s.name;
	cout << "请输入学生的学号(7位,1开头):";
	while (cin >> s.studentID)
	{
		if (checkIDIntegrity(s.studentID))
			break;
		cout << "您输入的ID不符合要求，请重新输入\n";
	}
	cout << "输入语文成绩\n";
	while (cin >> s.gpa.chinese)
	{
		if (s.gpa.chinese >= 0)
			break;
		cout << "分数不能是负数\n";
	}
	cout << "输入数学成绩\n";
	while (cin >> s.gpa.math)
	{
		if (s.gpa.math >= 0)
			break;
		cout << "分数不能是负数\n";
	}
	cout << "输入英语成绩\n";
	while (cin >> s.gpa.english)
	{
		if (s.gpa.english >= 0)
			break;
		cout << "分数不能是负数\n";
	}
	cout << "输入专业\n";
	cin >> s.major;

	insert(s, -1);
}

void Arrangement::readFile()
{
	fstream inFile;
	student s;
	inFile.open("studentInfo.txt", std::ios::in);
	if (!inFile.is_open())
	{
		int result = MessageBox(NULL, TEXT("Error!Opening File failed.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		return;
	}
	while (!inFile.eof())
	{
		string str;
		getline(inFile,str);

		const char* buffer= str.c_str();

		char temp1[128];
		char temp2[128];

		sscanf(buffer, "%s %ld %f %f %f %s", temp1, &s.studentID, &s.gpa.chinese, &s.gpa.math, &s.gpa.english, temp2);

		s.name = temp1;
		s.major = temp2;
		insert(s, -1);
	}
	int result = MessageBox(NULL, TEXT("读入学生信息文件成功\n点击确定即可\n"), "信息", MB_ICONINFORMATION | MB_OK);
	inFile.close();
}

void Arrangement::writeFile(Node * np,bool enter)const
{
	fstream outFile;
	outFile.open("studentInfo.txt",std::ios::app);
	if (!outFile.is_open())
	{
		int result = MessageBox(NULL, TEXT("Error!Opening File failed.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		return;
	}
	outFile << np->stu.name << " ";
	outFile << np->stu.studentID << " ";
	outFile << np->stu.gpa.chinese << " ";
	outFile << np->stu.gpa.math << " ";
	outFile << np->stu.gpa.english << " ";
	outFile << np->stu.major << " ";
	if(enter)
		outFile << endl;
	outFile.close();
}

void Arrangement::save()const
{
	Node * temp = this->_head;
	remove("studentInfo.txt");
	bool enter = true;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		if (temp->next == nullptr)
			enter = false;
		writeFile(temp, enter);
	}
	int result = MessageBox(NULL, TEXT("保存成功"), "信息", MB_ICONINFORMATION | MB_OK);

	
}

void Arrangement::quit()const
{
	int result = MessageBox(NULL, TEXT("确认放弃修改？"), "退出", MB_ICONINFORMATION | MB_YESNO);
	if (result == EXIT)
		exit(EXIT_SUCCESS);

}

void Arrangement::statistics()const
{
	cout << "您需要什么条件？（1.xx分以上的，2.xx分以下的 3.最高分 4.最低分 5.各分数段分布）\n";
	int choose;
	while (cin >> choose)
	{
		if (choose >= 1 && choose <= 5)
			break;
		cout << "您所输入的数字超出了范围，请输入1-5范围内的数字 \n";
	}
	int code;
	cout << "您需要根据哪门成绩统计？\n";
	cout << "1.语文 2.数学 3.英语\n";
	while (cin >> code)
	{
		if (code >= 1 && code <= 3)
			break;
		cout << "您所输入的数字超出了范围，请输入 1、2或者3 \n";
	}
	switch (choose)
	{
	case 1:
	{
		cout << "请输入分数线：";
		float line;
		while (cin >> line)
		{
			if (line >= 0)
				break;
			cout << "分数线不能是负数\n";
		}
		auto lambda_func = [](float x, const float dest)->bool {return x > dest; };
		OutTheLine(line, lambda_func, code);
		break;
	}
	case 2:
	{
		cout << "请输入分数线：";
		float line;
		while (cin >> line)
		{
			if (line >= 0)
				break;
			cout << "分数线不能是负数\n";
		}
		auto lambda_func = [](float x, const float dest)->bool {return x < dest; };
		OutTheLine(line, lambda_func, code);
		break;
	}
	case 3:
	{
		auto lambda_func = [](float a, float b)->bool {return a > b; };
		extremum(lambda_func, code);
		break;
	}
	case 4:
	{
		auto lambda_func = [](float a, float b)->bool {return a < b; };
		extremum(lambda_func, code);
		break;
	}
	case 5:
	{
		cout << "请输入最低成绩，步长，最高成绩\n";
		float start, step, end;

		while (cin >> start >> step >> end)
		{
			if (start >= 0 && step>0 && end>start)
				break;
			cout << "输入的内容存在逻辑错误\n";
		}
		histogram(start, step, end, code);
	}
	default:
		break;
	}
}

void Arrangement::OutTheLine(const float dest,bool(*cond)(float x,const float dest),int choise)const   //统计哪些人低于/超过x分
{
	Node * temp = this->_head;
	bool flag = false;
	while (temp->next != nullptr)
	{
		temp = temp->next;
		if (choise == 1)
		{
			if (cond(temp->stu.gpa.chinese, dest))
			{
				displayOne(temp);
				flag = true;
			}	
		}
		else if (choise == 2)
		{
			if (cond(temp->stu.gpa.math, dest))
			{
				displayOne(temp);
				flag = true;
			}
		}
		else if (choise == 3)
		{
			if (cond(temp->stu.gpa.english, dest))
			{
				displayOne(temp);
				flag = true;
			}
		}
		else
		{
			int result = MessageBox(NULL, TEXT("Error!Wrong code.\n"), "错误", MB_ICONINFORMATION | MB_OK);
		}
	}
	if (flag == false)
	{
		int result = MessageBox(NULL, TEXT("没有结果！\n"), "错误", MB_ICONINFORMATION | MB_OK);
	}

}

void Arrangement::extremum(bool(*cmp)(float a, float b),int choise)const
{
	Node * temp = this->_head->next;
	Node * result = temp->next;

	
	float extremum;
	if (choise == 1)
	{
		extremum = temp->next->stu.gpa.chinese;

		while (temp->next != nullptr)
		{
			temp = temp->next;
			if (cmp(temp->stu.gpa.chinese, extremum))
			{
				extremum = temp->stu.gpa.chinese;
				result = temp;
			}
		}
	}
	else if (choise == 2)
	{
		extremum = temp->next->stu.gpa.math;

		while (temp->next != nullptr)
		{
			temp = temp->next;
			if (cmp(temp->stu.gpa.math, extremum))
			{
				extremum = temp->stu.gpa.math;
				result = temp;
			}
		}
	}
	else if (choise == 3)
	{
		extremum = temp->next->stu.gpa.english;

		while (temp->next != nullptr)
		{
			temp = temp->next;
			if (cmp(temp->stu.gpa.english, extremum))
			{
				extremum = temp->stu.gpa.english;
				result = temp;
			}
		}
	}
	else
	{
		int result = MessageBox(NULL, TEXT("Error!Wrong code.\n"), "错误", MB_ICONINFORMATION | MB_OK);
	}
	displayOne(result);
}

void Arrangement::histogram(float start, float step, float end, int choise)const
{
	Node * temp = this->_head;

	float pointer;
	int count;
	int *chart = nullptr;
	int num;
	for (num = 1 ,count = 0, pointer = start; pointer < end; pointer += step, count = 0,num++,temp = this->_head)
	{
		if (choise == 1)
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;
				if (temp->stu.gpa.chinese > pointer && temp->stu.gpa.chinese <= pointer + step)
					count++;
			}
		}
		else if (choise == 2)
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;
				if (temp->stu.gpa.math > pointer && temp->stu.gpa.math <= pointer + step)
					count++;
			}

		}
		else if (choise == 3)
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;
				if (temp->stu.gpa.english > pointer && temp->stu.gpa.english <= pointer + step)
					count++;
			}

		}
		else {
			int result = MessageBox(NULL, TEXT("Error!Wrong code.\n"), "错误", MB_ICONINFORMATION | MB_OK);
			break;
		}
		chart = (int*)realloc(chart, sizeof(int)*num);
		chart[num - 1] = count;
	}

	//打印直方表
	cout << "                       各分数段人数统计及其比例                     \n";
	cout << "------------------------------------------------------------------\n";
	cout << "范围			人数				   比例      \n";
	for (int i = 1 , pointer = start ; i < num; i++, pointer += step)
	{
		cout << pointer << "~" << pointer + step;
		cout << "			 " << chart[i - 1] << "				    " << (float)chart[i - 1] / _total_num;
		cout << endl;
	}
	cout << "------------------------------------------------------------------\n";

	free(chart);
}



static inline bool checkIDIntegrity(long id)   //id规定 7位
{
	if (id / 1000000 >= 1 && id / 1000000 <= 9)
		return true;
	return false;
}
