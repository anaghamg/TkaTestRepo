#ifndef FIDUCIALSTRUCT_H
#define FIDUCIALSTRUCT_H


#define toolid 7100098
#define femurRef 435300
#define tibiaRef 435310

struct Point {
    double x;
    double y;
    double z;
};

struct Fiducial {
    Point point;
    bool status;
    double radius;
};

#endif // FIDUCIALSTRUCT_H
