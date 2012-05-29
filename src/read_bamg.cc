#include <iostream>
#include <fstream>
#include <cassert>
#include <string.h>
#include <cstdlib>
#include "grid.h"

using namespace std;

//------------------------------------------------------------------------------
// Read a grid in bamg format
//------------------------------------------------------------------------------
void Grid::read_bamg (string grid_file)
{
   unsigned int i, v_type, c_type;
   char line[80];

   cout << "Reading bamg grid file " << grid_file << endl;

   ifstream file;
   file.open (grid_file.c_str());
   assert ( file.is_open() );

   // Skip some lines
   for(i=0;i<=11;i++)
      file >> line;
   file >> line;
   assert(!strcmp("Vertices",line));
   file >> n_vertex;
   assert(n_vertex>0);
   vertex.resize(n_vertex);
   //Reading the vertices
   for(i=0; i<n_vertex; i++)
   {
      file >> vertex[i].coord.x >> vertex[i].coord.y >> v_type;
      vertex[i].coord.z = 0; //dimension =2
   }
   file >> line;
   assert(!strcmp(line,"Edges"));
   file >> n_face;
   face.resize(n_face);
   //Reading the edges next
   //Reducing the vertices in faces and cells by 1 is done
   //since it is taken from 0 in the vertex vector.
   for(i=0;i<n_face;i++)
   {
      file >> face[i].vertex[0] >> face[i].vertex[1] >> face[i].type;
      face[i].vertex[0]--;
      face[i].vertex[1]--;
   }
   file >> line;
   assert(!strcmp(line, "Triangles"));
   file >> n_cell;
   cell.resize(n_cell);
   //Reading Triangles
   for(i=0;i<n_cell;i++)
   {
      file >> cell[i].vertex[0] 
           >> cell[i].vertex[1] 
           >> cell[i].vertex[2] 
           >> c_type;
      cell[i].vertex[0]--;
      cell[i].vertex[1]--;
      cell[i].vertex[2]--;
   }
    
   file.close();
}
   
