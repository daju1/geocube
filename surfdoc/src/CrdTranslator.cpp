#include "stdafx.h"
#include "CrdTranslator.h"

bool InitTranslator(CrdTranslator& translator, SSaveProfData &sprData)
{
	switch(sprData.export_coordinate_type)
	{
		case SAVE_PROFILE_3D_XYZ:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xyz;
			}
			break;
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				/*translator.a = a;
				translator.b = b;
				translator.c = c;
				translator.d = d;

				translator.minX = minX;
				translator.minY = minY;
				translator.minZ = minZ;

				translator.maxX = maxX;
				translator.maxY = maxY;
				translator.maxZ = maxZ;

				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::along_plane;*/
				return false;
			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::yz;
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xz;
			}
			break;
		case SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xy;
			}
			break;
		case SAVE_PROFILE_AUTO_SELECT_PROJECTION:
			{
				// определяем преимущественное направление вектора нормали к плоскости
/*				if (fabs(c) >= fabs(a) && fabs(c) >= fabs(b))
				{
					// доминирует направление вдоль оси Z
					translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xy;
				}
				else if (fabs(a) >= fabs(b) && fabs(a) >= fabs(c))
				{
					// доминирует направление вдоль оси X
					translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::yz;
				}
				else if (fabs(b) >= fabs(a) && fabs(b) >= fabs(c))
				{
					// доминирует направление вдоль оси Y
					translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xz;
				}*/
				return false;
			}
			break;
		default:
			return false;
	}
	return true;
}

bool InitTranslator(CrdTranslator& translator, SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
	switch(sprData.export_coordinate_type)
	{
		case SAVE_PROFILE_3D_XYZ:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xyz;
			}
			break;
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				translator.a = a;
				translator.b = b;
				translator.c = c;
				translator.d = d;

				translator.minX = minX;
				translator.minY = minY;
				translator.minZ = minZ;

				translator.maxX = maxX;
				translator.maxY = maxY;
				translator.maxZ = maxZ;

				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::along_plane;
			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::yz;
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xz;
			}
			break;
		case SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION:
			{
				translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xy;
			}
			break;
		case SAVE_PROFILE_AUTO_SELECT_PROJECTION:
			{
				// определяем преимущественное направление вектора нормали к плоскости
				if (fabs(c) >= fabs(a) && fabs(c) >= fabs(b))
				{
					// доминирует направление вдоль оси Z
					translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xy;
				}
				else if (fabs(a) >= fabs(b) && fabs(a) >= fabs(c))
				{
					// доминирует направление вдоль оси X
					translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::yz;
				}
				else if (fabs(b) >= fabs(a) && fabs(b) >= fabs(c))
				{
					// доминирует направление вдоль оси Y
					translator.m_crd_translation_mode = CrdTranslator::crd_translation_mode::xz;
				}
			}
			break;
		default:
			return false;
	}
	return true;
}