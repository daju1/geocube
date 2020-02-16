
#ifndef _SRFENUMS_H
#define _SRFENUMS_H

enum SrfDupMethod
{ 
	srfDupAll = 1, // keep all duplicates; this cannot be used with Kriging, Nearest Neighbor, Radial Basis, Triangulation, and Natural Neighbor gridding methods 
	srfDupNone,// eliminate all duplicates 
	srfDupFirst,// keep the first duplicate found in the input file
	srfDupLast,// keep the last duplicate found in the input file
	srfDupMinX,// keep the duplicate with the minimum X coordinate 
	srfDupMaxX,// keep the duplicate with the maximum X coordinate 
	srfDupMedX,// keep the duplicate with the median X coordinate 
	srfDupMinY,// keep the duplicate with the minimum Y coordinate
	srfDupMaxY,// keep the duplicate with the maximum Y coordinate
	srfDupMedY,// keep the duplicate with the median Y coordinate
	srfDupMinZ,// keep the duplicate with the minimum Z coordinate 
	srfDupMaxZ,// keep the duplicate with the maximum Z coordinate
	srfDupMedZ,// keep the duplicate with the median Z coordinate
	srfDupSum,// Z value is equal to the sum of the duplicate Z values 
	srfDupAvg,// Z value is equal to the average of the duplicate Z values
	srfDupMid,// Z value is equal to the midrange of the duplicate Z values
	srfDupRand// keep only a single randomly selected representative point 
};

enum SrfGridAlgorithm
{
	srfInverseDistance = 1,// Inverse Distance to a Power 
	srfKriging,// Kriging 
	srfMinCurvature,// Minimum Curvature 
	srfShepards,// Modified Shepard's Method 
	srfNaturalNeighbor,// Natural Neighbor 
	srfNearestNeighbor,// Nearest Neighbor 
	srfRegression,// Polynomial Regression 
	srfRadialBasis,// Radial Basis Functions 
	srfTriangulation,// Triangulation with Linear Interpolation 
	srfMovingAverage,// Moving Average
	srfDataMetrics,// Data Metrics
	srfLocalPolynomial// Local Polynomial
};
inline SrfGridAlgorithm operator++( SrfGridAlgorithm &rs, int )
{
   return rs = (SrfGridAlgorithm)(rs + 1);
}
inline const char * SrfGridAlgorithm_toStr(SrfGridAlgorithm alg)
{
	switch (alg)
	{
	case srfInverseDistance:
		return "Inverse Distance to a Power ";
	case srfKriging:
		return "Kriging";
	case srfMinCurvature:
		return "Minimum Curvature";
	case srfShepards:
		return "Modified Shepard's Method";
	case srfNaturalNeighbor:
		return "Natural Neighbor";
	case srfNearestNeighbor:
		return "Nearest Neighbor";
	case srfRegression:
		return "Polynomial Regression"; 
	case srfRadialBasis:
		return "Radial Basis Functions"; 
	case srfTriangulation:
		return "Triangulation with Linear Interpolation"; 
	case srfMovingAverage:
		return "Moving Average";
	case srfDataMetrics:
		return "Data Metrics";
	case srfLocalPolynomial:
		return "Local Polynomial";
	}
	return "";
};
enum SrfKrigType
{
	srfKrigPoint = 1,// point kriging type 
	srfKrigBlock// block kriging type 
};

enum SrfDriftType
{
	srfDriftNone = 1,// kriging drift type - none 
	srfDriftLinear,// kriging drift type - linear 
	srfDriftQuadratic// kriging drift type - quadratic 
};
 

enum SrfBasisType
{
	srfInverseMultiquadric = 1,// radial basis function type inverse multiquadric 
	srfMultiLog,// radial basis function type multilog
	srfMultiQuadric,// radial basis function type multiquadric 
	srfNaturalCubicSpline,// radial basis function type natural cubic spline 
	srfThinPlateSpline// radial basis function type thin plate spline 
};
 
enum SrfGridFormat
{
	srfGridFmtBinary = 1, // GS Binary [.GRD] This format stores the grid as 32-bit floating point numbers.
	srfGridFmtAscii,// GS ASCII [.GRD] This format is text based and can be edited.
	srfGridFmtS7,// Surfer 7 [.GRD] This format stores the grids as 64-bit floating point numbers. This is the only format that stores fault information. This is the preferred output format.
	srfGridFmtXYZ// ASCII XYZ [.DAT] A text based format that stores the XYZ coordinates of each grid node on a separate line.
};
 

 enum SrfDataMetric
 {
	srfDMMinimum = 1,// minimum Z value within the search
	srfDMLowerQ,// lower quartile Z value within the search
	srfDMMedian,// median Z value within the search
	srfDMUpperQ,// upper quartile Z value within the search
	srfDMMaximum,// maximum Z value within the search
	srfDMRange,// range of Z values within the search
	srfDMMidrange,// midrange Z value within the search
	srfDMInterQRange,// interquartile range of Z values within the search
	srfDMMean,// mean Z value within the search
	srfDMStdDev,// Z standard deviation value within the search
	srfDMVariance,// Z variance value within the search
	srfDMCoefVar,// Z coefficient of variation value within the search
	srfDMMad,// Z median absolute deviation within the search
	srfDMRms,// Z root mean square within the search
	srfDMSum,// Z sum within the search
	srfDMCount,// number of samples within the search
	srfDMDensity,// approximate data density within the search
	srfDMNearest,// distance to nearest sample within the search
	srfDMFarthest,// distance to farthest sample within the search
	srfDMMedianDist,// median distance to the samples within the search
	srfDMAveDist,// average distance to the samples within the search
	srfDMOffset,// distance between the node and the centroid of samples within the search
	srfDMSlope,// terrain slope of samples within the search
	srfDMAspect// terrain aspect of the samples within the search
 };
 

#endif