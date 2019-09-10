/*
 * (C) Copyright 2019 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

#ifndef UFO_FILTERS_OBSFILTERDATA_H_
#define UFO_FILTERS_OBSFILTERDATA_H_

#include <ostream>
#include <string>
#include <vector>

#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"

namespace ioda {
  class ObsSpace;
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsDiagnostics;

// -----------------------------------------------------------------------------
/*! \brief ObsFilterData provides access to all data related to an ObsFilter
 *
 * \details ObsFilterData can always provide access to all data from ObsSpace
 * and optionally to data from H(x) ObsVector, GeoVaLs and ObsDiagnostics.
 * The latter three can be associated with ObsFilterData by using associate()
 * method.
 *
 */
class ObsFilterData : public util::Printable,
                      private util::ObjectCounter<ObsFilterData> {
 public:
  static const std::string classname() {return "ufo::ObsFilterData";}

  //! Constructs ObsFilterData and associates ObsSpace with it
  explicit ObsFilterData(ioda::ObsSpace &);
  ~ObsFilterData();

  //! Associates GeoVaLs with this ObsFilterData
  void associate(const GeoVaLs &);
  //! Associates H(x) ObsVector with this ObsFilterData
  void associate(const ioda::ObsVector &);
  //! Associates ObsDiagnostics from ObsOperator with this ObsFilterData
  void associate(const ObsDiagnostics &);

  //! Returns requested data from ObsFilterData
  std::vector<float> get(const std::string &) const;
  //! Checks if requested data exists in ObsFilterData
  bool has(const std::string &) const;

  //! Returns number of locations
  size_t nlocs() const;

 private:
  void print(std::ostream &) const;

  ioda::ObsSpace & obsdb_;                 //!< ObsSpace associated with this object
  const GeoVaLs mutable * gvals_;          //!< pointer to GeoVaLs associated with this object
  const ioda::ObsVector mutable * hofx_;   //!< pointer to H(x) associated with this object
  const ObsDiagnostics mutable * diags_;   //!< pointer to ObsDiagnostics associated with object
};

}  // namespace ufo

#endif  // UFO_FILTERS_OBSFILTERDATA_H_