# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main ( int argc, char *argv[] );
void timestamp ( );

int main ( int argc, char *argv[] )
{
# define N 100

  double array[N];
  int i;
  int master = 0;
  int my_id;
  int numprocs;
  double PI = 3.141592653589793238462643;
  double seed;
  MPI_Status status;
  double sum;
  double sum_all;

  MPI_Init ( &argc, &argv );

  MPI_Comm_size ( MPI_COMM_WORLD, &numprocs );

  MPI_Comm_rank ( MPI_COMM_WORLD, &my_id );

  if ( my_id == master )
  {
    timestamp ( );
    printf ( "\n" );
    printf ( "SUM - Master process:\n" );
    printf ( "  C version\n" );
    printf ( "\n" );
    printf ( "  An MPI example program.\n" );
    printf ( "  The master process computes some coefficients,\n" );
    printf ( "  sends them to each worker process, which sums them.\n" );
    printf ( "\n" );
    printf ( "  Compiled on %s at %s.\n", __DATE__, __TIME__ );
    printf ( "\n" );
    printf ( "  The number of processes available is %d.\n", numprocs );
  }

  if ( my_id == master ) 
  {
    seed = 1.2345;

    for ( i = 0; i < N; i++ )
    {
      array[i] = ( double ) i * seed * PI;
    }
  }

  MPI_Bcast ( array, N, MPI_DOUBLE, master, MPI_COMM_WORLD );

  sum = 0.0;
  for ( i = 0; i < N; i++ )
  {
    sum = sum + array[i] * ( double ) my_id;
  }

  printf ( "\n" );
  printf ( "SUM - Process %d:\n", my_id );
  printf ( "  My contribution to the sum is %f\n", sum );

  if ( my_id != master ) 
  {
    MPI_Send ( &sum, 1, MPI_DOUBLE, master, 1, MPI_COMM_WORLD );
  }
  else 
  {
    sum_all = sum;
    for ( i = 1; i < numprocs; i++ ) 
    {
      MPI_Recv ( &sum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1, 
        MPI_COMM_WORLD, &status );

      sum_all = sum_all + sum;
    }
  }

  if ( my_id == master )
  {
    printf ( "\n");         
    printf ( "SUM - Master process:\n");         
    printf ( "  The total sum is %.16f\n", sum_all );
  }

  MPI_Finalize ( );

  if ( my_id == master )
  {
    printf ( "\n");         
    printf ( "SUM - Master process:\n");         
    printf ( "  Normal end of execution.\n"); 
    printf ( "\n" );
    timestamp ( ); 
  }
  return 0;

# undef N
}

void timestamp ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
