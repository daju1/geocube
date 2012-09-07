/* config.hin.  Generated automatically from configure.in by autoheader.  */
#ifndef CONFIG_H
# define CONFIG_H

/* Define to empty if the keyword does not work.  */
#undef const

/* Define if you don't have vprintf but do have _doprnt.  */
#undef HAVE_DOPRNT

/* Define if you have the vprintf function.  */
/* KDJ */
#define HAVE_VPRINTF 1

/* Define if ansi-c headers are present. */
/* KDJ */
#define STDC_HEADERS 1

/* Define if both time.h and sys/time.h can be included */
#undef TIME_WITH_SYS_TIME

/* Define if sys/time.h is present */
#undef HAVE_SYS_TIME

/* Define if you have the HAVE_<xxx> function.  */
/* KDJ */
#define HAVE_STRSTR 1
/* KDJ */
#define HAVE_STRTOD 1
/* KDJ */
#define HAVE_STRTOL 1
/* KDJ */
//#define HAVE_POPEN 1
#undef HAVE_GETTIMEOFDAY
#undef HAVE_DRAND48
/* KDJ */
#define HAVE_TEMPNAM 1
#undef HAVE_GETOPT
#undef HAVE_ASPRINTF
#undef HAVE_VASPRINTF

/* Define if you have the <unistd.h> header file.  */
#undef HAVE_UNISTD_H

/* Define if you have the <unistd.h> header file.  */
#undef HAVE_GETOPT_H

/* Define if you have the GNU scientific library (-lgsl).  */
#undef HAVE_LIBGSL

/* for the PCRASTER cross system format (csf) library (-lcsf).  */
/* KDJ */
#define HAVE_LIBCSF 1

/* Define if you have the ncurses library (-lncurses).  */
#undef HAVE_LIBNCURSES

/* Define if you have the curses library (-lcurses).  */
#undef HAVE_LIBCURSES

/* Define if you have the gnu readline library (-lreadline).  */
#undef HAVE_LIBREADLINE

/* Define if you have the gd library (-lgd); */
#undef HAVE_LIBGD

/* ... with PNG support...  */
#undef HAVE_GDIMAGEPNG

/* ...or with GIF support. */
#undef HAVE_GDIMAGEGIF

/* Define if you have the netcdf library (-lnetcdf) for GMT map support  */
#undef HAVE_LIBNETCDF

/* Define if words are big endian */
#undef WORDS_BIGENDIAN

/* include sparse matrix routines in meschach */
#undef HAVE_SPARSE

/* define if target is libgstat.a */
/* KDJ */
#define LIBGSTAT 1

#endif
