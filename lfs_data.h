#ifndef LFS_DATA_H
#define LFS_DATA_H

struct lfs_outsim_struct{
    unsigned time;
    float angVel[3];
    float heading;
    float pitch;
    float roll;
    float accel[3];
    float velocity[3];
    int pos[3];
    int id;
};

struct lfs_outgauge_struct{
    unsigned time;
    char car[4];
    ushort flags;
    uchar gear;
    uchar spareB;
    float speed;
    float rpm;
    float turbo;
    float engTemp;
    float fuel;
    float oilPress;
    float oilTemp;
    unsigned dashLights;
    unsigned showLights;
    float throttle;
    float brake;
    float clutch;
    char display1[16];
    char display2[16];
    int id;
};

#define OG_SHIFT 1
#define OG_CTRL 2
#define OG_TURBO 8192
#define OG_KM 16384
#define OG_BAR 32768

enum{
    DL_SHIFT,
    DL_FULLBEAM,
    DL_HANDBRAKE,
    DL_PITSPEED,
    DL_TC,
    DL_SIGNAL_L,
    DL_SIGNAL_R,
    DL_SIGNAL_ALL,
    DL_OILWARN,
    DL_BATTERY,
    DL_ABS,
    DL_SPARE,
    DL_NUM
};

#endif // LFS_DATA_H
