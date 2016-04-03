
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_WEIGHT 20000
#define DEMAND_NUM 55
#define NODE_NUM 610

int Map[NODE_NUM][NODE_NUM];
int Node_of_all = 0;
int Node_of_demand = 0;
int Begin_node = -1, End_node = -1;
int is_demand[NODE_NUM] = {0};

struct Node
{
	int prev = -1;
	int num_of_demand = 0;
	int dist = 0;
}Nodes[NODE_NUM];

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
			Map[i][j] = 0;

	for(int i=0; i<edge_num; ++i)
	{
		sscanf(topo[i], "%d,%d,%d,%d", &a, &b, &c, &d);
		Map[b][c] = d;
	}
}

void search_route(char* topo[5000], int edge_num, char* demand)
{
	freopen("file.out", "w", stdout);


	read_demand(demand);
	read_data(topo, edge_num);
	

	fclose(stdout);
}

