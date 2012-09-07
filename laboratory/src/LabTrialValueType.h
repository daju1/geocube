#pragma once

class LabLayer;
class LabParameters;

struct LabTrialValueType;


struct CompressionValueType
{
	LabTrialValueType * m_LabTrialValueType;

	CompressionLabTrial::value_type vt_CompressionLabTrial;
	int n_compression_value_type;
	bool every_compression_experiment;
	CompressionLabTrialResults::value_type_0 vt_CompressionLabTrialResults_0;
#if USE_COMPR_PO_OTN_DEF	
	CompressionLabTrialResults::value_type_1 vt_CompressionLabTrialResults_1;
#endif
	CompressionLabTrialResults::value_type_2 vt_CompressionLabTrialResults_2;
	CompressionLabTrialResults::value_type_3 vt_CompressionLabTrialResults_3;
	CompressionLabTrial::type com_type;
	int n_compression_pressures;
	int i_compression_pressure;
	double compression_pressure;

	bool compression_zamachivanie;

	// конструктор
	CompressionValueType()
	{	
		this->clear();
		m_LabTrialValueType = NULL;
	}
	void SetParent(LabTrialValueType * p_LabTrialValueType)
	{	
		m_LabTrialValueType = p_LabTrialValueType;
	}
	void clear();
	void Printf();
	void EnumValueTypes(LabLayer * lab_layer, LabParameters * lab_params, vector<fmtstr> * text, vector<LabData> * labdata, bool (LabLayer::*CallBack)(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata));
	const char * GetValueTypeString();
	// Знак для коэффициента надёжности
	int GetSignForReliabilityK();
	int GetI();
	bool IsChecked(LabLayer * lab_layer, LabParameters * lab_params);
	int IsEvery();
};
struct CompressionValueType_3
{
	LabTrialValueType * m_LabTrialValueType;

	CompressionLabTrial::type com_type;

	CompressionValueType vt_Compression_nature;
	CompressionValueType vt_Compression_task;
	CompressionValueType vt_Compression_shrinkage;
	//tri
	CompressionLabTrialResults3::value_type vt_CompressionLabTrialResults3;

	// конструктор
	CompressionValueType_3()
	{	
		this->clear();
		m_LabTrialValueType = NULL;
	}
	void SetParent(LabTrialValueType * p_LabTrialValueType);
	void clear();
	void Printf();
	void EnumValueTypes(LabLayer * lab_layer, LabParameters * lab_params, vector<fmtstr> * text, vector<LabData> * labdata, bool (LabLayer::*CallBack)(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata));
	// Знак для коэффициента надёжности
	int GetSignForReliabilityK();
	int GetI();
	const char * GetValueTypeString();
	bool IsChecked(LabLayer * lab_layer, LabParameters * lab_params);
	int IsEvery();
	int Get_n_compression_value_type();
};
// тип данных для определения вида характеристики грунта
struct LabTrialValueType
{
	enum common_types
	{
		none = 0,
		depth
	};
	LabLayer * m_lablayer;
	// определяем признак испытания
	LabTrial::indication m_indication;
	// исходный или вычисленный
	bool is_result;
	// если массив, надо мспользовать индекс
#if USE_LAB_TRIALS_VECTOR
	long m_id_vyprob;
#endif

	//bool use_index;

	LabTrialValueType::common_types vt_common_type;
	// из ниже приведенного списка определяем только тот тип данных, 
	// который соответствует заданному признаку испытаний
	PhysicalLabTrial::value_type vt_PhysicalLabTrial;
	PhysicalLabTrialResults::value_type vt_PhysicalLabTrialResults;

	ChemicalLabTrial::value_type vt_ChemicalLabTrial;
	ChemicalLabTrialResults::value_type vt_ChemicalLabTrialResults;

	FractionsLabTrial::value_type vt_FractionsLabTrial;
	FractionsLabTrialResults::value_type vt_FractionsLabTrialResults;
	int n_fractions;
	int i_fraction;
#if !USE_FRACTION_DIAMETERS_INTERVAL
	double fraction_diameter;
#endif
	double fraction_diameter_high;
	double fraction_diameter_low;

	CompressionValueType vt_Compression;
	CompressionValueType_3 vt_Compression_3;
	int IsEvery();// return -1, if every is not defined, 0 if every = false, 1 if every = true

	CutLabTrial::value_type vt_CutLabTrial;
	CutLabTrialResults::value_type vt_CutLabTrialResults;
	bool every_cut_experiment;
	CutLabTrial::type cut_type;
	int n_cut_pressures;
	int i_cut_pressure;
	double cut_pressure;

	PressingLabTrial::value_type vt_PressingLabTrial;
	PressingLabTrialResults::value_type vt_PressingLabTrialResults;

	FiltrationLabTrial::value_type vt_FiltrationLabTrial;
	FiltrationLabTrialResults::value_type vt_FiltrationLabTrialResults;
	FiltrationLabTrial::type filtr_type;

	// конструктор
	LabTrialValueType();
	void clear();
	void Printf();
	// Знак для коэффициента надёжности
	int GetSignForReliabilityK();
	int GetI();
#if 0
	int GetValueTypeInt();
#endif
	const char * GetValueTypeString();
	void EnumValueTypes(LabLayer * lab_layer, vector<fmtstr> * text, vector<LabData> * labdata, bool (LabLayer::*CallBack)(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata));
	bool IsChecked(LabLayer * lab_layer);

	void Init(const LabTrialValueType & ob);
	LabTrialValueType(const LabTrialValueType & bp)
	{
		this->Init(bp);
	}
	LabTrialValueType& operator=(const LabTrialValueType& bp)
	{
		if (this == &bp)
		{
			return *this;
		}

		this->Init(bp);

		return *this;
	}
};
bool inline operator<(const CompressionValueType& ob1, const CompressionValueType& ob2)
{
	if (ob1.m_LabTrialValueType && ob2.m_LabTrialValueType)
	{
		if (ob1.m_LabTrialValueType->is_result)
		{
			if (ob1.every_compression_experiment == ob2.every_compression_experiment)
			{
				if (ob1.n_compression_value_type == ob2.n_compression_value_type)
				{
					switch(ob1.n_compression_value_type)
					{
					case 0:
						return (ob1.vt_CompressionLabTrialResults_0 < ob2.vt_CompressionLabTrialResults_0);
						break;
#if USE_COMPR_PO_OTN_DEF	
					case 1:
						return (ob1.vt_CompressionLabTrialResults_1 < ob2.vt_CompressionLabTrialResults_1);
						break;
#endif
					case 2:
						return (ob1.vt_CompressionLabTrialResults_2 < ob2.vt_CompressionLabTrialResults_2);
						break;
					case 3:
						return (ob1.vt_CompressionLabTrialResults_3 < ob2.vt_CompressionLabTrialResults_3);
						break;
					default:
						return false;
					}
				}
				else
				{
					return ob1.n_compression_value_type < ob2.n_compression_value_type;
				}
			}
			else
			{
				return (ob1.every_compression_experiment < ob2.every_compression_experiment);
			}
		}
		else
		{
			return (ob1.vt_CompressionLabTrial < ob2.vt_CompressionLabTrial);
		}
	}
	return false;
}

bool inline operator==(const CompressionValueType& ob1, const CompressionValueType& ob2)
{
	if (ob1.m_LabTrialValueType && ob2.m_LabTrialValueType)
	{
		if (ob1.m_LabTrialValueType->is_result)
		{
			if (ob1.every_compression_experiment == ob2.every_compression_experiment)
			{
				if (ob1.n_compression_value_type == ob2.n_compression_value_type)
				{
					switch(ob1.n_compression_value_type)
					{
					case 0:
						return (ob1.vt_CompressionLabTrialResults_0 == ob2.vt_CompressionLabTrialResults_0);
						break;
#if USE_COMPR_PO_OTN_DEF	
					case 1:
						return (ob1.vt_CompressionLabTrialResults_1 == ob2.vt_CompressionLabTrialResults_1);
						break;
#endif
					case 2:
						return (ob1.vt_CompressionLabTrialResults_2 == ob2.vt_CompressionLabTrialResults_2);
						break;
					case 3:
						return (ob1.vt_CompressionLabTrialResults_3 == ob2.vt_CompressionLabTrialResults_3);
						break;
					default:
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return (ob1.vt_CompressionLabTrial == ob2.vt_CompressionLabTrial);
		}
	}
	return false;
}

bool inline operator<(const CompressionValueType_3& ob1, const CompressionValueType_3& ob2)
{
	if (ob1.m_LabTrialValueType && ob2.m_LabTrialValueType)
	{
		if (ob1.com_type == ob2.com_type)
		{
			switch(ob1.com_type)
			{
			case CompressionLabTrial::type::nature_condition:
				return (ob1.vt_Compression_nature < ob2.vt_Compression_nature);
			case CompressionLabTrial::type::task_condition:
				return (ob1.vt_Compression_task < ob2.vt_Compression_task);
			case CompressionLabTrial::type::shrinkage:
				return (ob1.vt_Compression_shrinkage < ob2.vt_Compression_shrinkage);
			case CompressionLabTrial::type::tri:
				return (ob1.vt_CompressionLabTrialResults3 < ob2.vt_CompressionLabTrialResults3);
			default:
				return false;
			}
		}
		else
		{
			return ob1.com_type < ob2.com_type;
		}
	}
	return false;
}

bool inline operator==(const CompressionValueType_3& ob1, const CompressionValueType_3& ob2)
{
	if (ob1.m_LabTrialValueType && ob2.m_LabTrialValueType)
	{
		if (ob1.com_type == ob2.com_type)
		{
			switch(ob1.com_type)
			{
			case CompressionLabTrial::type::nature_condition:
				return (ob1.vt_Compression_nature == ob2.vt_Compression_nature);
			case CompressionLabTrial::type::task_condition:
				return (ob1.vt_Compression_task == ob2.vt_Compression_task);
			case CompressionLabTrial::type::shrinkage:
				return (ob1.vt_Compression_shrinkage == ob2.vt_Compression_shrinkage);
			case CompressionLabTrial::type::tri:
				return (ob1.vt_CompressionLabTrialResults3 == ob2.vt_CompressionLabTrialResults3);
			default:
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool inline operator<(const LabTrialValueType& ob1, const LabTrialValueType& ob2)
{
	if (ob1.is_result == ob2.is_result)
	{
		if (ob1.m_indication == ob2.m_indication)
		{
			switch(ob1.m_indication)
			{
			case LabTrial::indication::physical:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_PhysicalLabTrialResults < ob2.vt_PhysicalLabTrialResults);
					}
					else
					{
						return (ob1.vt_PhysicalLabTrial < ob2.vt_PhysicalLabTrial);
					}
				}
				break;
			case LabTrial::indication::chemical:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_ChemicalLabTrialResults < ob2.vt_ChemicalLabTrialResults);
					}
					else
					{
						return (ob1.vt_ChemicalLabTrial < ob2.vt_ChemicalLabTrial);
					}
				}
				break;
			case LabTrial::indication::fractions:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_FractionsLabTrialResults < ob2.vt_FractionsLabTrialResults);
					}
					else
					{
						return (ob1.vt_FractionsLabTrial < ob2.vt_FractionsLabTrial);
					}
				}
				break;	
			case LabTrial::indication::compression_3:
				{
					return ob1.vt_Compression_3 < ob2.vt_Compression_3;
				}
				break;
			case LabTrial::indication::compression_nature_condition_absolute_deformation:
			case LabTrial::indication::compression_task_condition_absolute_deformation:
			case LabTrial::indication::compression_shrinkage_absolute_deformation:
				{
					return ob1.vt_Compression < ob2.vt_Compression;
				}
				break;
			case LabTrial::indication::cut_resistance_nature_condition:
			case LabTrial::indication::cut_resistance_task_condition:
				{
					if (ob1.cut_type == ob2.cut_type)
					{
						if (ob1.is_result)
						{
							if (ob1.every_cut_experiment == ob2.every_cut_experiment)
							{
								return (ob1.vt_CutLabTrialResults < ob2.vt_CutLabTrialResults);
							}
							else
							{
								return ob1.every_cut_experiment < ob2.every_cut_experiment;
							}
						}
						else
						{							
							if (ob1.vt_CutLabTrial == ob2.vt_CutLabTrial)
							{
								switch (ob1.vt_CutLabTrial)
								{
								case CutLabTrial::value_type::vt_pressure:
								case CutLabTrial::value_type::vt_cut_resistance:
									{
										return (ob1.i_cut_pressure < ob2.i_cut_pressure);
									}
									break;
								default:
									{
										return (ob1.vt_CutLabTrial < ob2.vt_CutLabTrial);
									}
									break;
								}
							}
							else
							{
								return (ob1.vt_CutLabTrial < ob2.vt_CutLabTrial);
							}
						}
					}
					else
					{
						return ob1.cut_type < ob2.cut_type;
					}
				}
				break;
			case LabTrial::indication::pressing:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_PressingLabTrialResults < ob2.vt_PressingLabTrialResults);
					}
					else
					{
						return (ob1.vt_PressingLabTrial < ob2.vt_PressingLabTrial);
					}
				}
				break;	
			case LabTrial::indication::filtration_coefficient_with_pressures:
			case LabTrial::indication::filtration_coefficient_with_densities:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_FiltrationLabTrialResults < ob2.vt_FiltrationLabTrialResults);
					}
					else
					{
						return (ob1.vt_FiltrationLabTrial < ob2.vt_FiltrationLabTrial);
					}
				}
				break;
			default:
				return false;
			}

		}
		else
		{
			return ob1.m_indication < ob2.m_indication;
		}
	}
	else
	{
		return ob1.is_result < ob2.is_result;
	}
}
bool inline operator==(const LabTrialValueType& ob1, const LabTrialValueType& ob2)
{
	if (ob1.is_result == ob2.is_result)
	{
		if (ob1.m_indication == ob2.m_indication)
		{
			switch(ob1.m_indication)
			{
			case LabTrial::indication::physical:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_PhysicalLabTrialResults == ob2.vt_PhysicalLabTrialResults);
					}
					else
					{
						return (ob1.vt_PhysicalLabTrial == ob2.vt_PhysicalLabTrial);
					}
				}
				break;
			case LabTrial::indication::chemical:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_ChemicalLabTrialResults == ob2.vt_ChemicalLabTrialResults);
					}
					else
					{
						return (ob1.vt_ChemicalLabTrial == ob2.vt_ChemicalLabTrial);
					}
				}
				break;
			case LabTrial::indication::fractions:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_FractionsLabTrialResults == ob2.vt_FractionsLabTrialResults);
					}
					else
					{
						return (ob1.vt_FractionsLabTrial == ob2.vt_FractionsLabTrial);
					}
				}
				break;	
			case LabTrial::indication::compression_3:
				{
					return ob1.vt_Compression_3 == ob2.vt_Compression_3;
				}
				break;
			case LabTrial::indication::compression_nature_condition_absolute_deformation:
			case LabTrial::indication::compression_task_condition_absolute_deformation:
			case LabTrial::indication::compression_shrinkage_absolute_deformation:
				{
					return ob1.vt_Compression == ob2.vt_Compression;
				}
				break;
			case LabTrial::indication::cut_resistance_nature_condition:
			case LabTrial::indication::cut_resistance_task_condition:
				{
					if (ob1.cut_type == ob2.cut_type)
					{
						if (ob1.is_result)
						{
							if (ob1.every_cut_experiment == ob2.every_cut_experiment)
							{
								return (ob1.vt_CutLabTrialResults == ob2.vt_CutLabTrialResults);
							}
							else
							{
								return false;//return ob1.every_cut_experiment == ob2.every_cut_experiment;
							}
						}
						else
						{							
							if (ob1.vt_CutLabTrial == ob2.vt_CutLabTrial)
							{
								switch (ob1.vt_CutLabTrial)
								{
								case CutLabTrial::value_type::vt_pressure:
								case CutLabTrial::value_type::vt_cut_resistance:
									{
										return (ob1.i_cut_pressure == ob2.i_cut_pressure);
									}
									break;
								default:
									{
										return true;//return (ob1.vt_CutLabTrial == ob2.vt_CutLabTrial);
									}
									break;
								}
							}
							else
							{
								return false; //return (ob1.vt_CutLabTrial == ob2.vt_CutLabTrial);
							}
						}
					}
					else
					{
						return false;//return ob1.cut_type == ob2.cut_type;
					}
				}
				break;
			case LabTrial::indication::pressing:
				{
					if (ob1.is_result)
					{
						return (ob1.vt_PressingLabTrialResults == ob2.vt_PressingLabTrialResults);
					}
					else
					{
						return (ob1.vt_PressingLabTrial == ob2.vt_PressingLabTrial);
					}
				}
				break;	
			case LabTrial::indication::filtration_coefficient_with_pressures:
			case LabTrial::indication::filtration_coefficient_with_densities:
				{
					/*switch(m_indication)			
					{	
						case LabTrial::indication::filtration_coefficient_with_pressures:
							//this->filtr_type = FiltrationLabTrial::type::with_pressures;
							break;
						case LabTrial::indication::filtration_coefficient_with_densities:
							//this->filtr_type = FiltrationLabTrial::type::with_densities;
							break;
					}*/
					if (ob1.is_result)
					{
						return (ob1.vt_FiltrationLabTrialResults == ob2.vt_FiltrationLabTrialResults);
					}
					else
					{
						return (ob1.vt_FiltrationLabTrial == ob2.vt_FiltrationLabTrial);
					}
				}
				break;
			default:
				return false;
			}

		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return false;
}
