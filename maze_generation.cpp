#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

wchar_t maze[100][100];
int dx[4] = {-2, 2, 0, 0}; // 0: 상 1: 하 2: 좌 3: 우
int dy[4] = {0, 0, -2, 2};
int dir[100][100];
bool path[100][100];
vector<pair<int, int>> remain;
bool valide(int r, int c)
{
	if (r >= 1 && r < 12 && c >= 1 && c < 12)
		return true;
	return false;
}
void wilson_algorithm()
{
	memset(dir, 0, sizeof(dir));
	if (remain.size() == 0)
		return;
	int idx = rand() % remain.size();
	int f_r = remain[idx].first;
	int f_c = remain[idx].second;
	remain.erase(remain.begin() + idx);
	if (remain.size() == 0)
		return;
	idx = rand() % remain.size();
	int s_r = remain[idx].first;
	int s_c = remain[idx].second;
	remain.erase(remain.begin() + idx);
	if (remain.size() == 0)
		return;
	int t_x = s_r;
	int t_y = s_c;
	while (1)
	{
		if (t_x == f_r && t_y == f_c)
			break;
		int next = rand() % 4;
		int nx = t_x + dx[next];
		int ny = t_y + dy[next];
		if (valide(nx, ny))
		{
			dir[t_x][t_y] = next;
			t_x = nx;
			t_y = ny;
		}
	}
	/*
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			wcout << dir[i][j] << " "; //<<" ";
		}
		cout << '\n';
	}
	cout << s_r << " " << s_c << endl;
	*/
	while (1)
	{
		if (s_r == f_r && s_c == f_c)
			break;
		int a = s_r;
		int b = s_c;
		for (int i = 0; i <= abs(dx[dir[a][b]]); i++) // x 축
		{
			if (dx[dir[a][b]] < 0) //음수라면
			{
				maze[s_r - i][s_c] = '*';
			}
			else
			{
				maze[s_r + i][s_c] = '*';
			}
		}
		for (int i = 0; i <= abs(dy[dir[a][b]]); i++) // x 축
		{
			if (dy[dir[a][b]] < 0) //음수라면
			{
				maze[s_r][s_c - i] = '*';
			}
			else
			{
				maze[s_r][s_c + i] = '*';
			}
		}
		s_r += dx[dir[a][b]];
		s_c += dy[dir[a][b]];
		if (remain.size() == 0)
			return;
		for (int i = 0; i < remain.size(); i++)
		{
			if (remain[i].first == s_r && remain[i].second == s_c)
			{
				remain.erase(remain.begin() + i);
			}
		}
		if (remain.size() == 0)
			return;
	}
}
int main()
{
	wcout.imbue(locale("")); //지역 설정
	wcin.imbue(locale(""));
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			maze[i][j] = L'■';
			if (i % 2 == 1 && j % 2 == 1)
			{
				remain.push_back({i, j});
			}
		}
	}
	while (!remain.empty())
	{
		wilson_algorithm();
	}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			wcout << maze[i][j];
		}
		cout << '\n';
	}
	return 0;
}