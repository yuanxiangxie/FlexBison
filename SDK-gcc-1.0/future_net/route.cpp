
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include<string.h>
#include<ctype.h>

#define Node_Num  610
#define Demand_Num  55
#define MAX_INT 500
#define MAX_WEIGHT 20000

int begin_node = -1, end_node = -1;
int map[Node_Num][Node_Num] = {0};
int node_record[Node_Num][Node_Num] = {0};
int is_demand[610] = {0};
int node_of_all = 0;
int dist[610] = {MAX_WEIGHT};

struct Node 
{
	int prev;
	int num_of_demand;
	int dist;
}Nodes[610];

void split_str(char* str)
{

	int length = strlen(str);
	int sum = 0;
	int count = 2;
	for(int i = 0; i<=length; ++i)
	{
		if(str[i] != ',' && str[i] != '|' && str[i] != '\0')
		{
			sum = sum * 10 + str[i] - '0';
		}
		else
		{
			if(str[i] == ',')
			{ 
				if(count == 2)
					begin_node = sum;
				else 
					end_node = sum;
			}
			else
				is_demand[sum] = 1;
			sum = 0;
			continue;
		}
	}

}

void init_map(char* topo[5000], int edge_num)
{
	for(int i=0; i<610; ++i)
		for(int j=0; j<610; ++j)
			map[i][j] = MAX_INT;
	int sum = 0, count = 0;
	int array[4] = {0};
	for(int i=0; i<edge_num; ++i)
	{
		sum = 0; count = 0;
		int length = strlen(topo[i]);
		for(int j=0; j<=length; ++j)
		{
			if(isdigit(topo[i][j]))
				sum = sum * 10 + topo[i][j] - '0'; 
			else
			{
				array[count++] = sum;
				sum = 0;
			}
		}
		if(array[1] > node_of_all)
			node_of_all = array[1];
		map[array[1]][array[2]] = array[3];
		map[array[1]][array[1]] = 0;
		array[0] = 0; array[1] = 0;	array[2] = 0; array[3] = 0;
	}
	node_of_all ++;
}

void init_struct()
{
	for(int i=0; i<610; ++i)
	{
		Nodes[i].prev = -1;
		Nodes[i].num_of_demand = 0;
		Nodes[i].dist = MAX_WEIGHT;
	}
}

void init_node_record()
{
	for(int i=0; i<610; ++i)
		for(int j = 0; j<610; ++j)
			node_record[i][j] = 0;
}

void search_route(char *topo[5000], int edge_num, char *demand)
{
	freopen("file.out", "w", stdout);

	
	split_str(demand);
	init_map(topo, edge_num);
	init_struct();
	init_node_record();

	int min_weight  = MAX_WEIGHT;

	for(int i = 0; i < node_of_all; ++i)
		dist[i] =  map[begin_node][i];

	dist[begin_node] = 0;
	node_record[begin_node][begin_node] = 1;
	
	for(int i=0; i<num_of_all; ++i)
	{
		min_weight = MAX_WEIGHT;
		int min_node = begin_node;
		for(int j=0; j<num_of_all; ++j)
		if(!node_record[j][j] && dist[j] < min_weight)
		{
			min_node = j;
			min_weight = dist[j];
		}
		node_record[min_node][min_node] = 1;
		Nodes[min_node].prev = begin_node;
		Nodes[min_node].num_of_demand += is_demand[min_node];
		Nodes[min_node].dist = dist[j];

		for(int j=0; j<num_of_all; ++j)
		if(!node_record[j][j] && map[min_node][j] < dist[j])
		{
			if(dist[min_node] + map[min_node][j] < dist[j])
			{
				dist[j] = dist[min_node] + map[min_node][j];
				Nodes[j].prev = min_node;
				Nodes[j].num_of_demand += Nodes[min_node].num_of_demand + is_demand[j];
				Nodes[j].dist = dist[j];
			}
		}
	}


	/*
	for(int i=0; i<610; ++i)
	{
		for(int j=0; j<610; ++j)
		{ 
		//	if(map[i][j] == 0)
		//		continue;
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	*/

	fclose(stdout);
}
