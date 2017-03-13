#ifndef LFS_TRACK_DATA_H
#define LFS_TRACK_DATA_H

/*
 * LFS SMX file contains Header which specifies number of Objects
 * which each specifies Points and Triangles
 *
 */

struct struct_smx_header{
    char LFSSMX[6];
    uchar gameVersion, gameRevision, SMXVersion;
    uchar dimensions, resolution, vertexColor;
    uchar spare1[4];
    char track[32];
    uchar groundColR, groundColG, groundColB;
    uchar spare2[9];
    int numObjects;
};

struct struct_smx_objects{
    int xCenter;
    int yCenter;
    int zCenter;
    int radius;
    int numPoints;
    int numTriangles;
};

struct struct_smx_points{
    int X;
    int Y;
    int Z;
    unsigned char Opacity;
    unsigned char colors[3];
};

struct struct_smx_triangles{
    unsigned short vertex_A;
    unsigned short vertex_B;
    unsigned short vertex_C;
    unsigned short spare;
};

struct struct_smx_footer{
    int num_cp_objects;
    int *object_index;
};

#endif // LFS_TRACK_DATA_H
