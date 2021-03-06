#ifndef SHAPE_RECOGNITION_H
#define SHAPE_RECOGNITION_H

#include <common/types.h>
#include <common/segmented_plane.h>
#include <shape_fitting/model_fitting.h>
#include <shape_fitting/plane_fitting.h>

class ShapeRecognition : public PlaneCondition
{
public:
    ShapeRecognition();
    ~ShapeRecognition();

    common::Classification classify(const common::PointCloudRGB::Ptr &roi,
                                        const common::vision::SegmentedPlane::ArrayPtr& planes,
                                        const common::vision::SegmentedPlane* ground_plane);

    bool condition(const std::vector<pcl::ModelCoefficients> &planes, const std::vector<Eigen::Vector4f> &centroids);

#ifdef ENABLE_VISUALIZATION_RECOGNITION
    void set_viewer(boost::shared_ptr<pcl::visualization::PCLVisualizer>& viewer);
#endif

protected:

    bool condition_cube(const std::vector<pcl::ModelCoefficients>& planes, const std::vector<Eigen::Vector4f>& centroids);

    bool _parameter_initiated;

    Parameter<double> _dotprod_thresh;
    Parameter<double> _shape_thresh;

    pcl::ModelCoefficients::Ptr _best_coeffs;
    std::vector<ShapeClassifierBase*> _classifiers;
    const common::vision::SegmentedPlane* _ground_plane;

#ifdef ENABLE_VISUALIZATION_RECOGNITION
    boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer;
#endif
};

#endif // SHAPE_RECOGNITION_H
