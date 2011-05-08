#include "R3/R3.h"
#include <sstream>


#define R3Rgb R2Pixel

#define CHUNK_Z 16
#define CHUNK_X 16
#define CHUNK_Y 16

using namespace std;



typedef enum {
  R3_BOX_SHAPE,
  R3_SPHERE_SHAPE,
  R3_CYLINDER_SHAPE,
  R3_CONE_SHAPE,
  R3_MESH_SHAPE,
  R3_SEGMENT_SHAPE,
  R3_BLOCK_SHAPE,
  R3_NUM_SHAPE_TYPES,
} R3ShapeType;

typedef enum {
  R3_DIRECTIONAL_LIGHT,
  R3_POINT_LIGHT,
  R3_SPOT_LIGHT,
  R3_AREA_LIGHT,
  R3_NUM_LIGHT_TYPES
} R3LightType;


// Scene element definitions

struct R3Shape {
  R3ShapeType type;
  R3Box *box;
  R3Sphere *sphere;
  R3Cylinder *cylinder;
  R3Cone *cone;
  R3Mesh *mesh;
  R3Segment *segment;
  R3Block *block;
};  

struct R3Material {
  R3Rgb ka;
  R3Rgb kd;
  R3Rgb ks;
  R3Rgb kt;
  R3Rgb emission;
  double shininess;
  double indexofrefraction;
  R2Image *texture;
  int texture_index;
	//R3BlockType blockType;
  int id;
};

struct R3Light {
  R3LightType type;
  R3Point position;
  R3Vector direction;
  double radius;
  R3Rgb color;
  double constant_attenuation;
  double linear_attenuation;
  double quadratic_attenuation;
  double angle_attenuation;
  double angle_cutoff;
};

struct R3Camera {
  R3Point eye;
  R3Vector towards;
  R3Vector right;
  R3Vector up;
  double xfov, yfov;
  double neardist, fardist;
};

struct R3Node {
  struct R3Node *parent;
  vector<struct R3Node *> children;
  R3Shape *shape;
  R3Matrix transformation;
  R3Material *material;
	R3Material *material_top;
	R3Material *material_sides;
  R3Box bbox;
  bool selected;
};

struct R3Chunk{
  public:
  
  R3Chunk(void);
  void DeleteChunk();
  
  int ReadChunk(int xChunkCoord, int zChunkCoord);
  int WriteChunk(const char *filename);
  int GenerateChunk(int c_x, int c_z);
  
  
  public:
  R3Point start_point; // world coords
  R3Point end_point; // world coords
  int chunk_x; // chunk coords
  int chunk_z; // chunk coords
  double block_side;
  R3Node *chunk[CHUNK_X][CHUNK_Y][CHUNK_Z];
};