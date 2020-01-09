// $Id: shape.cpp,v 1.2 2019-02-28 15:24:20-08 - - $

#include <typeinfo>
#include <unordered_map>
using namespace std;
#include <cstring>
#include "shape.h"
#include "util.h"
#include <cmath>
static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font_, const string& textdata_):
      glut_bitmap_font(glut_bitmap_font_), textdata(textdata_) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {

   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices_): vertices(vertices_) {
   DEBUGF ('c', this);
}

// Needs implementation

vertex_list findrect(GLfloat width, GLfloat height){
   vertex_list verte;
   vertex v1{width/2, height/2 };
   verte.push_back(v1);
   vertex v2{width/2, -height/2 };
   verte.push_back(v2);
   vertex v3{-width/2, -height/2 };
   verte.push_back(v3);
   vertex v4{-width/2, height/2 };
   verte.push_back(v4);
   return verte;
}
rectangle::rectangle (GLfloat width, GLfloat height):
            polygon(findrect(width,height)) {

   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

// Needs implementation
vertex_list finddiamond(GLfloat width, GLfloat height){
   vertex_list verte;
   vertex v1{width, 0 };
   verte.push_back(v1);
   vertex v2{0, height };
   verte.push_back(v2);
   vertex v3{-width,0};
   verte.push_back(v3);
   vertex v4{0, -height};
   verte.push_back(v4);
   return verte;
}
diamond::diamond (GLfloat width, GLfloat height):
            polygon (finddiamond(width,height)) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

triangle::triangle (const vertex_list& vertices_): polygon(vertices_) {
   DEBUGF ('c', this);
}



vertex_list findeqi(GLfloat width){
   vertex_list verte;

   vertex v1{0,0};
   verte.push_back(v1);
   vertex v2{width,  0};
   verte.push_back(v2);
   vertex v3{width/2, sqrt(3)/2*width};
   verte.push_back(v3);
   return verte;
}
// Needs implementation
equilateral::equilateral (GLfloat width): triangle (findeqi(width)) {
   DEBUGF ('c', this << "(" << width << ")");
}

// Needs implementation

void text::draw (const vertex& center, const rgbcolor& color, string num, bool border, const rgbcolor& bColor,GLfloat lineWidth) const {

   auto u_str = reinterpret_cast<const GLubyte*> (textdata.c_str());
   const GLubyte c[] {color.ubvec[0], color.ubvec[1], color.ubvec[2]};
   glColor3ubv (c);
   GLfloat xpos = center.xpos;
   GLfloat ypos = center.ypos;
   glRasterPos2f (xpos, ypos);
   glutBitmapString (glut_bitmap_font, u_str);

}

// Basic hello world
// Needs proper implementation

void ellipse::draw 
(const vertex& center_, const rgbcolor& color, string num, bool border, const rgbcolor& bColor, GLfloat lineWidth) const {


const GLubyte c[] {color.ubvec[0], color.ubvec[1], color.ubvec[2]};


   glBegin (GL_POLYGON);
   glColor3ubv (c);
   for(GLfloat theta = 0;theta <=360;theta += .1){
     GLfloat xpos = center_.xpos + dimension.xpos * cos (theta);
     GLfloat ypos = center_.ypos + dimension.ypos * sin (theta);
     glVertex2f (xpos, ypos);
   }
   glEnd();
   
   string a = num;
   auto u_str = reinterpret_cast<const GLubyte*> (a.c_str());
   const GLubyte d[] {255 - color.ubvec[0], 255 - color.ubvec[1], 255 - color.ubvec[2]};
   glColor3ubv (d);
   GLfloat xpos = center_.xpos;
   GLfloat ypos = center_.ypos;
   glRasterPos2f (xpos, ypos);
        void* font = GLUT_BITMAP_HELVETICA_18;
   glutBitmapString (font, u_str);


   if(border){
    glLineWidth(lineWidth);
    glBegin (GL_LINE_LOOP);
	const GLubyte d[] {bColor.ubvec[0], bColor.ubvec[1], bColor.ubvec[2]};
    glColor3ubv (d);
       for(GLfloat theta = 0;theta <=360;theta += .1){
     GLfloat xpos = center_.xpos + dimension.xpos * cos (theta);
     GLfloat ypos = center_.ypos + dimension.ypos * sin (theta);
     glVertex2f (xpos, ypos);
   }
   glEnd();
   }

   
   
   
}

// Needs implementation, this will be the hardest
void polygon::draw (const vertex& center, const rgbcolor& color, string num, bool border, const rgbcolor& bColor, GLfloat lineWidth) const {
   const GLubyte c[] {color.ubvec[0], color.ubvec[1], color.ubvec[2]};


   glBegin (GL_POLYGON);
   if(vertices.size()==3){
     glBegin (GL_TRIANGLES);
   }
   glColor3ubv (c);
   //glVertex2f (vertices.size()*10, 100);
   int x = 0;
   int y = 0;
   
   for(vertex a :vertices){
     x+=a.xpos; 
	 y+=a.ypos;
   }
   x/=vertices.size();
   y/=vertices.size();
   for(vertex a :vertices){
     glVertex2f (a.xpos-x + center.xpos , a.ypos-y+center.ypos);
   }
   glEnd();


   auto u_str = reinterpret_cast<const GLubyte*> (num.c_str());
   void* font = GLUT_BITMAP_HELVETICA_18;
   const GLubyte d[] {255 - color.ubvec[0], 255 - color.ubvec[1], 255 - color.ubvec[2]};
   glColor3ubv (d);
   GLfloat xpos = center.xpos;
   GLfloat ypos = center.ypos;
   int str_width = glutBitmapLength (font, u_str);
   int str_height = glutBitmapHeight (font);
   glRasterPos2f (xpos-str_width/2, ypos-str_width/4);
   glutBitmapString (font, u_str);






   if(border){
      glLineWidth(lineWidth);
    glBegin (GL_LINE_LOOP);
	const GLubyte d[] {bColor.ubvec[0], bColor.ubvec[1], bColor.ubvec[2]};
    glColor3ubv (d);
   int x1 = 0;
   int y1 = 0;
   
   for(vertex a :vertices){
     x1+=a.xpos; 
    y1+=a.ypos;
   }
   x1/=vertices.size();
   y1/=vertices.size();
   for(vertex a :vertices){
     glVertex2f (a.xpos-x + center.xpos , a.ypos-y+center.ypos);
   }
   glEnd();
   }
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}

