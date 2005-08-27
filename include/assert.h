/* assert.h */



#ifndef ___ASSERT_H
# define ___ASSERT_H


# ifdef NDEBUG
#  define assert(ignore) ((void)0)
# else
#  include <stdio.h>
#  define assert(value) if(!(value)) { fprintf(stderr, "%s%s%s%d%s", \
			"assertion failed in \"", __FILE__, "\", line ", \
			__LINE__, "\n"); }
# endif

#endif
