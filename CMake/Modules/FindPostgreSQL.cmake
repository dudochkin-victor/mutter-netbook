# - Find PostgreSQL
# Find the PostgreSQL includes and client library
# This module defines
#  POSTGRESQL_INCLUDE_DIR, where to find POSTGRESQL.h
#  POSTGRESQL_LIBRARIES, the libraries needed to use POSTGRESQL.
#  POSTGRESQL_FOUND, If false, do not try to use PostgreSQL.

# Eventually add the postgresql include paths here

if(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
   set(POSTGRESQL_FOUND TRUE)

else(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)

# When using libpqfe, use this:
#  find_path(POSTGRESQL_INCLUDE_DIR libpq-fe.h

 FIND_PATH(POSTGRESQL_INCLUDE_DIR postgres.h
      /usr/include/server
      /usr/include/pgsql/server
      /usr/local/include/pgsql/server
      /usr/include/postgresql/server
      /usr/include/postgresql/*/server
      /usr/local/include/postgresql/server
      /usr/local/include/postgresql/*/server
      $ENV{ProgramFiles}/PostgreSQL/*/include/server
      $ENV{SystemDrive}/PostgreSQL/*/include/server
      )

  find_library(POSTGRESQL_LIBRARIES NAMES pq libpq
     PATHS
     /usr/lib
     /usr/local/lib
     /usr/lib/postgresql
     /usr/lib64
     /usr/local/lib64
     /usr/lib64/postgresql
     $ENV{ProgramFiles}/PostgreSQL/*/lib/ms
     $ENV{SystemDrive}/PostgreSQL/*/lib/ms
     )
      
  if(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
    set(POSTGRESQL_FOUND TRUE)
    message(STATUS "Found PostgreSQL: ${POSTGRESQL_INCLUDE_DIR}, ${POSTGRESQL_LIBRARIES}")
    INCLUDE_DIRECTORIES(${POSTGRESQL_INCLUDE_DIR})
  else(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
    set(POSTGRESQL_FOUND FALSE)
    message(STATUS "PostgreSQL not found.")
  endif(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)

  mark_as_advanced(POSTGRESQL_INCLUDE_DIR POSTGRESQL_LIBRARIES)

endif(POSTGRESQL_INCLUDE_DIR AND POSTGRESQL_LIBRARIES)
