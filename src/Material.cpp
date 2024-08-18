#include "Material.h"

Material mirror(Vector3d(0, 0.1, 0.05), 0.5, 20, 0.6, 0, 0);
Material stone(Vector3d(0.5, 0.5, 0.5), 0.8, 2, 0, 1, 0);
Material redgloss(Vector3d(1.0, 0.3, 0.3), 0.2, 100, 0.15, 2, 0);
Material bluegloss(Vector3d(0.3, 0.3, 1.0), 0.2, 100, 0.15, 2, 0);
Material glass(Vector3d(1.0, 1.0, 1.0), 0, 20, 0.5, 1.5, 0.9);

Material whiteWall(Vector3d(1, 1, 1), 0.8, 2, 0, 1, 0);
Material redWall(Vector3d(1, 0, 0), 0.8, 2, 0, 1, 0);
Material greenWall(Vector3d(0, 1, 0), 0.8, 2, 0, 1, 0);
