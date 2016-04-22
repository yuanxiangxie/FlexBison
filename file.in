/*
* This is my huawei test file
*/
#include "route.h"
#include "lib_record.h"
#include <cstdio>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stack>
#include <time.h>
#include<stdbool.h>

using namespace std;

#define Num_OF_All 610
#define Num_OF_Demand 55
#define MAX_WEIGHT 7200000

double times_cal = 0.0;
int vertex_num = 0;


int Begin_Node = -1, End_Node = -1;
int Is_Demand[Num_OF_All] = {0};
int Record_Array[Num_OF_All][Num_OF_All] = {0};
int Return_Record_Array[Num_OF_All][Num_OF_All] = {0};
int Path_Array[Num_OF_All][Num_OF_All] = { -1};
int Return_Path_Array[Num_OF_All][Num_OF_All] = {-1};
int num_of_all = 0, num_of_demand = 0;
int node_output[Num_OF_All] = {0};
int Return_node_output[Num_OF_All] = {0};

int final_path[Num_OF_All] = {-1};
int final_weight = MAX_WEIGHT;
int final_count = 0;

int Begin_Node_Num= 0, End_Node_Num = 0;
int Begin_Node_Array[Num_OF_All] = {0}, End_Node_Array[Num_OF_All] = {0};
bool Begin_Node_Flag[Num_OF_All]={false}, End_Node_Flag[Num_OF_All] = {false}; 

typedef struct 
{
	int prev;
	int is_viewed;
	int self_num;
	int num_of_demand;
	int dist;
}Node;

typedef struct
{
	int Edge_Num;
	int Weight;
}Route_Map;

Route_Map Map[Num_OF_All][Num_OF_All];
Route_Map Return_Map[Num_OF_All][Num_OF_All];
//stack<Node> s;
//stack<Node> return_s;

stack<Node> S[Num_OF_All];
stack<Node> Return_S[Num_OF_All];


void read_demand(char* demand)
{
	int count = 0, sum = 0;
	int length = strlen(demand);
	for(int i=0; i < length + 2 ; ++i)
		if(isdigit(demand[i]))
			sum = sum * 10 + demand[i] - '0';
		else if(demand[i] == ',')
		{
			if(!count)
				Begin_Node = sum;
			else
				End_Node = sum;
			sum = 0;
			count = 1;
		}
		else if(demand[i] == '\n')
		{
			Is_Demand[sum] = 1;
			num_of_demand ++;
			break;
		}
		else
		{
			Is_Demand[sum] = 1;
			sum = 0;
			num_of_demand ++;
		}
}

void read_data(char* topo[5000], int edge)
{
	int edge_num, node_1, node_2, weight;
	for(int i=0; i < Num_OF_All; ++i)
	{
		for(int j=0; j < Num_OF_All; ++j)
		{
			Map[i][j].Edge_Num = -1;
			Map[i][j].Weight = MAX_WEIGHT;
			Return_Map[i][j].Edge_Num = -1;
			Return_Map[i][j].Weight = MAX_WEIGHT;
		}
	}

	for(int i=0; i < edge; ++i)
	{
		sscanf(topo[i], "%d,%d,%d,%d", &edge_num, &node_1, &node_2, &weight); 
		if(weight < Map[node_1][node_2].Weight)
		{
			if(node_1 == Begin_Node)
				Begin_Node_Array[Begin_Node_Num++] = node_2;
			if(node_2 == End_Node)
				End_Node_Array[End_Node_Num++] = node_1;

			Map[node_1][node_2].Edge_Num = edge_num;
			Map[node_1][node_2].Weight = weight;
			node_output[node_1] ++;

			Return_Map[node_2][node_1].Edge_Num = edge_num;
			Return_Map[node_2][node_1].Weight = weight;
			Return_node_output[node_2] ++;
		}
		if(num_of_all < node_1)
			num_of_all = node_1;
	}
	num_of_all ++;
}

void init_parameter()
{
	for(int i = 0; i<num_of_all; ++i)
		for(int j=0; j<num_of_all; ++j)
		{
			Record_Array[i][j] = 0;
			Return_Record_Array[i][j] = 0;
			Path_Array[i][j] = -1;
			Return_Path_Array[i][j] = -1;
		}
}


void copy_node(Node* a, Node* b)
{
	(*a).prev = (*b).prev;
	(*a).is_viewed = (*b).is_viewed;
	(*a).self_num = (*b).self_num;
	(*a).num_of_demand = (*b).num_of_demand;
	(*a).dist = (*b).dist;
}

int cmp_1(const void* a, const void* b)
{
	Node* _a = (Node*)a; Node* _b = (Node*)b;
	/*
	if((*_a).self_num == Begin_Node && (*_a).num_of_demand == num_of_demand)
		return 1;
	else if((*_b).self_num == Begin_Node && (*_b).num_of_demand == num_of_demand)
		return -1;
	else if((*_a).dist < (*_b).dist)
		return 1;
	else if((*_a).dist == (*_b).dist && (*_a).num_of_demand > (*_b).num_of_demand)
		return 1;
	else
		return -1;
	*/
	//-------------------------------------------------------------------------------

	if((*_a).self_num == Begin_Node && (*_a).num_of_demand == num_of_demand)
		return 1;
	else if((*_b).self_num == Begin_Node && (*_b).num_of_demand == num_of_demand)
		return -1;
	else if((*_a).num_of_demand > (*_b).num_of_demand)
		return 1;
	else if((*_a).num_of_demand == (*_b).num_of_demand && (*_a).dist < (*_b).dist)
		return 1;
	else 
		return -1;
}


int cmp(const void* a, const void* b)
{
	Node* _a = (Node*)a; Node* _b = (Node*)b;
	/*
	if((*_a).self_num == End_Node && (*_a).num_of_demand == num_of_demand)
		return 1;
	else if(((*_b).self_num == End_Node) && (*_b).num_of_demand == num_of_demand)
		return -1;
	else if((*_a).dist < (*_b).dist)
		return 1;
	else if((*_a).dist == (*_b).dist && (*_a).num_of_demand > (*_b).num_of_demand)
		return 1;
	else
		return -1;
	*/
	//-----------------------------------------------------------------------------
	if((*_a).self_num == End_Node && (*_a).num_of_demand == num_of_demand)
		return 1;
	else if(((*_b).self_num == End_Node) && (*_b).num_of_demand == num_of_demand)
		return -1;
	else if((*_a).num_of_demand > (*_b).num_of_demand)
		return 1;
	else if((*_a).num_of_demand == (*_b).num_of_demand && (*_a).dist < (*_b).dist)
		return 1;
	else
		return -1;
	//-----------------------------------------------------------------------------
}

void save_path(int which_path)
{
	int num = End_Node, count = 0;
	int _sum = 0, _count = 0;
	unsigned short result[num_of_all];
	unsigned short result_node[num_of_all];
	while(Path_Array[which_path][num] != Begin_Node)
	{
		result_node[count++] = num;
		num = Path_Array[which_path][num];
	}
	result_node[count++] = num;
	result_node[count] = Begin_Node;
	for(int i=count; i>0; --i)
	{
		_sum += Map[result_node[i]][result_node[i-1]].Weight;
		result[_count++] = Map[result_node[i]][result_node[i-1]].Edge_Num;
		//printf("%d|", result[_count-1]);
	}
	//printf("\n");
	if(_sum < final_weight)
	{
		final_weight = _sum;
		for(int i=0; i<_count; ++i)
			final_path[i] = result[i];
		final_count = _count;
	}
}

void return_save_path(int which_path)
{
	int num = Begin_Node, count = 0;
	int _sum = 0, _count = 0;
	unsigned short result[num_of_all];
	unsigned short result_node[num_of_all];
	while(Return_Path_Array[which_path][num] != End_Node)
	{
		result_node[count++] = num;
		num = Return_Path_Array[which_path][num];
	}
	result_node[count++] = num;
	result_node[count] = End_Node;
	for(int i=0; i<count; ++i)
	{
		_sum += Map[result_node[i]][result_node[i+1]].Weight;
		result[_count++] = Map[result_node[i]][result_node[i+1]].Edge_Num;
		//printf("%d|", result[_count-1]);
	}
	//printf("\n");
	if(_sum < final_weight)
	{
		final_weight = _sum;
		for(int i=0; i<_count; ++i)
			final_path[i] = result[i];
		final_count = _count;
	}
}

void print_final_path()
{
	if(final_weight < MAX_WEIGHT)
	for(int i=0; i<final_count; ++i)
		record_result(final_path[i]);
	else
		printf("NA\n");
}

/*
void print_path()
{
	int num = End_Node, count = 0;
	unsigned short result_node[num_of_all];
	while(Path_Array[num] != Begin_Node)
	{
		result_node[count++] = num;
		num = Path_Array[num];
	}
	result_node[count++] = num;
	result_node[count] = Begin_Node;
	//--------------------------------------
	for(int i=count; i>=0; --i)
		printf("%d ", result_node[i]);
	printf("\n");
	//-------------------------------------
	for(int i=count; i>0; --i)
		record_result(Map[result_node[i]][result_node[i-1]].Edge_Num);
}
*/
/*
void return_print_path()
{
	int num = Begin_Node, count = 0;
	unsigned short result_node[num_of_all];
	while(Return_Path_Array[num] != End_Node)
	{
		result_node[count++] = num;
		num = Return_Path_Array[num];
	}
	result_node[count++] = num;
	result_node[count] = End_Node;
	for(int i=0;i<count; ++i)
		record_result(Map[result_node[i]][result_node[i+1]].Edge_Num);
}
*/

void add_view(Node* a, Node* b)
{
	(*a).is_viewed = 1;
	(*a).prev = (*b).prev;
	(*a).self_num = (*b).self_num;
	(*a).num_of_demand = (*b).num_of_demand;
	(*a).dist = (*b).dist;
}



void search_route(char* topo[5000], int edge, char* demand)
{
	freopen("file.out", "w", stdout);

	read_demand(demand);
	read_data(topo, edge);
	init_parameter();

	int need_of_demand;
	int need_of_dist;

	Node start_Node; //traintion_Node;
	Node Begin_Node_Trainsition[Begin_Node_Num], End_Node_Trainsition[End_Node_Num];
	Node end_Node; // trainsition_Node;

	start_Node.self_num = Begin_Node;
	start_Node.prev = -1;
	start_Node.num_of_demand = 0;
	start_Node.dist = 0;
	start_Node.is_viewed = 0;

	end_Node.self_num = End_Node;
	end_Node.prev = -1;
	end_Node.num_of_demand = 0;
	end_Node.dist = 0;
	end_Node.is_viewed = 0;

	Node second_Node;

	for(int i=0; i<Begin_Node_Num; ++i)
	{
		//printf("%d | %d\n", i, Begin_Node_Array[i]);
		while(!S[i].empty())
			S[i].pop();
		Record_Array[i][Begin_Node] = 1;
		S[i].push(start_Node);
		second_Node.self_num = Begin_Node_Array[i];
		second_Node.prev = Begin_Node;
		second_Node.num_of_demand = Is_Demand[second_Node.self_num];
		second_Node.dist = Map[Begin_Node][second_Node.self_num].Weight;
		second_Node.is_viewed = 0;
		S[i].push(second_Node);
	}

	for(int i=0; i<End_Node_Num; ++i)
	{
		//printf("the End_Node_Num: %d\n", End_Node_Num);
		while(!Return_S[i].empty())
			Return_S[i].pop();
		Return_Record_Array[i][End_Node] = 1;
		Return_S[i].push(end_Node);
		second_Node.self_num = End_Node_Array[i];
		second_Node.prev = End_Node;
		second_Node.num_of_demand = Is_Demand[second_Node.self_num];
		second_Node.dist = Return_Map[End_Node][second_Node.self_num].Weight;
		second_Node.is_viewed = 0;
		Return_S[i].push(second_Node);
	}


	int Node_Count[Begin_Node_Num]  = {0};
	int Return_Node_Count[End_Node_Num]  = {0};

	bool empty_bool = false;
	for(int i=0; i<Begin_Node_Num; ++i)
		if(S[i].size() > 1)
			empty_bool = true;
		else 
			continue;
	for(int i=0; i<End_Node_Num; ++i)
		if(Return_S[i].size() > 1)
			empty_bool = true;
		else
			continue;

	while(empty_bool)
	{
		//printf("Yes\n");
		for(int i=0; i<Begin_Node_Num; ++i)
			if(S[i].size() > 1)
			{
				//printf("size: %d | %d\n", i, S[i].size());
				copy_node(&Begin_Node_Trainsition[i], &S[i].top());
				//printf("%d | %d\n", i, Begin_Node_Trainsition[i].self_num);
				S[i].pop();
				Begin_Node_Flag[i] = false;
			}
			else
				Begin_Node_Flag[i] = true;

		for(int i=0; i<End_Node_Num; ++i)
			if(Return_S[i].size() > 1)
			{
				copy_node(&End_Node_Trainsition[i], &Return_S[i].top());
				//if(i==1)
				//	printf("%d | %d\n", i, End_Node_Trainsition[i].self_num);
				Return_S[i].pop();
				End_Node_Flag[i] = false;
			}
			else
				End_Node_Flag[i] = true;

		times_cal = (double)clock()/CLOCKS_PER_SEC;
		if(9.0 - times_cal < 0)
			break;

		for(int i=0; i<Begin_Node_Num; ++i)
			if(!Begin_Node_Flag[i] && Begin_Node_Trainsition[i].self_num == End_Node && Begin_Node_Trainsition[i].num_of_demand == num_of_demand)
			{
				//printf("the begin to end: %d | %d | %d\n", i, num_of_demand, Begin_Node_Trainsition[i].num_of_demand);
				save_path(i);
				Record_Array[i][Begin_Node_Trainsition[i].self_num] = 0;
				Begin_Node_Flag[i] = true;
			}
			else if(!Begin_Node_Flag[i] && Begin_Node_Trainsition[i].self_num == End_Node && Begin_Node_Trainsition[i].num_of_demand != num_of_demand)
			{
				Record_Array[i][Begin_Node_Trainsition[i].self_num] = 0;
				Begin_Node_Flag[i] = true;
			}
			else
			{
				if(!Begin_Node_Flag[i] && Begin_Node_Trainsition[i].is_viewed == 1)
				{
					Record_Array[i][Begin_Node_Trainsition[i].self_num] = 0;
					Begin_Node_Flag[i] = true;
				}
			}


		for(int i=0; i<End_Node_Num; ++i)
			if(!End_Node_Flag[i] && End_Node_Trainsition[i].self_num == Begin_Node && End_Node_Trainsition[i].num_of_demand == num_of_demand)
			{
				return_save_path(i);
				Return_Record_Array[i][End_Node_Trainsition[i].self_num] = 0;
				//for(int j=0; j<num_of_all; ++j)
					//printf("record_Array: %d | %d\n", i, Return_Record_Array[i][j]);
				End_Node_Flag[i] = true;
			}
			else if(!End_Node_Flag[i] && End_Node_Trainsition[i].self_num == Begin_Node && End_Node_Trainsition[i].num_of_demand != num_of_demand)
			{
				Return_Record_Array[i][End_Node_Trainsition[i].self_num] = 0;
				End_Node_Flag[i] = true;
			}
			else
			{
				if(!End_Node_Flag[i] && End_Node_Trainsition[i].is_viewed == 1)
				{
					Return_Record_Array[i][End_Node_Trainsition[i].self_num] = 0;
					End_Node_Flag[i] = true;
				}
			}

		for(int i=0; i<Begin_Node_Num; ++i)
		{
			if(!Begin_Node_Flag[i])
			{
				Node view_Node;
				add_view(&view_Node, &Begin_Node_Trainsition[i]);
				S[i].push(view_Node);

				Path_Array[i][Begin_Node_Trainsition[i].self_num] = Begin_Node_Trainsition[i].prev;
				Record_Array[i][Begin_Node_Trainsition[i].self_num] = 1;
				Node_Count[i] = 0;
			}
		}

		Node Nodes[Begin_Node_Num][num_of_all];

		for(int i=0; i<End_Node_Num; ++i)
		{
			if(!End_Node_Flag[i])
			{
				Node return_view_Node;
				add_view(&return_view_Node, &End_Node_Trainsition[i]);
				Return_S[i].push(return_view_Node);

				Return_Path_Array[i][End_Node_Trainsition[i].self_num] = End_Node_Trainsition[i].prev;
				Return_Record_Array[i][End_Node_Trainsition[i].self_num] = 1;
				Return_Node_Count[i] = 0;
			}
		}
		Node Return_Nodes[End_Node_Num][num_of_all];


		bool judge_flag = false;

		for(int i=0; i<Begin_Node_Num; ++i)
			if(!Begin_Node_Flag[i])
				judge_flag = true;
			else
				continue;
		for(int i=0; i<End_Node_Num; ++i)
			if(!End_Node_Flag[i])
				judge_flag = true;
			else
				continue;


		if(judge_flag)
		{
			for(int i=0; i<num_of_all; ++i)
			{
				for(int j = 0; j<Begin_Node_Num; ++j)
				{
					if(!Begin_Node_Flag[j] && Map[Begin_Node_Trainsition[j].self_num][i].Weight < MAX_WEIGHT)
					{
						//printf("%d | %d\n", i, Begin_Node_Trainsition[j].self_num);
						//printf("Begin_Node_Trainsition.dist: %d -- > %d | %d + %d\n", Begin_Node_Trainsition[j].self_num, i, Begin_Node_Trainsition[j].dist, Map[Begin_Node_Trainsition[j].self_num][i].Weight);
						need_of_dist = Begin_Node_Trainsition[j].dist + Map[Begin_Node_Trainsition[j].self_num][i].Weight;
						need_of_demand = Begin_Node_Trainsition[j].num_of_demand + Is_Demand[i];

						if(!Begin_Node_Flag[j] && (Begin_Node_Trainsition[j].self_num != i) && (need_of_dist < final_weight) && !Record_Array[j][i] && (node_output[i] > 0 || i == End_Node))
						{
						//if(j == 1)
						//	printf("%d --> %d | %d --> %d\n", Begin_Node_Trainsition[j].self_num, i, need_of_dist, final_weight);
							Path_Array[j][i] = Begin_Node_Trainsition[j].self_num;
							Nodes[j][Node_Count[j]].prev = Begin_Node_Trainsition[j].self_num; 
							Nodes[j][Node_Count[j]].is_viewed = 0;
							Nodes[j][Node_Count[j]].self_num = i;
							//printf("the answe is: %d | %d | %d | %d\n", Nodes[j][Node_Count[j]].self_num, j, Node_Count[j], i);
							Nodes[j][Node_Count[j]].num_of_demand = need_of_demand;
							Nodes[j][Node_Count[j]++].dist = need_of_dist;
						}
					}
				}

				for(int j = 0; j<End_Node_Num; ++j)
				{
					if(!End_Node_Flag[j] && Return_Map[End_Node_Trainsition[j].self_num][i].Weight < MAX_WEIGHT)
					{
						need_of_dist = End_Node_Trainsition[j].dist + Return_Map[End_Node_Trainsition[j].self_num][i].Weight;
						need_of_demand = End_Node_Trainsition[j].num_of_demand + Is_Demand[i];

						if(!End_Node_Flag[j] && (End_Node_Trainsition[j].self_num != i) && (need_of_dist <= final_weight) && !Return_Record_Array[j][i] && (Return_node_output[i] > 0 || i == Begin_Node))
						{
							Return_Path_Array[j][i] = End_Node_Trainsition[j].self_num;
							Return_Nodes[j][Return_Node_Count[j]].prev = End_Node_Trainsition[j].self_num;
							Return_Nodes[j][Return_Node_Count[j]].is_viewed = 0;
							Return_Nodes[j][Return_Node_Count[j]].self_num = i;
							Return_Nodes[j][Return_Node_Count[j]].num_of_demand = need_of_demand;
							Return_Nodes[j][Return_Node_Count[j]++].dist = need_of_dist;
						}
					}
				}
			}
				//printf("--------------------------------------------------\n");
		}

		for(int i=0; i < Begin_Node_Num; ++i)
		{
			if(!Begin_Node_Flag[i] && Node_Count[i] == 0)
			{
				S[i].pop();
				Record_Array[i][Begin_Node_Trainsition[i].self_num] = 0;
				Begin_Node_Flag[i] = true;
			}

			if(!Begin_Node_Flag[i])
			{
				qsort(Nodes[i], Node_Count[i], sizeof(Nodes[i][0]), cmp);
				for(int j=0; j<Node_Count[i]; ++j)
					S[i].push(Nodes[i][j]);
			}
		}

		for(int i=0; i < End_Node_Num; ++i)
		{
			if(!End_Node_Flag[i] && Return_Node_Count[i] == 0)
			{
				Return_S[i].pop();
				Return_Record_Array[i][End_Node_Trainsition[i].self_num] = 0;
				End_Node_Flag[i] = true;
			}
			 
			if(!End_Node_Flag[i])
			{
				qsort(Return_Nodes[i], Return_Node_Count[i], sizeof(Return_Nodes[i][0]), cmp_1);
				for(int j=0; j<Return_Node_Count[i]; ++j)
					Return_S[i].push(Return_Nodes[i][j]);
			}
		}

	empty_bool = false;
	for(int i=0; i<Begin_Node_Num; ++i)
		if(S[i].size() > 1)
			empty_bool = true;
		else 
			continue;
	for(int i=0; i<End_Node_Num; ++i)
		if(Return_S[i].size() > 1)
			empty_bool = true;
		else
			continue;
	}

	print_final_path();
	
	fclose(stdout);

}


