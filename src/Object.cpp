/* 
 * File:   Object.cpp
 * Author: lzuercher
 * 
 * Created on 06 August 2012, 19:53
 */

// http://www.allegro.cc/forums/thread/605528
// http://openglsamples.sourceforge.net/files/glut_obj.cpp

#include <GL/glew.h>

#include "Object.h"


using namespace std;

Object::Object() {
  Faces_Triangles = normals = vertexBuffer = textureBuffer = NULL;
}

Object::Object(const char* filename) {
  loadObject(filename);
  _texture = loadBmpTexture("C:\\metoritewars\\objects\\player\\road.bmp");
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
  
  textureBuffer[0] = 1;
  textureBuffer[1] = 0;
  textureBuffer[2] = 1;
  textureBuffer[3] = 0;
  textureBuffer[4] = 1;
  textureBuffer[5] = 1;
  textureBuffer[6] = 0;
  textureBuffer[7] = 0;
  textureBuffer[8] = 1;
  
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
    
    //cout << line << endl;
  }
  
  //close file
  obj.close();
  
  return NOERROR;
}

void Object::Draw()
{
 	//glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
 	//glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	
  glColor3f(1.0,0.5,0.2);
  
  //glEnable(GL_TEXTURE_2D);
  //glBindTexture(GL_TEXTURE_2D, _texture);
  //cout << _texture << endl;
  
  /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glColor3f(1.0f, 1.0f, 1.0f);*/

  glColor3f(0.5,0.5,0.5);
  
  glBegin(GL_QUADS);
    
  glNormal3f(0.0, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-2.5f, -2.5f, 2.5f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(2.5f, -2.5f, 2.5f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(2.5f, -2.5f, -2.5f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-2.5f, -2.5f, -2.5f);

  glEnd();
  /*
  glVertexPointer(3,GL_FLOAT,	0,Faces_Triangles);				// Vertex Pointer to triangle array
	glNormalPointer(GL_FLOAT, 0, normals);						// Normal pointer to normal array
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);		// Draw the triangles
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays**/
}

GLint Object::loadBmpTexture(char* filename){
  
  
  // Data read from the header of the BMP file
  unsigned char header[54]; // Each BMP file begins by a 54-bytes header
  unsigned int dataPos;     // Position in the file where the actual data begins
  unsigned int width, height;
  unsigned int imageSize;   // = width*height*3
  // Actual RGB data
  unsigned char * data;
  GLuint textureID;
    
  // Open the file
  FILE * file = fopen(filename,"rb");
  if (!file) {
    printf("file not found\n");
    return ERROR_FILE_INVALID;
  }
  
  if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    fclose(file);
    return ERROR_FILE_CORRUPT;
  }
  
  dataPos    = *(int*)&(header[0x0A]);
  imageSize  = *(int*)&(header[0x22]);
  width      = *(int*)&(header[0x12]);
  height     = *(int*)&(header[0x16]);
  
  // Some BMP files are misformatted, guess missing information
  if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
  if (dataPos==0)      dataPos=54; // The BMP header is done that way
  
  // Create a buffer
  data = new unsigned char [imageSize];

  // Read the actual data from the file into the buffer
  fread(data,1,imageSize,file);

  //Everything is in memory now, the file can be closed
  fclose(file);
  
  glGenTextures( 1, &textureID ); //generate the texture with the loaded data
  glBindTexture( GL_TEXTURE_2D, textureID ); //bind the texture to it’s array
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

  //here we are setting what textures to use and when. The MIN filter is which quality to show
  //when the texture is near the view, and the MAG filter is which quality to show when the texture
  //is far from the view.

  //The qualities are (in order from worst to best)
  //GL_NEAREST
  //GL_LINEAR
  //GL_LINEAR_MIPMAP_NEAREST
  //GL_LINEAR_MIPMAP_LINEAR

  //And if you go and use extensions, you can use Anisotropic filtering textures which are of an
  //even better quality, but this will do for now.
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  //Here we are setting the parameter to repeat the texture instead of clamping the texture
  //to the edge of our shape. 
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

  //Generate the texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
  cout << textureID << endl;
  
  return textureID;
}

Object::~Object() {
  free(Faces_Triangles);
  free(normals);
  free(vertexBuffer);
}

