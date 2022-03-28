#define _CRT_SECURE_NO_WARNINGS 1
#include<math.h>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include<Windows.h>

#define WIDTH  1280
#define HEIGHT 720
#define TIME  100
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


	int num;        //���
	char p[20];     //���ݵ�����
	double x;       //x����
	double y;       //y����
	double z;       //z����
};

class Line
{
public:
	Line(Point m = Point(), Point n = Point(), Point z = Point(),int flag=0)   //�����ߵ����ɶ����������
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



	void make_line(Point m = Point(), Point n = Point())   //�����ߵ����ɶ����������
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
	Point right_point;        //һ��ֱ�ߵ� ��������
	Point third;             // �����һ��ֱ�ߣ���ôһ������һ�������ΰ�����ֱ��(��һ�������γ��⣩��������ʾ������������ֱ����Եĵ�
	int flag;                //��ʶһ��ֱ�߱����ٸ������ι���
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

Line make_line(const Point& m = Point(), const Point& n = Point(), const Point& z = Point())   //�����ߵ����ɶ����������
{
	return Line(m, n, z, false);
}

void Point_to_gragh(Point& p,const Point& origin, double scaling_X,double scaling_Y)   //��ʵ�ʵ������ת��������easyX�ϴ�ӡ������
{

	int easy_x = (int)((p.x-origin.x ) / scaling_X );
	int easy_y  = (int)((p.y-origin.y) / scaling_Y);


	setcolor(BLUE);
	setfillcolor(GREEN);
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

//���������ε����Բ������������������Բ��Բ�� ������ �Ͱ뾶
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

bool is_in_circle(Point& p,double x,double y,double r, double& min_x, double& min_y)  //�ж�point�Ƿ���Բ��Ϊ��x,y���뾶Ϊr��԰��   ��->true  ����->false               
{
	double ret = (p.x-min_x - x)*(p.x-min_x - x)+(p.y-min_y - y)*(p.y-min_y - y);
	if ((int)ret < (int)r*r)
		return true;
	else
		return false;
}

// ���ڼ�������ľ���
double distance(double x1, double y1, double x2, double y2)
{
	double ret=sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
	return ret;
}


//������ֵΪ���ʱ���������������ֵ
bool JudgePoint(Point& pt1, Point& pt2, Point& pt3, Point& node) {//�Ƚ�������node pt3��pt1 pt2���ɽǵĴ�С
	double dist11 = sqrt((pt1.x - node.x) * (pt1.x - node.x) + (pt1.y - node.y) * (pt1.y - node.y));
	double dist12 = sqrt((pt2.x - node.x) * (pt2.x - node.x) + (pt2.y - node.y) * (pt2.y - node.y));
	double dist12_3 = sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
	double dist21 = sqrt((pt1.x - pt3.x) * (pt1.x - pt3.x) + (pt1.y - pt3.y) * (pt1.y - pt3.y));
	double dist22 = sqrt((pt3.x - pt2.x) * (pt3.x - pt2.x) + (pt3.y - pt2.y) * (pt3.y - pt2.y));
	return ((pow(dist11, 2) + pow(dist12, 2) - pow(dist12_3, 2)) / (2 * dist11 * dist12) < (pow(dist21, 2) + pow(dist22, 2) - pow(dist12_3, 2)) / (2 * dist21 * dist22)); //�����жϽǶ�
}

////����С���Բ��û��������Ϊ��������������
//bool form_trangle_by_circle(Line& root, Point& newpoint, std::vector<Point>& mypoint, std::vector<Line>& myline, std::vector<Triangle>& mytriangle, double& min_x, double& min_y)
//{
//	Point circle;
//	double r;
//	for (int i = 0; i < mypoint.size(); i++)
//	{
//		if (mypoint[i] != root.left_point && mypoint[i] != root.right_point )  //��ֱ�߽��������εĵ������û���ù���
//		{
//			continue;
//		}
//
//		if (myline.size() != 1 && (is_same_side(root, mypoint[i], min_x, min_y) || mypoint[i] == root.third) )
//		{
//			continue;
//		}
//
//		//����������ԲԲ�ĵ�ʱ����Ҫ����һ������ƽ�ƣ���(min_x,min_y)Ϊԭ�������ϵ����������������Բ��ʱ�����ݿ��ܻ����
//		CircleCenter(root.left_point.x - min_x, root.left_point.y - min_y, root.right_point.x - min_x, root.right_point.y - min_y, mypoint[i].x - min_x, mypoint[i].y - min_y, &(circle.x), &(circle.y), &r);
//		int flag = 1;
//		Point p3 = Point(-1, NULL, min_x, min_y, 0);
//		for (int j = 0; j < mypoint.size(); j++) //���ﲻ������� ��Ϊ��ʹ������������ε����㣬����Բ�ı߽���
//		{
//			//if (is_in_circle(mypoint[j], circle.x, circle.y, r, min_x, min_y))   //���е㶼���벻��Բ��
//			//{
//			//	flag = 0;
//			//	break;
//			//}
//
//			if (p3 == Point(-1, NULL, min_x, min_y, 0))
//			{
//				p3 = mypoint[j];
//			}
//			else
//			{
//				if (JudgePoint(root.left_point, root.right_point, p3, mypoint[j]))
//				{
//					p3 = mypoint[j];
//				}
//			}
//		}
//
//		if (p3 != Point(-1, NULL, min_x, min_y, 0))
//		{
//			newpoint = p3;
//			return true;
//		}
//	}
//
//	return false;
//}
//
////������Ϊ��׼����������
//bool form_trangle_by_angle(Line& root, Point& newpoint ,std::vector<Point>& mypoint, std::vector<Line>& myline, std::vector<Triangle>& mytriangle, double& min_x, double& min_y)
//{
//	Point circle;
//	double r;
//	for (int i = 0; i < mypoint.size(); i++)
//	{
//		if(mypoint[i]!=root.left_point && mypoint[i]!=root.right_point && (myline.size()==1 || (is_same_side(root, mypoint[i], min_x, min_y) == false && mypoint[i]!=root.third) ))  //��ֱ�߽��������εĵ������û���ù���
//		{
//			//����������ԲԲ�ĵ�ʱ����Ҫ����һ������ƽ�ƣ���(min_x,min_y)Ϊԭ�������ϵ����������������Բ��ʱ�����ݿ��ܻ����
//			CircleCenter(root.left_point.x - min_x, root.left_point.y - min_y, root.right_point.x - min_x, root.right_point.y - min_y, mypoint[i].x - min_x, mypoint[i].y - min_y, &(circle.x), &(circle.y), &r);
//			int flag = 1;
//			Point p3 = Point(-1, NULL, min_x, min_y, 0);
//			for (int j = 0; j < mypoint.size(); j++) //���ﲻ������� ��Ϊ��ʹ������������ε����㣬����Բ�ı߽���
//			{
//				if (is_in_circle(mypoint[j], circle.x, circle.y, r, min_x, min_y))   //���е㶼���벻��Բ��
//				{
//					flag = 0;
//					break;
//				}
//			}
//			if (flag)
//			{
//				newpoint = mypoint[i];
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//void TIN(Line& root,std::vector<Point>& mypoint,std::vector<Line>& myline,std::vector<Triangle>& mytriangle,double &min_x,double &min_y ,double scaling_x, double scaling_y)
//{
//	Point newpoint;
//	if (form_trangle_by_angle(root,newpoint,mypoint,myline,mytriangle, min_x, min_y))    //���Ƿ����γ�������  ��->�����棬���ҽ���������±�push������used_point��		          
//	{                                                                                                  //����->���ؼ�
//		//����line���͵Ĳ���Ѱ�ҵ�������
//		Line newleftline;
//		Line newrightline;
//
//		line_to_gragh(root, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, GREEN);
//		Sleep(TIME);
//
//
//		newleftline=make_line(root.left_point, newpoint,root.right_point);    //���γɵ��ߵ� ���ҵ� һ��Ҫȷ����� 
//		line_to_gragh(newleftline, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, RED);
//		Sleep(TIME);
//		
//		newrightline=make_line(root.right_point, newpoint,root.left_point);    //���������ε��ұ�
//		line_to_gragh(newrightline, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, RED);
//		Sleep(TIME);
//		
//		//һ��һ�����������Σ��ֱ��ߺ�������¼����Ӧ������
//		Triangle newT(root, newleftline, newrightline);
//		if (std::find(myline.begin(), myline.end(), newleftline) == myline.end())
//		{
//			myline.push_back(newleftline);
//			TIN(newleftline, mypoint, myline, mytriangle, min_x, min_y, scaling_x, scaling_y);
//		}
//		if (std::find(myline.begin(), myline.end(), newrightline) == myline.end())
//		{
//			myline.push_back(newrightline);
//			TIN(newrightline, mypoint, myline, mytriangle, min_x, min_y, scaling_x, scaling_y);
//		}
//		mytriangle.push_back(newT);
//
//		//�ݹ�  ������ ǰ�����
//		//TIN(left...............);
//		//TIN(right..............);
//	}
//	else
//	{
//		line_to_gragh(root, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, GREEN);
//		Sleep(TIME);
//	}
//}



bool is_same_line(Line& l1,const Line& l2)    //�жϴ�����������ڼ������Ƿ���һ����
{
	if ((l1.left_point == l2.left_point && l1.right_point == l2.right_point) || (l1.left_point == l2.right_point && l1.right_point == l2.left_point))
		return true;
	else
		return false;
}

int is_in_myline(Line& l,std::vector<Line>& myline)   //�жϴ���� line �Ƿ��� myline ��
{                                                       //����� �ͷ��ظ�ֱ����myline�����е��±�
	int ret = 0;                                        //�������  �ͷ���һ������
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
	std::vector<Point> mypoint;     //�������γɵĵ㼯
	std::vector<Line> myline;       // �������γɵ��߼�
	std::vector<Triangle> mytriangle; //�������γɵ������μ�
	initgraph(WIDTH, HEIGHT);
	// ���ñ���ɫΪ��ɫ
	setbkcolor(WHITE);
	// �ñ���ɫ�����Ļ
	cleardevice();


	get_point(mypoint);  //��txt�ļ��ж�ȡ�ļ�


	myline.reserve((1 + mypoint.size()) * mypoint.size() / 2);   //�������������Ҫ������������Ϊtriangle�ṹ������mypoint[i]�еĵ�ַ������mypoint�����ݵ�ʱ����Բ��ܳ��ָı��ַ����������Ըտ�ʼ����һ���Կ���
	//����������

	//���ҵ�x,y,z�����ϵ����ֵ����Сֵ
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



	//��������Χ������ϵ�ճ� ����ͼ����1/50 �����߽����������ʾ
	min_x -= WIDTH / 50;
	min_y -= HEIGHT / 50;
	max_x += WIDTH / 50;
	max_y += HEIGHT / 50;

	double scaling_x = (max_x - min_x) / WIDTH;
	double scaling_y = (max_y - min_y) / HEIGHT;

	
	//for (auto e : mypoint)  //�����ȴ�����Ļ��
	//{
	//	Point_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
	//}



	//Ѱ�Ҿ��������������
	//std::vector<int> used_point;    //��¼�Ѿ�ʹ�ù��ĵ���±�
	int pt1, pt2;                      //���ڼ�¼ͷ������������ĵ�������±�
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



	/*�ݹ�����������
	myline.push_back(MIN_line);
	TIN(MIN_line, mypoint, myline, mytriangle,min_x,min_y, scaling_x, scaling_y);*/



	//�����������������
	//���ɵ�һ��������
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
	//line_to_gragh(MIN_line, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);

	myline.push_back(make_line(p3,mypoint[pt1],mypoint[pt2]));
	//line_to_gragh(make_line(p3, mypoint[pt1], mypoint[pt2]), Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);

	myline.push_back(make_line(p3, mypoint[pt2], mypoint[pt1]));
	//line_to_gragh(make_line(p3, mypoint[pt2], mypoint[pt1]), Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);

	mytriangle.push_back(Triangle(&myline[0], &myline[1], &myline[2]));


	//��ʼѭ������
	Point p1;
	Point p2;  //������¼ ����ʱ�������˵����ʱ����
	for (int i = 0; i < myline.size(); i++)
	{
		/*setlinecolor(GREEN);
		line_to_gragh(myline[i], Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,GREEN);
		Sleep(TIME);*/
		int ret = 0;
		if (myline[i].flag > 0)
			continue;

		p1 = myline[i].left_point;
		p2 = myline[i].right_point;

		p3 = Point(-1, NULL, min_x, min_y, 0);
		for (int j = 0; j < mypoint.size(); j++)
		{
			if (p1 == mypoint[j] || p2 == mypoint[j])
			{
				continue;
			}

			if (is_same_side(myline[i], mypoint[j],min_x,min_y))
			{
				continue;
			}

			if (p3 == Point(-1, NULL, 0, 0, 0))
				p3 = mypoint[j];
			else
			{
				if (JudgePoint(p1, p2, p3, mypoint[j]))
					p3 = mypoint[j];
			}
		}

		if (p3 != Point(0, NULL, min_x, min_y, 0))
		{
			Line ln13 = make_line(p3, p1, p2);
			Line ln23 = make_line(p3, p2, p1);

			Line* tri_l1 = nullptr;   //Ҫ���������εıߵ�ָ��
			Line* tri_l2 = nullptr;

			int ret1 = 0;
			if ((ret1=is_in_myline(ln13, myline))<0 )
			{
				myline.push_back(ln13);

			/*	line_to_gragh(ln13, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);
				Sleep(TIME);*/
				tri_l1 = &myline[myline.size() - 1];   //˵��ln13����myline�����������ɵıߣ�ֱ��ָ��myline�����²�������һ��Ԫ��
			}
			else
			{
				tri_l1 = &myline[ret1];   //ln13��myline���Ѿ������ˣ�ָ��ָ��ret1�±괦��myline�����ֵ
				myline[ret1].flag=2;
			}

			int ret2 = 0;   
			if ((ret2 = is_in_myline(ln23, myline))<0)
			{
				myline.push_back(ln23);
				tri_l2 = &myline[myline.size() - 1];
			/*	
				line_to_gragh(ln23, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y,RED);
				Sleep(TIME);*/
			}
			else
			{
				tri_l2 = &myline[ret2];
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

	for (auto e : myline)
	{
		setlinestyle(0, 2, NULL, 0UL);
		line_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y, BLACK);
	}


	//for (auto e : mypoint)  //�����ȴ�����Ļ��
	//{
	//	Point_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
	//}



	/*int count = 0;
	for (auto e : myline)
	{
		if (e.flag == 2)
			count++;
	}
	std::cout << count << std:: endl;*/

	double interval = (max_z - min_z) / RATE;

	for (double Hz = min_z + interval; Hz < max_z; Hz += interval)   //ȡһ���ȸ���Hz
	{
		Line* open = nullptr;
		Line* close = nullptr;
		int flag = 0;
		for (auto& e : myline)   //����������ͷ��һ����flagΪ1�ı��ϣ���flag==1�ı�ֻ��������һ�������Σ��������ҵ�������
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
				if (*(e.left) == *open || *(e.right) == *open || *(e.root) == *open)  //�ҵ�������flag==1�ı����ڵ�������
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
				if (*(e.left) == *close || *(e.right) == *close || *(e.root) == *close)  //�ҵ�������flag==1�ı����ڵ�������
				{
					build_close_line(e, Hz, open, min_x, min_y, scaling_x, scaling_y, mytriangle, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
					break;
				}
			}
		}
		//if (flag == 1)  //������
		//{
		//}
		//else   //������
		//{
		//}

	}

	for (auto e : mypoint)  //�����ȴ�����Ļ��
	{
		Point_to_gragh(e, Point(0, NULL, min_x, min_y, 0), scaling_x, scaling_y);
	}
	getchar();
	closegraph();
}


