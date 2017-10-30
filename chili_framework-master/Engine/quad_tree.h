#pragma once

#include "utils.h"
#include "Graphics.h"
#include "Colors.h"
#include "Vec2.h"
#include <vector>

using namespace std;

#define GMINY 0
#define GMAXY (Graphics::ScreenHeight - 1)
#define GMINX 0
#define GMAXX (Graphics::ScreenWidth - 1)

//#define GMINY -500000
//#define GMAXY  500000
//#define GMINX -500000
//#define GMAXX  500000

//-----------------------------------------------------------------------------
int random_int(int min, int max);
float random_between(const float & min, const float & max);
double random_between(const double & min, const double & max);

long sq_distance(const Tpoint<int> & a, const Tpoint<int> & b);
long long sq_distance(const Tpoint <long> & a, const Tpoint<long> & b);
double sq_distance(const Tpoint<float> & a, const Tpoint<float> & b);
double sq_distance(const Tpoint<double> & a, const Tpoint<double> & b);

template<typename T>
Tpoint<T> get_closest_p(const Trect<T> & rect, const Tpoint<T> & p);
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
class node
{
public:
	node(const Tpoint<int> & p = {},
		const Trect<int> upleft_rect = {},
		const Trect<int> m_upright_rect = {},
		const Trect<int> m_downleft_rect = {},
		const Trect<int> m_downright_rect = {});
	~node(void);
	node::node(const node & src);
	node & node::operator = (const node & src);
	void insert(const Tpoint<int> & p, const node * parent);
	Tpoint<int> find_closest_point(const Tpoint<int> & p, Tpoint<int> & closest, unsigned long long & best_dist) const;
	vector<Tpoint<int>> find_n_closest_points(const Tpoint<int> & p, int n, vector<Tpoint<int>> & found) const;
	void draw(Graphics & gfx, bool draw_rect = false) const;
public:
	Tpoint<int> m_p;
	_Vec2<float> velocity;
	Trect<int> m_ul_r, m_ur_r, m_dl_r, m_dr_r;
	node * m_ul, *m_ur, *m_dl, *m_dr;
};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
class quad_tree
{
public:
	quad_tree(void);
	~quad_tree(void);
	quad_tree::quad_tree(const quad_tree & src);
	quad_tree & quad_tree::operator = (const quad_tree & src);
	void insert(int x, int y);
	void insert(const Tpoint<int> & p);
	void clear(void);
	Tpoint<int> find_closest_point(const Tpoint<int> & p) const;
	vector<Tpoint<int>> find_n_closest_points(const Tpoint<int> & p, int n);
	void draw(Graphics & gfx, bool draw_rect = false) const;
public:
	node * m_root;
};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
class node_f
{
public:
	node_f(const Tpoint<float> & p = {},
		const Trect<float> upleft_rect = {},
		const Trect<float> m_upright_rect = {},
		const Trect<float> m_downleft_rect = {},
		const Trect<float> m_downright_rect = {});
	node_f(const node_f & src);
	node_f & operator=(const node_f & src);
	~node_f(void);
	void insert(const Tpoint<float> & p, const node_f * parent);
	void insert(const node_f & p, const node_f * parent);
	Tpoint<float> find_closest_point(const Tpoint<float> & p, Tpoint<float> & closest, double & best_dist) const;
	vector<node_f> find_n_closest_points(const Tpoint<float> & p, int n, vector<node_f> & found) const;
public:
	Tpoint<float> m_p;
	_Vec2<float> m_velocity;
	Trect<float> m_ul_r, m_ur_r, m_dl_r, m_dr_r;
	node_f * m_ul, *m_ur, *m_dl, *m_dr;
};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
class quad_tree_f
{
public:
	quad_tree_f(void);
	quad_tree_f(const quad_tree_f & src);
	quad_tree_f & operator = (const quad_tree_f & src);
	~quad_tree_f(void);

	void insert(float x, float y);
	void insert(const Tpoint<float> & p);
	void insert(const node_f & n);
	void clear(void);
	Tpoint<float> find_closest_point(const Tpoint<float> & p) const;
	vector<node_f> find_n_closest_points(const Tpoint<float> & p, int n);
public:
	node_f * m_root;
};
//-----------------------------------------------------------------------------