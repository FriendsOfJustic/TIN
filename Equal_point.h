#pragma once
class Equal_point
{
public:
	double x;       //x����
	double y;       //y����
	double z;       //z����

	Equal_point(double _x = 0, double _y = 0, double _z = 0)
		:x(_x)
		, y(_y)
		,z(_z)
	{}
	void operator=(const Equal_point& m)
	{
		x = m.x;
		y = m.y;
		z = m.z;
	}


	bool operator == (const Equal_point& m)
	{
		return (x == m.x) && (y == m.y);
	}


	bool operator !=(const Equal_point& m)
	{
		return !((x == m.x) && (y == m.y));
	}
};



class Equal_line
{
public:
	Equal_line(Equal_point m = Equal_point(), Equal_point n = Equal_point())   //�����ߵ����ɶ����������
		:left_point(m)
		, right_point(n)
	{}
	void make_line(Equal_point m = Equal_point(), Equal_point n = Equal_point())   //�����ߵ����ɶ����������
	{
		left_point = m;
		right_point = n;
	}


	bool operator == (const Equal_line& l2)
	{
		if ((this->left_point == l2.left_point && this->right_point == l2.right_point) || (this->left_point == l2.right_point && this->right_point == l2.left_point))
			return true;
		else
			return false;
	}

	Equal_point left_point;
	Equal_point right_point;
};


bool line_contourline(Line& ln, double Hz)    //�ж�ln�Ƿ���߶�ΪHz�ĵȸ����ཻ
{
	if ((ln.left_point.z > Hz && ln.right_point.z < Hz) || (ln.left_point.z<Hz && ln.right_point.z>Hz))
		return true;
	else
		return false;

}
bool triangle_contourline(Triangle& t, double Hz)   //�жϴ�����������봫��ĵȸ����Ƿ��ཻ
{
	if (line_contourline(*(t.left), Hz) || line_contourline(*(t.root), Hz) || line_contourline(*(t.right), Hz))
		return true;
	else
		return false;
}


Equal_point find_equal_point(Line& l,double h)   //���� l ����ȸ����ཻ�ĵ� 
{
	double a = l.left_point.x + (l.right_point.x - l.left_point.x) * ((h - l.left_point.z) / (l.right_point.z - l.left_point.z));
	double b= l.left_point.y + (l.right_point.y - l.left_point.y) * ((h - l.left_point.z) / (l.right_point.z - l.left_point.z));
	return Equal_point(a, b,h);
}

void Equalline_to_gragh(const Equal_line& l, const Equal_point& origin, double scaling_X, double scaling_Y, COLORREF color)
{
	int easy_x1 = (int)((l.left_point.x - origin.x) / scaling_X);
	int easy_y1 = (int)((l.left_point.y - origin.y) / scaling_Y);

	int easy_x2 = (int)((l.right_point.x - origin.x) / scaling_X);
	int easy_y2 = (int)((l.right_point.y - origin.y) / scaling_Y);

	setlinecolor(color);
	//setlinestyle(20);
	line(easy_x1, easy_y1, easy_x2, easy_y2);
}


//�ȸ��ߵ����ʣ�
//1.һ������������Ҫô��������ȸ����ཻ��Ҫôû�б���ȸ����ཻ

void build_open_line(Triangle& t,double h,Line* first, double min_x, double min_y,double scaling_x, double scaling_y, std::vector<Triangle> mytriangle, const Point& origin, double scaling_X, double scaling_Y)
{
	std::vector <Equal_line> myEqualline;
	std::vector<Equal_point> myEqualpoint;
	Line* next=nullptr;   //�ҵ�Ŀǰ�������е���һ����ȸ����ཻ�ı�    
	Triangle n = t;
	do
	{
		//�ҳ���һ����ȸ����ཻ�ı�
		if (*(n.left) != *first && line_contourline(*n.left, h))
			next = n.left;
		if (*n.right != *first && line_contourline(*n.right, h))
			next = n.right;
		if (*n.root != *first && line_contourline(*n.root, h))
			next = n.root;

		//
		myEqualpoint.push_back(find_equal_point(*first, h));
		myEqualpoint.push_back(find_equal_point(*next, h));

		//
		if ((*next).flag != 1)
		{
			for (auto& e : mytriangle)
			{
				if (n != e && e.is_have_line(*next))
				{
					first = next;
					n = e;
					break;
				}
			}
		}
	} while ((*next).flag!=1);

	int j = 0;
	for (int i = 0; i < myEqualpoint.size()-1; i++)
	{
		myEqualline.push_back(Equal_line(myEqualpoint[i], myEqualpoint[i + 1]));
	}

	for (auto e : myEqualline)
	{
		setlinestyle(0, 1, NULL, 0UL);
		Equalline_to_gragh(e, Equal_point(min_x, min_y, 0), scaling_x, scaling_y, RED);
	}

	
	/*POINT* p=new POINT[myEqualpoint.size()];
	for (int i = 0; i < myEqualpoint.size(); i++)
	{
		p[i].x = (LONG)((myEqualpoint[i].x - origin.x) / scaling_X);
		p[i].y = (LONG)((myEqualpoint[i].y - origin.y) / scaling_Y);	
	}
	setlinecolor(BLACK);
	setlinestyle(0, 1, NULL, 0UL);
	polybezier(p, myEqualpoint.size());*/
}



void build_close_line(Triangle& t, double h, Line* first, double min_x, double min_y, double scaling_x, double scaling_y, std::vector<Triangle> mytriangle, const Point& origin, double scaling_X, double scaling_Y)
{
	std::vector <Equal_line> myEqualline;
	std::vector<Equal_point> myEqualpoint;
	Line* next = nullptr;   //�ҵ�Ŀǰ�������е���һ����ȸ����ཻ�ı� 
	Line* begin = first;
	Triangle n = t;
	do
	{
		//�ҳ���һ����ȸ����ཻ�ı�
		if (*(n.left) != *first && line_contourline(*n.left, h))
			next = n.left;
		if (*n.right != *first && line_contourline(*n.right, h))
			next = n.right;
		if (*n.root != *first && line_contourline(*n.root, h))
			next = n.root;

		//
		myEqualpoint.push_back(find_equal_point(*first, h));
		myEqualpoint.push_back(find_equal_point(*next, h));

		//
		if ((*next).flag != 1)
		{
			for (auto& e : mytriangle)
			{
				if (n != e && e.is_have_line(*next))
				{
					first = next;
					n = e;
					break;
				}
			}
		}
	} while (next!=begin);

	int j = 0;
	for (int i = 0; i < myEqualpoint.size() - 1; i++)
	{
		myEqualline.push_back(Equal_line(myEqualpoint[i], myEqualpoint[i + 1]));
	}

	/*for (auto e : myEqualline)
	{
		Equalline_to_gragh(e, Equal_point(min_x, min_y, 0), scaling_x, scaling_y, RED);
	}*/


	POINT* p = new POINT[myEqualpoint.size()];
	for (int i = 0; i < myEqualpoint.size(); i++)
	{
		p[i].x = (LONG)((myEqualpoint[i].x - origin.x) / scaling_X);
		p[i].y = (LONG)((myEqualpoint[i].y - origin.y) / scaling_Y);
	}
	setlinecolor(BLACK);
	polybezier(p, myEqualpoint.size());
}