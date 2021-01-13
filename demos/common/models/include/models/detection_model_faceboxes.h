/*
// Copyright (C) 2018-2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#pragma once
#include "detection_model.h"

class ModelFaceBoxes : public DetectionModel {
public:
    struct Anchor {
        int left;
        int top;
        int right;
        int bottom;

        int getWidth() const { return (right - left) + 1; }
        int getHeight() const { return (bottom - top) + 1; }
        int getXCenter() const { return left + (getWidth() - 1) / 2; }
        int getYCenter() const { return top + (getHeight() - 1) / 2; }
    };
    static const int INIT_VECTOR_SIZE = 200;

    ModelFaceBoxes(const std::string& modelFileName, float confidenceThreshold, bool useAutoResize, float boxIOUThreshold);
    std::unique_ptr<ResultBase> postprocess(InferenceResult& infResult) override;

protected:
    int maxProposalsCount;
    const float boxIOUThreshold;
    const std::vector<int> steps;
    const std::vector<float> variance;
    const std::vector<std::vector<int>> minSizes;
    std::vector<Anchor> anchors;
    virtual void prepareInputsOutputs(InferenceEngine::CNNNetwork& cnnNetwork) override;
    void priorBoxes(const std::vector<std::pair<size_t, size_t>>& featureMaps);

};
