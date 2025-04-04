/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef itkLandmarkRegistrationEstimator_h
#define itkLandmarkRegistrationEstimator_h

#include "itkPoint.h"
#include "itkObjectFactory.h"
#include "itkPointsLocator.h"
#include "KDTreeVectorOfVectorsAdaptor.h"
#include "itkParametersEstimator.h"
namespace itk
{


template <unsigned int Dimension, typename TTransform>
class LandmarkRegistrationEstimator : public itk::ParametersEstimator<Point<double, Dimension>, double>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(LandmarkRegistrationEstimator);

  using Self = LandmarkRegistrationEstimator;
  using Superclass = ParametersEstimator<itk::Point<double, Dimension>, double>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  
  typedef std::vector<std::vector<double> > VectorofVectorsT;
  using self_t =
        KDTreeVectorOfVectorsAdaptor<VectorofVectorsT, double, 3, nanoflann::metric_L2>;
  using metric_t =
        typename nanoflann::metric_L2::template traits<double, self_t>::distance_t;
  using index_t =
        nanoflann::KDTreeSingleIndexAdaptor<metric_t, self_t, 3, size_t>;

  using KdTreeT = KDTreeVectorOfVectorsAdaptor< VectorofVectorsT, double >;

  using PointsLocatorType = itk::PointsLocator<itk::VectorContainer<IdentifierType, itk::Point<double, 3>>>;
  using PointsContainer = itk::VectorContainer<IdentifierType, itk::Point<double, 3>>;

  itkTypeMacro(LandmarkRegistrationEstimator, ParametersEstimator);
  /** New method for creating an object using a factory. */
  itkNewMacro(Self);

  virtual void
  Estimate(std::vector<Point<double, Dimension> *> & data, std::vector<double> & parameters) override;
  virtual void
  Estimate(std::vector<Point<double, Dimension>> & data, std::vector<double> & parameters) override;

  virtual void
  LeastSquaresEstimate(std::vector<Point<double, Dimension> *> & data, std::vector<double> & parameters) override;
  virtual void
  LeastSquaresEstimate(std::vector<Point<double, Dimension>> & data, std::vector<double> & parameters) override;

  virtual bool
  Agree(std::vector<double> & parameters, Point<double, Dimension> & data) override;

  virtual std::vector<double>
  AgreeMultiple(std::vector<double> & parameters, std::vector<Point<double, Dimension>> & data, unsigned int currentBest) override;

  virtual bool
  CheckCorresspondenceDistance(std::vector<double> & parameters, std::vector<Point<double, Dimension> *> & data) override;

  virtual bool
  CheckCorresspondenceEdgeLength(std::vector<double> & parameters, std::vector<Point<double, Dimension> *> & data, double edgeLength) override;

  virtual void
  SetDelta(double delta);

  virtual double
  GetDelta();

  void SetAgreeData(std::vector<Point<double, Dimension>> & data);

protected:
  LandmarkRegistrationEstimator();
  ~LandmarkRegistrationEstimator() override = default;

private:
  double delta;
  PointsLocatorType::Pointer pointsLocator;
  PointsContainer::Pointer agreePoints;
  VectorofVectorsT samples;
  KdTreeT * mat_adaptor;
};

} // end namespace itk

// the implementation is in this file
#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkLandmarkRegistrationEstimator.hxx"
#endif

#endif //_PLANE_PARAM_ESTIMATOR_H_
