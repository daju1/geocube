#include "stdafx.h"
#include "LocalExtremumsFiltering.h"

void GetLocalExtremums(vector<double>& in, vector<size_t> * vi_lock_min, vector<size_t> * vi_lock_max)
{
	if (vi_lock_min) vi_lock_min->clear();
	if (vi_lock_max) vi_lock_max->clear();

	for (size_t i = 1; i < in.size()-1; i++)
	{
		if (vi_lock_max && in[i] > in[i-1] && in[i] > in[i+1])
			vi_lock_max->push_back(i);
		if (vi_lock_min && in[i] < in[i-1] && in[i] < in[i+1])
			vi_lock_min->push_back(i);
	}
}

void GetLocalExtremums(vector<double>& in, vector<size_t>& vi_in,
					   vector<size_t> * vi_lock_min, vector<size_t> * vi_lock_max)
{
	if (vi_lock_min) vi_lock_min->clear();
	if (vi_lock_max) vi_lock_max->clear();

	for (size_t i = 1; i < vi_in.size()-1; i++)
	{
		if (vi_lock_max && in[vi_in[i]] > in[vi_in[i-1]] && in[vi_in[i]] > in[vi_in[i+1]])
			vi_lock_max->push_back(vi_in[i]);
		if (vi_lock_min && in[vi_in[i]] < in[vi_in[i-1]] && in[vi_in[i]] < in[vi_in[i+1]])
			vi_lock_min->push_back(vi_in[i]);
	}
}

void Filtration(vector<double>& in, 
				vector<vector<size_t> >& vvi_lock_min, 
				vector<vector<size_t> >& vvi_lock_max)
{
	vvi_lock_min.resize(1),	vvi_lock_max.resize(1);
	GetLocalExtremums(in, &vvi_lock_min[0], &vvi_lock_max[0]);
	//for (size_t j = 0; j < nMaxLevels; j++)
	size_t j = 0;
	while (true)
	{
		if (vvi_lock_max[j].size() > 2 &&  vvi_lock_min[j].size() > 2)
		{
			vvi_lock_min.push_back(vector<size_t>());
			vvi_lock_max.push_back(vector<size_t>());
			GetLocalExtremums(in, vvi_lock_max[j], NULL, &vvi_lock_max[j+1]);
			GetLocalExtremums(in, vvi_lock_min[j], &vvi_lock_min[j+1], NULL);
		}
		else
			break;

		bool to_break = 
			vvi_lock_max[j+1].size() == 0 ||
			vvi_lock_min[j+1].size() == 0;

		if (to_break)
		{
			break;
		}
		j++;
	}
}
// Вычисление локальных экстремумов, как точек перегиба
// точки перегиба - это точки локальных экстремумов во второй производной
// Точка перегиба, которая соответствует локальному минимуму,
// определяется как локальный максимум второй производной
// Точка перегиба, которая соответствует локальному максимуму,
// определяется как локальный минимум второй производной
void GetLocalExtremums(bool allow_sd_limit, double quantil, 
#if SOURCE_COORDINATES_3D
				vector<double>& X, 
				vector<double>& Y, 
#else
					   vector<double>& t, 
#endif
					   vector<double>& in, vector<size_t>& vi_in,
					   vector<size_t> * vi_lock_min, vector<size_t> * vi_lock_max)
{
//printf("GetLocalExtremums\n");		
	//bool allow_sd_limit = true;
	//bool allow_sd_limit = false;
	//double quantil = 0.40;
	// квантиль отбора точек перегиба по их крутизне
	// квантиль отбора локальных экстремумов второй производной
	// если квантиль отбора равен 0,5 то мы отбираем все определяемые точки перегиба
	// чем меньше квантиль отбора тем больше точек перегиба мы отфильтровываем,
	// тем самым мы оставляем лишь блее крутые точки перегиба

	if (vi_in.size() > 2)
	{
	// строим вторую производную
		vector<double> sd;
		sd.resize(vi_in.size());
		size_t i;
		for (i = 1; i < vi_in.size()-1; i++)
		{
#if SOURCE_COORDINATES_3D
			sd[i] = 
				( 
				(in[vi_in[i+1]] - in[vi_in[i]])
				/
				//(t [vi_in[i+1]] - t [vi_in[i]])
				sqrt( pow(X[vi_in[i+1]] - X [vi_in[i]],2.0) +  pow(X[vi_in[i+1]] - X [vi_in[i]],2.0))
				-
				(in[vi_in[i]] - in[vi_in[i-1]])
				/
				//(t [vi_in[i]] - t [vi_in[i-1]])
				sqrt( pow(X[vi_in[i]] - X [vi_in[i-1]],2.0) +  pow(X[vi_in[i]] - X [vi_in[i-1]],2.0))
				)
				/
				//(t [vi_in[i+1]] - t [vi_in[i-1]]);
				sqrt( pow(X[vi_in[i+1]] - X [vi_in[i-1]],2.0) +  pow(X[vi_in[i+1]] - X [vi_in[i-1]],2.0));
#else
			sd[i] = 
				( 
				(in[vi_in[i+1]] - in[vi_in[i]])
				/
				(t [vi_in[i+1]] - t [vi_in[i]])
				-
				(in[vi_in[i]] - in[vi_in[i-1]])
				/
				(t [vi_in[i]] - t [vi_in[i-1]])
				)
				/
				(t [vi_in[i+1]] - t [vi_in[i-1]]);
#endif

		}
#if SOURCE_COORDINATES_3D
		// вторую производню в начале и в конце вычисляем путём зеркального отображения
		sd[0] = (in[vi_in[1]] - in[vi_in[0]]) / 
			(pow(X [vi_in[1]] - X [vi_in[0]], 2.0) + pow(Y [vi_in[1]] - Y [vi_in[0]], 2.0));
		size_t end = vi_in.size()-1;
		sd[end] = (in[vi_in[end-1]] - in[vi_in[end]]) / 
			(pow(X [vi_in[end]] - X [vi_in[end-1]], 2.0) + pow(Y [vi_in[end]] - Y [vi_in[end-1]], 2.0));
#else
		// вторую производню в начале и в конце вычисляем путём зеркального отображения
		sd[0] = (in[vi_in[1]] - in[vi_in[0]]) / pow(t [vi_in[1]] - t [vi_in[0]], 2.0);
		size_t end = vi_in.size()-1;
		sd[end] = (in[vi_in[end-1]] - in[vi_in[end]]) / pow(t [vi_in[end]] - t [vi_in[end-1]], 2.0);
#endif
		// сортирем вторую производную
		vector<double> sorted_sd = sd;
		sort(sorted_sd.begin(), sorted_sd.end());
		printf("sorted_sd.size(%u), sd.size(%u)\n", sorted_sd.size(), sd.size());

		if (vi_lock_min) vi_lock_min->clear();
		if (vi_lock_max) vi_lock_max->clear();


		bool use_sd_limit = sorted_sd.size() > 5;
		if (use_sd_limit && allow_sd_limit)
		{
			size_t len = sorted_sd.size();
			size_t dlen = size_t(quantil*len);

			double pos_sd_limit = sorted_sd[len-dlen];
			double neg_sd_limit = sorted_sd[dlen > 0 ? dlen-1 : 0];
			i = 0; 
			{
				if (vi_lock_min && sd[i] > sd[i+1] && sd[i] >= pos_sd_limit)
					vi_lock_min->push_back(vi_in[i]);

				if (vi_lock_max && sd[i] < sd[i+1] && sd[i] <= neg_sd_limit)
					vi_lock_max->push_back(vi_in[i]);
			}
			for (size_t i = 1; i < vi_in.size()-1; i++)
			{
				if (vi_lock_min && sd[i] > sd[i-1] && sd[i] > sd[i+1] && sd[i] >= pos_sd_limit)
					vi_lock_min->push_back(vi_in[i]);

				if (vi_lock_max && sd[i] < sd[i-1] && sd[i] < sd[i+1] && sd[i] <= neg_sd_limit)
					vi_lock_max->push_back(vi_in[i]);
			}
			i = vi_in.size()-1; 
			{
				if (vi_lock_min && sd[i] > sd[i-1] && sd[i] >= pos_sd_limit)
					vi_lock_min->push_back(vi_in[i]);

				if (vi_lock_max && sd[i] < sd[i-1] && sd[i] <= neg_sd_limit)
					vi_lock_max->push_back(vi_in[i]);
			}
		}
		else
		{
			i = 0; 
			{
				if (vi_lock_min && sd[i] > sd[i+1])
					vi_lock_min->push_back(vi_in[i]);

				if (vi_lock_max && sd[i] < sd[i+1])
					vi_lock_max->push_back(vi_in[i]);
			}
			for (size_t i = 1; i < vi_in.size()-1; i++)
			{
				if (vi_lock_min && sd[i] > sd[i-1] && sd[i] > sd[i+1])
					vi_lock_min->push_back(vi_in[i]);

				if (vi_lock_max && sd[i] < sd[i-1] && sd[i] < sd[i+1])
					vi_lock_max->push_back(vi_in[i]);
			}
			i = vi_in.size()-1; 
			{
				if (vi_lock_min && sd[i] > sd[i-1])
					vi_lock_min->push_back(vi_in[i]);

				if (vi_lock_max && sd[i] < sd[i-1])
					vi_lock_max->push_back(vi_in[i]);
			}
		}
	}
}

void Filtration(bool allow_sd_limit, double quantil, 
#if SOURCE_COORDINATES_3D
				vector<double>& X, 
				vector<double>& Y, 
#else
				vector<double>& t, 
#endif
				vector<double>& in, 
				vector<vector<size_t> >& vvi_lock_min, 
				vector<vector<size_t> >& vvi_lock_max)
{
//printf("Filtration\n");
	vvi_lock_min.resize(1),	vvi_lock_max.resize(1);
	GetLocalExtremums(in, &vvi_lock_min[0], &vvi_lock_max[0]);

	//for (size_t j = 0; j < nMaxLevels; j++)
	size_t j = 0;
	while (true)
	{
//printf("Filtration t.size(%u), in.size(%u), vvi_lock_max[%u].size(%u), vvi_lock_min[%u].size(%u) \n", t.size(), in.size(), j, vvi_lock_max[j].size(), j, vvi_lock_min[j].size());
		if (vvi_lock_max[j].size() > 2 &&  vvi_lock_min[j].size() > 2)
		{
			vvi_lock_min.push_back(vector<size_t>());
			vvi_lock_max.push_back(vector<size_t>());

#if SOURCE_COORDINATES_3D
			GetLocalExtremums(allow_sd_limit, quantil, X, Y, in, vvi_lock_max[j], NULL, &vvi_lock_max[j+1]);
			GetLocalExtremums(allow_sd_limit, quantil, X, Y, in, vvi_lock_min[j], &vvi_lock_min[j+1], NULL);
#else
			GetLocalExtremums(allow_sd_limit, quantil, t, in, vvi_lock_max[j], NULL, &vvi_lock_max[j+1]);
			GetLocalExtremums(allow_sd_limit, quantil, t, in, vvi_lock_min[j], &vvi_lock_min[j+1], NULL);
#endif
		}
		else
			break;

		bool to_break = 
			vvi_lock_max[j+1].size() == 0 ||
			vvi_lock_min[j+1].size() == 0;

		if (to_break)
		{
			break;
		}
		j++;
	}
}