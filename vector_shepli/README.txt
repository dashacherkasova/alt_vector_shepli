
	Комментарий: программа работает для произвольного числа n. В конце приводится результат работы программы, когда на вход подаются данные из примера 7.
Работа программы основывается на правиле: В простой кооперативной игре N,V, i -я компонента ее вектора Шепли 〖Sh〗_i (V)   определяется формулой: 〖Sh〗_i (V)=∑_S▒(k-1)!(n-k)!/n!, где суммирование производится по тем коалициям S  N, в которых игрок i является решающим, и k=|S|.
Примечание: массив coalition содержит игроков данной коалиции. Массив gamer_power содержит в себе, сколько голосов есть у игрока под номером i. Число rule – правило принятия решения (необходимое количество голосов, которое нужно набрать, чтобы решение было принято.
Функция is_decisive определяет, является ли игрок решающим: если коалиция до вступления в нее игрока уже была выигрывающей или после вступления игрока все еще осталась проигрывающей – игрой не решающий. Иначе – решающий.
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
Функция coalition_power считает, сколько голосов набирается в сумме у участников коалиции до вступления в нее последнего игрока. Нужна для реализации предыдущей функции.
int coalition_power(vector <int>& coalition, vector <int>& gamer_power)
{
	int result = 0;
	for (int i = 0;i < size(coalition) - 1; i++)
	{
		result += gamer_power[coalition[i]];
	}
	return result;
}
	Вспомогательная функция fact считает факториал числа n. 
int fact(int n)
{
	if (n == 0)
	{
		return 1;
	}
	return fact(n - 1) * n;
}
Функция parts_vector считает компоненты вектора Шепли согласно формуле. Замечание: так как тип double теряет «хвосты» дробей, приходится использовать отдельную переменную под числитель и под знаменатель дроби (структура double_shepli).
void parts_vector(int n, vector <int>& coalition,vector <double_shepli>& rez_shepli)
{
	int fact1 = fact(size(coalition) - 1);
	int fact2 = fact(n - size(coalition));
	int fact3 = fact(n);
	rez_shepli[coalition[size(coalition) - 1]].chislitel +=fact1 * fact2;
	rez_shepli[coalition[size(coalition) - 1]].znamenatel=fact3;
	return;
}
struct double_shepli {
	int chislitel = 0;
	int znamenatel = 0;
};
Вспомогательная функция nod помогает сократить числитель и знаменатель дроби.
int nod(int a,int b) {
	while (a && b)
		if (a > b) a %= b;
		else b %= a;
	return a + b;
}
Функция vector_shepli составляет различные коалиции через двоичное число (аналогично тому, что указано в Замечании (3)) и затем проверяет каждого игрока, не входящего ранее в данную коалицию, является ли он в ней решающим после присоединения или нет. Если он является решающим, то, согласно формуле вектора Шепли, мы добавляем вероятность появления данной коалиции к компоненте вектора Шепли для этого игрока.
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
	}}
