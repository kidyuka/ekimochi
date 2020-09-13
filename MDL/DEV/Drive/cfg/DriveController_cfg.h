#ifndef DRIVECONTROLLER_CFG_H
#define DRIVECONTROLLER_CFG_H

// 最も急なカーブの回転半径を設定する(mm)
#define DRIVECTL_CURVE_MAX 250
// 最も緩いカーブの回転半径を設定する(mm)
// ※直線走行時の車体方向調整の最小値を想定
#define DRIVECTL_CURVE_MIN 800

// ライントレースのPID
#define LINETRACE_PID_KP 2.5
#define LINETRACE_PID_KI 6.0
#define LINETRACE_PID_KD 6.0
#define LINETRACE_PID_DISCOUNT 0.4

#endif // DRIVECONTROLLER_CFG_H