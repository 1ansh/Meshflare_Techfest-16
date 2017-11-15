/* This code is not complete. The complete code was lost. This is a backup that I saved before completing the algorithm.
   Dijkstra's Algorithm part needs modification and rest part works just fine. :) */

#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int search(int x,int y,int angle,int dir_arr[8]);
int travel(int arr[]);

typedef struct
{
	int x,y,angle,array[8];
}Node;
Node node[30];
Node dupnode[30];

typedef struct
{
	int barray[3][3];
}ShortestPath;
ShortestPath store_path[30];

int aaya[30],i,j,count=0,parent=0,current_visited=0;

int main()
{
  node[0].x=0;
  node[0].y=0;
  node[0].angle=0;
  dupnode[0].x=0;
  dupnode[0].y=0;
  dupnode[0].angle=0;
  aaya[0]=1;
  for(i=0;i<8;i++)
  {
  	if(i==6)
  	{
  		node[0].array[i]=2;
  	}
  	else if(i==2)
  	{
  		node[0].array[i]=10;
  	}
  	else
  	{
  		node[0].array[i]=0;
  	}
  }
  dupnode[0]=node[0];
  for(i=0;i<3;i++)
  {
  	for(j=0;j<3;j++)
  	{
  		if(i==0&&j==0)
  		{
  			store_path[0].barray[i][j]=aaya[0];
  		}
  		else if(i==0&&j==1)
  		{
  			store_path[0].barray[i][j]=102;
  		}
  		else if(i==0&&j==2)
  		{
  			store_path[0].barray[i][j]=1;
  		}
  		else
  		{
  			store_path[0].barray[i][j]=999;
  		}
  	}
  }
  for(i=1;i<30;i++)
  {
  	aaya[i]=999;
  }
  search(x,y,angle,arr1[8]);
}




int search(int x,int y,int angle,int dir_arr[8])
{
  int check=0,temp[8],norm_angle,kaha_jau;
	for(i=0;i<=count;i++)
	{
		if(node[i].x==x && node[i].y==y && !(dir_arr[0]==0&& dir_arr[1]==0&& dir_arr[2]==0&& dir_arr[3]==0&& dir_arr[4]==0&& dir_arr[5]==0&& dir_arr[6]==0&& dir_arr[7]==0) )
		{
			check++;
		}
		if(check==1)
		{
			current_visited=i;
			break;
		}
	}
	if(check==1)
	{
		aaya[current_visited]=aaya[current_visited]+1;
		for(j=0;j<8;j++)
		{
			temp[j]=dupnode[current_visited].array[j];
		}
		norm_angle=(angle-dupnode[current_visited].angle)/45;
		for(i=0;i<8;i++)
		{
			if((i-norm_angle)>=0)
			{
				temp[i-norm_angle]=dupnode[current_visited].array[i];//////////////////////////////////////////////////sign change
			}
			else if((i-norm_angle)<0)
			{
				temp[8+i-norm_angle]=dupnode[current_visited].array[i];/////////////////////////////////////////////////sign change
			}
		}

		for(j=0;j<8;j++)
		{
			dupnode[current_visited].array[j]=temp[j];
		}
		dupnode[current_visited].angle=angle;
		kaha_jau=travel(dupnode[current_visited].array);

	}
	if(check==0 && !(dir_arr[0]==0&& dir_arr[1]==0&& dir_arr[2]==0&& dir_arr[3]==0&& dir_arr[4]==0&& dir_arr[5]==0&& dir_arr[6]==0&& dir_arr[7]==0) )
	{
		count++;
		current_visited=count;
		aaya[current_visited]=1;
		node[current_visited].x=x;
		node[current_visited].y=y;
		node[current_visited].angle=angle;
		////////////////////
		for(j=0;j<8;j++)
		{
			node[current_visited].array[j]=dir_arr[j];
		}
		///////////////

		dupnode[current_visited]=node[current_visited];
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				store_path[current_visited].barray[i][j]=999;
			}
		}
		kaha_jau=travel(dupnode[current_visited].array);
	}
	if(check==0 && (dir_arr[0]==0&& dir_arr[1]==0&& dir_arr[2]==0&& dir_arr[3]==0&& dir_arr[4]==0&& dir_arr[5]==0&& dir_arr[6]==0&& dir_arr[7]==0 ))
	{
		x=x+1;
		y=y+1;
		count++;
		current_visited=count;
		aaya[current_visited]=1;
		node[current_visited].x=x;
		node[current_visited].y=y;
		node[current_visited].angle=angle;
		////////////////////
		for(j=0;j<8;j++)
		{
			node[current_visited].array[j]=dir_arr[j];
		}
		///////////////

		dupnode[current_visited]=node[current_visited];
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				store_path[current_visited].barray[i][j]=999;
			}
		}
		kaha_jau=travel(dupnode[current_visited].array);
	}
	return kaha_jau;
}

int travel(int arr[])
{
	int i,go_to=0,pcount,flag=0;

	store_path[parent].barray[aaya[parent]-1][2]=current_visited;
	pcount=aaya[current_visited]-1;
  for(i=0;i<8;i++)
  {
    if(arr[i]==1)
    {
      arr[i]=10;
      go_to=i;
      flag++;
      break;
    }
  }
  if(flag!=1)
  {
	  for(i=0;i<8;i++)
	  {
	    if(arr[i]==2)
	    {
	      arr[i]=10;
	      go_to=i;
	      break;
	    }
	  }
  }

	store_path[current_visited].barray[pcount][0]=aaya[current_visited];
	if(go_to==0)
  {
		store_path[current_visited].barray[pcount][1]=100;
    // return leftturn();
  }
  if(go_to==1)
  {
		store_path[current_visited].barray[pcount][1]=101;
    // return leftchota();
  }
  if(go_to==2)
  {
		store_path[current_visited].barray[pcount][1]=102;
    // return straight();
  }
  if(go_to==3)
  {
		store_path[current_visited].barray[pcount][1]=103;
    // return rightchota();
  }
  if(go_to==4)
  {
		store_path[current_visited].barray[pcount][1]=104;
    // return rightturn();
  }
  if(go_to==6)
  {
		store_path[current_visited].barray[pcount][1]=106;
    // return uturn();
  }

	parent=current_visited;


	return store_path[current_visited].barray[pcount][1];
}



int actualrun()
{
	int flag=0,count1=-1,path[30];
	for(i=0;i<30;i++)
	{
		path[i]=999;
	}
	for(i=0;i<=count;i++)
	{
		for(j=0;j<8;j++)
		{
			if(dupnode[count].array[j]==2)
			{
				flag++;
			}
		}
		if(flag>0)
		{
			count1++;
			path[count1]=i;
		}
		flag=0
	}
	int I=0;
	while(path[I+1]!=999)
	{
		int chaloindex,chalocount=0,go;
		for(i=0;i<3;i++)
		{
			if(store_path[path[I]].barray[i][2]==path[I+1])
			{
				chaloindex=i;
			}
		}
		for(i=0;i<8;i++)
		{
			if(node[path[I]].array[i]!=0)
			{
					chalocount++;
			}
			if(chalocount==chaloindex)
			{
				go=i;
			}
		}
		  if(go==0)
		  {
				chalo[I]=100;
		    // leftturn();
		  }
		  if(go==1)
		  {
				chalo[I]=101;
		    // leftchota();
		  }
		  if(go==2)
		  {
				chalo[I]=102;
		    // straight();
		  }
		  if(go==3)
		  {
				chalo[I]=103;
		    // rightchota();
		  }
		  if(go==4)
		  {
				chalo[I]=104;
		    // rightturn();
		  }
		  if(go==6)
		  {
				chalo[I]=106;
		    // uturn();
		  }

		I++;
	}
}



int dijkstra()
{
	int cost[count+1][count+1];
	for(i=0;i<=count;i++)
	{
		for(j=0;j<=count;j++)
		{
			cost[i][j]=0;
		}
	}
	for(i=0;i<=count;i++)
	{
		for(j=0;j<3;j++)
		{
			if(store_path[i].barray[j][2]!=999)
			{
				cost[i][store_path[i].barray[j][2]]=store_path[i].barray[j][3];
			}
		}
	}
	int start=0,end=count,mindup,indexmin,path[30];
	int d[count+1];
	int dup[count+1];
	int v[count+1];
	int p[count+1];
	for(i=0;i<=count;i++)
	{
		d[i]=999;
		dup[i]=999;
		v[i]=0;
		p[i]=999;
	}
	d[start]=0;
	dup[start]=0;
	p[start]=-1;
	while(start!=end)
	{
		for(i=0;i<=count;i++)
		{
			if(cost[start][i]!=0 && d[i]>d[start]+cost[start][i] && v[i]==0)
			{
				d[i]=d[start]+cost[start][i];
				dup[i]=d[start]+cost[start][i];
				p[i]=start;
			}
		}
		v[start]=1;
		dup[start]=999;
		mindup=999;
		for(i=0;i<=count;i++)
		{
			if(dup[i]<mindup)
			{
				mindup=dup[i];
				indexmin=i;
			}
		}
		start=i;
	}
	if(start==end and p[end]!=999)
	{
		path[0]=end;
		i=1;
		while(p[end]!=-1)
		{
			path[i]=p[end];
			end=p[end];
			i++;
		}
	}
	i=0;
	for(j=29;j>=0;j--)
	{
		if(path[j]!=999)
		{
			path[i]=path[j];
			i++;
		}
	}
	int I=0;
	while(path[I+1]!=999)
	{
		int chaloindex,chalocount=0,go;
		for(i=0;i<3;i++)
		{
			if(store_path[path[I]].barray[i][2]==path[I+1])
			{
				chaloindex=i;
			}
		}
		for(i=0;i<8;i++)
		{
			if(node[path[I]].array[i]!=0)
			{
					chalocount++;
			}
			if(chalocount==chaloindex)
			{
				go=i;
			}
		}
		  if(go==0)
		  {
				chalo[I]=100;
		    // return leftturn();
		  }
		  if(go==1)
		  {
				chalo[I]=101;
		    // return leftchota();
		  }
		  if(go==2)
		  {
				chalo[I]=102;
		    // return straight();
		  }
		  if(go==3)
		  {
				chalo[I]=103;
		    // return rightchota();
		  }
		  if(go==4)
		  {
				chalo[I]=104;
		    // return rightturn();
		  }
		  if(go==6)
		  {
				chalo[I]=106;
		    // return uturn();
		  }

		I++;
	}
}



int chale(int Node)
{
	return chalo[Node];
}
