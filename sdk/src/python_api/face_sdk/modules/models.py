import os
from typing import List

import requests

from tqdm import tqdm

__UNIT_TYPES = {
    "FACE_DETECTOR": ["data/models/face_detector/face.onnx"],
    "FACE_RECOGNIZER": ["data/models/recognizer/recognizer.onnx"],
    "FITTER": ["data/models/mesh_fitter/mesh_fitter.onnx"],
    "MATCHER_MODULE": [],
    "HUMAN_BODY_DETECTOR": ["data/models/body_detector/body.onnx"],
    "EMOTION_ESTIMATOR": ["data/models/emotion_estimator/emotion.onnx"],
    "AGE_ESTIMATOR": ["data/models/age_estimator/age_heavy.onnx"],
    "GENDER_ESTIMATOR": ["data/models/gender_estimator/gender_heavy.onnx"],
    "MASK_ESTIMATOR": ["data/models/mask_estimator/mask.onnx"],
    "GLASSES_ESTIMATOR": ["data/models/glasses_estimator/glasses_v2.onnx"],
    "EYE_OPENNESS_ESTIMATOR": ["data/models/eye_openness_estimator/eye.onnx"],
    "LIVENESS_ESTIMATOR": ["data/models/liveness_estimator/liveness_2_7.onnx",
                           "data/models/liveness_estimator/liveness_4_0.onnx"],
    "BODY_RE_IDENTIFICATION": ["data/models/body_reidentification/re_id_heavy_model.onnx"],
    "POSE_ESTIMATOR": ["data/models/top_down_hpe/hpe-td.onnx"],
    "POSE_ESTIMATOR_LABEL": ["data/models/top_down_hpe/label_map_keypoints.txt"],
}

def make_model_paths(path_to_dir: str, unit_type: str) -> List[str]:
    result: List[str] = list()

    for model in __UNIT_TYPES[unit_type]:
        result.append(os.path.join(path_to_dir, model))

    return result