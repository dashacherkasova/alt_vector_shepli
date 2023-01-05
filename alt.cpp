#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

struct double_shepli {
	int chislitel = 0;
	int znamenatel = 0;
};

int nod(int a,int b) {
	while (a && b)
		if (a > b) a %= b;
		else b %= a;
	return a + b;
}

int coalition_power(vector <int>& coalition, vector <int>& gamer_power)
{
	int result = 0;
	for (int i = 0;i < size(coalition) - 1; i++)
	{
		result += gamer_power[coalition[i]];
	}
	return result;
}

bool is_decisive(vector <int>& coalition, int gamer, vector <int>& gamer_power, int rule)
{
	int result = coalition_power(coalition, gamer_power);
	if (result < rule)
	{
		result += gamer_power[gamer];
		if (result >= rule) {
			return 1;
		}
	}
	return 0;
}

int fact(int n)
{
	if (n == 0)
	{
		return 1;
	}
	return fact(n - 1) * n;
}

void parts_vector(int n, vector <int>& coalition,vector <double_shepli>& rez_shepli)
{
	int fact1 = fact(size(coalition) - 1);
	int fact2 = fact(n - size(coalition));
	int fact3 = fact(n);
	rez_shepli[coalition[size(coalition) - 1]].chislitel += fact1 * fact2;
	rez_shepli[coalition[size(coalition) - 1]].znamenatel=fact3;
	return;
}

void vector_shepli(vector <int>& gamer_power, int rule)
{
	vector <bool> components;
	vector <double_shepli> rez_shepli;
	for (int i = 0;i < size(gamer_power);i++) {
		components.push_back(0);
		rez_shepli.push_back({ 0,0 });
	}
	int two = pow(2, size(gamer_power));
	for (int i = 0;i < two;i++) {
		int count = size(gamer_power)-1;
		int i_copy = i;
		while (i_copy) {
			components[count] = i_copy % 2;
			i_copy=i_copy/2;
			--count;
		}
		vector <int> coalition;
		for (int j = 0;j < size(gamer_power);j++) {
			if (components[j]) { coalition.push_back(j); }
		}
		for (int j = 0;j < size(gamer_power);j++) {
			if (!components[j]) { 
				coalition.push_back(j);
				if (is_decisive(coalition, j, gamer_power, rule)) { parts_vector(size(gamer_power), coalition,rez_shepli); }
				coalition.pop_back();
			}
		}
		for (int j = 0;j < size(components);j++) {
			components[j] = 0;
		}

	}
	for (int i = 0;i < size(rez_shepli);i++) {
		cout << "Для игрока " << i+1 << " компонента вектора Шепли равна " << (rez_shepli[i].chislitel)/nod(rez_shepli[i].chislitel, rez_shepli[i].znamenatel)
			<<"/"<< (rez_shepli[i].znamenatel) / nod(rez_shepli[i].chislitel, rez_shepli[i].znamenatel) << endl;
	}
}

int main()
{
	setlocale(0,"");
	cout << "Дорогие участники альтернативного экзамена" << endl;
	cout << "Пожалуйста, если вы найдете примеры задач, на которых программа выдает неверный ответ" << endl;
	cout << "Сообщите нам в личные сообщения, чтобы мы могли доработать эти моменты" << endl;
	cout << "Благодарим!" << endl;
	cout << endl;
	cout << "Программа находит компоненты так называемого вектора Шепли для заданной простой кооперативной игры" << endl;
	cout << "Компонента вектора Шепли для определенного игрока интерпретируется как выигрыш, который должен получить игрок, в соответствии с его влиянием в данной игре" << endl;
	cout << "(Если подразумевать выигрыш равным единице (ста процентам))" << endl;
	cout << "Вам необходимо ввести количество игроков и силу каждого игрока, то есть сколько голосов данный игрок имеет в рамках данной игры" << endl;
	cout << endl;
	cout << "Введите количество игроков" << endl;
	int count;
	bool flag = 1;
	while (flag)
	{
		cin >> count;
		if (!cin)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Ошибка ввода. попробуйте еще раз" << endl;
		}
		else {
			flag = 0;
		}
	}
	cout << "Вы ввели: " << count << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Введите количество голосов, имеющееся у каждого игрока:" << endl;
	vector <int> gamer_power;
	int sum_power = 0;
	for (int i = 0;i < count;i++)
	{
		cout << "Для игрока №"<< i+1<<endl;
		int power;
		flag = 1;
		while (flag)
		{
			cin >> power;
			if (!cin)
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Ошибка ввода. попробуйте еще раз" << endl;
			}
			else {
				flag = 0;
			}
		}
		cout << "Вы ввели: " << power << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		sum_power += power;
		gamer_power.push_back(power);
	}
	cout << "Введите, какое количество голосов необходимо набрать, чтобы решение было принято. Число не должно превосходить суммарного количества голосов всех участников: " <<sum_power << endl;
	int rule;
	flag = 1;
	while (flag)
	{
		cin >> rule;
		if (!cin)
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Ошибка ввода. попробуйте еще раз" << endl;
		}
		else {
			flag = 0;
		}
	}
	cout << "Вы ввели: " << rule << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	vector_shepli(gamer_power, rule);
	getchar();
	return 0;
}