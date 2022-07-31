#pragma once

#ifndef EIGEN_MPL2_ONLY
#define EIGEN_MPL2_ONLY 1
#endif

//#ifndef EIGEN_DEFAULT_TO_ROW_MAJOR
//#define EIGEN_DEFAULT_TO_ROW_MAJOR 1
//#endif

#ifdef _MSVC
#pragma warning(push)
#pragma warning(disable:4819)
#endif

#ifdef Success
#undef Success
#endif

#ifdef Status
#undef Status
#endif

#include <Eigen>

#ifdef _MSVC
#pragma warning(pop)
#endif
