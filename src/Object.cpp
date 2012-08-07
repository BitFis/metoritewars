/* 
 * File:   Object.cpp
 * Author: lzuercher
 * 
 * Created on 06 August 2012, 19:53
 */

// http://www.allegro.cc/forums/thread/605528
// http://openglsamples.sourceforge.net/files/glut_obj.cpp

#include "Object.h"


using namespace std;

Object::Object() {
  Faces_Triangles = normals = vertexBuffer = textureBuffer = NULL;
}

Object::Object(const char* filename) {
  _texture = loadObject(filename);
  tex = new GLTexture();
  //tex->Load("C:\\c\\metoritewars\\objects\\player\\road.bmp");
}

int Object::calculateNormal( float *coord1, float *coord2, float *coord3, float* norm )
{
  /* calculate Vector1 and Vector2 */
  float va[3], vb[3], vr[3], val;
  
  va[0] = coord1[0] - coord2[0];
  va[1] = coord1[1] - coord2[1];
  va[2] = coord1[2] - coord2[2];

  vb[0] = coord1[0] - coord3[0];
  vb[1] = coord1[1] - coord3[1];
  vb[2] = coord1[2] - coord3[2];

  /* cross product */
  vr[0] = va[1] * vb[2] - vb[1] * va[2];
  vr[1] = vb[0] * va[2] - va[0] * vb[2];
  vr[2] = va[0] * vb[1] - vb[0] * va[1];

  /* normalization factor */
  val = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );

  norm[0] = vr[0]/val;
  norm[1] = vr[1]/val;
  norm[2] = vr[2]/val;

  return 0;
}

GLint Object::loadObject(const char* filename){
  
  ifstream obj;    //object file open and reads all lines of object
  string line; //current line
  char stringbuffer[64] = {0}; //buffer to use for sscanf
  
  //set face and vertex index to 0
  int triangle_index = 0;
  int normal_index = 0;
  
  //open file
  obj.open(filename);
  
  obj.seekg (0, ios::end); // Go to end of the file, 
  long fileSize = obj.tellg(); // get file size
  obj.seekg (0, ios::beg); // we'll use this to register memory for our 3d model
  
  //free memory bevor use
  free(Faces_Triangles);
  free(normals);
  free(vertexBuffer);
  free(textureBuffer);
  
  vertexBuffer = (float*) malloc (fileSize); // Allocate memory for the verteces
  Faces_Triangles = (float*) malloc(fileSize*sizeof(float)); // Allocate memory for the triangles
  normals  = (float*) malloc(fileSize*sizeof(float)); // Allocate memory for the normals
  textureBuffer = (float*) malloc(fileSize*sizeof(float));
  
  //check if it is open
  if(obj.is_open() == false){    
    cout << "could not open object" << endl;
    return ERROR_FILE_NOT_FOUND;
  }
  
  //read file
  while(obj.eof() == false){
    getline(obj, line);
    
    if(line.compare(0, 2, "o ") == 0){
      //get the name of the object
      sscanf(line.c_str(), "o %s", stringbuffer);
      _name = stringbuffer;
      
    }else if(line.compare(0, 7, "mtllib ") == 0){
      //get materialfile
      sscanf(line.c_str(), "mtllib %s", stringbuffer);
      _materialfile = stringbuffer;
      
    }else if(line.compare(0, 2, "v ") == 0){
      //save vertexes of object
      sscanf(line.c_str(), "v %f %f %f",
              &vertexBuffer[TotalConnectedPoints ],
              &vertexBuffer[TotalConnectedPoints+1 ],
              &vertexBuffer[TotalConnectedPoints+2 ]);
      
      TotalConnectedPoints += 3;
      
    }else if(line.compare(0, 2, "f ") == 0){
      //get vertexnumber
      int vertexnumber[4] = {1 , 1 , 1, 1}; //save vertexnumbers
      int texturcordinats[4] = {1 , 1 , 1, 1}; //save texturecordinate
      int vertexnormals[4] = {1 , 1 , 1 , 1}; //save normals
      
      //.obj file contains vertexpoints, texturecoordinats and normalcoordinates
      if(sscanf(line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i", 
              &vertexnumber[0],
              &texturcordinats[0],
              &vertexnormals[0],
              &vertexnumber[1],
              &texturcordinats[1],
              &vertexnormals[1],
              &vertexnumber[2],
              &texturcordinats[2],
              &vertexnormals[2],
              &vertexnumber[3],
              &texturcordinats[3],
              &vertexnormals[3]) < 6){
        //.obj file contains only texturcordinat and vertex
        if(sscanf(line.c_str(), "f %i/%i %i/%i %i/%i %i/%i", 
                &vertexnumber[0], &texturcordinats[0],
                &vertexnumber[1], &texturcordinats[1],
                &vertexnumber[2], &texturcordinats[2],
                &vertexnumber[3], &texturcordinats[3]) < 6){
          //.obj file contains only vertexpints
          if(sscanf(line.c_str(), "f %i %i %i %i", 
                  &vertexnumber[0], &vertexnumber[1],
                  &vertexnumber[2], &vertexnumber[3]) < 3){
            //format contains an error
            cout << ".obj file contains errors" << endl;
            return ERROR_BAD_FORMAT;
          }
        }
      }
      
      //.obj counter starts from 1, but must start from 0
      vertexnumber[0] -= 1;
      vertexnumber[1] -= 1;
      vertexnumber[2] -= 1;
      vertexnumber[3] -= 1;
      
      //.obj counter starts from 1, but must start from 0
      texturcordinats[0] -= 1;
      texturcordinats[1] -= 1;
      texturcordinats[2] -= 1;
      texturcordinats[3] -= 1;
      
      //initialise counter
      int tCounter = 0;
      
      //temporary only triangles using 3 points
      //create triangles by using vertex read out of file earlier
      for (int i = 0; i < 3; i++)					
      {
        Faces_Triangles[triangle_index + tCounter   ] = vertexBuffer[3*vertexnumber[i] ];
        Faces_Triangles[triangle_index + tCounter +1 ] = vertexBuffer[3*vertexnumber[i]+1 ];
        Faces_Triangles[triangle_index + tCounter +2 ] = vertexBuffer[3*vertexnumber[i]+2 ];
        tCounter += 3;
      }
      
      //initialice normal variable
      float norm[3] = {0};
      
      //calculate normals if not set
      if(vertexnormals[0] != 0){
        /*********************************************************************
				 * Calculate all normals, used for lighting
				 */ 
				float coord1[3] = { Faces_Triangles[triangle_index], Faces_Triangles[triangle_index+1],Faces_Triangles[triangle_index+2]};
				float coord2[3] = {Faces_Triangles[triangle_index+3],Faces_Triangles[triangle_index+4],Faces_Triangles[triangle_index+5]};
				float coord3[3] = {Faces_Triangles[triangle_index+6],Faces_Triangles[triangle_index+7],Faces_Triangles[triangle_index+8]};
				calculateNormal( coord1, coord2, coord3, norm );

      }else{
        //.obj counter starts from 1, but must start from 0
        norm[0] = vertexnormals[0] - 1;
        norm[1] = vertexnormals[1] - 1;
        norm[2] = vertexnormals[2] - 1;
        vertexnormals[3] -= 1;
      }
      
      //set normals
      tCounter = 0;
      for (int i = 0; i < 3; i++)
      {
        normals[normal_index + tCounter ] = norm[0];
        normals[normal_index + tCounter +1] = norm[1];
        normals[normal_index + tCounter +2] = norm[2];
        tCounter += 3;
      }

      //set triangle_index
      triangle_index += OBJECT_TOTAL_FLOATS_IN_TRIANGLE;
      //set normal index only for triangle
      normal_index += OBJECT_TOTAL_FLOATS_IN_TRIANGLE;
      TotalConnectedTriangles += OBJECT_TOTAL_FLOATS_IN_TRIANGLE;
    }
    
    cout << line << endl;
  }
  
  //close file
  obj.close();
  
  return NOERROR;
}

void Object::Draw()
{
 	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
 	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	glVertexPointer(3,GL_FLOAT,	0,Faces_Triangles);				// Vertex Pointer to triangle array
	glNormalPointer(GL_FLOAT, 0, normals);						// Normal pointer to normal array
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);		// Draw the triangles
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
}

GLint Object::loadBmpTexture(char* filename){
  
  
  
  return 0;
}

Object::~Object() {
  free(Faces_Triangles);
  free(normals);
  free(vertexBuffer);
}

