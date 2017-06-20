#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <string>

#define EXIT 6

//成绩信息
struct GPA {
	float chinese;  //语文
	float math;     //数学
	float english;  //英语
};
//学生信息
struct student {
	std::string name;     //姓名
	struct GPA gpa;          //成绩
	long studentID;      //ID
	std::string major;     //专业 
};



//单向链表
typedef struct Node {
	student stu;
	Node *next;
} *List;

//面向对象程序设计
class Arrangement
{
	//构造析构赋值等
public:
	Arrangement();          //初始化
	~Arrangement();         //直接调用clear()

	Arrangement(const Arrangement &) = delete;  //禁止拷贝构造
	Arrangement & operator=(const Arrangement &) = delete; //禁止赋值拷贝

	//输入模块
public:
	void readFile();
	void readStdin();

	//查询模块
public:
	void search()const;

	//更新模块
public:
	void append();     //增加信息
	void del();        //删除信息
	bool set();        //修改信息

	void sort();       //进行排序
	//统计模块
public:
	void statistics()const;  //统计
	
	//输出模块
public:
	void displayAll()const; //屏幕输出所有信息
	void displayOne(Node * np)const;  //屏幕输出一个人的信息
	void writeFile(Node * np,bool enter)const; //写入文件
	void save()const;   //修改内容全部写入文件
	void quit()const;   //结束进程


	//内部非接口函数
private:
	bool insert(student & s, int n = -1); //插入新成员，默认在末尾插入（-1）
	bool erase(student &s, int n = -1); //删除新成员，默认在末尾删除（-1）

	void searchWithName(std::string& dest, bool(*cond)(const std::string& x, const std::string& dest))const; //按姓名查询 （具体哪个姓名）
	void searchWithID(long& dest, bool(*cond)(const long& x, const long& dest))const; //按学号查询 （具体哪个学号）

	bool sortWithGpa(bool(*cmp)(float a, float b), int choise);      //按照成绩排序
	bool sortWithName(bool(*cmp)(std::string a, std::string b));   //按照姓名排序
	bool sortWithID(bool(*cmp)(long a, long b));		//按照学号排序

	void OutTheLine(const float dest, bool(*cond)(float x, const float dest), int choise)const;   //统计哪些人低于/超过x分
	void extremum(bool(*cmp)(float a, float b), int choise)const;  //成绩的极大值，极小值所在的学生的信息
	void histogram(float start, float step, float end, int choise)const;  //成绩直方表 给定开始点，步长，结束点 ，统计各个分数段学生个数

	unsigned int size()const;  //表中目前多少人
	bool is_empty()const;   //是否为空
	bool is_full()const;    //链表是否满了
	bool clear();  //清空链表

	//封装数据
private:
	List  _head;     //链表头结点
	unsigned int _total_num;      //表中的总数
	const static unsigned int _MAX_NUM = 100;   //表中最多100人 可修改
};

#endif // !_MYLIB_H_
