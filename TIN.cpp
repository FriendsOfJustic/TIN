#define _CRT_SECURE_NO_WARNINGS 1
#include<math.h>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include<Windows.h>

#define WIDTH  1280
#define HEIGHT 720
#define TIME  10
#define RATE 10

class Point
{
public:
	Point(int _num = 0, char* _p = nullptr, double _x = 0, double _y = 0, double _z = 0)
		:num(_num)
		, x(_x)
		, y(_y)
		, z(_z)
	{
		if(_p)
		strcpy(p, _p);
	}

	void operator=(const Point& m)
	{
		num = m.num;
		if(m.p)
			strcpy(p, m.p);
		x = m.x;
		y = m.y;
		z = m.z;
	}


	bool operator == (const Point& m)
	{
		return (x == m.x) && (y == m.y);
	}


	bool operator !=(const Point& m)
	{
		return !((x == m.x) && (y == m.y));
	}


	int num;        //序号
	char p[20];     //数据点名称
	double x;       //x坐标
	double y;       //y坐标
	double z;       //z坐标
};

class Line
{
public:
	Line(Point m = Point(), Point n = Point(), Point z = Point(),int flag=0)   //所有线的生成都用这个定义
		:left_point(m)
		,right_point(n)
		,third(z)
		,flag(0)
	{}

	Line(const Line& l)
		:left_point(l.left_point)
		, right_point(l.right_point)
		, third(l.third)
		, flag(l.flag)
		{}



	void make_line(Point m = Point(), Point n = Point())   //所有线的生成都用这个定义
	{
		left_point = m;
		right_point = n;
	}


	bool operator == (const Line & l2)
	{
		if ((this->left_point == l2.left_point && this->right_point == l2.right_point) || (this->left_point == l2.right_point && this->right_point == l2.left_point))
			return true;
		else
			return false;
	}
	bool operator != (const Line& l2)
	{
		return !(*this == l2);
	}


	Point left_point;      
	Point right_point;        //一条直线的 两个顶点
	Point third;             // 如果有一条直线，那么一定存在一个三角形包含该直线(第一个三角形除外），这个点表示该三角形中与直线相对的点
	int flag;                //标识一条直线被多少个三角形共有
};


class Triangle
{
public:
	Triangle(Line* x = nullptr, Line* y = nullptr, Line* z = nullptr)
		:root(x)
		, left(y)
		,right(z)
	{}

	bool operator ==(const Triangle& x)
	{
		if (root == x.root)
		{
			if (left == x.left)
			{
				if (right == x.right)
					return true;
			}
			else if (left == x.right)
			{
				if (right == x.left)
					return true;
			}
		}
		else if (root == x.right)
		{
			if (left == x.left)
			{
				if (right == x.root)
					return true;
			}
			else if (left == x.root)
			{
				if (right == x.left)
					return true;
			}

		}
		else if (root == x.left)
		{
			if (left == x.root)
			{
				if (right == x.right)
					return true;
			}
			else if (left == x.right)
			{
				if (right == x.root)
					return true;
			}
		}
		return false;
	}


	bool operator !=(const Triangle& x)
	{
		bool ret = (*this == x);
		return !ret;
	}


	bool is_have_line(Line& l)
	{
		return (*root == l) || (*left == l) || (*right == l);
	}





	Line* root;
	Line* left;
	Line* right;
};

Line make_line(const Point& m = Point(), const Point& n = Point(), const Point& z = Point())   //所有线的生成都用这个定义
{
	return Line(m, n, z, false);
}

void Point_to_gragh(Point& p,const Point& origin, double scaling_X,double scaling_Y)   //将实际点的坐标转换成能在easyX上打印的坐标
{

	int easy_x = (int)((p.x-origin.x ) / scaling_X );
	int easy_y  = (int)((p.y-origin.y) / scaling_Y);


	setcolor(BLUE);
	setfillcolor(BLACK);
	fillcircle(easy_x, easy_y, 3);

};



void line_to_gragh(const Line& l, const Point& origin, double scaling_X, double scaling_Y,COLORREF color)
{
	int easy_x1 = (int)((l.left_point.x - origin.x) / scaling_X);
	int easy_y1 = (int)((l.left_point.y - origin.y) / scaling_Y);
	
	int easy_x2 = (int)((l.right_point.x - origin.x) / scaling_X);
	int easy_y2 = (int)((l.right_point.y - origin.y) / scaling_Y);

	setlinecolor(color);
	//setlinestyle(20);
	line(easy_x1,easy_y1,easy_x2,easy_y2);
}


void get_point(std::vector<Point>& v)
{
	char* buffer = new char[1024 * 8];
	FILE* fd = fopen("data.txt", "r");
	int sz = fread(buffer, 1, 8 * 1024, fd);
	int num;
	double x;
	double y;
	double z;
	char* name;

	char* p = strtok(buffer, ",\n");
	sz -= strlen(p);
	num = atof(p);

	p = strtok(NULL, ",\n");
	sz -= strlen(p);
	name = p;

	p = strtok(NULL, ",\n");
	sz -= strlen(p);
	x = atof(p);

	p = strtok(NULL, ",\n");
	sz -= strlen(p);
	y = atof(p);

	p = strtok(NULL, ",\n");
	sz -= strlen(p);
	z = atof(p);
	v.push_back(Point(num, name, x , y, z));
	z -= 5;

	while (sz > 0)
	{
		char* p = strtok(NULL, ",\n");
		sz -= strlen(p);
		num = atof(p);

		p = strtok(NULL, ",\n");
		sz -= strlen(p);
		name = p;

		p = strtok(NULL, ",\n");
		sz -= strlen(p);
		x = atof(p);

		p = strtok(NULL, ",\n");
		sz -= strlen(p);
		y = atof(p);

		p = strtok(NULL, ",\n");
		sz -= strlen(p);
		z = atof(p);

		v.push_back(Point(num, name, x , y , z));
		z -= 5;
	}
	v.pop_back();
}

//计算三角形的外接圆，最后三个参数是外接圆的圆心 的坐标 和半径
double CircleCenter(double x1, double y1, double x2, double y2, double x3, double y3, double* x, double* y, double* r)
{
	if ((2.0 * (x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2)) == 0)
	{
		*x = 0;
		*y = 0;
		*r = 0;
		return *r;
	}
	*x = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / (2.000000000 * (x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2));
	*y = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / (2.000000000 * (x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2));
	*r = sqrt((*x - x1) * (*x - x1) + (*y - y1) * (*y - y1));
	return *r;
}


bool is_same_side(Line& l, Point& tmp,double min_x,double min_y)
{
	double k = (l.left_point.y - l.right_point.y) / (l.left_point.x - l.right_point.x);
	double b = l.left_point.y-min_y - k * (l.left_point.x-min_x);

	double ret1 = tmp.y-min_y - k * (tmp.x-min_x) - b;
	double ret2 = l.third.y-min_y - k * (l.third.x-min_x) - b;
	if (ret1 * ret2 >= 0)
		return true;
	else
		return false;
}

bool is_in_circle(Point& p,double x,double y,double r, double& min_x, double& min_y)  //判断point是否在圆心为（x,y）半径为r的园内   在->true  不在->false               
{
	double ret = (p.x-min_x - x)*(p.x-min_x - x)+(p.y-min_y - y)*(p.y-min_y - y);
	if ((int)ret < (int)r*r)
		return true;
	else
		return false;
}

// 用于计算两点的距离
double distance(double x1, double y1, double x2, double y2)
{
	double ret=sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
	return ret;
}


//当返回值为真的时候就是满足条件的值
bool JudgePoint(Point& pt1, Point& pt2, Point& pt3, Point& node) {//比较链表中node pt3与pt1 pt2所成角的大小
	double dist11 = sqrt((pt1.x - node.x) * (pt1.x - node.x) + (pt1.y - node.y) * (pt1.y - node.y));
	double dist12 = sqrt((pt2.x - node.x) * (pt2.x - node.x) + (pt2.y - node.y) * (pt2.y - node.y));
	double dist12_3 = sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
	double dist21 = sqrt((pt1.x - pt3.x) * (pt1.x - pt3.x) + (pt1.y - pt3.y) * (pt1.y - pt3.y));
	double dist22 = sqrt((pt3.x - pt2.x) * (pt3.x - pt2.x) + (pt3.y - pt2.y) * (pt3.y - pt2.y));
	return ((pow(dist11, 2) + pow(dist12, 2) - pow(dist12_3, 2)) / (2 * dist11 * dist12) < (pow(dist21, 2) + pow(dist22, 2) - pow(dist12_3, 2)) / (2 * dist21 * dist22)); //余弦判断角度
}


bool is_same_line(Line& l1,const Line& l2)    //判断传入的两条线在几何上是否是一样的
{
	if ((l1.left_point == l2.left_point && l1.right_point == l2.right_point) || (l1.left_point == l2.right_point && l1.right_point == l2.left_point))
		return true;
	else
		return false;
}

int is_in_myline(Line& l,std::vector<Line>& myline)   //判断传入的 line 是否在 myline 中
{                                                       //如果在 就返回该直线在myline数组中的下标
	int ret = 0;                                        //如果不在  就返回一个负数
	int i = 0;
	for (i = 0; i < myline.size(); i++)
	{
		if (is_same_line(l, myline[i]))
		{
			ret = 1;
			break;
		}
	}

	if (ret == 1)
		return i;
	else
		return -1;
}


#include"Equal_point.h"

int main()
{
	std::vector<Point> mypoint;     //三角网形成的点集
	std::vector<Line> myline;       // 三角网形成的线集
	std::vector<Triangle> mytriangle; //三角网形成的三角形集
	initgraph(WIDTH, HEIGHT);
	// 设置背景色为蓝色
	setbkcolor(WHITE);
	// 用背景色清空屏幕
	cleardevice();


	get_point(mypoint);  //从txt文件中读取文件


	myline.reserve((1 + mypoint.size()) * mypoint.size() / 2);   //这个条件至关重要！！！！，因为triangle结构体存的是mypoint[i]中的地址，所以mypoint在增容的时候绝对不能出现改变地址的情况，所以刚开始索性一次性开够
	//求缩放因子

	//先找到x,y,z方向上的最大值和最小值
	double max_x = mypoint[0].x, max_y = mypoint[0].y, min_x = mypoint[0].x, min_y = mypoint[0].y, min_z = mypoint[0].z, max_z = mypoint[0].z;
	for (auto& e : mypoint)
	{
		if (e.x < min_x)
			min_x = e.x;
		else if (e.y < min_y)
			min_y = e.y;
		else if (e.x > max_x)
			max_x = e.x;
		else if (e.y > max_y)
			max_y = e.y;
		else if (e.z < min_z)
			min_z = e.z;
		else if (e.z > max_z)
			max_z = e.z;
	}



	//让整个范围与坐标系空出 整个图幅的1/50 这样边界点能完整显示
	min_x -= (max_x - min_x) / 70;
	min_y -= (max_y - min_y) / 70;
	max_x += (max_x - min_x) / 70;
	max_y += (max_y - min_y) / 70;

	double scaling_x = (max_x - min_x) / WIDTH;
	double scaling_y = (max_y - min_y) / HEIGHT;

	
	for (auto e : mypoint)  //将点先打在屏幕上
	{
		Point_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
	}



	//寻找距离最近的两个点
	//std::vector<int> used_point;    //记录已经使用过的点的下标
	int pt1, pt2;                      //用于记录头两个举例最近的点的数组下表
	double MIN = distance(mypoint[0].x, mypoint[0].y, mypoint[1].x, mypoint[1].y);
	Line MIN_line;
	for (int i=0;i<mypoint.size();i++)
	{
		for (int j=i+1;j<mypoint.size();j++)
		{
			if (distance(mypoint[i].x, mypoint[i].y, mypoint[j].x, mypoint[j].y)<MIN)
			{
				MIN = distance(mypoint[i].x, mypoint[i].y, mypoint[j].x, mypoint[j].y);
				MIN_line.make_line(mypoint[i], mypoint[j]);
				pt1 = i;
				pt2 = j;
			}
		}
	}


	//层序遍历生成三角网
	//生成第一个三角形
	double r, a, b;
	Point p3 = mypoint[0];
	for (int i = 0; i < mypoint.size(); i++)
	{
		if (i != pt1 && i != pt2)
		{
			if (JudgePoint(MIN_line.left_point, MIN_line.right_point, p3, mypoint[i]))
			{
				p3 = mypoint[i];
			}

		}
	}
	myline.push_back(make_line(MIN_line.left_point, MIN_line.right_point, p3));
	line_to_gragh(MIN_line, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);

	myline.push_back(make_line(p3,mypoint[pt1],mypoint[pt2]));
	line_to_gragh(make_line(p3, mypoint[pt1], mypoint[pt2]), Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);

	myline.push_back(make_line(p3, mypoint[pt2], mypoint[pt1]));
	line_to_gragh(make_line(p3, mypoint[pt2], mypoint[pt1]), Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);

	mytriangle.push_back(Triangle(&myline[0], &myline[1], &myline[2]));


	//开始循环遍历
	Point p1;
	Point p2;  //用来记录 遍历时线两个端点的临时变量
	for (int i = 0; i < myline.size(); i++)
	{
		setlinecolor(GREEN);
		line_to_gragh(myline[i], Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,GREEN);
		Sleep(TIME);
		int ret = 0;
		if (myline[i].flag > 0)
			continue;

		p1 = myline[i].left_point;
		p2 = myline[i].right_point;

		p3 = Point(-1, NULL, min_x, min_y, 0);
		for (int j = 0; j < mypoint.size(); j++)
		{
			if (p1 == mypoint[j] || p2 == mypoint[j])    // 判断待定点是否与基线边的两个端点相同
			{
				continue;
			}

			if (is_same_side(myline[i], mypoint[j],min_x,min_y))  //判断相对点和待定点是否在同一边
			{
				continue;
			}

			if (p3 == Point(-1, NULL, 0, 0, 0))
				p3 = mypoint[j];
			else
			{
				if (JudgePoint(p1, p2, p3, mypoint[j]))    // 判断是否满足最大角原则
					p3 = mypoint[j];
			}
		}

		if (p3 != Point(0, NULL, min_x, min_y, 0))
		{
			Line ln13 = make_line(p3, p1, p2);
			Line ln23 = make_line(p3, p2, p1);

			Line* tri_l1 = nullptr;   //要插入三角形的边的指针
			Line* tri_l2 = nullptr;

			int ret1 = 0;
			if ((ret1=is_in_myline(ln13, myline))<0 )
			{
				myline.push_back(ln13);

				line_to_gragh(ln13, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);
				Sleep(TIME);

				tri_l1 = &myline[myline.size() - 1];   //说明ln13不在myline中属于新生成的边，直接指向myline数组新插入的最后一个元素
			}
			else
			{
				tri_l1 = &myline[ret1];   //ln13在myline中已经存在了，指针指向ret1下标处的myline数组的值
				myline[ret1].flag=2;
			}

			int ret2 = 0;   
			if ((ret2 = is_in_myline(ln23, myline))<0)
			{
				myline.push_back(ln23);
				tri_l2 = &myline[myline.size() - 1];  //说明ln23不在myline中属于新生成的边，直接指向myline数组新插入的最后一个元素
				
				line_to_gragh(ln23, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);
				Sleep(TIME);
			}
			else
			{
				tri_l2 = &myline[ret2];           //ln23在myline中已经存在了，指针指向ret1下标处的myline数组的值
				myline[ret2].flag=2;
			}

			mytriangle.push_back(Triangle(&myline[i], tri_l1, tri_l2));

		}


		if (p3 != Point(0, NULL, min_x, min_y, 0))
			myline[i].flag = 2;
		else
			myline[i].flag = 1;
	}

	/*for (auto e : myline)
	{
		if(e.flag==1)
			line_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);
		else
			line_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, GREEN);
	}*/

	double interval = (max_z - min_z) / RATE;

	for (double Hz = min_z + interval; Hz < max_z; Hz += interval)   //取一个等高线Hz
	{
		Line* open = nullptr;
		Line* close = nullptr;
		int flag = 0;
		for (auto& e : myline)   //开曲线有线头，一定在flag为1的边上，且flag==1的边只可能属于一个三角形，我们先找到这条边
		{
			if (e.flag == 1 && line_contourline(e, Hz))
			{
				open = &e;
				flag = 1;
				break;
			}

			if (e.flag == 2 && line_contourline(e, Hz))
			{
				close = &e;
			}
		}

		if (flag==1)
		{
			for (auto& e : mytriangle)
			{
				if (*(e.left) == *open || *(e.right) == *open || *(e.root) == *open)  //找到开曲线flag==1的边所在的三角形
				{
					build_open_line(e, Hz, open, min_x, min_y, scaling_x, scaling_y, mytriangle, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
					break;
				}
			}
		}
		else if(flag!=1 && close!=nullptr)
		{
			for (auto& e : mytriangle)
			{
				if (*(e.left) == *close || *(e.right) == *close || *(e.root) == *close)  //找到开曲线flag==1的边所在的三角形
				{
					build_close_line(e, Hz, close, min_x, min_y, scaling_x, scaling_y, mytriangle, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
					break;
				}
			}
		}
	}

	for (auto e : mypoint)  //将点先打在屏幕上
	{
		Point_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
	}

	getchar();
	closegraph();
}


