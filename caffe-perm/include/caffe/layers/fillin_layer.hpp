#ifndef CAFFE_FILLIN_LAYER_HPP_
#define CAFFE_FILLIN_LAYER_HPP_

#include <utility>
#include <vector>
#include <curand_kernel.h>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

/**
 * @brief Takes a Blob and crop it, to the shape specified by the second input
 *  Blob, across all dimensions after the specified axis.
 *
 * TODO(dox): thorough documentation for Forward, Backward, and proto params.
 */

template <typename Dtype>
class FillinLayer : public Layer<Dtype> {
 public:
  explicit FillinLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "Fillin"; }
  virtual inline int ExactNumBottomBlobs() const { return 2; }
  virtual inline int MinTopBlobs() const { return 2; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);

   Blob<float> coord;
   curandState *devStates;
   bool isCurandInit = false;

 private:

  void generate_fillin(Blob<int>& batch_fillin, Blob<Dtype>& labels);

};
}  // namespace caffe

#endif  // CAFFE_FILLIN_LAYER_HPP_
