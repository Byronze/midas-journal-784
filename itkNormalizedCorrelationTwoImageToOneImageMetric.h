/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkNormalizedCorrelationTwoImageToOneImageMetric.h,v $
  Language:  C++
  Date:      $Date: 2010/12/20 $
  Version:   $Revision: 1.0 $
  Author:    Jian Wu (eewujian@hotmail.com)
             Univerisity of Florida
		     Virginia Commonwealth University

  This program was modified from the ITK program--itkNormalizedCorrelationImageToImageMetric.h

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNormalizedCorrelationTwoImageToOneImageMetric_h
#define __itkNormalizedCorrelationTwoImageToOneImageMetric_h

#include "itkTwoImageToOneImageMetric.h"
#include "itkCovariantVector.h"
#include "itkPoint.h"


namespace itk
{
/** \class NormalizedCorrelationTwoImageToOneImageMetric
 * \brief Computes similarity between two fixed images and one moving image
 *
 * This metric computes the correlation between pixels in the two fixed images
 * and pixels in the moving image. The spatial correspondance between 
 * two fixed images and the moving image is established through a Transform. Pixel values are
 * taken from the fixed images, their positions are mapped to the moving
 * image and result in general in non-grid position on it. Values at these
 * non-grid position of the moving image are interpolated using user-selected
 * Interpolators. The correlation is normalized by the autocorrelations of both
 * the fixed and moving images.
 *
 * \ingroup RegistrationMetrics
 */
template < class TFixedImage, class TMovingImage > 
class ITK_EXPORT NormalizedCorrelationTwoImageToOneImageMetric : 
    public TwoImageToOneImageMetric< TFixedImage, TMovingImage>
{
public:

  /** Standard class typedefs. */
  typedef NormalizedCorrelationTwoImageToOneImageMetric    Self;
  typedef TwoImageToOneImageMetric<TFixedImage, TMovingImage >  Superclass;

  typedef SmartPointer<Self>         Pointer;
  typedef SmartPointer<const Self>   ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
 
  /** Run-time type information (and related methods). */
  itkTypeMacro(NormalizedCorrelationTwoImageToOneImageMetric, Object);

 
  /** Types transferred from the base class */
  typedef typename Superclass::RealType                 RealType;
  typedef typename Superclass::TransformType            TransformType;
  typedef typename Superclass::TransformPointer         TransformPointer;
  typedef typename Superclass::TransformParametersType  TransformParametersType;
  typedef typename Superclass::TransformJacobianType    TransformJacobianType;
  typedef typename Superclass::GradientPixelType        GradientPixelType;

  typedef typename Superclass::MeasureType              MeasureType;
  typedef typename Superclass::DerivativeType           DerivativeType;
  typedef typename Superclass::FixedImageType           FixedImageType;
  typedef typename Superclass::MovingImageType          MovingImageType;
  typedef typename Superclass::FixedImageConstPointer   FixedImageConstPointer;
  typedef typename Superclass::MovingImageConstPointer  MovingImageConstPointer;


  /** Get the derivatives of the match measure. */
  void GetDerivative( const TransformParametersType & parameters,
                      DerivativeType & Derivative ) const;

  /**  Get the value for single valued optimizers. */
  MeasureType GetValue( const TransformParametersType & parameters ) const;

  /**  Get value and derivatives for multiple valued optimizers. */
  void GetValueAndDerivative( const TransformParametersType & parameters,
                              MeasureType& Value, DerivativeType& Derivative ) const;

  /** Set/Get SubtractMean boolean. If true, the sample mean is subtracted 
   * from the sample values in the cross-correlation formula and
   * typically results in narrower valleys in the cost fucntion.
   * Default value is false. */
  itkSetMacro( SubtractMean, bool );
  itkGetConstReferenceMacro( SubtractMean, bool );
  itkBooleanMacro( SubtractMean );

protected:
  NormalizedCorrelationTwoImageToOneImageMetric();
  virtual ~NormalizedCorrelationTwoImageToOneImageMetric() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  NormalizedCorrelationTwoImageToOneImageMetric(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  bool    m_SubtractMean;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkNormalizedCorrelationTwoImageToOneImageMetric.txx"
#endif

#endif



