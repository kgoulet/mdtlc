//
//
// 
//
// Kirby Goulet Copyright 2004 

#define MAXFILENAMELEN 1000

class Filename_work {

private:
  char directory[MAXFILENAMELEN];
  char base_name[MAXFILENAMELEN];
  char extension[MAXFILENAMELEN];
  char original[MAXFILENAMELEN];
  char current[MAXFILENAMELEN];


public:
  Filename_work();
  int set(const char *start);
  void clear(void);
  int add2base(const char *start);
  char* current_name();
  char* original_name();

};

Filename_work::Filename_work(){
*original=0;
*directory=0;
*base_name=0;
*current=0;
*extension=0;
}

int Filename_work::set(const char* start) {
  
  const char *q1 = 0;
  const char *q2 = 0;
  char *p1 = 0;
  char *p2 = 0;
  const char *end;
  const char *p = start;

  /* copy string to original and current */
  p=start;p1=current;p2=original;
  while (*p!=0) { *p1++=*p2++=*p++; }
  *p1=*p2=0;
  end=p; /* p points to last character */

  /* find first character after '/' or '\' from end and point with q2 */
  q2=end;
  while ( p!=start )
	{
	if ( *p=='/' || *p=='\\' ) { q2=p; q2++; break;  }
    else { p--;}
    }

  /* copy path to directory including training separator */;
  p=start;p2=directory;
  while ( p!=q2 ) {*p2++ = *p++; }
  p2=0; 

  /* extract extension */
  p=end;q1=end;
  while ( p!=q2 )
	{
	if (*p == '.' ) { q1=p; break;  }
      else { p--;}
      }
  p1=extension;
  while (q1!=end ) { *p1++=*q1++; }
  *p1=0;

  /* extract filename */

  p1=base_name;
  while (q2!=q1) { *p1++=*q2++; }
  *p1=0;

  return 0;

}

void Filename_work::clear(){
	*original=0;
	*directory=0;
	*base_name=0;
	*current=0;
	*extension=0;
	return; }


int Filename_work::add2base(const char* newpart) {
	char *q1 = 0;
  	const char *q2 = 0;
  	char *p1 = 0;
  	char *p2 = 0;
  	const char *end;
  	const char *p = newpart;

	/* add to basename */
      q1=base_name; q2=newpart;
      while (*q1!=0) { *q1++; }
      while (*q2!=0) { *q1++=*q2++; }
      *q1=0;

      /* build up new current */
      q1=current; p2=directory;
      while (*q2!=0) { *q1++=*p2++; }
	p2=base_name;
	while (*q2!=0) { *q1++=*p2++; }
	p2=extension;
	while (*q2!=0) { *q1++=*p2++; }
	*q1=0;

	return 0;
	}

char* Filename_work::current_name() {
	return(current);
	}

char* Filename_work::original_name() {
	return(original);
	}

