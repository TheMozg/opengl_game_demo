#include <GL/glut.h>

#define WINDOW_NAME "Lab"

int main( int argc, char **argv ) {

  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );

  glutInitWindowSize( 800, 600 );
  glutCreateWindow( WINDOW_NAME );

  glClearColor( 0, 0, 0, 0 );

  glutMainLoop( );
  return 0;
}
