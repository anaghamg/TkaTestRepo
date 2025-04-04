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

#include <fstream>
#include "ransacitk/itkRANSAC.h"
#include "ransacitk/itkLandmarkRegistrationEstimator.h"
#include "ransacitk/RandomNumberGenerator.h"
#include "itkMesh.h"
#include "itkMeshFileReader.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "itkPoint.h"



template <unsigned int Dimension>
void
GenerateData(std::vector<itk::Point<double, Dimension> > & data,
             std::vector<itk::Point<double, Dimension> > & agreeData,
             const char * patientFile, const char * imageFile);


int
itkRansacTest_LandmarkRegistration(const char * patientFile, const char * imageFile)
{




  using TTransform = itk::Similarity3DTransform<double>;
  const unsigned int DimensionPoint = 6;
  typedef itk::RANSAC<itk::Point<double, DimensionPoint>, double, TTransform> RANSACType;

  std::vector<itk::Point<double, DimensionPoint> > data;
  std::vector<itk::Point<double, DimensionPoint> > agreeData;
  std::vector<double> transformParameters;

  // Read the coordinates from the patient and image files
  GenerateData<DimensionPoint>(data, agreeData, patientFile, imageFile);
  
  // create and initialize the parameter estimator
  double inlierValue = 3;
  int ransacPoints = 3;
  int maxIteration = 10000;
  auto   registrationEstimator = itk::LandmarkRegistrationEstimator<6, TTransform>::New();
  registrationEstimator->SetMinimalForEstimate(ransacPoints);
  registrationEstimator->SetDelta(inlierValue);
  registrationEstimator->SetAgreeData(agreeData);
  registrationEstimator->LeastSquaresEstimate(data, transformParameters);

  unsigned int i = 0;
  for (i = 0; i < transformParameters.size(); i++)
  {
    std::cout << transformParameters[i] << ", ";
  }

  // create and initialize the RANSAC algorithm
  double              desiredProbabilityForNoOutliers = 0.99;
  RANSACType::Pointer ransacEstimator = RANSACType::New();
  ransacEstimator->SetData(data);
  ransacEstimator->SetAgreeData(agreeData);
  ransacEstimator->SetParametersEstimator(registrationEstimator);
  ransacEstimator->SetCheckCorresspondenceDistance(true);
  ransacEstimator->SetCheckCorrespondenceEdgeLength(0.9);
  ransacEstimator->SetMaxIteration(maxIteration);
  
  auto percentageOfDataUsed = ransacEstimator->Compute(transformParameters, desiredProbabilityForNoOutliers);

  if (transformParameters.empty())
  {
    std::cout << "RANSAC estimate failed, degenerate configuration?\n";
  }
  else
  {
    std::cout << "RANSAC parameters: [n,a]\n\t [ ";
    for (i = 0; i < transformParameters.size(); i++)
    {
      std::cout << transformParameters[i] << ", ";
    }
  }

  std::cout << "\n\n" << std::endl;
  std::cout << "percentageOfDataUsed " << percentageOfDataUsed[0] << "\n\n";
  std::cout << "Inlier RMSE is  " << percentageOfDataUsed[1] << "\n\n";
  return EXIT_SUCCESS;
}


template <unsigned int Dimension>
void
GenerateData(std::vector<itk::Point<double, Dimension> > & data,
             std::vector<itk::Point<double, Dimension> > & agreeData,
             const char * patientFile, const char * imageFile)
{
  using PointType = itk::Point<double, Dimension>;
  std::vector<PointType> patientPoints;
  std::vector<PointType> imagePoints;

  // Read patient space points
  std::ifstream patientStream(patientFile);
  if (!patientStream)
  {
    std::cerr << "Error opening file: " << patientFile << std::endl;
    return;
  }

  std::string line;
  double x, y, z;

  // Read patient space coordinates (x, y, z in separate lines)
  while (std::getline(patientStream, line))
  {
    std::istringstream iss(line);
    if (iss >> x >> y >> z)
    {
      PointType point;
      point[0] = x;
      point[1] = y;
      point[2] = z;
      patientPoints.push_back(point);
    }
  }
  patientStream.close();

  // Read image space points
  std::ifstream imageStream(imageFile);
  if (!imageStream)
  {
    std::cerr << "Error opening file: " << imageFile << std::endl;
    return;
  }

  // Read image space coordinates (x, y, z in separate lines)
  while (std::getline(imageStream, line))
  {
    std::istringstream iss(line);
    if (iss >> x >> y >> z)
    {
      PointType point;
      point[0] = x;
      point[1] = y;
      point[2] = z;
      imagePoints.push_back(point);
    }
  }
  imageStream.close();

  // Match points based on the minimum count between the two sets
  unsigned int minCount = std::min(patientPoints.size(), imagePoints.size());
  data.clear();
  agreeData.clear();

  // Combine points into a 6D vector (3D patient + 3D image)
  PointType combinedPoint;
  for (unsigned int i = 0; i < minCount; ++i)
  {
    combinedPoint[0] = patientPoints[i][0];
    combinedPoint[1] = patientPoints[i][1];
    combinedPoint[2] = patientPoints[i][2];
    combinedPoint[3] = imagePoints[i][0];
    combinedPoint[4] = imagePoints[i][1];
    combinedPoint[5] = imagePoints[i][2];

    data.push_back(combinedPoint);
    agreeData.push_back(combinedPoint);  // You can modify agreeData handling if needed
  }

  std::cout << "Loaded " << minCount << " matching points from patient and image spaces." << std::endl;
}
