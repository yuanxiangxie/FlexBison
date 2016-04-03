
#include "route.h"
#include "lib_record.h"
#include <cstdio>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stack>

using namespace std;

#define MAX_WEIGHT 20000
#define DEMAND_NUM 55
#define NODE_NUM 610

int Map[NODE_NUM][NODE_NUM];
int Edge[NODE_NUM][NODE_NUM];
int Node_of_all = 0;
int Node_of_demand = 0;
int Begin_node = -1, End_node = -1;
int is_demand[NODE_NUM] = {0};
int node_record[NODE_NUM] = {0};
int Min_node = -1;

typedef struct
{
	int prev;
	int self;
	int num_of_demand;
	int dist;
}Node;

Node struct_node;
Node Nodes[NODE_NUM];

stack<Node> s;

void read_demand(char* str)
{
	int sum = 0, count = 1;
	int length = strlen(str);
	for(int i=0; i < length; ++i)
	{
		if(isdigit(str[i]))
			sum = sum * 10 + str[i] -'0';
		else 
		{
			if(str[i] == ',')
			{
				if(count == 1)
					Begin_node = sum;
				else 
					End_node = sum;
				count ++;
			}
			else
			{
				is_demand[sum] = 1;
				Node_of_demand ++;
			}
			sum = 0;
		}
	}
}

void read_data(char* topo[5000], int edge_num)
{

	int a, b, c, d;
	for(int i=0; i<NODE_NUM; ++i)
		for(int j=0; j<NODE_NUM; ++j)
		{
			Map[i][j] = MAX_WEIGHT;
			Edge[i][j] = -1;
		}

	for(int i=0; i<edge_num; ++i)
	{
		sscanf(topo[i], "%d,%d,%d,%d", &a, &b, &c, &d);
		Map[b][c] = d;
		Edge[b][c] = a;
		if(Node_of_all < b)
			Node_of_all = b;
	}

	Node_of_all ++;
}

void init_recorde_node()
{
	for(int i=0; i < Node_of_all; ++i)
	{
		Nodes[i].prev = -1;
		Nodes[i].self = i;
		Nodes[i].num_of_demand = is_demand[i];
		Nodes[i].dist = MAX_WEIGHT;
	}
}

int cmp( const void* a, const void* b)
{
	Node* _a = (Node*) a;
	Node* _b = (Node*) b;
	if((*_a).num_of_demand > (*_b).num_of_demand)
		return 1;
	else if((*_a).num_of_demand == (*_b).num_of_demand && (*_a).dist < (*_b).dist)
		return 1;
	else
		return -1;
}

void copy(Node* a, Node* b)
{
	(*a).prev = (*b).prev;
	(*a).self = (*b).self;
	(*a).num_of_demand = (*b).num_of_demand;
	(*a).dist = (*b).dist;
}

void print_path()
{
	int Array[Node_of_all] = {-1}; 
	int count = 0;
	int u = 0;
	//for(int i=0; i<Node_of_all; ++i)
	//	printf("%d|%d|%d|%d\n", Nodes[i].prev, Nodes[i].self, Nodes[i].num_of_demand, Nodes[i].dist);

	while(struct_node.self != Begin_node)
	{
		Array[count++] = struct_node.self;
		u = Nodes[struct_node.self].prev;
		copy(&struct_node, &Nodes[u]);
	}
	
	Array[count] = Begin_node;
	unsigned short result[count];
	for(int i= count; i > 0; --i)
		result[count-i] = Edge[Array[i]][Array[i-1]];
	for(int i=0; i<count; ++i)
		record_result(result[i]);
		//printf("%d\n", result[i]);
}

void search_route(char* topo[5000], int edge_num, char* demand)
{
	//freopen("file.out", "w", stdout);

	read_demand(demand);
	read_data(topo, edge_num);
	init_recorde_node();

	bool flag = false;

	Node N[Node_of_all];
	int count_all = 0;
	for(int i=0; i < Node_of_all; ++i)
		if(Map[Begin_node][i] < MAX_WEIGHT)
		{
			Nodes[i].prev = Begin_node;
			N[count_all].prev = Begin_node;
			N[count_all].self = i;
			N[count_all].num_of_demand = is_demand[i];
			N[count_all++].dist = Map[Begin_node][i];
		}
	qsort(N, count_all, sizeof(N[0]), cmp);
	for(int i=0; i<count_all; ++i)
		s.push(N[i]);
	node_record[Begin_node] = 1;
	//printf("%d\n", Begin_node);

	while(!s.empty())
	{
		copy(&struct_node, &s.top());
		s.pop();
		node_record[struct_node.self] = 1;
		//printf("%d\n", struct_node.self);

		if(struct_node.self == End_node)
		{
			if(struct_node.num_of_demand == Node_of_demand)
			{
				print_path();
				return ;
			}
			else
			{
				continue;
			}
		}
		Min_node = struct_node.self;
		count_all = 0; flag = false;
		for(int i=0; i < Node_of_all; ++i)
			if(Map[Min_node][i] < MAX_WEIGHT && !node_record[i])
			{
				Nodes[i].prev = Min_node;
				N[count_all].prev = Min_node;
				N[count_all].self = i;
				N[count_all].num_of_demand = struct_node.num_of_demand + is_demand[i];
				N[count_all++].dist = struct_node.dist + Map[Min_node][i];
				flag = true;
			}
		if(!flag)
		{
			node_record[Min_node] = 0;
			continue;
		}
		qsort(N, count_all, sizeof(N[0]), cmp);
		
		for(int i=0; i<count_all; ++i)
			s.push(N[i]);
	}

	//fclose(stdout);
}

