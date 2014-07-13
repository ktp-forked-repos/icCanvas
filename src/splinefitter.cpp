#include <icCanvasManager.hpp>

#include <cmath>

icCanvasManager::SplineFitter::SplineFitter() {
    this->beizer_4_coeff << -1.0,  3.0, -3.0, 1.0,
                             3.0, -6.0,  3.0, 0.0,
                            -3.0,  3.0,  0.0, 0.0,
                             1.0,  0.0,  0.0, 0.0;
    this->beizer_4_invcoeff = this->beizer_4_coeff.inverse();
};
icCanvasManager::SplineFitter::~SplineFitter() {};

void icCanvasManager::SplineFitter::begin_fitting(icCanvasManager::RefPtr<icCanvasManager::BrushStroke> storage, int error_threshold) {
    this->unfitted_points.clear();
    this->distances.clear();
    this->distances.push_back(0);
    this->indexes.clear();
    this->target_curve = storage;
    this->unfitted_id = 0;
};

void icCanvasManager::SplineFitter::add_fit_point(int x, int y, int pressure, int tilt, int angle, int dx, int dy) {
    icCanvasManager::BrushStroke::__ControlPoint cp;
    
    cp.x = x;
    cp.y = y;
    cp.pressure = pressure;
    cp.tilt = tilt;
    cp.angle = angle;
    cp.dx = dx;
    cp.dy = dy;
    
    this->unfitted_points.push_back(cp);
    auto ptsize = this->unfitted_points.size();
    
    if (ptsize < 2) return;
    
    auto& lastcp = this->unfitted_points.at(ptsize - 2);
    int xDelta = cp.x - lastcp.x, yDelta = cp.y - lastcp.y;
    int segDist = (int)sqrt((float)xDelta * (float)xDelta + (float)yDelta * (float)yDelta);
    int newTotalDist = this->distances.at(ptsize - 2) + segDist;
    this->distances.push_back(newTotalDist);
    this->indexes.push_back(0);
    
    Eigen::Matrix<float, Eigen::Dynamic, 4> b_indexes(ptsize, 4);
    Eigen::Matrix<float, Eigen::Dynamic, 1> xposVec(ptsize, 1), yposVec(ptsize, 1), pressureVec(ptsize, 1), tiltVec(ptsize, 1), angleVec(ptsize, 1), xdeltaVec(ptsize, 1), ydeltaVec(ptsize, 1);
    
    auto i = this->distances.begin();
    auto j = this->indexes.begin();
    auto k = this->unfitted_points.begin();
    
    for (int l = 0;
         i != this->distances.end() &&
         j != this->indexes.end() &&
         k != this->unfitted_points.end() &&
         l != ptsize;
         i++, j++, k++, l++) {
        auto tval = (float)(*i) / (float)newTotalDist;
        *j = (int)tval;
        
        b_indexes(l,0) = tval * tval * tval;
        b_indexes(l,1) = tval * tval;
        b_indexes(l,2) = tval;
        b_indexes(l,3) = 1.0f;

        xposVec(l, 0) = k->x;
        yposVec(l, 0) = k->y;
        pressureVec(l, 0) = k->pressure;
        tiltVec(l, 0) = k->tilt;
        angleVec(l, 0) = k->angle;
        xdeltaVec(l, 0) = k->dx;
        ydeltaVec(l, 0) = k->dy;
    }
    
    auto b_indexes_transpose = b_indexes.transpose();
    auto b_indexes_matrix = b_indexes_transpose * b_indexes;
    Eigen::MatrixXf b_matrix_inverse;
    Eigen::MatrixXf bmat_identity = Eigen::MatrixXf::Identity(b_indexes_matrix.rows(), b_indexes_matrix.rows());
    
    if (b_indexes_matrix.determinant() == 0) {
        b_matrix_inverse = b_indexes_matrix.llt().solve(bmat_identity);
    } else {
        b_matrix_inverse = b_indexes_matrix.inverse();
    }
    
    auto curve_xpos = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * xposVec;
    auto curve_ypos = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * yposVec;
    auto curve_pressure = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * pressureVec;
    auto curve_tilt = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * tiltVec;
    auto curve_angle = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * angleVec;
    auto curve_xdelta = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * xdeltaVec;
    auto curve_ydelta = this->beizer_4_invcoeff * b_matrix_inverse * b_indexes_transpose * ydeltaVec;
    
    this->target_curve->pen_begin(curve_xpos(0,0), curve_ypos(0,0));
    this->target_curve->pen_begin_pressure(curve_pressure(0,0));
    this->target_curve->pen_begin_tilt(curve_tilt(0,0), curve_angle(0,0));
    this->target_curve->pen_begin_velocity(curve_xdelta(0,0), curve_ydelta(0,0));
    
    this->target_curve->pen_to(curve_xpos(1,0), curve_ypos(1,0), curve_xpos(2,0), curve_ypos(2,0), curve_xpos(3,0), curve_ypos(3,0));
    this->target_curve->pen_to_pressure(curve_pressure(1,0), curve_pressure(2,0), curve_pressure(3,0));
    this->target_curve->pen_to_tilt(curve_tilt(1,0), curve_angle(1,0), curve_tilt(2,0), curve_angle(2,0), curve_tilt(3,0), curve_angle(3,0));
    this->target_curve->pen_to_velocity(curve_xdelta(1,0), curve_ydelta(1,0), curve_xdelta(2,0), curve_ydelta(2,0), curve_xdelta(3,0), curve_ydelta(3,0));
};

void icCanvasManager::SplineFitter::finish_fitting() {};
