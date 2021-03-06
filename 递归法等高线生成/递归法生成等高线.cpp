#define _CRT_SECURE_NO_WARNINGS 1
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
		if (_p)
			strcpy(p, _p);
	}

	void operator=(const Point& m)
	{
		num = m.num;
		if (m.p)
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
	Line(Point m = Point(), Point n = Point(), Point z = Point(), int flag = 0)   //所有线的生成都用这个定义
		:left_point(m)
		, right_point(n)
		, third(z)
		, flag(0)
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


	bool operator == (const Line& l2)
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
		, right(z)
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

void Point_to_gragh(Point& p, const Point& origin, double scaling_X, double scaling_Y)   //将实际点的坐标转换成能在easyX上打印的坐标
{

	int easy_x = (int)((p.x - origin.x) / scaling_X);
	int easy_y = (int)((p.y - origin.y) / scaling_Y);


	setcolor(BLUE);
	setfillcolor(BLACK);
	fillcircle(easy_x, easy_y, 3);

};



void line_to_gragh(const Line& l, const Point& origin, double scaling_X, double scaling_Y, COLORREF color)
{
	int easy_x1 = (int)((l.left_point.x - origin.x) / scaling_X);
	int easy_y1 = (int)((l.left_point.y - origin.y) / scaling_Y);

	int easy_x2 = (int)((l.right_point.x - origin.x) / scaling_X);
	int easy_y2 = (int)((l.right_point.y - origin.y) / scaling_Y);

	setlinecolor(color);
	//setlinestyle(20);
	line(easy_x1, easy_y1, easy_x2, easy_y2);
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
	v.push_back(Point(num, name, x, y, z));
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

		v.push_back(Point(num, name, x, y, z));
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


bool is_same_side(Line& l, Point& tmp, double min_x, double min_y)
{
	double k = (l.left_point.y - l.right_point.y) / (l.left_point.x - l.right_point.x);
	double b = l.left_point.y - min_y - k * (l.left_point.x - min_x);

	double ret1 = tmp.y - min_y - k * (tmp.x - min_x) - b;
	double ret2 = l.third.y - min_y - k * (l.third.x - min_x) - b;
	if (ret1 * ret2 >= 0)
		return true;
	else
		return false;
}

bool is_in_circle(Point& p, double x, double y, double r, double& min_x, double& min_y)  //判断point是否在圆心为（x,y）半径为r的园内   在->true  不在->false               
{
	double ret = (p.x - min_x - x) * (p.x - min_x - x) + (p.y - min_y - y) * (p.y - min_y - y);
	if ((int)ret < (int)r * r)
		return true;
	else
		return false;
}

// 用于计算两点的距离
double distance(double x1, double y1, double x2, double y2)
{
	double ret = sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
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

//以最大角为标准生成三角形
bool form_trangle_by_angle(Line& root, Point& newpoint, std::vector<Point>& mypoint, std::vector<Line>& myline, std::vector<Triangle>& mytriangle, double& min_x, double& min_y)
{
	double r;
	//for (int i = 0; i < mypoint.size(); i++)
	{

		//这里计算外接圆圆心的时候需要进行一个坐标平移，以(min_x,min_y)为原点的坐标系建立，否则计算外接圆的时候数据可能会溢出
		int flag = 1;
		Point p3 = Point(-1, NULL, min_x, min_y, 0);
		for (int j = 0; j < mypoint.size(); j++) //这里不用做检查 因为即使这个点是三角形的三点，会在圆的边界上
		{
			if (mypoint[j] == root.left_point || mypoint[j] == root.right_point)  //与直线建立三角形的点必须是没有用过的
			{
				continue;
			}

			if (myline.size() != 1)//如果不是第一条基线边，就要满足待定点和相对点不同侧
			{
				//if((is_same_side(root, mypoint[i], min_x, min_y)) || (mypoint[i] == root.third))
				if (is_same_side(root, mypoint[j], min_x, min_y))
					continue;
				if (mypoint[j] == root.third)
					continue;
			}
			if (p3 == Point(-1, NULL, min_x, min_y, 0))
			{
				p3 = mypoint[j];
			}
			else
			{
				if (JudgePoint(root.left_point, root.right_point, p3, mypoint[j]))
				{
					p3 = mypoint[j];
				}
			}
		}

		if (p3 != Point(-1, NULL, min_x, min_y, 0))
		{
			newpoint = p3;
			return true;
		}
	}

	return false;
}


//以最小外接圆内没有其他点为条件生成三角网
bool form_trangle_by_circle(Line& root, Point& newpoint, std::vector<Point>& mypoint, std::vector<Line>& myline, std::vector<Triangle>& mytriangle, double& min_x, double& min_y)
{
	Point circle;
	double r;
	for (int i = 0; i < mypoint.size(); i++)
	{
		if (mypoint[i] != root.left_point && mypoint[i] != root.right_point && (myline.size() == 1 || (is_same_side(root, mypoint[i], min_x, min_y) == false && mypoint[i] != root.third)))  //与直线建立三角形的点必须是没有用过的
		{
			//这里计算外接圆圆心的时候需要进行一个坐标平移，以(min_x,min_y)为原点的坐标系建立，否则计算外接圆的时候数据可能会溢出
			CircleCenter(root.left_point.x - min_x, root.left_point.y - min_y, root.right_point.x - min_x, root.right_point.y - min_y, mypoint[i].x - min_x, mypoint[i].y - min_y, &(circle.x), &(circle.y), &r);
			int flag = 1;
			Point p3 = Point(-1, NULL, min_x, min_y, 0);
			for (int j = 0; j < mypoint.size(); j++) //这里不用做检查 因为即使这个点是三角形的三点，会在圆的边界上
			{
				if (is_in_circle(mypoint[j], circle.x, circle.y, r, min_x, min_y))   //所有点都必须不在圆内
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				newpoint = mypoint[i];
				return true;
			}
		}
	}

	return false;
}
//
void TIN(Line* root, std::vector<Point>& mypoint, std::vector<Line>& myline, std::vector<Triangle>& mytriangle, double& min_x, double& min_y, double scaling_x, double scaling_y)
{
	Point newpoint;
	if (form_trangle_by_circle(*root, newpoint, mypoint, myline, mytriangle, min_x, min_y))    //看是否还能形成三角形  能->返回真，并且将第三点的下标push到数组used_point中		          
	{                                                                                                  //不能->返回假
		//根据line类型的参数寻找第三个点
		Line newleftline;
		Line newrightline;
		Line* l = nullptr, * r = nullptr;

		line_to_gragh(*root, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, GREEN);
		Sleep(TIME);


		newleftline = make_line((*root).left_point, newpoint, (*root).right_point);    //新形成的线的 左右点 一定要确定清楚 
		line_to_gragh(newleftline, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, RED);
		Sleep(TIME);

		newrightline = make_line((*root).right_point, newpoint, (*root).left_point);    //生成三角形的右边
		line_to_gragh(newrightline, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, RED);
		Sleep(TIME);

		//一线一点连成三角形，分别将线和三角形录入相应的数组

		if (std::find(myline.begin(), myline.end(), newleftline) == myline.end())
		{
			myline.push_back(newleftline);
			l = &myline[myline.size() - 1];
			TIN(l, mypoint, myline, mytriangle, min_x, min_y, scaling_x, scaling_y);

		}
		if (std::find(myline.begin(), myline.end(), newrightline) == myline.end())
		{
			myline.push_back(newrightline);
			r = &myline[myline.size() - 1];
			TIN(r, mypoint, myline, mytriangle, min_x, min_y, scaling_x, scaling_y);
		}
		Triangle newT(root, r, l);
		mytriangle.push_back(newT);

		//递归  根左右 前序遍历
		//TIN(left...............);
		//TIN(right..............);
	}
	else
	{
		line_to_gragh(*root, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, GREEN);
		Sleep(TIME);
	}
}



bool is_same_line(Line& l1, const Line& l2)    //判断传入的两条线在几何上是否是一样的
{
	if ((l1.left_point == l2.left_point && l1.right_point == l2.right_point) || (l1.left_point == l2.right_point && l1.right_point == l2.left_point))
		return true;
	else
		return false;
}

int is_in_myline(Line& l, std::vector<Line>& myline)   //判断传入的 line 是否在 myline 中
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
	for (int i = 0; i < mypoint.size(); i++)
	{
		for (int j = i + 1; j < mypoint.size(); j++)
		{
			if (distance(mypoint[i].x, mypoint[i].y, mypoint[j].x, mypoint[j].y) < MIN)
			{
				MIN = distance(mypoint[i].x, mypoint[i].y, mypoint[j].x, mypoint[j].y);
				MIN_line.make_line(mypoint[i], mypoint[j]);
				pt1 = i;
				pt2 = j;
			}
		}
	}



	//递归生成三角网
	myline.push_back(MIN_line);
	TIN(&myline[0], mypoint, myline, mytriangle,min_x,min_y, scaling_x, scaling_y);

	for (auto e : mypoint)  //将点先打在屏幕上
	{
		Point_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
	}

	getchar();
	closegraph();
}